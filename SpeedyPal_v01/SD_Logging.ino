#include <SdFat.h>
#include "sdios.h"

// The Speeduino stats to be saved to the log
// "logStatsCount" is the number of stats to be saved.
int logStatsCount = 56;
// de-comment the stats in "logStats" that you want to be saved to the log
int logStats[] = {
    0,   // SPEEDUINO_BYTE_SECL               Simple counter, incremented each second
            // Status bitfield
//  1,   // SPEEDUINO_STATUS_INJ1_BIT
//  2,   // SPEEDUINO_STATUS_INJ2_BIT
//  3,   // SPEEDUINO_STATUS_INJ3_BIT
//  4,   // SPEEDUINO_STATUS_INJ4_BIT
    5,   // SPEEDUINO_STATUS_DFCO_BIT         Deceleration Fuel Cut Off
//  6,   // SPEEDUINO_STATUS_BOOSTCUT_BIT
//  7,   // SPEEDUINO_STATUS_TOOTH1_BIT       Tooth Log 1 Ready
//  8,   // SPEEDUINO_STATUS_TOOTH2_BIT       Tooth Log 2 Ready
            // Engine bitfield
//  9,   // SPEEDUINO_ENGINE_RUNNING_BIT
//  10,  // SPEEDUINO_ENGINE_CRANKING_BIT
    11,  // SPEEDUINO_ENGINE_ASE_BIT          Afterstart Enrichment
    12,  // SPEEDUINO_ENGINE_WARMUP_BIT       Warmup Enrichment
//  13,  // SPEEDUINO_ENGINE_TPSAE_BIT        TPS-based Acceleration Enrichment
//  14,  // SPEEDUINO_ENGINE_TPSDE_BIT        TPS-based Deceleration Enleanment
//  15,  // SPEEDUINO_ENGINE_MAPAE_BIT        MAP-based Acceleration Enrichment
//  16,  // SPEEDUINO_ENGINE_MAPDE_BIT        MAP-based Deceleration Enleanment
    17,  // SPEEDUINO_DWELL_BYTE              Dwell (ms, divide by 10)
    18,  // SPEEDUINO_MAP_WORD                MAP (kPa, 2 bytes)
    19,  // SPEEDUINO_IAT_BYTE                Intake Air Temperature (Degrees, subtract 40)
    20,  // SPEEDUINO_CLT_BYTE                Coolant Temperature (Degrees, subtract 40)
    21,  // SPEEDUINO_VOLTAGE_BYTE            Battery Voltage (Volts, divide by 10)
    22,  // SPEEDUINO_AFR_BYTE                Air-Fuel Ratio (divide by 10)
    23,  // SPEEDUINO_EGOCORR_BYTE            EGO Correction (%)
    24,  // SPEEDUINO_IATCORR_BYTE            Air Temperature Correction (%)
    25,  // SPEEDUINO_WUECORR_BYTE            Warmup Enrichment Correction (%)
    26,  // SPEEDUINO_RPM_WORD                RPM (2 bytes)
    27,  // SPEEDUINO_AECORR_BYTE             Acceleration Enrichment Correction (%)
    28,  // SPEEDUINO_GAMMAE_BYTE             Gamma Correction (%)
    29,  // SPEEDUINO_CURRENTVE_BYTE          Current VE
    30,  // SPEEDUINO_AFRTARGET_BYTE          AFR Target (divide by 10)
    31,  // SPEEDUINO_PW1_WORD                PulseWidth 1 (ms, divide by 10)
    32,  // SPEEDUINO_TPSDOT_BYTE             TPSdot (%/s, multiply by 10)
    33,  // SPEEDUINO_ADVANCE                 (Degrees BTDC)
    34,  // SPEEDUINO_TPS_BYTE                Throttle Position (%, divide by 2, 0.5% resolution)
    35,  // SPEEDUINO_LOOPSPERSEC_WORD        (Loops/s, 2 bytes)
//  36,  // SPEEDUINO_FREERAM_WORD            (Bytes, 2 bytes)
//  37,  // SPEEDUINO_BOOSTTARGET             (kPa, multiply by 2)
//  38,  // SPEEDUINO_BOOSTDUTY               Boost PWM duty (%)
            // Spark bitfield register, see single bits below
//  39,  // SPEEDUINO_SPARK_HARDLAUNCH_BIT    Launch Control limiter, hard
//  40,  // SPEEDUINO_SPARK_SOFTLAUNCH_BIT    Launch Control limiter, soft
//  41,  // SPEEDUINO_SPARK_HARDLIMIT_BIT     Rev limiter, hard
//  42,  // SPEEDUINO_SPARK_SOFTLIMIT_BIT     Rev limiter, soft
//  43,  // SPEEDUINO_SPARK_BOOSTCUT_BIT
//  44,  // SPEEDUINO_SPARK_ERROR_BIT
    45,  // SPEEDUINO_SPARK_IDLECTRL_BIT
//  46,  // SPEEDUINO_SPARK_SYNC_BIT
    47,  // SPEEDUINO_RPMDOT_WORD             RPMdot (rpm/s, 2 bytes)
    48,  // SPEEDUINO_ETHANOLPCT_BYTE         Ethanol content (%, 0 if not used)
    49,  // SPEEDUINO_FLEXCORR_BYTE           Flex fuel Correction (%)
    50,  // SPEEDUINO_FLEXIGNCORR_BYTE        Flex fuel advance correction (Degrees)
    51,  // SPEEDUINO_IDLELOAD_BYTE           Idle valve load (PWM duty or Steps)
            // Test Outputs Bitfield Register, see single bits below
//  52,  // SPEEDUINO_TESTOUTPUTS_ENABLED_BIT
//  53,  // SPEEDUINO_TESTOUTPUTS_ACTIVE_BIT
//  54,  // SPEEDUINO_02_2_BYTE               Secondary AFR Sensor (divide by 10)
    55,  // SPEEDUINO_BARO_BYTE               Berometric pressure (kPa)
//  56,  // SPEEDUINO_CANIN0_WORD             CAN Input 0 (2 bytes)
//  57,  // SPEEDUINO_CANIN1_WORD             CAN Input 1 (2 bytes)
//  58,  // SPEEDUINO_CANIN2_WORD             CAN Input 2 (2 bytes)
//  59,  // SPEEDUINO_CANIN3_WORD             CAN Input 3 (2 bytes)
//  60,  // SPEEDUINO_CANIN4_WORD             CAN Input 4 (2 bytes)
//  61,  // SPEEDUINO_CANIN5_WORD             CAN Input 5 (2 bytes)
//  62,  // SPEEDUINO_CANIN6_WORD             CAN Input 6 (2 bytes)
//  63,  // SPEEDUINO_CANIN7_WORD             CAN Input 7 (2 bytes)
//  64,  // SPEEDUINO_CANIN8_WORD             CAN Input 8 (2 bytes)
//  65,  // SPEEDUINO_CANIN9_WORD             CAN Input 9 (2 bytes)
//  66,  // SPEEDUINO_CANIN10_WORD            CAN Input 10 (2 bytes)
//  67,  // SPEEDUINO_CANIN11_WORD            CAN Input 11 (2 bytes)
//  68,  // SPEEDUINO_CANIN12_WORD            CAN Input 12 (2 bytes)
//  69,  // SPEEDUINO_CANIN13_WORD            CAN Input 13 (2 bytes)
//  70,  // SPEEDUINO_CANIN14_WORD            CAN Input 14 (2 bytes)
//  71,  // SPEEDUINO_CANIN15_WORD            CAN Input 15 (2 bytes)
//  72,  // SPEEDUINO_TPSADC_BYTE             TPS ADC Value (0...255)
    73,  // SPEEDUINO_ERROR_BYTE              Error code (Error Number 0:1, Current Error 2:7)
//  74,  // SPEEDUINO_LAUNCHCORR_BYTE         Launch Correction (%)
    75,  // SPEEDUINO_PW2_WORD                PulseWidth 2 (ms, divide by 10)
//  76,  // SPEEDUINO_PW3_WORD                PulseWidth 3 (ms, divide by 10)
//  77,  // SPEEDUINO_PW4_WORD                PulseWidth 4 (ms, divide by 10)
            // Status 3 bitfield register, see single bits below
//  78,  // SPEEDUINO_STATUS3_RESETLOCKON_BIT
//  79,  // SPEEDUINO_STATUS3_NITROUSON_BIT
//  80,  // SPEEDUINO_STATUS3_FUEL2ACTIVE_BIT Secondary VE Table
    81,  // SPEEDUINO_STATUS3_VSSREFRESH_BIT
//  82,  // SPEEDUINO_STATUS3_HALFSYNC_BIT
//  83,  // SPEEDUINO_STATUS3_NSQUIRTS_BITS   Bits 5:7
            // Engine protect bitfield register, see single bits below
//  84,  // SPEEDUINO_ENGINEPROTECT_RPM_BIT
    85,  // SPEEDUINO_ENGINEPROTECT_MAP_BIT
//  86,  // SPEEDUINO_ENGINEPROTECT_OIL_BIT
//  87,  // SPEEDUINO_ENGINEPROTECT_AFR_BIT
    88,  // SPEEDUINO_ENGINEPROTECT_CLT_BIT
    89,  // SPEEDUINO_FUELLOAD_WORD           Fuel Table load (kPa or TPS%, 2 bytes)
    90,  // SPEEDUINO_IGNLOAD_WORD            Spark Table load (kPa or TPS%, 2 bytes)
//  91,  // SPEEDUINO_INJANGLE_WORD           Injection angle (2 bytes)
//  92,  // SPEEDUINO_IDLELOAD_BYTE2          DUPLICATE OF ADDRESS 37 - HOPEFULLY WILL BE FIXED IN THE SPEEDUINO FIRMWARE
    93,  // SPEEDUINO_CLIDLETARGET_BYTE       Closed-Loop Idle Target RPM (multiply by 10)
//  94,  // SPEEDUINO_MAPDOT_BYTE             MAPdot (kPa/s, multiply by 10)
//  95,  // SPEEDUINO_VVT1ANGLE_BYTE          VVT1 Angle (Degrees, SIGNED)
//  96,  // SPEEDUINO_VVT1TARGET_BYTE         VVT1 Target Angle (Degrees)
//  97,  // SPEEDUINO_VVT1DUTY_BYTE           VVT1 PWM Duty (%)
//  98,  // SPEEDUINO_FLEXBOOSTCORR_WORD      Flex fuel Boost Correction, 2 bytes)
    99,  // SPEEDUINO_BAROCORR_BYTE           Barometric Correction (%)
//  100, // SPEEDUINO_ASECORR_BYTE            After Start Enrichment Correction (%)
    101, // SPEEDUINO_VSS_WORD                Speed reading via VSS (2 bytes)
    102, // SPEEDUINO_GEAR_BYTE               Current gear
//  103, // SPEEDUINO_FUELPRESSURE_BYTE       (PSI or Bar)
//  104, // SPEEDUINO_OILPRESSURE_BYTE        (PSI or Bar)
//  105, // SPEEDUINO_WMIPW_BYTE              Water-Meth Injection Pulsewidth
            // Status 4 bitfield register, see single bits below
//  106, // SPEEDUINO_STATUS4_WMIEMPTY_BIT    Water-Meth Tank empty
//  107, // SPEEDUINO_STATUS4_VVT1ERROR_BIT
//  108, // SPEEDUINO_STATUS4_VVT2ERROR_BIT
    109, // SPEEDUINO_STATUS4_FAN_BIT         Cooling fan
//  110, // SPEEDUINO_VVT2ANGLE_BYTE          VVT2 Angle (Degree, SIGNED)
//  111, // SPEEDUINO_VVT2TARGET_BYTE         VVT2 Target Angle (Degrees)
//  112, // SPEEDUINO_VVT2DUTY_BYTE           VVT2 PWM Duty (%)
//  113, // SPEEDUINO_OUTPUTSSTATUS_BYTE      Programmable Outputs
//  114, // SPEEDUINO_FUELTEMP_BYTE           Fuel Temperature from Flex Sensor (Degrees, subtract 40)
//  115, // SPEEDUINO_FUELTEMPCORR_BYTE       Fuel Temperature Correction (%)
    116, // SPEEDUINO_VE1_BYTE                VE from Primary Fuel Table
    117, // SPEEDUINO_VE2_BYTE                VE from Secondary Fuel Table
    118, // SPEEDUINO_ADVANCE1_BYTE           Advance from Primary Spark Table (Degrees BTDC)
    119, // SPEEDUINO_ADVANCE2_BYTE           Advance from Secondary Spark Table (Degrees BTDC)
            // Nitrous status bitfield - N2O status, see values below
//  120, // SPEEDUINO_NITROUSSTATUS_OFF
//  121, // SPEEDUINO_NITROUSSTATUS_STAGE1
//  122, // SPEEDUINO_NITROUSSTATUS_STAGE2
//  123, // SPEEDUINO_NITROUSSTATUS_BOTH
            // SD Card bitfield register, see single bits below
//  124, // SPEEDUINO_SDCARD_PRESENT_BIT      SD Card is inserted
//  125, // SPEEDUINO_SDCARD_TYPE_BIT         SD Card type (0=SD, 1=SDHC)
//  126, // SPEEDUINO_SDCARD_READY_BIT
//  127, // SPEEDUINO_SDCARD_LOGGING_BIT
//  128, // SPEEDUINO_SDCARD_ERROR
//  129, // SPEEDUINO_SDCARD_VERSION_BIT      SD Card version (0=1.x, 1=2.x)
//  130, // SPEEDUINO_SDCARD_FS_BIT           SD Card filesystem (0=no FAT16, 1=FAT32)
//  131, // SPEEDUINO_SDCARD_UNUSED
//  132, // SPEEDUINO_EMAP_WORD               EMAP (kPa, 2 bytes)
//  133, // SPEEDUINO_FANDUTY_BYTE            Cooling Fan PWM duty (%)
            // Air conditioning bitfield register, see single bits below
//  134, // SPEEDUINO_AIRCON_REQUEST_BIT
//  135, // SPEEDUINO_AIRCON_COMPRESSOR_BIT
//  136, // SPEEDUINO_AIRCON_RPMLOCKOUT_BIT
//  137, // SPEEDUINO_AIRCON_TPSLOCKOUT_BIT
    138, // SPEEDUINO_AIRCON_TURNINGON_BIT
//  139, // SPEEDUINO_AIRCON_CLTLOCKOUT_BIT
//  140, // SPEEDUINO_AIRCON_FAN_BIT
            // Calculated stats
    141, // CALCULATED_FRAME_RATE
    142, // CALCULATED_MPG
    143, // CALCULATED_MPH
    144, // CALCULATED_ODOMETER
    145, // CALCULATED_ACCELERATION
    146, // CALCULATED_HORSEPOWER
    147, // CALCULATED_TORQUE
    148, // CALCULATED_TIME_TO_30
    149};// CALCULATED_TIME_TO_60



// SD_FAT_TYPE = 0 for SdFat/File as defined in SdFatConfig.h,
// 1 for FAT16/FAT32, 2 for exFAT, 3 for FAT16/FAT32 and exFAT.
#define SD_FAT_TYPE 3
// Set DISABLE_CHIP_SELECT to disable a second SPI device.
// For example, with the Ethernet shield, set DISABLE_CHIP_SELECT
// to 10 to disable the Ethernet controller.
const int8_t DISABLE_CHIP_SELECT = -1;
// Test with reduced SPI speed for breadboards.  SD_SCK_MHZ(4) will select
// the highest speed supported by the board that is not over 4 MHz.
// Change SPI_SPEED to SD_SCK_MHZ(50) for best performance.
#define SPI_SPEED SD_SCK_MHZ(25)
//------------------------------------------------------------------------------
#if SD_FAT_TYPE == 0
SdFat sd;
File file;
#elif SD_FAT_TYPE == 1
SdFat32 sd;
File32 file;
#elif SD_FAT_TYPE == 2
SdExFat sd;
ExFile file;
#elif SD_FAT_TYPE == 3
SdFs sd;
FsFile file;
#else  // SD_FAT_TYPE
#error Invalid SD_FAT_TYPE
#endif  // SD_FAT_TYPE

FsFile dataFile; // file handle
char filename[25]; // file name

// Define constants for file extensions
#define FILENAME_PREFIX "Speedy0000"
#define BINARY_LOG_EXTENSION ".mlg"
#define ASCII_LOG_EXTENSION ".msl"

void SDsetup() {

  if ( RTCconnected() ) {
    DateTime now = rtc.now();
    if (now.year() < 2000) {
      Serial.println("Year is set before 2000");
    }
    // Set callback
    FsDateTime::setCallback(dateTime);
  }

  // Initialize the SD card
  if (!sd.begin(chipSelect, SPI_SPEED)) {
    if (sd.card()->errorCode()) {
      Serial.println(F(
          "\nSD initialization failed.\n"
          "Do not reformat the card!\n"
          "Is the card correctly inserted?\n"
          "Is chipSelect set to the correct value?\n"
          "Does another SPI device need to be disabled?\n"
          "Is there a wiring/soldering problem?\n"));
      Serial.print(F("\nerrorCode: "));
      Serial.print(int(sd.card()->errorCode()), HEX);
      Serial.print(F(", errorData: "));
      Serial.print(int(sd.card()->errorData()));
      Serial.println();
      SD_PRESENT = false;
      return;
    }
    Serial.println(F("\nCard successfully initialized.\n"));
    if (sd.vol()->fatType() == 0) {
      Serial.println(F("Can't find a valid FAT16/FAT32 partition."));
      Serial.println(F("Try reformatting the card.  For best results use\n"
                   "the SdFormatter program in SdFat/examples or download\n"
                   "and use SDFormatter from www.sdcard.org/downloads.\n"));
      SD_PRESENT = false;
      return;
    }
    Serial.println(F("Can't determine error type"));
    SD_PRESENT = false;
    return;
  }
  Serial.println(F("\nCard successfully initialized.\n"));
  Serial.println();

  uint32_t size = sd.card()->sectorCount();
  if (size == 0) {
    Serial.println(F("Can't determine the card size."));
    Serial.println(F("Try another SD card or reduce the SPI bus speed.\n"
                   "Edit SPI_SPEED in this program to change it.\n"));
    SD_PRESENT = false;
    return;
  }
  uint32_t sizeMB = 0.000512 * size + 0.5;
  Serial.print(F("Card size: "));
  Serial.print(sizeMB);
  Serial.println(F(" MB (MB = 1,000,000 bytes)"));
  Serial.println();

  Serial.print(F("Volume is FAT"));
  Serial.print(int(sd.vol()->fatType()));
  Serial.print(F(", Cluster size (bytes): "));
  Serial.println(sd.vol()->bytesPerCluster());
  Serial.println();

  Serial.println(F("Files found (date time size name):"));
  sd.ls(LS_R | LS_DATE | LS_SIZE);

  if ((sizeMB > 1100 && sd.vol()->sectorsPerCluster() < 64) ||
      (sizeMB < 2200 && sd.vol()->fatType() == 32)) {
    Serial.println(F("\nThis card should be reformatted for best performance.\n"
                     "Use a cluster size of 32 KB for cards larger than 1 GB.\n"
                     "Only cards larger than 2 GB should be formatted FAT32.\n"));
    Serial.println(F("Try reformatting the card.  For best results use\n"
                   "the SdFormatter program in SdFat/examples or download\n"
                   "and use SDFormatter from www.sdcard.org/downloads.\n"));
    SD_PRESENT = false;
    return;
  }
  // Read any extra Serial data.
  clearSerialInput();
}

void SDstartLogBIN() {

  strcpy(filename, FILENAME_PREFIX);
  if (binaryLog) {
    strcat(filename, BINARY_LOG_EXTENSION);
  } else {
    strcat(filename, ASCII_LOG_EXTENSION);
  }

  if (RTCconnected()) {
    sprintf(filename, "/%04d-%02d-%02d_%02d.%02d.%02d%s", year, month, day, hour, minute, second, binaryLog ? BINARY_LOG_EXTENSION : ASCII_LOG_EXTENSION);
  } else {
      while (sd.exists(filename)) {
        char* p = strchr(filename, '.');
        if (!p) {
          Serial.println("no dot in filename");
        }
        while (true) {
          p--;
          if (p < filename || *p < '0' || *p > '9') {
            Serial.println("Can't create file name");
          }
          if (p[0] != '9') {
            p[0]++;
            break;
          }
          p[0] = '0';
      }
    }
  }

  // Open the file with the filename in write mode
  dataFile = sd.open(filename, O_WRITE | O_CREAT);

  if (dataFile) {
    Serial.println("Log file created.");
    Serial.print("Filename: ");
    Serial.println(filename);
    SD_PRESENT = true;
  } else {
    Serial.println("Error creating log file.");
    SD_PRESENT = false;
  }

  // add header for log file
  if (dataFile) {

    uint8_t fourBytes[4]; // four byte array for storage
    uint8_t twoBytes[2]; // two byte array for storage

    // FIle Format, Format Version
    uint8_t binaryData[] = {0x4D, 0x4C, 0x56, 0x4C, 0x47, 0x00, 0x00, 0x01}; // Header MLVLG version 01
    dataFile.write(binaryData, sizeof(binaryData));

    // Time Stamp
    uint32_t timeStamp = createUnixTimestamp(year, month, day, hour, minute, second); // Write 32-bit Unix timestamp
    // Convert the 32-bit timestamp into a byte array
    fourBytes[0] = timeStamp & 0xFF;
    fourBytes[1] = (timeStamp >> 8) & 0xFF;
    fourBytes[2] = (timeStamp >> 16) & 0xFF;
    fourBytes[3] = (timeStamp >> 24) & 0xFF;
    // Write the byte array to the file
    dataFile.write(fourBytes, sizeof(fourBytes));

    // This start offset must be after the LoggerField[] definitions and before Data Begin Index Set to 0 if no Log info Data
    uint8_t startOffset[] = {0x00, 0x00};
    dataFile.write(startOffset, sizeof(startOffset));

    // 4 bytes, address of start of log data
    uint32_t startAddress = 22 + (55 * (logStatsCount + 1));
    // Split the value into four bytes
    fourBytes[3] = startAddress & 0xFF;
    fourBytes[2] = (startAddress >> 8) & 0xFF;
    fourBytes[1] = (startAddress >> 16) & 0xFF;
    fourBytes[0] = (startAddress >> 24) & 0xFF;
    // Write the byte array to the file
    dataFile.write(fourBytes, sizeof(fourBytes));

    Serial.print("start of logs: ");
    Serial.println(startAddress);

    // 2 bytes, log data length (just data)
    uint16_t recordLength = 4; // starts with 4 bytes for time counter
    for ( int i = 0 ; i < logStatsCount ; i++ ) {
      // 0=bit / 1=byte / 2=word / 3=three bits / 4 = signed word / 5 = calculated variable (float) / 6 = signed byte
      if ( speeduino[logStats[i]].type == 0 ) {recordLength=recordLength+1;} // bit
      if ( speeduino[logStats[i]].type == 1 ) {recordLength=recordLength+1;} // byte
      if ( speeduino[logStats[i]].type == 2 ) {recordLength=recordLength+2;} // word
      if ( speeduino[logStats[i]].type == 3 ) {recordLength=recordLength+1;} // three bits
      if ( speeduino[logStats[i]].type == 4 ) {recordLength=recordLength+2;} // signed word
      if ( speeduino[logStats[i]].type == 5 ) {recordLength=recordLength+4;} // float
      if ( speeduino[logStats[i]].type == 6 ) {recordLength=recordLength+1;} // signed byte
    }
    // Split the value into two bytes
    twoBytes[1] = recordLength & 0xFF;         // Low byte (LSB)
    twoBytes[0] = (recordLength >> 8) & 0xFF;  // High byte (MSB)
    // Write the byte array to the file
    dataFile.write(twoBytes, sizeof(twoBytes));

    Serial.print("data length: ");
    Serial.println(recordLength);

    // 2 bytes, number of log fields
    uint16_t logNum = logStatsCount + 1; // count of stats to be logged plus one for time counter
    // Split the value into two bytes
    twoBytes[1] = logNum & 0xFF;         // Low byte (LSB)
    twoBytes[0] = (logNum >> 8) & 0xFF;  // High byte (MSB)
    // Write the byte array to the file
    dataFile.write(twoBytes, sizeof(twoBytes));

    // "Time" Logger Field info, 55 bytes per field
    uint8_t timeDefinition[] = {0x07, 0x54, 0x69, 0x6D, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03};
    dataFile.write(timeDefinition, sizeof(timeDefinition));

    // write other Logger Field definitions here
    for ( int i = 0 ; i < logStatsCount ; i++ ) {
      // Type 0=U08, 1=S08, 2=U16, 3=S16, 4=U32, 5=S32, 6=S64, 7=F32
        uint8_t logType;
        if ( speeduino[logStats[i]].type == 0 ) {logType = 0;} // bit
        else if ( speeduino[logStats[i]].type == 1 ) {logType = 0;} // byte
        else if ( speeduino[logStats[i]].type == 2 ) {logType = 2;} // word
        else if ( speeduino[logStats[i]].type == 3 ) {logType = 0;} // two bits
        else if ( speeduino[logStats[i]].type == 4 ) {logType = 3;} // signed word
        else if ( speeduino[logStats[i]].type == 5 ) {logType = 7;} // float
        else if ( speeduino[logStats[i]].type == 6 ) {logType = 1;} // signed byte
        dataFile.write(&logType, 1);
      // Name - 34 bytes null terminated
          writeStringToFile(speeduino[logStats[i]].fullName, 34); // Writing as 34-byte
      // Units - 10 bytes null terminated
          writeStringToFile(speeduino[logStats[i]].unit, 10); // Writing as 10-byte
      // Display Style - 0=Float, 1=Hex, 2=bits, 3=Date, 4=On/Off, 5=Yes/No, 6=High/Low, 7=Active/Inactive
          uint8_t displayType;
          if ( speeduino[logStats[i]].type == 0 ) {displayType = 0;} // bit
          else if ( speeduino[logStats[i]].type == 1 ) {displayType = 0;} // byte
          else if ( speeduino[logStats[i]].type == 2 ) {displayType = 0;} // word
          else if ( speeduino[logStats[i]].type == 3 ) {displayType = 0;} // three bits
          else if ( speeduino[logStats[i]].type == 4 ) {displayType = 0;} // signed word
          else if ( speeduino[logStats[i]].type == 5 ) {displayType = 0;} // float
          else if ( speeduino[logStats[i]].type == 6 ) {displayType = 0;} // signed byte
          dataFile.write(&displayType, 1);
      // Scale - A IEEE 754 float representing the scale applied to (raw+transform)
          // multiplier - divide by 10 then multiply stat with resulting number. If the multiplier is "0" the stat goes through temp conversion
          // decimal - 0 for no decimal, 1 for a single decimal, 2 for two decimal places.
          float scaleValue = 1;
          if (speeduino[logStats[i]].multiplier == 0) { scaleValue *= 1; } // multiplier 1
          else if (speeduino[logStats[i]].multiplier == 1) { scaleValue *= 0.1; } // multiplier 0.1
          else if (speeduino[logStats[i]].multiplier == 10) { scaleValue *= 1; } // multiplier 1
          else if (speeduino[logStats[i]].multiplier == 50) { scaleValue *= 5; } // multiplier 5
          else if (speeduino[logStats[i]].multiplier == 100) { scaleValue *= 10; } // multiplier 10
          if (speeduino[logStats[i]].decimal == 0) { scaleValue *= 1; } // divider /1
          else if (speeduino[logStats[i]].decimal == 1) { scaleValue *= 0.1; } // divider /10
          else if (speeduino[logStats[i]].decimal == 2) { scaleValue *= 0.01; } // divider /100
          // Write the scale value as IEEE 754 float to 4 bytes of the dataFile
          uint32_t scaleValueIEEE754 = floatToIEEE754(scaleValue);
          dataFile.write(reinterpret_cast<uint8_t*>(&scaleValueIEEE754), sizeof(scaleValueIEEE754));
      // Transform - A IEEE 754 float representing any shift of raw value before scaling
          // 0 = temp, divide by 10 then multiply stat with resulting number. If the multiplier is "0" the stat goes through temp conversion
          if ( speeduino[logStats[i]].multiplier == 0 ) {
              // Write the IEEE 754 representation of -40 as a float to the dataFile
              float transformValue = -40.0;
              uint32_t transformValueIEEE754 = floatToIEEE754(transformValue);
              dataFile.write(reinterpret_cast<uint8_t*>(&transformValueIEEE754), sizeof(transformValueIEEE754));
          }
          else {
              float transformValue = 0.0;
              uint32_t transformValueIEEE754 = floatToIEEE754(transformValue);
              dataFile.write(reinterpret_cast<uint8_t*>(&transformValueIEEE754), sizeof(transformValueIEEE754));
          }
      // Digits - S08 representing the number of decimal places to display to the right
          int8_t displayDigits;
          if ( speeduino[logStats[i]].decimal == 0 ) {displayDigits = 0;} // 1
          if ( speeduino[logStats[i]].decimal == 1 ) {displayDigits = 0;} // 0.1
          if ( speeduino[logStats[i]].decimal == 2 ) {displayDigits = 0;} // 0.01
          dataFile.write(&displayDigits, 1);
    }

    Serial.println("Log file header appended.");
    SD_PRESENT = true;
  } else {
    Serial.println("Error opening the log file. Did not add header.");
    SD_PRESENT = false;
  }
  dataFile.seek(dataFile.size());
}

void SDlogBIN() {
  if (!dataFile) {
    Serial.println("File not open. Unable to append.");
    // SD Card not inserted or not initialized
    SD_PRESENT = false;
    SDsetup();
    SDstartLogBIN();
    return;
  }
  
  // Initialize CRC overflow byte
  uint8_t crcOverflow = 0;

  // Write null terminator
  uint8_t nullTerminator[] = {0x00};
  dataFile.write(nullTerminator, 1);

  // Increment counter
  static uint8_t counter = 0;
  counter++;
  counter %= 255;
  dataFile.write(&counter, 1);

  // Write timestamp
  uint16_t timestamp_us = 1234; // Replace with actual timestamp
  uint8_t timestamp_bytes[2];
  timestamp_bytes[1] = timestamp_us & 0xFF;
  timestamp_bytes[0] = (timestamp_us >> 8) & 0xFF;
  dataFile.write(timestamp_bytes, 2);

  // Get the current millis time and convert to seconds
  unsigned long millisTime = millis();
  float seconds = millisTime / 1000.0;

  // Convert seconds to a 32-bit IEEE 754 float representation
  uint32_t floatBits = *((uint32_t*)&seconds);

  // Extract individual bytes of the float representation
  uint8_t floatBytes[4];
  floatBytes[0] = (floatBits >> 24) & 0xFF;
  floatBytes[1] = (floatBits >> 16) & 0xFF;
  floatBytes[2] = (floatBits >> 8) & 0xFF;
  floatBytes[3] = floatBits & 0xFF;
  
  // Write the float bytes to the file
  dataFile.write(floatBytes, 4);
  crcOverflow += floatBytes[0];
  crcOverflow += floatBytes[1];
  crcOverflow += floatBytes[2];
  crcOverflow += floatBytes[3];

  // Iterate through logStats[] array
  for (int i = 0; i < logStatsCount; i++) {
    // Determine type of variable
    switch (speeduino[logStats[i]].type) { // int type; // 0=bit / 1=byte / 2=word / 3=three bits / 4 = signed word / 5 = calculated variable (float) / 6 = signed byte
      case 0: // bit
        {
          uint8_t value = getBit(speeduino[logStats[i]].number, speeduino[logStats[i]].subNumber); // Get value from statGrab function
          dataFile.write(&value, sizeof(value));
          crcOverflow += value;
          break;
        }
      case 1: // byte
        {
          uint8_t value = getByte(speeduino[logStats[i]].number); // Get value from statGrab function
          dataFile.write(&value, sizeof(value));
          crcOverflow += value;
          break;
        }
      case 6: // signed byte
        {
          int8_t value = getSignedByte(speeduino[logStats[i]].number); // Get value from statGrab function
          dataFile.write(&value, sizeof(value));
          crcOverflow += value;
          break;
        }
      case 3: // three bits
        {
          uint8_t value = getThreeBits(speeduino[logStats[i]].number, speeduino[logStats[i]].subNumber); // Get value from statGrab function
          dataFile.write(&value, sizeof(value));
          crcOverflow += value;
          break;
        }
      case 4: // signed word
        {
          int16_t value = getSignedWord(speeduino[logStats[i]].number); // Get value from statGrab function
          uint8_t value_bytes[2];
          value_bytes[1] = value & 0xFF;
          value_bytes[0] = (value >> 8) & 0xFF;
          dataFile.write(value_bytes, sizeof(value_bytes));
          crcOverflow += value_bytes[0];
          crcOverflow += value_bytes[1];
          break;
        }
      case 2: // word
        {
          uint16_t value = getWord(speeduino[logStats[i]].number); // Get value from statGrab function
          uint8_t value_bytes[2];
          value_bytes[1] = value & 0xFF;
          value_bytes[0] = (value >> 8) & 0xFF;
          dataFile.write(value_bytes, sizeof(value_bytes));
          crcOverflow += value_bytes[0];
          crcOverflow += value_bytes[1];
          break;
        }
      case 5: // float
        {
          float floatValue = *(speeduino[logStats[i]].calculated); // Get value from statGrab function
          uint32_t floatBits = *((uint32_t*)&floatValue);
          uint8_t floatBytes[4];
          floatBytes[0] = (floatBits >> 24) & 0xFF;
          floatBytes[1] = (floatBits >> 16) & 0xFF;
          floatBytes[2] = (floatBits >> 8) & 0xFF;
          floatBytes[3] = floatBits & 0xFF;
          dataFile.write(floatBytes, sizeof(floatBytes));
          crcOverflow += floatBytes[0];
          crcOverflow += floatBytes[1];
          crcOverflow += floatBytes[2];
          crcOverflow += floatBytes[3];
          break;
        }
    }
  }


  // Write CRC overflow byte
  dataFile.write(&crcOverflow, 1);

  // if button pressed, add mark
  if (markerFlag) {
    markerFlag = false;
    static int markNum = 0;

    // Block Type
    uint8_t blockTypeMarker[] = {0x01};
    dataFile.write(blockTypeMarker, sizeof(blockTypeMarker));
    // Counter
    static uint8_t counter = 0;
    counter++;
    counter %= 255;
    dataFile.write(&counter, 1);
    // Timestamp
    uint16_t timestamp_us = 1234; // Replace with actual timestamp
    uint8_t timestamp_bytes[2];
    timestamp_bytes[1] = timestamp_us & 0xFF;
    timestamp_bytes[0] = (timestamp_us >> 8) & 0xFF;
    dataFile.write(timestamp_bytes, 2);
    // Message String 50 bytes
    char marker[50];
    sprintf(marker, "MARK %04d - Manual - %02d/%02d/%04d %02d:%02d:%02d", markNum, month, day, year, hour, minute, second);
    writeStringToFile(marker, 50); // Writing as 50-byte
    markNum ++;

    Serial.println("Marker added to Log File.");
  }

}

uint32_t floatToIEEE754(float value) {
    uint32_t result;
    uint8_t *resultBytes = reinterpret_cast<uint8_t*>(&result);
    uint8_t *valueBytes = reinterpret_cast<uint8_t*>(&value);
  
    // Copy bytes in little-endian order
    resultBytes[0] = valueBytes[3];
    resultBytes[1] = valueBytes[2];
    resultBytes[2] = valueBytes[1];
    resultBytes[3] = valueBytes[0];

    return result;
}

void writeStringToFile(const String& str, int length) {
    // Create a buffer of specified length
    uint8_t buffer[length];
    // Fill the buffer with null bytes
    memset(buffer, 0x00, length);
    // Copy the string to the buffer, up to a maximum of length - 1 characters
    str.getBytes(buffer, static_cast<size_t>(min(static_cast<unsigned int>(str.length()), static_cast<unsigned int>(length - 1))) + 1);
    // Write the buffer to the file
    dataFile.write(buffer, length);
}

// Function to calculate CRC overflow byte
uint8_t calculateCRCOverflow(uint8_t* bytes) {
  uint8_t crc = 0;
  for (int i = 0; i < 4; i++) {
    crc += bytes[i];
  }
  return crc;
}

time_t createUnixTimestamp(int year, int month, int day, int hour, int minute, int second) {
  // Adjust the year to be within the range 2000-2099
  // year += 2000;
  
  // Create a tm struct with the provided date and time
  tm tmDateTime;
  tmDateTime.tm_year = year - 1900; // Years since 1900
  tmDateTime.tm_mon = month - 1;     // Months since January (0-11)
  tmDateTime.tm_mday = day;          // Day of the month (1-31)
  tmDateTime.tm_hour = hour;         // Hours since midnight (0-23)
  tmDateTime.tm_min = minute;        // Minutes after the hour (0-59)
  tmDateTime.tm_sec = second;        // Seconds after the minute (0-59)

  // Convert the tm struct to a time_t value (Unix timestamp)
  Serial.print("Unix Timestamp: ");
  Serial.println(mktime(&tmDateTime));
  return mktime(&tmDateTime);
}

void SDsync() {
  dataFile.sync();
  dataFile.close();
  dataFile = sd.open(filename, O_WRITE | O_CREAT);
  dataFile.seek(dataFile.size());
}

void clearSerialInput() {
  uint32_t m = micros();
  do {
    if (Serial.read() >= 0) {
      m = micros();
    }
  } while (micros() - m < 10000);
}

// Call back for file timestamps.  Only called for file create and sync().
void dateTime(uint16_t* date, uint16_t* time, uint8_t* ms10) {
  DateTime now = rtc.now();
  // Return date using FS_DATE macro to format fields.
  *date = FS_DATE(now.year(), now.month(), now.day());
  // Return time using FS_TIME macro to format fields.
  *time = FS_TIME(now.hour(), now.minute(), now.second());
  // Return low time bits in units of 10 ms.
  *ms10 = now.second() & 1 ? 100 : 0;
}

void SDstartLogASCII() {

  // Creating a filename based on the date and time if RTC connected. If not, create a sequentially numbered filename
  if ( RTCconnected() ) {
    sprintf(filename, "/%04d-%02d-%02d_%02d.%02d.%02d.msl", year, month, day, hour, minute, second);
  }
  else {
    while (sd.exists(filename)) {
    char* p = strchr(filename, '.');
    if (!p) {
      Serial.println("no dot in filename");
    }
    while (true) {
      p--;
      if (p < filename || *p < '0' || *p > '9') {
        Serial.println("Can't create file name");
      }
      if (p[0] != '9') {
        p[0]++;
        break;
      }
      p[0] = '0';
    }
  }
  }

  // Open the file with the filename in write mode
  dataFile = sd.open(filename, O_WRITE | O_CREAT);

  if (dataFile) {
    Serial.println("Log file created.");
    Serial.print("Filename: ");
    Serial.println(filename);
    SD_PRESENT = true;
  } else {
    Serial.println("Error creating log file.");
    SD_PRESENT = false;
  }

  // add header for log file
  if (dataFile) {
    // Append text to the file
    dataFile.println("speeduino");

    char header[40];
    sprintf(header, "Capture Date: %02d/%02d/%04d %02d:%02d:%02d", month, day, year, hour, minute, second);
    dataFile.println(header);

    // we need to start with the time counter
    dataFile.print("Time");
    dataFile.print('\t');

    // add variable names for stats read from the Speeduino ECU
    for ( int i = 0; i < (logStatsCount); i++) {
      dataFile.print( speeduino[logStats[i]].fullName );
      dataFile.print('\t');
      }

    dataFile.println("");

    // we need to start with the time counter
    dataFile.print("s");
    dataFile.print('\t');

    // add variable units for stats read from the Speeduino ECU
    for ( int i = 0; i < (logStatsCount); i++) {
      dataFile.print( speeduino[logStats[i]].unit );
      dataFile.print('\t');
      }

    dataFile.println("");

    Serial.println("Log file header appended.");
  } else {
    Serial.println("Error opening the log file. Did not add header.");
  }
  dataFile.seek(dataFile.size());
}

void SDlogASCII() {

  uint32_t logTime = millis();

  if (!dataFile) {
    Serial.println("File not open. Unable to append.");
    // SD Card not inserted or not initialized
    SD_PRESENT = false;
    SDsetup();
    SDstartLogASCII();
    return;
  }

  // if button pressed, add mark
  if (markerFlag) {
    markerFlag = false;
    static int markNum = 0;
    char marker[50];
    sprintf(marker, "MARK %04d - Manual - %02d/%02d/%04d %02d:%02d:%02d", markNum, month, day, year, hour, minute, second);
    dataFile.print(marker);
    markNum++;
    Serial.println("Marker added to Log File.");
  }

  // we need to start with the time counter
  static long startTime = millis();
  dataFile.print((millis() - startTime) / 1000.0);
  dataFile.print('\t');

  // Add stats read from the Speeduino ECU
  for (int i = 0; i < (logStatsCount); i++) {
    dataFile.print(statString(logStats[i]));
    dataFile.print('\t');
  }

  dataFile.print('\r');

}