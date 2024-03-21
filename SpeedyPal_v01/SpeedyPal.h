#define STRING_LENGTH 8

// pages info
#define LAST_PAGE 7 // number for last page of gauges
#define SETTINGS_PAGE 8 // 
#define CUSTOM_PAGE 9 //
#define SETTINGS_LINES 10 // number of lines on settings page
#define SETTINGS_NUMBER 29 // number of selectable elements on settings page

// number of stats for the Custom Page
#define CUSTOM_SCREEN_PAGE_COUNT 84

// button times
#define MEDIUM_PRESS 1000
#define LONG_PRESS 2000
#define PRESS_DELAY 500
#define DOUBLE_CLICK 250

#define SHIFTLIGHT_OFF_RPM SHIFTLIGHT_ON_RPM - 100  // Turn off shift light under this threshold

#define SPEEDUINO_TEMPERATURE_OFFSET -40
#define SPEEDUINO_TEMPERATURE_MULTIPLIER 1.8 // 1 for C, 1.8 for F
#define C_TO_F 32 // 32 for F, 0 for C