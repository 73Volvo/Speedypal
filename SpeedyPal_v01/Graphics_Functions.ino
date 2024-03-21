#include <Adafruit_SSD1306.h>
#include "Numbers24pt7b.h"
#include "FreeMono9pt7b.h"
#include "FreeSans20pt7b.h"
#include "splash.h"
#include "Settings_Screen.h"
#include "Moon.h"

// storage variable for each graph, this is set up to hold four different graphs with the [4] increase that number for more graphs
int16_t graphData[4][108]; // places to store data for the graphs. Could probably use a smaller number for vertical screens
uint8_t graphIndex[4]; // what place are we currently writing for the graph?

// for circle gauges
#define DEG_TO_RAD(deg) ((deg) * 3.14159 / 180)

// variables for screen(s)
#define SCREEN1_ADDR 0x3C // address for screen 1 0x3C default
#define SCREEN2_ADDR 0x3D // address for screen 2
// declare "name" for each screen
Adafruit_SSD1306 screen1(128, 64, &Wire, -1);
Adafruit_SSD1306 screen2(128, 64, &Wire, -1);

// Global variable to represent the currently selected OLED screen
Adafruit_SSD1306* selectedOLED;

void clearBuffer(char *buf, uint8_t bufLen = STRING_LENGTH);

void setDisplay(int display)
{
  if (display == 1) selectedOLED = &screen1;
  if (display == 2) selectedOLED = &screen2;
}

void initDisplay()
{ 
  // Initialize both screens
  if (!screen1.begin(SSD1306_SWITCHCAPVCC, SCREEN1_ADDR)) {
    Serial.println(F("Screen 1 initialization failed"));
  } else Serial.println(F("Screen 1 initialized"));

  if (multiScreen) {
      if (!screen2.begin(SSD1306_SWITCHCAPVCC, SCREEN2_ADDR)) {
        Serial.println(F("Screen 2 initialization failed"));
      } else Serial.println(F("Screen 2 initialized"));

      selectedOLED = &screen2;

      selectedOLED->setFont();
      selectedOLED->setTextColor(INVERSE);
      selectedOLED->clearDisplay();
      selectedOLED->setTextWrap(0);
      selectedOLED->setRotation(SCREEN_ROTATION);
      splashStart();
      endPage();
  }

  // Set the default selected OLED
  selectedOLED = &screen1;

  selectedOLED->setFont();
  selectedOLED->setTextColor(INVERSE);
  selectedOLED->clearDisplay();
  selectedOLED->setTextWrap(0);
  selectedOLED->setRotation(SCREEN_ROTATION);
  splashStart();
  endPage();
}

void updateRotation() {
      selectedOLED->setRotation(SCREEN_ROTATION);
      if (SCREEN_ROTATION == 0 || SCREEN_ROTATION == 2) {
        SCREEN_WIDTH = 128;
        SCREEN_HEIGHT = 64;
      }
      else {
        SCREEN_WIDTH = 64;
        SCREEN_HEIGHT = 128;
      }
}

void splashStart(){
  int16_t centerX = (SCREEN_WIDTH - 64) / 2;
  int16_t centerY = (SCREEN_HEIGHT - 64) / 2;
  int16_t width = 64;
  int16_t height = 64;
  int16_t x1, y1;
  uint16_t w, h;
  int logoX; // offset for logo display based on screen orientation
  String noECU = "LOADING";
  int frame = 0;

  if (SCREEN_ROTATION == 0 || SCREEN_ROTATION == 2) logoX = 32;
  if (SCREEN_ROTATION == 1 || SCREEN_ROTATION == 3) logoX = 0;

  Serial.println("displaying logo");

  // Display initial boot animation
  for ( int i = 0; i < Speeduino_Logo_Anim_LEN ; i ++) {
  selectedOLED->clearDisplay();
  selectedOLED->drawBitmap(logoX, 0, Speeduino_Logo_Anim_Array[i], 64, 64, WHITE);
  endPage();
  delay(50);
  }

  // Cycle boot animation until ECU is detected
  while (!ecuConnected) {
  selectedOLED->clearDisplay();
  selectedOLED->drawBitmap(logoX, 0, Speeduino_Logo_Anim_Array[frame], 64, 64, WHITE);
  frame ++;
  if (frame > Speeduino_Logo_Anim_LEN) frame = 0;

  selectedOLED->getTextBounds(noECU,0,0,&x1, &y1, &w, &h);
  if (SCREEN_ROTATION == 0 || SCREEN_ROTATION == 2) selectedOLED->setCursor(SCREEN_WIDTH-w-4, SCREEN_HEIGHT-h-4);
  if (SCREEN_ROTATION == 1 || SCREEN_ROTATION == 3) selectedOLED->setCursor((SCREEN_WIDTH-w)/2, SCREEN_HEIGHT-h-4);
  selectedOLED->setTextSize(1);
  selectedOLED->setTextColor(INVERSE);
  selectedOLED->print("LOADING");

  endPage();
  delay(50);

  // is the Speeduino connected? Also, read the ECU's information into a buffer called "buffer"
  if (ecuWait < 5) ecuWait = 5; // don't wait less than 5ms for Speeduino to respond
  ecuConnected = requestData(ecuWait);

  }

}

bool testShiftLight() {
  static bool shiftLightFlag = 0;

  if ( !shiftLightFlag && rpm >= SHIFTLIGHT_ON_RPM ) {
    shiftLightFlag = true;
    return 1;
  }
  else if ( shiftLightFlag && rpm > SHIFTLIGHT_OFF_RPM ) {
    return 1;
  }
  else if ( shiftLightFlag && rpm <= SHIFTLIGHT_OFF_RPM ) {
    shiftLightFlag = false;
    return 0;
  }
  else return 0;
}

void shiftLight() {
  //Drawing a INVERSE rectangle over the whole display will invert all graphics
  if(testShiftLight())
    selectedOLED->fillRect(0, 0, 128, 64, INVERSE);
}

void startPage()
{
  selectedOLED->clearDisplay();
}

void endPage()
{
  selectedOLED->display();
}

void buttonIndicator(int side, int size) {
  if (side == 0 && size == 0){
    selectedOLED->drawFastVLine( 0 , SCREEN_HEIGHT/2 , SCREEN_HEIGHT/2 , WHITE);
    selectedOLED->drawFastVLine( 1 , SCREEN_HEIGHT/2 , SCREEN_HEIGHT/2 , WHITE);
  }
  if (side == 0 && size == 1){
    selectedOLED->drawFastVLine( 0 , 0 , SCREEN_HEIGHT , WHITE);
    selectedOLED->drawFastVLine( 1 , 0 , SCREEN_HEIGHT , WHITE);
  }
  if (side == 1 && size == 0){
    selectedOLED->drawFastVLine( SCREEN_WIDTH-1 , SCREEN_HEIGHT/2 , SCREEN_HEIGHT/2 , WHITE);
    selectedOLED->drawFastVLine( SCREEN_WIDTH-2 , SCREEN_HEIGHT/2 , SCREEN_HEIGHT/2 , WHITE);
  }
  if (side == 1 && size == 1){
    selectedOLED->drawFastVLine( SCREEN_WIDTH-1 , 0 , SCREEN_HEIGHT , WHITE);
    selectedOLED->drawFastVLine( SCREEN_WIDTH-2 , 0 , SCREEN_HEIGHT , WHITE);
  }
}

void tachSweep(){
  int rpmMax = 8000;
  int cltMax = 230;
  static int rpmMod = rpm;
  static int cltMod = clt;
  static int steps = 0;
  
  if ( sweepFlag == 0) {
      rpmSweep = easing(rpmMod, rpmMax, 0.3, 12, steps);
      cltSweep = easing(cltMod, cltMax, 0.5, 12, steps);
      rpmMod = rpmSweep;
      cltMod = cltSweep;
      steps++;
      delay(50);
  }
  if (steps >= 12 && sweepFlag == 0) {
      steps = 0;
      sweepFlag = 1;
  }
  if ( sweepFlag == 1) {
      rpmSweep = easing(rpmMod, rpm, 0.5, 18, steps);
      cltSweep = easing(cltMod, clt, 0.8, 18, steps);
      rpmMod = rpmSweep;
      cltMod = cltSweep;
      steps++;
  }
  if (steps >= 18 && sweepFlag == 1) {
      sweepFlag = 2;
  }
}

void markX() {
  selectedOLED->drawLine(0, 0 , SCREEN_WIDTH, SCREEN_HEIGHT , WHITE);
  selectedOLED->drawLine(0, 1 , SCREEN_WIDTH, SCREEN_HEIGHT+1 , WHITE);
  selectedOLED->drawLine(0, SCREEN_HEIGHT , SCREEN_WIDTH, 0 , WHITE);
  selectedOLED->drawLine(0, SCREEN_HEIGHT+1 , SCREEN_WIDTH, 1 , WHITE);
}

// Display one stats per row
void oneStat(float row, String title1, float stat1, int decimal1, int min1, int max1)
{
  char valString[8];
  int16_t x1, y1;
  uint16_t w, h;
  int LROffset = 4;
  int height = ( SCREEN_HEIGHT*( (row-1)/4.0) );// + row;
  int celHeight = SCREEN_HEIGHT*0.25;
  int celWidth = SCREEN_WIDTH*0.33;
  int decimalMod = 1;

  // Print 1
  selectedOLED->setTextSize(0);
  selectedOLED->getTextBounds(title1,0,0,&x1, &y1, &w, &h);
  selectedOLED->setCursor( 0 , height );
  selectedOLED->print(title1);
  selectedOLED->setFont(&FreeMono9pt7b);
  formatValue(valString, stat1, decimal1);
  selectedOLED->getTextBounds(valString,0,0,&x1, &y1, &w, &h);
  selectedOLED->setCursor(SCREEN_WIDTH-w-LROffset, height+12);
  selectedOLED->print(valString);
  selectedOLED->setFont();
  if (decimal1 == 0) decimalMod = 1;
  else decimalMod = 10;
  if(stat1 < min1*decimalMod) selectedOLED->fillRoundRect( SCREEN_WIDTH-w-2 , (celHeight*(row-1))+1 , w + 2, h + 2 , 2, INVERSE);
  if(stat1 > max1*decimalMod) selectedOLED->fillRoundRect( SCREEN_WIDTH-w-2 , (celHeight*(row-1))+1 , w + 2, h + 2 , 2, INVERSE);

}

// Display two stats per row
void twoStats(float row, String title1, float stat1, int decimal1, int min1, int max1, String title2, float stat2, int decimal2, int min2, int max2)
{

  if (SCREEN_ROTATION == 0 || SCREEN_ROTATION == 2){
      char valString[8];
      int16_t x1, y1;
      uint16_t w, h;
      int LROffset = 3;
      int height = ( SCREEN_HEIGHT*( (row-1)/4.0) );// + row;
      int celHeight = SCREEN_HEIGHT*0.25;
      int celWidth = SCREEN_WIDTH*0.33;
      int decimalMod = 1;

      // Print 1
      if (title1 != "0"){
      selectedOLED->setTextSize(0);
      selectedOLED->getTextBounds(title1,0,0,&x1, &y1, &w, &h);
      selectedOLED->setCursor( (SCREEN_WIDTH/2)-(w*.75) , height );
      selectedOLED->print(title1);
      selectedOLED->setFont(&FreeMono9pt7b);
      selectedOLED->setCursor(1-LROffset, height+12);
      formatValue(valString, stat1, decimal1);
      selectedOLED->print(valString);
      selectedOLED->setFont();
      if (decimal1 == 0) decimalMod = 1;
      else decimalMod = 10;
      if(stat1 < min1*decimalMod) selectedOLED->fillRoundRect( 0 , (celHeight*(row-1))+1, celWidth, celHeight, 2, INVERSE);
      if(stat1 > max1*decimalMod) selectedOLED->fillRoundRect( 0 , (celHeight*(row-1))+1, celWidth, celHeight, 2, INVERSE);
      }

      // Print 2
      if (title2 != "0"){
      selectedOLED->setTextSize(0);  
      selectedOLED->getTextBounds(title2,0,0,&x1, &y1, &w, &h);
      selectedOLED->setCursor( (SCREEN_WIDTH/2)-(w*.25), height+8 );
      selectedOLED->print(title2);
      selectedOLED->setFont(&FreeMono9pt7b);
      formatValue(valString, stat2, decimal2);
      selectedOLED->getTextBounds(valString,0,0,&x1, &y1, &w, &h);
      selectedOLED->setCursor(SCREEN_WIDTH-w-LROffset, height+12);
      selectedOLED->print(valString);
      selectedOLED->setFont();
      if (decimal2 == 0) decimalMod = 1;
      else decimalMod = 10;
      if(stat2 < min2*decimalMod) selectedOLED->fillRoundRect( (celWidth*2)+2 , (celHeight*(row-1))+1, celWidth, celHeight, 2, INVERSE);
      if(stat2 > max2*decimalMod) selectedOLED->fillRoundRect( (celWidth*2)+2 , (celHeight*(row-1))+1, celWidth, celHeight, 2, INVERSE);
      }
  }
  else {
      if (title1 != "0") oneStat(row, title1, stat1, decimal1, min1, max1);
      if (title2 != "0") oneStat( (row+0.5) , title2, stat2, decimal2, min2, max2);
  }
}


// Display three stats per row
void threeStats(float row, String title1, float stat1, int decimal1, int min1, int max1, String title2, float stat2, int decimal2, int min2, int max2, String title3, float stat3, int decimal3, int min3, int max3)
{
  char valString[8];
  int16_t x1, y1;
  uint16_t w, h;
  int LROffset = 3;
  int height = ( SCREEN_HEIGHT*( (row-1)/3.0) ) + row;
  int celHeight = SCREEN_HEIGHT*0.33;
  int celWidth = SCREEN_WIDTH*0.33;
  int decimalMod = 1;

  // Print 1
  if (title1 != "0"){
  selectedOLED->setTextSize(0);
  selectedOLED->getTextBounds(title1,0,0,&x1, &y1, &w, &h);
  selectedOLED->setCursor( 1 , height );
  selectedOLED->print(title1);
  selectedOLED->setFont(&FreeMono9pt7b);
  selectedOLED->setCursor(1-LROffset, height+18);
  formatValue(valString, stat1, decimal1);
  selectedOLED->print(valString);
  selectedOLED->setFont();
  if (decimal1 == 0) decimalMod = 1;
  else decimalMod = 10;
  if(stat1 < min1*decimalMod) selectedOLED->fillRoundRect( 0 , (celHeight*(row-1))+1, celWidth, celHeight, 2, INVERSE);
  if(stat1 > max1*decimalMod) selectedOLED->fillRoundRect( 0 , (celHeight*(row-1))+1, celWidth, celHeight, 2, INVERSE);
  }

  // Print 2
  if (title2 != "0"){
  selectedOLED->setTextSize(0);
  selectedOLED->getTextBounds(title2,0,0,&x1, &y1, &w, &h);
  selectedOLED->setCursor( ((SCREEN_WIDTH/2)-(w/2)) , height );
  selectedOLED->print(title2);
  selectedOLED->setFont(&FreeMono9pt7b);
  formatValue(valString, stat2, decimal2);
  selectedOLED->getTextBounds(valString,0,0,&x1, &y1, &w, &h);
  selectedOLED->setCursor((SCREEN_WIDTH/2)-(w/2)-LROffset, height+18);
  selectedOLED->print(valString);
  selectedOLED->setFont();
  if (decimal2 == 0) decimalMod = 1;
  else decimalMod = 10;
  if(stat2 < min2*decimalMod) selectedOLED->fillRoundRect( celWidth+1 , (celHeight*(row-1))+1, celWidth, celHeight , 2 , INVERSE);
  if(stat2 > max2*decimalMod) selectedOLED->fillRoundRect( celWidth+1 , (celHeight*(row-1))+1, celWidth, celHeight , 2  , INVERSE);
  int middle = w/2;
  }

  // Print 3
  if (title3 != "0"){
  selectedOLED->setTextSize(0);  
  selectedOLED->getTextBounds(title3,0,0,&x1, &y1, &w, &h);
  selectedOLED->setCursor( SCREEN_WIDTH-w, height );
  selectedOLED->print(title3);
  selectedOLED->setFont(&FreeMono9pt7b);
  formatValue(valString, stat3, decimal3);
  selectedOLED->getTextBounds(valString,0,0,&x1, &y1, &w, &h);
  selectedOLED->setCursor(SCREEN_WIDTH-w-LROffset, height+18);
  selectedOLED->print(valString);
  selectedOLED->setFont();
  if (decimal3 == 0) decimalMod = 1;
  else decimalMod = 10;
  if(stat3 < min3*decimalMod) selectedOLED->fillRoundRect( (celWidth*2)+2 , (celHeight*(row-1))+1, celWidth, celHeight, 2, INVERSE);
  if(stat3 > max3*decimalMod) selectedOLED->fillRoundRect( (celWidth*2)+2 , (celHeight*(row-1))+1, celWidth, celHeight, 2, INVERSE);
  }
}

// Display Big Number on the bottom row
void bottomRow(String title, int variable, int decimal, int min, int max)
{
  if (SCREEN_ROTATION == 0 || SCREEN_ROTATION == 2) {
      int decimalMod = 1;
      char valString[8];
      int16_t x1, y1;
      uint16_t w, h;

      selectedOLED->setCursor(1, SCREEN_HEIGHT-8);
      selectedOLED->setTextSize(0);
      selectedOLED->print(title);
      selectedOLED->setFont(&FreeSans20pt7b);
      formatValue(valString, variable, decimal);
      selectedOLED->getTextBounds(valString,0,0,&x1, &y1, &w, &h);
      selectedOLED->setCursor(SCREEN_WIDTH-w-5, SCREEN_HEIGHT-2);
      selectedOLED->print(valString);
      selectedOLED->setFont();
      if (decimal == 0) decimalMod = 1;
      else decimalMod = 10;
      if(variable < min*decimalMod) selectedOLED->fillRoundRect( 0 , SCREEN_HEIGHT-h-1, SCREEN_WIDTH, h+1, 2, INVERSE);
      if(variable > max*decimalMod) selectedOLED->fillRoundRect( 0 , SCREEN_HEIGHT-h-1, SCREEN_WIDTH, h+1, 2, INVERSE);
  }
  else oneStat(4.5, title, variable, decimal, min, max);
}

void recordGraph(float Var, int Num, int speedGraph)
{
  static int speedGraphArray[4][10]; // first [4] limits the number of graphs
  static int speedGraphCounter[4]; // first [4] limits the numner of graphs
  int speedGraphAverage = 0;

  speedGraphArray[Num][speedGraphCounter[Num]] = Var*100;
  speedGraphCounter[Num]++;

  if (speedGraphCounter[Num] == speedGraph) {
      for (int i = 0; i < speedGraph; i++){
        speedGraphAverage = speedGraphAverage + speedGraphArray[Num][i];
      }
      speedGraphAverage = speedGraphAverage / (speedGraph);
      graphData[Num][graphIndex[Num]] = speedGraphAverage;
      graphIndex[Num]++; // Next time we will write to the next data entry
      if(graphIndex[Num] > 107 || graphIndex[Num] < 0) graphIndex[Num] = 0;
      speedGraphCounter[Num] = 0;
  }
}

void displayGraph( float row, int Num, float minX, float maxX, String nameGraph1, float variableGraph1, int decimal1, int min1, int max1, String nameGraph2, float variableGraph2, int decimal2, int min2, int max2 )
{
  uint8_t i, x;
  float y, y2;
  float midX = (minX+maxX)/2; //figure out middle axis value
  int miX = minX; // axis label for min graph value 
  int maX = maxX; // axis label for max graph value
  int mdX = midX; // axis label for middle graph value
  float convertX = 50/(maxX-minX); // multiplier to scale graph to fit the full range (50 pixels)
  row = row * 64.0; // for vertical orientation, top or bottom of screen

  char valString[8];
  int16_t x1, y1;
  uint16_t w, h;
  int16_t xA, yA, xB, yB;

  int decimalMod = 1;

  // Print Variable 1 Upper Left
  if (nameGraph1 != "0"){
  selectedOLED->setTextSize(0);  
  selectedOLED->setCursor( 1, 2 + row );
  selectedOLED->print(nameGraph1);
  formatValue(valString, variableGraph1, decimal1);
  selectedOLED->getTextBounds(valString,0,0,&x1, &y1, &w, &h);
  if (SCREEN_ROTATION == 0 || SCREEN_ROTATION == 2)   selectedOLED->setCursor((SCREEN_WIDTH/2)-w-6, 2 + row );
    else selectedOLED->setCursor((SCREEN_WIDTH)-w, 2 + row );
  selectedOLED->print(valString);
  selectedOLED->setFont();
  if (decimal1 == 0) decimalMod = 1;
    else decimalMod = 10;
  if ((SCREEN_ROTATION == 0 || SCREEN_ROTATION == 2) && (variableGraph1 < min1*decimalMod || variableGraph1 > max1*decimalMod )) selectedOLED->fillRect( 0 , 0 + row , SCREEN_WIDTH/2, 12 , INVERSE);
  if ((SCREEN_ROTATION == 1 || SCREEN_ROTATION == 3) && (variableGraph1 < min1*decimalMod || variableGraph1 >= max1*decimalMod )) selectedOLED->fillRect( 0 , 0 + row , SCREEN_WIDTH, 12 , INVERSE);
  }

  // Print Variable 2 Upper Right
  if (nameGraph2 != "0"){
  selectedOLED->setTextSize(0);  
  selectedOLED->setCursor( SCREEN_WIDTH/2, 2 + row );
  selectedOLED->print(nameGraph2);
  formatValue(valString, variableGraph2, decimal2);
  selectedOLED->getTextBounds(valString,0,0,&x1, &y1, &w, &h);
  selectedOLED->setCursor(SCREEN_WIDTH-w, 2 + row );
  selectedOLED->print(valString);
  selectedOLED->setFont();
  if (decimal2 == 0) decimalMod = 1;
    else decimalMod = 10;
  if(variableGraph2 < min2*decimalMod) selectedOLED->fillRect( SCREEN_WIDTH/2 , 0, SCREEN_WIDTH/2, 12, INVERSE);
  if(variableGraph2 > max2*decimalMod) selectedOLED->fillRect( SCREEN_WIDTH/2 , 0, SCREEN_WIDTH/2, 12, INVERSE);
  }

  // Print Graph Axis Scale
  selectedOLED->drawLine(14, 13 + row , 17, 13 + row , WHITE); // maxX
  selectedOLED->setCursor(0, 13 + row );
  selectedOLED->print(maX);
  selectedOLED->drawLine(14, 38 + row , 17, 38 + row , WHITE); // midpoint
  selectedOLED->setCursor(0, 35 + row );
  selectedOLED->print(mdX);
  selectedOLED->drawLine(14, 63 + row , 17, 63 + row , WHITE); // minX
  selectedOLED->setCursor(0, 56 + row );
  selectedOLED->print(miX);
  
  selectedOLED->setTextColor(INVERSE); // Reset to regular text color

  i = ( graphIndex[Num] + (128 - SCREEN_WIDTH) ) % 108;         // Start from the oldest data
  for(x = 0; x < (SCREEN_WIDTH-20); x++)
  {
    if(i > 107) i = 0;                // Overflow back to zero

    y2 = y;                // y1 equals the previous pixel

    y = (((graphData[Num][i]/100.0)-minX) * convertX );   // convert int back to decimal value

    xA = x+20;
    yA = (63-y) + row;
    xB = x+19;
    yB = (63-y2) + row;

    if(x == 0){ //if this is the first point
      selectedOLED->drawPixel(xA, yA , WHITE);
    }
    if(x > 0 && x < (SCREEN_WIDTH-20)) {
      cropLineToRange(xA, yA, xB, yB, 12+row, 63+row);
    }
    i++;

  }

}

void displayGraph2( float row, int Num, float minX, float maxX)
{
  uint8_t i, x;
  float y, y2;
  float convertX = 50/(maxX-minX); // multiplier to scale graph to fit the full range (50 pixels)
  row = row * 64.0; // for vertical orientation, top or bottom of screen
  int16_t xA, yA, xB, yB;
  
  selectedOLED->setTextColor(INVERSE); // Reset to regular text color

  i = ( graphIndex[Num] + (128 - SCREEN_WIDTH) ) % 108;         // Start from the oldest data
  for(x = 0; x < (SCREEN_WIDTH-20); x++)
  {
    if(i > 107) i = 0;                // Overflow back to zero
    y2 = y;                // y1 equals the previous pixel
    y = (((graphData[Num][i]/100.0)-minX) * convertX );   // convert int back to decimal value

    xA = x+20;
    yA = (63-y) + row;
    xB = x+19;
    yB = (63-y2) + row;

      if ( ((i / 2)  % 2 == 0) && (x > 0 && x < (SCREEN_WIDTH-20)) ) { // draw a line two cycles on, two cycles off
          cropLineToRange(xA, yA, xB, yB, 12+row, 63+row);
      }
    i++;
  }
}

void drawCircleGauge(int GAUGE_CENTER_X, int GAUGE_CENTER_Y, int GAUGE_RADIUS, int GAUGE_START_ANGLE, int GAUGE_END_ANGLE,int NUM_GRADUATIONS, int sensorValue, int rangeMin, int rangeMax, int redlineValue, bool numbers) {

  // Calculate the angle range for the active area of the gauge
  float gaugeRange = GAUGE_END_ANGLE - GAUGE_START_ANGLE;
  
  // Determine the start and end angles based on clockwise or counterclockwise
  float startAngle, endAngle;
    startAngle = DEG_TO_RAD(GAUGE_START_ANGLE + gaugeRange);
    endAngle = DEG_TO_RAD(GAUGE_START_ANGLE);

  // Draw the active area of the gauge
  drawArc(GAUGE_CENTER_X, GAUGE_CENTER_Y, GAUGE_RADIUS, startAngle, endAngle, WHITE, 0);

  // Calculate the angle between each graduation
  float anglePerGraduation = gaugeRange / (float)(NUM_GRADUATIONS - 1);

  // Draw graduations and labels
  for (int i = 0; i < NUM_GRADUATIONS; i++) {
    float angle = DEG_TO_RAD(GAUGE_START_ANGLE + i * anglePerGraduation);
    
    // Determine the coordinates
    int x1, y1, x2, y2;
      x1 = GAUGE_CENTER_X + cos(angle) * GAUGE_RADIUS;
      y1 = GAUGE_CENTER_Y - sin(angle) * GAUGE_RADIUS;
      x2 = GAUGE_CENTER_X + cos(angle) * (GAUGE_RADIUS - 4);
      y2 = GAUGE_CENTER_Y - sin(angle) * (GAUGE_RADIUS - 4);

    selectedOLED->drawLine(x1, y1, x2, y2, WHITE);

    if (numbers){
    // Calculate the position for the label
    int xOffset = -2;
    int yOffset = -2;
    float labelRadius = GAUGE_RADIUS - 8;  // Adjust the radius as needed
    int labelX = GAUGE_CENTER_X + cos(angle) * labelRadius + xOffset;
    int labelY = GAUGE_CENTER_Y - sin(angle) * labelRadius + yOffset;
    // Display the first digit of the degree label
    selectedOLED->setCursor(labelX, labelY);
    int range = (rangeMax- rangeMin);
    int firstDigit = getFirstDigit(rangeMin + i * (range / (NUM_GRADUATIONS - 1)));
    selectedOLED->print(firstDigit);
    }
  }

  // Calculate the angle range for the redline
  float redlineAngleStart = DEG_TO_RAD(GAUGE_START_ANGLE + (redlineValue - rangeMin) * gaugeRange / (rangeMax - rangeMin));
  float redlineAngleEnd = DEG_TO_RAD(GAUGE_START_ANGLE + gaugeRange);
  
  // Draw the redline indicator arc
  drawArc(GAUGE_CENTER_X, GAUGE_CENTER_Y, GAUGE_RADIUS - 4, redlineAngleStart, redlineAngleEnd, WHITE, 4); 

  // Calculate the position of the needle tip based on the sensor value
  sensorValue = constrain(sensorValue, rangeMin, rangeMax);
  float needleAngle = DEG_TO_RAD(GAUGE_START_ANGLE + (sensorValue - rangeMin) * gaugeRange / (rangeMax - rangeMin));

  // Determine the coordinates based on clockwise or counterclockwise
  int needleX, needleY, needleX2, needleY2;
    needleX = GAUGE_CENTER_X + cos(needleAngle) * GAUGE_RADIUS;
    needleY = GAUGE_CENTER_Y - sin(needleAngle) * GAUGE_RADIUS;
    needleX2 = GAUGE_CENTER_X + cos(needleAngle) * (GAUGE_RADIUS - 20);
    needleY2 = GAUGE_CENTER_Y - sin(needleAngle) * (GAUGE_RADIUS - 20);

  // Draw the needle
  selectedOLED->drawLine(needleX, needleY, needleX2, needleY2, WHITE);
}

void drawBarGraph(int row, float variable, int decimal, float minVal, float maxVal, float redline, String label) {
  int16_t x1, y1;
  uint16_t w, h;
  char valString[8];
  float displayVariable = variable;

  if ( decimal != 0 ) variable = variable / pow(10, decimal);
  variable = constrain(variable, minVal, maxVal);


  // Calculate dimensions based on row number
  int startY = ((row == 1) ? 0 : SCREEN_HEIGHT / 2) + 5;
  int rectHeight = SCREEN_HEIGHT / 2 - 10;
  
  // Draw rectangle for the bar graph
  selectedOLED->drawRoundRect(0, startY, SCREEN_WIDTH, rectHeight, 5, SSD1306_WHITE);
  
  // Calculate width of filled rectangle based on variable, min, and max values
  int rectWidth = mapFloat(variable, minVal, maxVal, 0.0, SCREEN_WIDTH-4);
  
  // Draw filled rectangle representing the variable
  selectedOLED->fillRoundRect(2, startY+2, rectWidth, rectHeight-4, 3, SSD1306_WHITE);
  
  // Draw redline
  if (redline >= minVal && redline <= maxVal) {
    int redlineX = mapFloat(redline, minVal, maxVal, 0, SCREEN_WIDTH);
    selectedOLED->drawFastVLine(redlineX, startY, rectHeight, SSD1306_INVERSE);
  }
  
  // Display label
  selectedOLED->setTextSize(1);
  selectedOLED->setTextColor(SSD1306_INVERSE);
  selectedOLED->setCursor(5, startY + 7);
  selectedOLED->println(label);

  formatValue(valString, displayVariable, decimal);
  selectedOLED->getTextBounds(valString,0,0,&x1, &y1, &w, &h);
  selectedOLED->setCursor(SCREEN_WIDTH-5-w, startY + 7);
  selectedOLED->println(valString);

}

void drawSmallBarGraph(int row, float variable, int decimal, float minVal, float maxVal, float redline, String label) {
  int16_t x1, y1;
  uint16_t w, h;
  char valString[8];
  float displayVariable = variable;
  
  if ( decimal != 0 ) variable = variable / pow(10, decimal);
  variable = constrain(variable, minVal, maxVal);

  // Calculate dimensions based on row number
  int startY;
  int rectHeight = SCREEN_HEIGHT / 4 - 3;
  
  switch (row) {
    case 1:
      startY = 0;
      break;
    case 2:
      startY = SCREEN_HEIGHT / 4 + 1;
      break;
    case 3:
      startY = SCREEN_HEIGHT / 2 + 1;
      break;
    case 4:
      startY = 3 * SCREEN_HEIGHT / 4 + 1;
      break;
    default:
      // Invalid row number
      return;
  }
  
  // Draw rectangle for the bar graph
  selectedOLED->drawRoundRect(0, startY, SCREEN_WIDTH, rectHeight, 5, SSD1306_WHITE);
  
  // Calculate width of filled rectangle based on variable, min, and max values
  int rectWidth = mapFloat(variable, minVal, maxVal, 0.0, SCREEN_WIDTH-4);
  
  // Draw filled rectangle representing the variable
  selectedOLED->fillRoundRect(2, startY+2, rectWidth, rectHeight-4, 3, SSD1306_WHITE);
  
  // Draw redline
  if (redline >= minVal && redline <= maxVal) {
    int redlineX = map(redline, minVal, maxVal, 0, SCREEN_WIDTH);
    selectedOLED->drawFastVLine(redlineX, startY, rectHeight, SSD1306_INVERSE);
  }
  
  // Display label
  selectedOLED->setTextSize(1);
  selectedOLED->setTextColor(SSD1306_INVERSE);
  selectedOLED->setCursor(5, startY + 3);
  selectedOLED->println(label);

  formatValue(valString, displayVariable, decimal);
  selectedOLED->getTextBounds(valString,0,0,&x1, &y1, &w, &h);
  selectedOLED->setCursor(SCREEN_WIDTH-5-w, startY + 3);
  selectedOLED->println(valString);
}


void customGauge(int customScreenSelect)
{
  int16_t x1, y1;
  uint16_t w, h;
  char valString[8];
  uint8_t currentStat;
  int HVmod;
  uint8_t statNum[] = { 0, 1, 9, 17, 18, 19, 20, 21, 22, 23, 24, 25, 
            26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 
            38, 39, 47, 48, 49, 50, 51, 52, 54, 55, 72, 73,
            74, 75, 76, 77, 78, 84, 89, 90, 91, 92, 93, 94,
            95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105,
            106, 110, 111, 112, 113, 114, 115, 116, 117, 118,
            119, 120, 124, 132, 133, 134, 
            141, 142, 143, 144, 145, 146, 147, 148, 149}; // 84 stats to cycle through on the custom screen
    currentStat = statNum[customScreenSelect];
    String name = speeduino[currentStat].name;
    int number = speeduino[currentStat].number;
    int subNumber = speeduino[currentStat].subNumber;
    int type = speeduino[currentStat].type; // 0=bit / 1=byte / 2=word / 3=two bits / 4 = signed word
    float multiplier = (speeduino[currentStat].multiplier)/10.00;
    int decimal = speeduino[currentStat].decimal;
    selectedOLED->setTextSize(0);
    selectedOLED->setCursor(0, 0);

    if (type != 0 && type != 3) { // if the stats are not a bitfield
        if (multiplier != 0) {
            if (type == 1) formatValue(valString, (getByte(number))*multiplier, decimal);
            if (type == 2) formatValue(valString, (getWord(number))*multiplier, decimal);
            if (type == 4) formatValue(valString, (getSignedWord(number))*multiplier, decimal);
            if (type == 5) formatValue(valString, (*(speeduino[currentStat].calculated)) * multiplier, decimal);
        }
        if (multiplier == 0) {
            if (type == 1) formatValue(valString, ( (getByte(number) + SPEEDUINO_TEMPERATURE_OFFSET ) * SPEEDUINO_TEMPERATURE_MULTIPLIER ) + C_TO_F, decimal);
            if (type == 2) formatValue(valString, ( (getWord(number) + SPEEDUINO_TEMPERATURE_OFFSET ) * SPEEDUINO_TEMPERATURE_MULTIPLIER ) + C_TO_F, decimal);
            if (type == 4) formatValue(valString, ( (getSignedWord(number) + SPEEDUINO_TEMPERATURE_OFFSET ) * SPEEDUINO_TEMPERATURE_MULTIPLIER ) + C_TO_F, decimal);
        }
      if (SCREEN_ROTATION == 0 || SCREEN_ROTATION == 2) {
        selectedOLED->print("CUSTOM GAUGE ");
        if (customScreenSwitch == 0) selectedOLED->println("A");
        if (customScreenSwitch == 1) selectedOLED->println("B");
        selectedOLED->print(name);
        selectedOLED->setFont(&Numbers24pt7b);
        selectedOLED->getTextBounds(valString,0,0,&x1, &y1, &w, &h);
        selectedOLED->setCursor(SCREEN_WIDTH-w-5, SCREEN_HEIGHT-11);
      }
      if (SCREEN_ROTATION == 1 || SCREEN_ROTATION == 3) {
        selectedOLED->println("CUSTOM");
        selectedOLED->print("GAUGE ");
        if (customScreenSwitch == 0) selectedOLED->println("A");
        if (customScreenSwitch == 1) selectedOLED->println("B");
        selectedOLED->println(" ");
        selectedOLED->print(name);
        selectedOLED->setFont(&FreeMono9pt7b);
        selectedOLED->getTextBounds(valString,0,0,&x1, &y1, &w, &h);
        selectedOLED->setCursor(SCREEN_WIDTH-w-4, SCREEN_HEIGHT-h);
      }
    selectedOLED->print(valString);
    selectedOLED->setFont();
    }
    else { // if the stats are a bitfield
      if (SCREEN_ROTATION == 0 || SCREEN_ROTATION == 2) {
        selectedOLED->print("CUSTOM GAUGE ");
        if (customScreenSwitch == 0) selectedOLED->print("A");
        if (customScreenSwitch == 1) selectedOLED->print("B");
        HVmod = 0;
      }
      if (SCREEN_ROTATION == 1 || SCREEN_ROTATION == 3) {
        selectedOLED->println("CUSTOM");
        selectedOLED->print("GAUGE ");
        if (customScreenSwitch == 0) selectedOLED->print("A");
        if (customScreenSwitch == 1) selectedOLED->print("B");
        HVmod = 1;
      }
        for (int i = (1 + HVmod) ; i < (9 + HVmod) ; i++) {
          if (speeduino[currentStat].number == speeduino[currentStat + i - (1+HVmod)].number) {
            uint8_t x, y;
            name = speeduino[currentStat + i - (1+HVmod)].name;
            if ( (SCREEN_ROTATION == 0 || SCREEN_ROTATION == 2) && (i < 5) ) {
                y = i*(SCREEN_HEIGHT/6);
                x = 0;
                }
            if ( (SCREEN_ROTATION == 0 || SCREEN_ROTATION == 2) && (i > 4) ) {
                y = (i-4)*(SCREEN_HEIGHT/6);
                x = SCREEN_WIDTH/2;
                }
            if (SCREEN_ROTATION == 1 || SCREEN_ROTATION == 3) {
                y = i*(SCREEN_HEIGHT/10);
                x = 0;
                }
            selectedOLED->setCursor(x+1, y+1); 
            selectedOLED->print(name);
            selectedOLED->print(" ");
            if ( speeduino[currentStat + i - (1+HVmod)].type == 0 ) formatValue(valString, getBit(number, i- (1+HVmod)), 0);
            if ( speeduino[currentStat + i - (1+HVmod)].type == 3 ) formatValue(valString, getThreeBits(number, i- (1+HVmod)), 0);
            selectedOLED->print(valString);
            selectedOLED->getTextBounds(valString,0,0,&x1, &y1, &w, &h);
            if (getBit(number, i- (1+HVmod)) == 1) selectedOLED->fillRect( x, y, 62, h+1, INVERSE);
            selectedOLED->println(" ");
            }
        }
        selectedOLED->setFont();
    }
    // draw navigation scroll at bottom of screen
    selectedOLED->drawFastHLine(0, SCREEN_HEIGHT-1, SCREEN_WIDTH, INVERSE);
    selectedOLED->drawFastVLine(0, SCREEN_HEIGHT-6, 5, INVERSE);
    selectedOLED->drawFastVLine(SCREEN_WIDTH-1, SCREEN_HEIGHT-6, 5, INVERSE);
    selectedOLED->drawFastVLine( ((customScreenSelect/(CUSTOM_SCREEN_PAGE_COUNT*1.0))*(SCREEN_WIDTH-2))+1, SCREEN_HEIGHT-6, 5, INVERSE);
}

void errorPopUp(bool ECU, bool SD) // display error popups if EDU and/or SD Card aren't present
{
  int16_t x1, y1;
  uint16_t w, h;
  String noECU = "NO ECU";
  String noSD = "NO SD";
  int vertOffset;

  selectedOLED->setFont();
  selectedOLED->getTextBounds(noECU,0,0,&x1, &y1, &w, &h);
  if (!ECU && !SD) vertOffset = (h+2)/2;
  else vertOffset = 0;

  if (!ECU) {
  selectedOLED->getTextBounds(noECU,0,0,&x1, &y1, &w, &h);
  selectedOLED->fillRect(((SCREEN_WIDTH-w)/2)-1, ((SCREEN_HEIGHT-h)/2)-1-vertOffset, w+1, h+1, WHITE);
  selectedOLED->setCursor((SCREEN_WIDTH-w)/2, ((SCREEN_HEIGHT-h)/2)-vertOffset);
  selectedOLED->setTextSize(1);
  selectedOLED->setTextColor(INVERSE);
  selectedOLED->print("NO ECU");
  }

  if (!SD) {
  selectedOLED->getTextBounds(noSD,0,0,&x1, &y1, &w, &h);
  selectedOLED->fillRect(((SCREEN_WIDTH-w)/2)-1, ((SCREEN_HEIGHT-h)/2)-1+vertOffset, w+1, h+1, WHITE);
  selectedOLED->setCursor((SCREEN_WIDTH-w)/2, ((SCREEN_HEIGHT-h)/2)+vertOffset);
  selectedOLED->setTextSize(1);
  selectedOLED->setTextColor(INVERSE);
  selectedOLED->print("NO SD");
  }
}

int getFirstDigit(int number) {
  while (number >= 100) {
    number = number/10;
  }
  return number / 10;
}

void drawArc(int centerX, int centerY, int radius, float startAngle, float endAngle, uint16_t color, int numSegments) {
   // calculate segments based on radius of arc
   if (numSegments == 0) numSegments = radius/4;

  // Calculate the angular distance between each segment
  float angleStep = (endAngle - startAngle) / numSegments;

  // Draw each segment of the arc
  for (int i = 0; i < numSegments; i++) {
    float angle = startAngle + i * angleStep;

    // Calculate the coordinates of the current segment
    int x1 = centerX + cos(angle) * radius;
    int y1 = centerY - sin(angle) * radius;
    int x2 = centerX + cos(angle + angleStep) * radius;
    int y2 = centerY - sin(angle + angleStep) * radius;

    // Draw a line segment between the coordinates
    selectedOLED->drawLine(x1, y1, x2, y2, color);
  }
}

uint8_t formatValue(char *buf, int32_t value, uint8_t decimal)
{
  clearBuffer(buf);
  snprintf(buf, 22, "%d", value);
  uint8_t len = strlen(buf);

  if (decimal != 0)
  {
    uint8_t target = decimal + 1;
    uint8_t numLen = len - ((value < 0) ? 1 : 0);
    while (numLen < target)
    {
      for (uint8_t i = 0; i < numLen + 1; i++)
      // if negative, skip negative sign
      {
        buf[len - i + 1] = buf[len - i];
        buf[len - i] = '0';
      }
      buf[len + 1] = '\0';
      numLen++;
      len++;
    }
    // insert
    for (uint8_t i = 0; i < decimal + 1; i++)
    {
      buf[len - i + 1] = buf[len - i];
      buf[len - i] = '.';
    }
  }
  return strlen(buf);
}

void clearBuffer(char *buf, uint8_t bufLen)
{
  for (uint8_t i = 0; i < bufLen; i++)
  {
    buf[i] = '\0';
  }
}

float easing(float currentValue, float targetValue, float easingFactor, int totalSteps, int currentStep) {
  if (currentStep <= 0) {
    return currentValue; // No change if currentStep is 0 or negative
  } else if (currentStep >= totalSteps) {
    return targetValue; // Reached target value if currentStep is greater than or equal to totalSteps
  } else {
    float t = (float)currentStep / totalSteps; // Normalized time (0.0 to 1.0)
    float tSquared = t * t;
    float tCubed = tSquared * t;
    float easeIn = 2 * tCubed - 3 * tSquared + 1; // Ease-in formula
    float easeOut = 1 - easeIn; // Ease-out formula

    // Calculate the eased value between currentValue and targetValue
    float easedValue = currentValue + (targetValue - currentValue) * (easeIn * (1 - easingFactor) + easeOut * easingFactor);

    return easedValue;
  }
}

void cropLineToRange(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t minY, int16_t maxY) {
  // Check if the line is completely outside the range
  if ((y1 <= minY && y2 <= minY) || (y1 >= maxY && y2 >= maxY)) {
    // Line is completely outside the range, no need to draw anything
    return;
  }

  // Clip the line to the specified range
  if (y1 < minY) {
    float slope = static_cast<float>(y2 - y1) / (x2 - x1);
    x1 += static_cast<int16_t>((minY - y1) / slope);
    y1 = minY;
  }
  if (y2 < minY) {
    float slope = static_cast<float>(y2 - y1) / (x2 - x1);
    x2 += static_cast<int16_t>((minY - y2) / slope);
    y2 = minY;
  }
  if (y1 > maxY) {
    float slope = static_cast<float>(y2 - y1) / (x2 - x1);
    x1 += static_cast<int16_t>((maxY - y1) / slope);
    y1 = maxY;
  }
  if (y2 > maxY) {
    float slope = static_cast<float>(y2 - y1) / (x2 - x1);
    x2 += static_cast<int16_t>((maxY - y2) / slope);
    y2 = maxY;
  }
  selectedOLED->drawLine(x1, y1  , x2, y2 , WHITE); 
}

void drawPartialBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int16_t width, int16_t height, uint8_t numColumns) {
  int16_t byteWidth = (width + 7) / 8;

  for (int16_t j = 0; j < height; j++) {
    for (int16_t i = 0; i < numColumns; i++) {
      if (x + i >= 0 && x + i < SCREEN_WIDTH && y + j >= 0 && y + j < SCREEN_HEIGHT) {
        uint8_t byte = pgm_read_byte(bitmap + j * byteWidth + i / 8);
        uint8_t bit = byte & (128 >> (i % 8));
        if (bit != 0) {
          selectedOLED->drawPixel(x + i, y + j, WHITE);
        }
      }
    }
  }
}

// Reset function A
void resetAverageMPGa() {
  totalCountMPHa = 0;
  sumMPHa = 0;
  averageMPHa = 0;
  tripDistanceA = 0;
  tripGallonsUsedA = 0.0;  // Total gallons used for MPGa calc
  Serial.println("Reset Trip A");
}

// Reset function B
void resetAverageMPGb() {
  totalCountMPHb = 0;
  sumMPHb = 0;
  averageMPHb = 0;
  tripDistanceB = 0;
  tripGallonsUsedB = 0.0;  // Total gallons used for MPGa calc
  Serial.println("Reset Trip B");
}

// Update average function
void updateAverageMPG() {
      if (tripDistanceA != 0 && tripGallonsUsedA != 0) { averageMPGa =   ( tripDistanceA * 10 ) / tripGallonsUsedA; }
        else averageMPGa = 0;
      if (tripDistanceB != 0 && tripGallonsUsedB != 0) { averageMPGb =   ( tripDistanceB * 10 ) / tripGallonsUsedB; }
        else averageMPGb = 0;
}

// Update average function
void updateAverageMPH(int number) {
  number = abs(number);
  if ( number != 0) {
      averageMPHa = sumMPHa * 1.0 / totalCountMPHa;
      averageMPHb = sumMPHb * 1.0 / totalCountMPHb;
        if (totalCountMPHa == 1) {
            sumMPHa = number;
          } else {
            sumMPHa += number;
          }
        if (totalCountMPHb == 1) {
            sumMPHb = number;
          } else {
            sumMPHb += number;
          }
      totalCountMPHa++;
      totalCountMPHb++;
      }
}

int getDigitFromInteger(int number, int position) {
  if (position >= 0) {
    int divisor = 1;
    for (int i = 0; i < position; i++) {
      divisor *= 10;
    }
    
    int digit = (number / divisor) % 10; // Extract the digit at the specified position
    return digit;
  } else {
    // Invalid position
    return -1; // You can choose to return an error code or handle it differently
  }
}

int setDigitInInteger(int number, int position, int newDigit) {
  if (position >= 0) {
    int divisor = 1;
    for (int i = 0; i < position; i++) {
      divisor *= 10;
    }
    
    int quotient = number / divisor; // Extract digits to the left of the position
    int remainder = number % (divisor / 10); // Extract digits to the right of the position
    int modifiedNumber = (quotient * 10 + newDigit) * (divisor / 10) + remainder;
    
    return modifiedNumber;
  } else {
    // Invalid position
    return number; // Return the original number since no modification is done
  }
}

// Settings
void settingsPage() {
  String name;

  char valString[1];
  int16_t x1, y1;
  uint16_t w, h;
  int16_t xA, yA, xB, yB;
  uint8_t j, k, var;

    selectedOLED->setTextColor(INVERSE);
    selectedOLED->setTextSize(0);
    selectedOLED->setCursor(1, 1); 
    selectedOLED->println("SETTINGS");

  for (int i = 1; i < 11; i=i) { // total number of settings = 8+1 = 9
            static uint8_t r = 0;
            uint8_t x, y;

            if ( (SCREEN_ROTATION == 0 || SCREEN_ROTATION == 2) && (i < 6) ) {
              y = (i*(SCREEN_HEIGHT/6))+2;
              x = 0+r;
              }
            if ( (SCREEN_ROTATION == 0 || SCREEN_ROTATION == 2) && (i > 5) ) {
              y = ((i-5)*(SCREEN_HEIGHT/6))+2;
              x = (SCREEN_WIDTH/2)+r;
              }
            if (SCREEN_ROTATION == 1 || SCREEN_ROTATION == 3) {
              y = (i*(SCREEN_HEIGHT/11))+2;
              x = 1+r;
              }
            selectedOLED->setCursor(x+1, y+1); 

            name = settingsScreen[k].name;
            selectedOLED->print(name);
            while ( j == 0 || settingsScreen[k+j].number == settingsScreen[k+j-1].number ) {

                    if (settingsScreen[k+j].type == INT_8) {
                        uint8_t value8 = *(static_cast<uint8_t*>(settingsScreen[k+j].pointer));
                        var = getDigitFromInteger( value8, settingsScreen[k+j].subNumber);
                    }
                    if (settingsScreen[k+j].type == INT_16) {
                        uint16_t value16 = *(static_cast<uint16_t*>(settingsScreen[k+j].pointer));
                        var = getDigitFromInteger( value16, settingsScreen[k+j].subNumber);
                    }
                    if (settingsScreen[k+j].type == INT_32) {
                        uint32_t value32 = *(static_cast<uint32_t*>(settingsScreen[k+j].pointer));
                        var = getDigitFromInteger( value32, settingsScreen[k+j].subNumber);
                    }

                    formatValue(valString, var , 0);
                    selectedOLED->getTextBounds(valString,0,0,&x1, &y1, &w, &h);
                    selectedOLED->print(valString);
                    x1 = selectedOLED->getCursorX()-w;
                    y1 = selectedOLED->getCursorY();
                    if (settingsSelect == k+j) selectedOLED->fillRect( x1, y1, w, h+1, INVERSE);
              
              if ( settingsScreen[k+j].CR == 0 )  r = selectedOLED->getCursorX();
              if ( settingsScreen[k+j].CR == 1 ) {
                i++;
                r = 0;
                }
              j++;
            }
            k = j+k;
            j = 0;
    }

    if (settingsAdd == 1) {
                    if (settingsScreen[settingsSelect].number <= 6) clockSetFlag = 1; // the time has been changed
                    if (settingsScreen[settingsSelect].number >= 7) settingsFlag = 1; // a non-clock setting has been changed
                    if (settingsScreen[settingsSelect].type == INT_8) {
                        uint8_t* intPtr = static_cast<uint8_t*>(settingsScreen[settingsSelect].pointer);
                        if (intPtr != nullptr) {
                          if ( settingsScreen[settingsSelect].max == getDigitFromInteger( *intPtr, settingsScreen[settingsSelect].subNumber)) {
                                (*intPtr) -= (settingsScreen[settingsSelect].max * settingsScreen[settingsSelect].multiplier);
                          }
                          else {
                            var++;
                            (*intPtr) += (settingsScreen[settingsSelect].multiplier);
                          }
                        }
                    }
                    if (settingsScreen[settingsSelect].type == INT_16) {
                        uint16_t* intPtr = static_cast<uint16_t*>(settingsScreen[settingsSelect].pointer);
                        if (intPtr != nullptr) {
                          if ( settingsScreen[settingsSelect].max == getDigitFromInteger( *intPtr, settingsScreen[settingsSelect].subNumber)) {
                                (*intPtr) -= (settingsScreen[settingsSelect].max * settingsScreen[settingsSelect].multiplier);
                          }
                          else {
                            var++;
                            (*intPtr) += (settingsScreen[settingsSelect].multiplier);
                          }
                        }
                    }
                    if (settingsScreen[settingsSelect].type == INT_32) {
                        uint32_t* intPtr = static_cast<uint32_t*>(settingsScreen[settingsSelect].pointer);
                        if (intPtr != nullptr) {
                          if ( settingsScreen[settingsSelect].max == getDigitFromInteger( *intPtr, settingsScreen[settingsSelect].subNumber)) {
                                (*intPtr) -= (settingsScreen[settingsSelect].max * settingsScreen[settingsSelect].multiplier);
                          }
                          else {
                            var++;
                            (*intPtr) += (settingsScreen[settingsSelect].multiplier);
                          }
                        }
                    }

    } 

    settingsAdd = 0;

    selectedOLED->setFont();
}

void drawAnalogClock(int hour, int minute, int second, int x, int y, int faceDiameter) {
  int centerX = x;
  int centerY = y;
  int hourLength = faceDiameter / 2 * 0.5;
  int minuteLength = faceDiameter / 2 * 0.7;
  int secondLength = faceDiameter / 2 * 0.9;

  selectedOLED->drawCircle(centerX, centerY, faceDiameter / 2, WHITE);

  // Draw gradations for each hour
  for (int i = 0; i < 12; i++) {
    float angle = map(i, 0, 12, 0, 360) - 90;
    float radian = DEG_TO_RAD(angle);
    int x1 = centerX + cos(radian) * (faceDiameter / 2 - 2);
    int y1 = centerY + sin(radian) * (faceDiameter / 2 - 2);
    int x2 = centerX + cos(radian) * (faceDiameter / 2 - 6);
    int y2 = centerY + sin(radian) * (faceDiameter / 2 - 6);
    selectedOLED->drawLine(x1, y1, x2, y2, WHITE);
  }

  // Calculate the angles for the hands
  float secondAngle = map(second, 0, 60, 0, 360) - 90;
  float minuteAngle = map(minute, 0, 60, 0, 360) - 90;
  
  // Calculate the hour angle considering both hour and minute
  float hourAngle = map(hour % 12, 0, 12, 0, 360) - 90 + minute * 0.5; // Move hour hand by 0.5 degrees for each minute

  // Calculate the positions of the hands
  int secondX = centerX + cos(DEG_TO_RAD(secondAngle)) * secondLength;
  int secondY = centerY + sin(DEG_TO_RAD(secondAngle)) * secondLength;
  int minuteX = centerX + cos(DEG_TO_RAD(minuteAngle)) * minuteLength;
  int minuteY = centerY + sin(DEG_TO_RAD(minuteAngle)) * minuteLength;
  int hourX = centerX + cos(DEG_TO_RAD(hourAngle)) * hourLength;
  int hourY = centerY + sin(DEG_TO_RAD(hourAngle)) * hourLength;

  // Draw clock hands
  selectedOLED->drawLine(centerX, centerY, secondX, secondY, WHITE);
  selectedOLED->drawLine(centerX, centerY, minuteX, minuteY, WHITE);
  selectedOLED->drawLine(centerX, centerY, hourX, hourY, WHITE);
}


// Function to print the date in the specified format
void printFormattedDate(int day, int month, int year, const String& dayOfWeek, int Xpos, int Ypos) {
  int16_t x1, y1;
  uint16_t w, h;

  // Array of month names
  String monthNames[] = {"", "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
  
  // Convert the full day name to uppercase and get the first three letters
  String shortDayOfWeek = dayOfWeek.substring(0, 3);
  shortDayOfWeek.toUpperCase();

  // Check for valid month
  if (month < 1 || month > 12) {
    Serial.println("Invalid month.");
    return;
  }

  // Print the formatted date
  selectedOLED->setTextColor(INVERSE);
  selectedOLED->setFont(&FreeMono9pt7b);

  selectedOLED->getTextBounds(shortDayOfWeek,0,0,&x1, &y1, &w, &h);
  selectedOLED->setCursor( Xpos - (w/2) -1 , Ypos );
  selectedOLED->println(shortDayOfWeek);

  selectedOLED->getTextBounds(monthNames[month],0,0,&x1, &y1, &w, &h);
  selectedOLED->setCursor( Xpos - (w/2) , Ypos + 17);
  selectedOLED->println(monthNames[month]);

  String Day = String(day);
  selectedOLED->getTextBounds(Day,0,0,&x1, &y1, &w, &h);
  selectedOLED->setCursor( Xpos - ((w+16+13)/2) , Ypos + 34);
  selectedOLED->print(String(day));
  selectedOLED->fillRect(Xpos - ((w+16+13)/2) + w + 8, Ypos + (h * 2) + 8, 2, 2, WHITE);
  showMoon(Xpos - ((w+16+13)/2) + w + 16, Ypos + (h * 2) + 1);
  selectedOLED->setFont();
}

void showMoon(int xPos, int yPos) {
  selectedOLED->drawBitmap(xPos, yPos, epd_bitmap_allArray[lunarProgress()], 13, 13, WHITE);
}