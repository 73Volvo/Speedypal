#include "speeduino_data.h"

static uint8_t buffer[SPEEDUINO_DATA_LEN];
bool requestData(uint16_t timeout = 20);

bool getBit(uint16_t address, uint8_t bit);
uint16_t getByte(uint16_t address);
uint16_t getWord(uint16_t address);

bool isDeviceConnected(int address) {
  Wire.beginTransmission(address);
  byte error = Wire.endTransmission();

  if (error == 0) {
    return true; // Device acknowledged the transmission
  } else {
    return false; // Device did not acknowledge the transmission
  }
}

bool requestData(uint16_t timeout) // Returns FALSE if timeout occurs or data is corrupted
{
  Serial1.setTimeout(timeout);
  if ( timeout < 5 ) {
    timeout = 5;
    ecuWait = 5;
  }

  // flush input buffer

  Serial1.write('n');

  // wait for data or timeout
  uint32_t start = millis();
  uint32_t end = start;
  while (Serial1.available() < 3 && (end - start) < timeout)
  {
    end = millis();
  }

  // if within timeout, read data
  if (end - start < timeout)
  {
    // Check first two bytes for validation
    uint8_t check1 = Serial1.read();
    uint8_t check2 = Serial1.read();
    if(check1 != 0x6E || check2 != 0x32) // 0x6E = n, 0x32 is a check value
    {
      while(Serial1.available())
        Serial1.read();  // Empty the incoming buffer

      return true; // We keep the last valid dataset
    }

    uint8_t dataLen = Serial1.read();
    Serial1.readBytes(buffer, dataLen);

    return true;
  }
  else
    return false;
}

bool getBit(uint16_t address, uint8_t bit)
{
  return bitRead(buffer[address], bit);
}

uint16_t getByte(uint16_t address)
{
  return buffer[address];
}

int8_t getSignedByte(uint16_t address)
{
  return buffer[address];
}

uint8_t getThreeBits(uint16_t address, uint8_t bit)
{
  uint8_t resultNum = 0;
  if ( bitRead(buffer[address], bit) == 1 ) resultNum = ( resultNum + 1 );
  if ( bitRead(buffer[address], bit+1) == 1 ) resultNum = ( resultNum + 2 );
  if ( bitRead(buffer[address], bit+2) == 1 ) resultNum = ( resultNum + 4 );
  return (resultNum+1);
  Serial.println("Three Bits");
}

int16_t getSignedWord(uint16_t address)
{
  int8_t resultNumA = buffer[address];
  uint8_t resultNumB = buffer[address + 1];
  return makeWord(resultNumB, resultNumA);
}

uint16_t getWord(uint16_t address)
{
  return makeWord(buffer[address + 1], buffer[address]);
}

// returns the printable string of a stat with proper decimals
String statString(int statNum)
{
  char valString[8];
  int number = speeduino[statNum].number;
  int subNumber = speeduino[statNum].subNumber;
  int type = speeduino[statNum].type; // 0=bit / 1=byte / 2=word / 3=two bits / 4 = signed word
  float multiplier = (speeduino[statNum].multiplier)/10.00;
  int decimal = speeduino[statNum].decimal;

  if (type != 0 && type != 3) {
        if (multiplier != 0) {
            if (type == 1) formatValue(valString, (getByte(number))*multiplier, decimal);
            if (type == 2) formatValue(valString, (getWord(number))*multiplier, decimal);
            if (type == 4) formatValue(valString, (getSignedWord(number))*multiplier, decimal);
            if (type == 5) formatValue(valString, (*(speeduino[statNum].calculated)) * multiplier, decimal);
            if (type == 6) formatValue(valString, (getSignedByte(number))*multiplier, decimal);
        }
        if (multiplier == 0) {
            if (type == 1) formatValue(valString, ( (getByte(number) + SPEEDUINO_TEMPERATURE_OFFSET ) * SPEEDUINO_TEMPERATURE_MULTIPLIER ) + C_TO_F, decimal);
            if (type == 2) formatValue(valString, ( (getWord(number) + SPEEDUINO_TEMPERATURE_OFFSET ) * SPEEDUINO_TEMPERATURE_MULTIPLIER ) + C_TO_F, decimal);
            if (type == 4) formatValue(valString, ( (getSignedWord(number) + SPEEDUINO_TEMPERATURE_OFFSET ) * SPEEDUINO_TEMPERATURE_MULTIPLIER ) + C_TO_F, decimal);
        }
      }
    if (type == 0) {
      // bit
      formatValue(valString, getBit(number, subNumber), 0 );
      }
    if (type == 3) {
      // two bits
      formatValue(valString, getThreeBits(number, subNumber), 0 );
      }
    return valString;
}

//returns the float of a stat
float statGrab(int statNum)
{
  int number = speeduino[statNum].number;
  int subNumber = speeduino[statNum].subNumber;
  int type = speeduino[statNum].type; // 0=bit / 1=byte / 2=word / 3=two bits / 4 = signed word
  float multiplier = (speeduino[statNum].multiplier) / 10.00;
  int decimal = speeduino[statNum].decimal; // 0 for no decimal, 1 for a single decimal, 2 for two decimals
  int divider;

  if (decimal == 0) divider = 1;
  else if (decimal == 1) divider = 10;
  else if (decimal == 2) divider = 100;

  if (type != 0 && type != 3)
  {
    if (multiplier != 0)
    {
      if (type == 1)
        return getByte(number) * multiplier / divider;
      if (type == 2)
        return getWord(number) * multiplier / divider;
      if (type == 4)
        return getSignedWord(number) * multiplier / divider;
      if (type == 5) 
        return (*(speeduino[statNum].calculated)) * multiplier / divider;
      if (type == 6) 
        return getSignedByte(number) * multiplier / divider;
    }
    if (multiplier == 0)
    {
      if (type == 1)
        return ((getByte(number) + SPEEDUINO_TEMPERATURE_OFFSET) * SPEEDUINO_TEMPERATURE_MULTIPLIER) + C_TO_F;
      if (type == 2)
        return ((getWord(number) + SPEEDUINO_TEMPERATURE_OFFSET) * SPEEDUINO_TEMPERATURE_MULTIPLIER) + C_TO_F;
      if (type == 4)
        return ((getSignedWord(number) + SPEEDUINO_TEMPERATURE_OFFSET) * SPEEDUINO_TEMPERATURE_MULTIPLIER) + C_TO_F;
    }
  }
  if (type == 0)
  {
    // bit
    return getBit(number, subNumber);
  }
  if (type == 3)
  {
    // two bits
    return getThreeBits(number, subNumber);
  }

  // Return a default value if none of the conditions are met
  return 0.0;
}