#include "Arduino.h"
#include "SpeedyPal.h"
#include "Wire.h"

// *****************************************************
// HERE ARE SOME VARIABLES YOU MIGHT WANT TO ADJUST
// *****************************************************

// Set to "true" record a binary MLG log. Set to "false" to record an ASCII MSL log
bool binaryLog = true;

// is there a second screen connected?
bool multiScreen = false;

// frames per second for sampling and display
uint8_t fps = 10;

// vehicle info
uint16_t flowRate = 329; // cc/min
uint8_t cyl = 4; // 4 cylinders
uint16_t weightKg = 1332; // weight in kg
float frontalArea = 1.749; // frontal area in square meters
float dragCoefficient =  0.41; // drag coefficient

// constants for arduino pins
const int8_t ButtonPinL = D1;  // the number of the left button pin
const int8_t ButtonPinR = D2;  // the number of the right button pin
const int8_t chipSelect = D3; // D3 for Seeed ESP32S3, 21 for Seeed Sense  // the number of Chip Select pin for the SD card
const int8_t TXpin = D6;  // the number of the TX pin
const int8_t RXpin = D7;  // the number of the RX pin
const int8_t ledPin = LED_BUILTIN; // LED pin

// *****************************************************
// HERE ARE SOME VARIABLES YOU PROBABLY WON'T ADJUST
// *****************************************************

// bool to detect if SD card is present
bool SD_PRESENT = false;

// screen variables
uint8_t SCREEN_ROTATION = 0; // 0 = 0° normal horizontal, 1 = 90° normal vertical, 2 = 180° flipped horizontal, 3 = 270° flipped vertical
uint8_t SCREEN_WIDTH = 128; // 128 for horizontal, 64 for vertical
uint8_t SCREEN_HEIGHT = 64; // 64 for horizontal, 128 for vertical

// extra unused variable for settings screen
uint8_t VAR1;

// Engine info, this will be overwritten when the program reads from SPIFFS, so just adjust it in the "Settings" screen
uint16_t SHIFTLIGHT_ON_RPM = 5500; // Activate shift light above this threshold

// these are used when adding markers to the log file (quick click with both buttons)
bool markerFlag = false; // flag that a button has been short-pressed to leave a marker in the log file.
long markerCounter = 0; // counter to make the "X" appear on screen for a bit of time.

// for settingsScreen navigation
bool settingsAdd = 0;
uint8_t settingsSelect = 0;

//time variables, these will be overwritten when the program reads from the RTC
uint8_t hour = 12;
uint8_t minute = 12;
uint8_t second = 12;
uint8_t day = 12;
String dayWeek; // such as "Friday"
uint8_t month = 12;
uint16_t year = 2023;

//global variables
uint8_t sweepFlag = 0; // are the gauges being swept?
int16_t clt; // coolant temp
int16_t cltSweep; // used for needle sweep
int16_t iat; // intake air temp
uint8_t bat; // battery voltage
float mph; // miles per hour
uint8_t smoothMPH = 8; // smoothing for MPH
float acceleration; // MPH per Second
uint8_t smoothPerf = 9; // smoothing for HP, Torque and Acceleration
float horsepower; // Horsey Power
float torque; // Torque Power
float timeTo30; // recording the zero-to-30 time
float timeTo60; // recording the zero-to-60 time
float mpg; // miles per gallon
uint8_t baro; // barometric pressure
uint8_t afr; // o2 Sensor Air Fuel Ratio Reading
uint8_t afrT; // AFR target
uint8_t adv; // Advance Degrees
uint16_t MAP; // Manifold Air Pressire
uint16_t pw; // Pulse Width
uint16_t rpm; // RPM
uint16_t rpmSweep; // used to tell if needle sweep is happening
uint16_t tpsdot; // Trottle Position Sensor DOT
uint8_t ve; // current VE
uint16_t tps; // throttle position sensor %
float null; // null float for stats that are ready from the Speeduino and so don't need to be connected to a calculated float

float currentFrameRate; // tracking the framerate of the arduino
uint8_t ecuWait = 5; // pause in ms we'll wait for ECU to respond
bool ecuConnected = false; // used when checking for ECU connection

// sampling rate for logging, calculated by the "fps" above
uint32_t interval;

uint32_t odometer; // There's an extra two digits for a tenths & hundreths. Divide by 100 before display.
float odometerFloat; // a float of the odometer is needed for the logging
float thousandthsCounter; // count hundreths of a mile to update odometer
float tripDistanceA;  // trip miles A covered
float tripDistanceB;  // trip miles B covered

// keeping track of trip gallons used
float tripGallonsUsedA = 0.0; 
float tripGallonsUsedB = 0.0;

//variable to calculate average MPG
uint32_t totalCountMPGa = 0;   // Total count of numbers
uint32_t sumMPGa = 1;          // Sum of numbers
uint16_t averageMPGa = 1;      // Average of numbers
uint32_t totalCountMPGb = 0;   // Total count of numbers
uint32_t sumMPGb = 1;          // Sum of numbers
uint16_t averageMPGb = 1;      // Average of numbers

//variable to calculate average MPH
uint32_t totalCountMPHa = 0;   // Total count of numbers
uint32_t sumMPHa = 1;          // Sum of numbers
uint16_t averageMPHa = 1;      // Average of numbers
uint32_t totalCountMPHb = 0;   // Total count of numbers
uint32_t sumMPHb = 1;          // Sum of numbers
uint16_t averageMPHb = 1;      // Average of numbers

// for custom screen
uint8_t customScreen = 0; // flag - is Custom Screen selected?
uint8_t customScreenSelect = 0; // which custom stat is currently shown?
bool customScreenSwitch = 0; // which screen, A or B, is selected?
uint8_t customScreenSelectA = 0; // which custom stat A is selected?
uint8_t customScreenSelectB = 0; // which custom stat B is selected?

uint8_t pageNum = 0; // currently displayed page
bool clockSetFlag = 0; // has the clock been adjusted by the user on the settings page?
bool settingsFlag = 0; // has a non-clock setting been adjusted by the user on the settings page?

void setup()
{
  pinMode(ButtonPinR, INPUT_PULLUP);
  pinMode(ButtonPinL, INPUT_PULLUP);

  Wire.begin();
  Serial.begin(115200); // usb connection on Arduino Nano
  Serial1.begin(115200, SERIAL_8N1, RXpin, TXpin); // serial connection to Speeduino. D7 and D6 on Seeed SAMD21, RX and TX on Seeed ESP32
  // Serial1.begin(115200); // for SAMD21
  Serial.println("serial started");
  initDisplay();

  // setup RTC
  setupClock();
  updateTimeVariables(); // grab time variables from RTC clock

  // setup SPIFFS
  setupSPIFFS();
  if (SPIFFSconnected()) readFromSPIFFS();

  Serial.println("checking for ECU");
  ecuConnected = requestData(50); // is the Speeduino connected? Waits 50ms for ECU to respond
  if(!ecuConnected) Serial.println("ECU not found");
  else Serial.println("ECU found");

  // setup SD card, count files on SD card
  SDsetup();
  // start SD log file
  if (binaryLog) SDstartLogBIN(); // start Binary log
    else SDstartLogASCII(); // start ASCII log
}

void loop()
{
  // set interval based on fps setting
  if (fps<10) fps = 10;
  interval = 1000/fps;

  // variables for governing consistent framerate
  static uint32_t previousMillisLog;
  static uint32_t nextTimeLog = millis() + interval;
  static uint32_t nextTimeTen = millis() + 10000;

  //*********************************************************************
  // Run this part in the preset interval (default is 10 times per second)
  //*********************************************************************

  if (millis() >= nextTimeLog) // only run this section if it's been at least the "interval" since the last loop
  {
    currentFrameRate = 1000.0 / (millis() - previousMillisLog); 
    // Serial.print("Current Frame Rate: ");
    // Serial.println(currentFrameRate);

    previousMillisLog = millis();
    // update next time
    nextTimeLog = (previousMillisLog + interval);

    updateTimeVariables(); // set time variables based off the RTC clock
    
    // is the Speeduino connected? Also, read the ECU's information into a buffer called "buffer"
    if (ecuWait < 5) ecuWait = 5; // don't wait less than 5ms for Speeduino to respond
    ecuConnected = requestData(ecuWait);

    // this reads a bunch of stats from the buffer and assigns them to variables like "map" and "baro"
    grabStats();

    // log the stats to the SD card
    if (binaryLog) SDlogBIN(); // add to log with Binary
      else SDlogASCII(); // add to log with ASCII

    // Record stats for the graphs
    recordGraph(mpg/10.0, 0, 10); // settings are:  (variable to record, graph number, graph speed from 1-10 higher is slower)
    recordGraph(averageMPGa/10.0, 1, 10);
    recordGraph(afr/10, 2, 1);
    recordGraph(afrT/10, 3, 1);

    if (millis() >= nextTimeTen) // Only run this stuff every ten seconds
    {
      // **************************************
      // This subroutine runs every 10 seconds)
      // **************************************
      nextTimeTen += 10000;
      if (SPIFFSconnected()) {
        writeToSPIFFS(); // save trip & settings info to SPIFFS
      }
      SDsync();
    }

    // *******************************************************************************
    // Back to the part that runs at the preset interval (default 10 times per second)
    // *******************************************************************************

    // sweep the tach if just starting the code. Runs after logging so it doesnt reflect in logs.
    tachSweep();

    setDisplay(1);

    //has the screen rotation been changed in the settings? If so, update it.
    updateRotation();

    startPage(); // Clears display

      switch(pageNum)   // this part decides what page is displayed in the horizontal view
      {
        case 0:
          // variables for gauge display
          int16_t CLTdisplay;
          uint16_t RPMdisplay;
          // are the gauges being swept?
          if (sweepFlag != 2) RPMdisplay = rpmSweep;
            else RPMdisplay = rpm;
          if (sweepFlag != 2) CLTdisplay = cltSweep;
            else CLTdisplay = clt;
          // three circle gauges
          // ( x position, y position, diameter, start angle, end angle, gradiations, stat value, start range, end range, redline, numbers switch )
          if (SCREEN_ROTATION == 0 || SCREEN_ROTATION == 2){
          // horizontal screen
          drawCircleGauge( 64, 64, 62 , 170, 10, 9, RPMdisplay, 0, 8000, 6500, 1);
          drawCircleGauge( 64, 64, 40 , 170, 10, 5, CLTdisplay, 125, 230, 212, 0);
          drawCircleGauge( 64, 64, 18 , 170, 10, 3, bat, 100, 160, 130, 0);
          }
          else {
          // vertical screen
          drawCircleGauge( 64, 64, 62 , 260, 100, 9, RPMdisplay, 0, 8000, 6500, 1);
          drawCircleGauge( 64, 64, 40 , 260, 100, 5, CLTdisplay, 125, 230, 212, 0);
          drawCircleGauge( 64, 64, 18 , 260, 100, 3, bat, 100, 160, 130, 0);
          }
          break;
        case 1:
          // date and time
          if (SCREEN_ROTATION == 0 || SCREEN_ROTATION == 2){
            drawAnalogClock(hour, minute, second, SCREEN_WIDTH/1.5, SCREEN_HEIGHT/2, SCREEN_HEIGHT-1);
            printFormattedDate(day, month, year, dayWeek, 21, 16);
          }
          else {
            drawAnalogClock(hour, minute, second, SCREEN_WIDTH/2, SCREEN_HEIGHT/4, SCREEN_WIDTH-1);
            printFormattedDate(day, month, year, dayWeek, 32 , (SCREEN_HEIGHT/2)+16);
          }
          break;
        case 2:
          twoStats(1, "WATER", clt, 0, 32, 212, "AIR", iat, 0, 32, 110);
          twoStats(2, "RPM", rpm, 0, 600, 6000, "MPGb", averageMPGb, 1, 0, 100);
          bottomRow("MPG", mpg , 1, 0, 100);
          break;
        case 3:
          // bar graphs
          // drawBarGraph(int row, int variable, int minVal, int maxVal, int redline, String label)
          drawSmallBarGraph(1, afr, 1, 11.7, 17.6, 14.7, "AFR");
          drawSmallBarGraph(2, afrT, 1, 11.7, 17.6, 14.7, "AFRt");
          drawBarGraph(2, MAP, 0, 0, 100, 50, "MAP");
          break;
        case 4:
          // fast AFR graph
          if (SCREEN_ROTATION == 0 || SCREEN_ROTATION == 2){
          // horizontal screen
          displayGraph(0, 2, 0, 20, "AFR" , afr, 1, 0, 20, "AFRt", afrT, 1, 0, 20);
          displayGraph2(0, 3, 0, 20); // second dotted line graph
          }
          else {
          // vertical screen
          displayGraph(0, 2, 0, 20, "AFR" , afr, 1, 0, 20, "0", 0, 0, 0, 0);
          displayGraph(1, 3, 0, 20, "AFRt", afrT, 1, 0, 20, "0", 0, 0, 0, 0);
          }
          break;
        case 5:
          // trip computer
          twoStats(1, "MPHa", averageMPHa, 0, -1, 100, "MPHb", averageMPHb, 0, -1, 100);
          twoStats(2, "MPGa", averageMPGa, 1, 0, 99, "MPGb", averageMPGb, 1, 0, 99);
          if (tripGallonsUsedA < 10 ) twoStats(3, "GALa", (tripGallonsUsedA*100.0), 2, -1, 9999, "0", 0, 0, 0, 0);
            else if (tripGallonsUsedA >= 10 && tripGallonsUsedA < 100) twoStats(3, "GALa", (tripGallonsUsedA*10.0), 1, -1, 9999, "0", 0, 0, 0, 0);
              else twoStats(3, "GALa", (tripGallonsUsedA), 0, -1, 9999, "0", 0, 0, 0, 0);
          if (tripGallonsUsedB < 10) twoStats(3, "0", 0, 0, 0, 0, "GALb", (tripGallonsUsedB*100.0), 2, -1, 9999);
            else if (tripGallonsUsedB >= 10 && tripGallonsUsedB < 100) twoStats(3, "0", 0, 0, 0, 0, "GALb", (tripGallonsUsedB*10.0), 1, -1, 9999);
              else twoStats(3, "0", 0, 0, 0, 0, "GALb", (tripGallonsUsedB), 0, -1, 9999);
          if (tripDistanceA < 10) twoStats(4, "TRPa", (tripDistanceA*100.0), 2, -1, 9999, "0", 0, 0, 0, 0);
            else if (tripDistanceA >= 10 && tripDistanceA < 100) twoStats(4, "TRPa", (tripDistanceA*10.0), 1, -1, 9999, "0", 0, 0, 0, 0);
              else twoStats(4, "TRPa", (tripDistanceA), 0, -1, 9999, "0", 0, 0, 0, 0);
          if (tripDistanceB < 10) twoStats(4, "0", 0, 0, 0, 0, "TRPb", (tripDistanceB*100.0), 2, -1, 9999);
            else if (tripDistanceB >= 10 && tripDistanceB < 100) twoStats(4, "0", 0, 0, 0, 0, "TRPb", (tripDistanceB*10.0), 1, -1, 9999);
              else twoStats(4, "0", 0, 0, 0, 0, "TRPb", (tripDistanceB), 0, -1, 9999);
          // twoStats(4, "0", 0, 0, 0, 0, "" , (odometer/100), 0 , 0, 999999); // full odometer
          break;
        case 6:
          // performance screen
          twoStats(1, "MPH", mph, 0, -200, 200, "0", 0, 0, 0, 0);
          twoStats(2, "TRQ", torque, 0, -1000, 1000 , "0", 0, 0, 0, 0);
          if (timeTo60 < 1000) twoStats(1, "0", 0, 0, 0, 0, "0-60", (timeTo60), 2, -1, 9999);
            else twoStats(1, "0", 0, 0, 0, 0, "0-60", (timeTo60/10), 1, -1, 9999);
          if (timeTo30 < 1000) twoStats(2, "0", 0, 0, 0, 0, "0-30", (timeTo30), 2, -1, 9999);
            else twoStats(2, "0", 0, 0, 0, 0, "0-30", (timeTo30/10), 1, -1, 9999);
          bottomRow("HP", horsepower , 0, -1000, 1000);
          break;
        case 7:
          twoStats(1, "WATER", clt, 0, 32, 212, "FPS", currentFrameRate, 0, 10, 100);
          twoStats(2, "TPS", tps, 1, -1, 100, "AFR" , afr, 1 , 0, 20);
          twoStats(3, "ADV", adv, 0, 0, 60, "AFRt", afrT, 1, 10, 20);
          twoStats(4, "MAP", MAP, 0, 0, 110, "PW", pw, 1, 0, 30);
          break;
        case 8:
          // settings Screen
          settingsPage();
          break;
        case 9:
          // simple customizable display page
          customGauge(customScreenSelect);
          break;
        default:
          break;
        }

    shiftLight(); // draw an inverse rectangle if the rpm is over the shift limit

    buttonCheck(); // Button operation and display button indicator overlays
    
    if (markerFlag) markerCounter = millis() + 250;
    if (millis() < markerCounter) markX(); // if marker is being added to the log, draw an "X" on the screen
    // Serial.println(markerFlag);

    errorPopUp(ecuConnected, SD_PRESENT); // display a notification if ECU or SD Card are not present

    endPage(); // writes the latest changes to the screen

    if (multiScreen){
        setDisplay(2);
          //has the screen rotation been changed in the settings? If so, update it.
          updateRotation();
          startPage(); // Clears display
            bool tempSwitch = customScreenSwitch;
            customScreenSwitch = 1;
            customGauge(customScreenSelectB);
            customScreenSwitch = tempSwitch;
            if(!ecuConnected) errorPopUp(ecuConnected, SD_PRESENT); // if Speeduino isn't connected, print the "no connection" page
          endPage();
    }

    // if a setting has been changed, save it to SPIFFS
    if (SPIFFSconnected() && settingsFlag == 1) {
      writeToSPIFFS();
      settingsFlag = 0;
    }

    // if clock has been set, reflect those changes in the RTC
    if (clockSetFlag == 1) {
      if ( RTCconnected() ) { // if the RTC is connected
        displayVariableTime(); // display time variables in Serial Monitor
        checkTimeVariables(); // make sure the time isn't set to impossible dates
        setTime(year, month, day, hour, minute, second);
        displayTime(); // display RTC clock in Serial Monitor
        Serial.println("RTC clock set");
      }
      clockSetFlag = 0;
    }
  }

}
