#include <RTClib.h>

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday"
};

void setupClock () {
  // SETUP RTC MODULE 0x68
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    // Serial.flush();
    // while (1);
  }
  if (rtc.begin()) Serial.println("RTC Clock Connected");
}

bool RTCconnected() {
  if (isDeviceConnected(0X68)) return 1;
  else  return 0;
}

void displayTime () {
  DateTime now = rtc.now();
  Serial.print("Date & Time: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);
}

void displayVariableTime () {
  Serial.print("Date & Time Variables: ");
  Serial.print(year);
  Serial.print('/');
  Serial.print(month);
  Serial.print('/');
  Serial.print(day);
  Serial.print(" (");
  Serial.print(dayWeek);
  Serial.print(") ");
  Serial.print(hour);
  Serial.print(':');
  Serial.print(minute);
  Serial.print(':');
  Serial.println(second);
}

void updateTimeVariables () {
  DateTime now = rtc.now();
  year = now.year();
  month = now.month();
  day = now.day();
  dayWeek = daysOfTheWeek[now.dayOfTheWeek()];
  hour = now.hour();
  minute = now.minute();
  second = now.second();
}

void checkTimeVariables () {
    if (hour < 1) hour = 1;
    if (hour > 23) hour = 20;
    if (minute > 59) minute = 50;
    if (second > 59) second = 50;
    if (month < 1) month = 1;
    if (month > 12) month = 10;
    if (day < 1) day = 1;
    if (day > getMaxDaysInMonth(month,year)) day = 1;
}

int getMaxDaysInMonth(int month, int year) {
    if (month == 2) {
        // February
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            // Leap year, February has 29 days
            return 29;
        } else {
            // Non-leap year, February has 28 days
            return 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        // Months with 30 days
        return 30;
    } else {
        // Months with 31 days
        return 31;
    }
}

void setTime(int yr, int mth, int dy, int hr, int min, int sec) {
  rtc.adjust(DateTime(yr, mth, dy, hr, min, sec));
}

// Function to calculate the progress from new moon to almost new moon
int lunarProgress() {
    // Date of the last new moon (example date)
    DateTime lastNewMoon(2024, 2, 11, 0, 0, 0);  // Replace this with the actual last new moon date

    DateTime now = rtc.now(); // Get current date and time from RTC
    // Calculate the current phase
    int daysSinceNewMoon = (now.unixtime() - lastNewMoon.unixtime()) / 86400; // 86400 seconds in a day
    float lunarPhase = fmod(static_cast<float>(daysSinceNewMoon), 29.53f) / 29.53f;  // Normalize to the lunar cycle

    // Map the lunar phase to the progress scale (0-25)
    int progress = ((int)(lunarPhase * 26) + 2 ) % 26;

    return progress;
}