void buttonCheck() {
  static uint32_t RbtnPressed = 0;
  static uint32_t RbtnStartTime = 0;
  static long RbtnLastPressed = 0;
  static uint32_t LbtnPressed = 0;
  static uint32_t LbtnStartTime = 0;
  static long LbtnLastPressed = 0;

  // Left Button Visual Indicators
  if (LbtnPressed) {
  if ( ( millis() - LbtnStartTime ) > MEDIUM_PRESS && ( millis() - LbtnStartTime ) <= LONG_PRESS) buttonIndicator(0,0);
  if ( ( millis() - LbtnStartTime ) > LONG_PRESS ) buttonIndicator(0,1);
  }

  // Left Button Logic
  if (!digitalRead(ButtonPinL)) { // Button is pressed
    digitalWrite(ledPin, LOW);
    if (LbtnPressed == 0) {
      LbtnPressed = millis(); // start timer
      LbtnStartTime = millis(); // record start time for the button press
    }
  } else {
    if (LbtnPressed) {
      digitalWrite(ledPin, HIGH);
      LbtnLastPressed = millis(); // remember when the Left Button was last pressed
      uint32_t LbtnDuration = millis() - LbtnStartTime; // calculate the duration of the button press
      // Check for long press (1 second or more)
      if (LbtnDuration >= MEDIUM_PRESS) {
        if (LbtnDuration >= LONG_PRESS) {
          // 2 - second action
          if ( ( millis() - RbtnStartTime ) >= LONG_PRESS && RbtnPressed) {
            if (pageNum == SETTINGS_PAGE) {
            Serial.println("2-second both buttons press 1");
            pageNum = 0;
            RbtnPressed = 0;
            }
            else { 
            Serial.println("2-second both buttons press 2");
            pageNum = SETTINGS_PAGE;
            RbtnPressed = 0;
            }
          }
          else if (pageNum == SETTINGS_PAGE || pageNum == CUSTOM_PAGE) {
            Serial.println("2-second left button press 1");
            if ( pageNum == CUSTOM_PAGE && customScreenSwitch == 1) {
              customScreenSwitch = 0;
              customScreenSelect = customScreenSelectA;
              }
            else pageNum = 0;
          }
          else if (!RbtnPressed) {
            Serial.println("2-second left button press CustomA");
            customScreenSwitch = 0;
            customScreenSelect = customScreenSelectA;
            pageNum = CUSTOM_PAGE;
          }
        } else {
          // 1 - second action
          Serial.println("1-second left button press - reset A");
          resetAverageMPGa();
        }
      } else {
        // Short press
            Serial.println("short left button press");
            if ( ( millis() - RbtnLastPressed ) < DOUBLE_CLICK ) {
                markerFlag = true; // if both buttons are pressed quickly, add a marker to the log
                Serial.println("Both buttons short-pressed. Left routine.");
            }
            if (pageNum == CUSTOM_PAGE) {
              if (customScreenSwitch == 0) {
                if (customScreenSelectA == 0) {
                customScreenSelectA = CUSTOM_SCREEN_PAGE_COUNT-1;
                }
                else {
                customScreenSelectA--; // constrains value between 0 and CUSTOM_SCREEN_PAGE_COUNT
                }
                Serial.print("customScrteenSelectA: ");
                Serial.println(customScreenSelectA);
                customScreenSelect = customScreenSelectA;
              }
              if (customScreenSwitch == 1) {
                if (customScreenSelectB == 0) {
                customScreenSelectB = CUSTOM_SCREEN_PAGE_COUNT-1;
                }
                else {
                  customScreenSelectB--; // constrains value between 0 and CUSTOM_SCREEN_PAGE_COUNT
                }
                Serial.print("customScrteenSelectB: ");
                Serial.println(customScreenSelectB);
                customScreenSelect = customScreenSelectB;
              }
            } 
            else if (pageNum == SETTINGS_PAGE) {
                settingsAdd = 1;
              }
            else if (pageNum == 0) {
              pageNum = LAST_PAGE;
              }
            else pageNum--; // constrains value between 0 and LAST_PAGE
      }
    }
    LbtnPressed = 0;
  }    

  // Right Button visual indicators  
  if (RbtnPressed) {
  if ( ( millis() - RbtnStartTime ) > MEDIUM_PRESS && ( millis() - RbtnStartTime ) <= LONG_PRESS) buttonIndicator(1,0);
  if ( ( millis() - RbtnStartTime ) > LONG_PRESS ) buttonIndicator(1,1);
  }

  // Right Button Logic
  if (!digitalRead(ButtonPinR)) { // Button is pressed
    digitalWrite(ledPin, LOW);
    if (RbtnPressed == 0) {
      RbtnPressed = millis(); // start timer
      RbtnStartTime = millis(); // record start time for the button press
    }
  } else {
    if (RbtnPressed) {
      digitalWrite(ledPin, HIGH);
      RbtnLastPressed = millis(); // remember when the Right Button was last pressed
      uint32_t RbtnDuration = millis() - RbtnStartTime; // calculate the duration of the button press
      // Check for long press (1 second or more)
      if (RbtnDuration >= MEDIUM_PRESS) {
        if (RbtnDuration >= LONG_PRESS) {
          // 2 - second action
          if ( ( millis() - LbtnStartTime ) >= LONG_PRESS && LbtnPressed) {
            if (pageNum == SETTINGS_PAGE) {
            Serial.println("2-second both buttons press 3");
            pageNum = 0;
            LbtnPressed = 0;
            }
            else {
            Serial.println("2-second both buttons press 4");
            pageNum = SETTINGS_PAGE;
            LbtnPressed = 0;
            }
          }
          else if (pageNum == SETTINGS_PAGE || pageNum == CUSTOM_PAGE) {
            Serial.println("2-second right button press 1");
            if ( pageNum == CUSTOM_PAGE && customScreenSwitch == 0) {
              customScreenSwitch = 1;
              customScreenSelect = customScreenSelectB;
              }
            else pageNum = 0;
          }
          else if (!LbtnPressed) {
            Serial.println("2-second right button press CustomB");
            customScreenSwitch = 1;
            customScreenSelect = customScreenSelectB;
            pageNum = CUSTOM_PAGE;
          }
        } else {
          // 1 - second action
          Serial.println("1-second right button press - reset B");
          resetAverageMPGb();
        }
      } else {
        // Short press
            Serial.println("short right button press");
            if ( ( millis() - LbtnLastPressed ) < DOUBLE_CLICK ) {
                markerFlag = true; // if both buttons are pressed quickly, add a marker to the log
                Serial.println("Both buttons short-pressed. Right routine.");
            }
            if (pageNum == CUSTOM_PAGE) {
              if (customScreenSwitch == 0) {
                customScreenSelectA = (customScreenSelectA + 1) % ( CUSTOM_SCREEN_PAGE_COUNT ); // constrains value between 0 and CUSTOM_SCREEN_PAGE_COUNT
                Serial.print("customScrteenSelectA: ");
                Serial.println(customScreenSelectA);
                customScreenSelect = customScreenSelectA;
              }
              else {
                customScreenSelectB = (customScreenSelectB + 1) % ( CUSTOM_SCREEN_PAGE_COUNT ); // constrains value between 0 and CUSTOM_SCREEN_PAGE_COUNT
                Serial.print("customScrteenSelectB: ");
                Serial.println(customScreenSelectB);
                customScreenSelect = customScreenSelectB;
              }
            }
            else if (pageNum == SETTINGS_PAGE) {
              settingsSelect = (settingsSelect + 1) % ( SETTINGS_NUMBER + 1 );
            }
            else {
              pageNum = (pageNum + 1) % ( LAST_PAGE + 1 ); // constrains value between 0 and LAST_PAGE
            }
      }
    }
    RbtnPressed = 0;
  }
}

// grabStats function grabs the values from Speeduino and assigns them to variables used by the gauge
// it's also a place to calculate custom stats
void grabStats()
{
  // variables for standard stats from Speeduino
  // Some variables are multiplied by "10" so they can be stored as ints rather than floats
  // they'll be divided by 10 when displayed
  clt = statGrab(SPEEDUINO_CLT_BYTE);
  iat = statGrab(SPEEDUINO_IAT_BYTE);
  bat = statGrab(SPEEDUINO_VOLTAGE_BYTE)*10;
  baro = statGrab(SPEEDUINO_BARO_BYTE);
  afr = statGrab(SPEEDUINO_AFR_BYTE)*10;
  afrT = statGrab(SPEEDUINO_AFRTARGET_BYTE)*10;
  adv = statGrab(SPEEDUINO_ADVANCE);
  MAP = statGrab(SPEEDUINO_MAP_WORD);
  pw = statGrab(SPEEDUINO_PW1_WORD)*10;
  rpm = statGrab(SPEEDUINO_RPM_WORD);
  tps = statGrab(SPEEDUINO_TPS_BYTE)*10;

  mph = (statGrab(SPEEDUINO_VSS_WORD)/1.609344); // convert kph to mph
  noPeakMPH(); //  smooth out VSS signal by cutting off peaks
  mph = smoothNum( mph, smoothMPH, 0); //  smooth out VSS signal by averaging several recent readings
  updateAverageMPH(mph); // add current mph to average mph information
  calculateDistance(mph); // calculate distance covered given mph

  // calculate acceleration  
  acceleration = calculateAcceleration(mph);
  // smooth out acceleration (acceleration can be prett jumpy, might mess up HP and TRQ if it's passed along before filtering)
  acceleration = smoothNum( acceleration, smoothPerf, 1);

  // calculate performance data
  horsepower = calculateHorsepower( acceleration , mph, weightKg , frontalArea, dragCoefficient, iat, baro);
  torque = calculateTorque(horsepower, rpm);
  // smooth performance data
  horsepower = smoothNum( horsepower, smoothPerf, 2);
  torque = smoothNum( torque, smoothPerf, 3);

  // track acceleration times
  timeTo30 = calculateTimeTo30(mph, tps);
  timeTo60 = calculateTimeTo60(mph, tps);

  mpgCalc(); // calculate MPG from fuel usage and distance travelled
  updateAverageMPG(); // updates "averageMPG" stat
}

void noPeakMPH() {
  static float lastVar = 0;
  if (mph > lastVar + ((10-smoothMPH )/2) ) mph = lastVar + ((10-smoothMPH )/2); // limits the positive change possible for MPH per cycle. 10mph with 1 smoothing, 1mph with 10 smoothing.
  if (mph < lastVar - ((10+smoothMPH )/2) ) mph = lastVar - ((10+smoothMPH )/2); // limits the negative change possible for MPH per cycle 10mph with 1 smoothing, 1mph with 10 smoothing.
  if (mph < 0) mph = 0;
  lastVar = mph;
}

// Takes a number and averages it with the previous number (set by smoothing) of readings of that number
float smoothNum(float Var, int smoothing, int whichVar) {
  static float varArray[4][10];  // variables go here
  static int counter[4]; //  our place in the array
  float average = 0; // average of numbers
  smoothing = smoothing + 1;

  varArray[whichVar][counter[whichVar]] = Var;
  counter[whichVar] = (counter[whichVar] + 1) % smoothing;

  for (int i = 0; i < smoothing; i++) {
    average += varArray[whichVar][i];
  }
  average = average / (smoothing*1.0);

  return average;
}


void calculateDistance(int speedMph) {  // Function to calculate distance covered based on speed in mph
  static unsigned long previousMillis = 0; 
  unsigned long currentMillis = millis();  // Get the current time
  unsigned long elapsedTime = currentMillis - previousMillis;  // Calculate the time elapsed since the last call
  float elapsedTimeHours = (float)elapsedTime / 3600000.0;  // Convert time from milliseconds to hours (3600000 milliseconds in an hour)
  float distance = (float)speedMph * elapsedTimeHours;  // Calculate the distance covered using distance = speed × time
  tripDistanceA += distance;  // Add the calculated distance to the trip distance covered
  tripDistanceB += distance;  // Add the calculated distance to the trip distance covered
  thousandthsCounter += distance; // Add the calculated distance to the total distance covered
  if  (thousandthsCounter >= 0.01) {   // add 0.01 to the odometer every time the distance ticks up
    odometer = odometer + 1;
    odometerFloat = odometer;
    thousandthsCounter = thousandthsCounter - 0.01;
  }
  previousMillis = currentMillis;  // Update the previousMillis for the next call
}

float calculateAcceleration(float currentSpeed) {
    static float previousSpeed = 0; // Previous speed in mph, initialized once
    static unsigned long previousTime = 0; // Previous time in milliseconds, initialized once
    float acceleration = 0; // Acceleration in mph/s

    unsigned long currentTime = millis(); // Get the current time in milliseconds

    // Calculate time elapsed since the previous calculation
    unsigned long timeElapsed = currentTime - previousTime;

    if (timeElapsed > 0) {
        // Calculate acceleration using the formula: acceleration = change in speed / time
        acceleration = ( (currentSpeed - previousSpeed) / ( timeElapsed / 1000.0 ) ); // Conversion for mph/s

        // Update previous speed and time for the next calculation
        previousSpeed = currentSpeed;
        previousTime = currentTime;

        return acceleration;
    }
    else return 0;
}

float calculateHorsepower( float accelerationMPHPS, float speedMPH, float vehicleWeightKg, float frontalAreaSqM, float dragCoefficient, float airTemperatureFahrenheit, float barometricPressure) {
  const float standardTemperatureKelvin = 273.15; // Standard temperature in Kelvin (0°C)
  const float specificGas = 287.05; // Specific gas constant for dry air
  const float MPH_TO_MPS = 0.44704;
  const float WATTS_TO_HORSEPOWER = 745.7;

  // Convert speed to m/s
  float speedMPS = speedMPH * MPH_TO_MPS;

  // Convert acceleration to m/s^2
  float accelMPS2 = accelerationMPHPS * MPH_TO_MPS;

  // for INERTIA
  // calculate power from inertia into watts 
  float powerInertia = vehicleWeightKg * accelMPS2 * speedMPS;

  // for AERO

  // Convert Fahrenheit to Celsius
  float airTemperatureCelsius = (airTemperatureFahrenheit - 32.0) * 5.0 / 9.0;

  // Convert Celsius to Kelvin
  float temperatureKelvin = airTemperatureCelsius + standardTemperatureKelvin;

  // Calculate air density based on temperature and pressure (in Kg per cubic Meter)
  float airDensity = ( ( barometricPressure * 1000 ) / ( specificGas * temperatureKelvin ) );

  // Calculate force due to aerodynamic drag (in Newtons)
  float velocityMS = speedMPS; // Speed in meters per second

  // Drag Force in Newtons
  float dragForce = 0.5 * airDensity * frontalAreaSqM * dragCoefficient * velocityMS * velocityMS;

  // Calculate power to overcome aerodynamic drag (in watts)
  float powerAero = dragForce * velocityMS;

  // total HP
  float horsepowerOut = ( powerAero + powerInertia ) / 746.0; // 1 horsepower = 746 watts
    
  return horsepowerOut;
}

float calculateTorque(float horsepower, float RPM) {
    const float TORQUE_CONSTANT = 5252.0;

    // Calculate torque using the formula: Torque = (Horsepower * TORQUE_CONSTANT) / RPM
    if ( rpm > 0 ) {
    float torqueOut = (horsepower * TORQUE_CONSTANT) / RPM;
    return torqueOut;
    }
    else return 0;
}

int calculateTimeTo30(float speedMPH, int throttlePosition) {
    throttlePosition = throttlePosition/10;
    static unsigned long startTime = 0;
    static unsigned long endTime = 0;
    static bool timing = false;
    static int prevRun = 0;
    static int tempRun = 0;
    const int thresholdTPS = 5;  // Throttle position sensor threshold

    // if the speed is less than 3mph and the TPS is over the threshold, start timing.
    if (speedMPH < 3 && throttlePosition > thresholdTPS && !timing) {
        startTime = millis();
        timing = true;
        // Serial.println("Start 0 to 30 Run");
    }

    // if we're not moving and the timing has been going for more than a second, reset.
    if (speedMPH < 1 && timing && (millis() - startTime) > 1000 ) {
        timing = false;
        // Serial.println("Car is stopped. 0 to 30 Run Reset.");
    }

    // if the speed is over 30 and we're timing, check the time.
    if (timing && speedMPH >= 30) {
        endTime = millis();
        timing = false;
        // Serial.println("30mph reached");
        tempRun = prevRun;
        prevRun = (endTime - startTime) / 10.0;
        // if time is less than 60 seconds, return time.
          if (prevRun < 6000) {
            // Serial.print("New Time to 30: ");
            // Serial.println(prevRun/100);
            return prevRun; // Return time in seconds
          }
        else {
          // Serial.print("Time Over 60 seconds: ");
          // Serial.println(prevRun/100);
          prevRun = tempRun;
          return 0;
        }
    }

    if (prevRun == 0) return 0; // Indicate no valid 0-60 time yet
    else return prevRun;
}

int calculateTimeTo60(float speedMPH, int throttlePosition) {
    throttlePosition = throttlePosition/10;
    static unsigned long startTime = 0;
    static unsigned long endTime = 0;
    static bool timing = false;
    static int prevRun = 0;
    static int tempRun = 0;
    const int thresholdTPS = 5;  // Throttle position sensor threshold

    // if the speed is less than 3mph and the TPS is over the threshold, start timing.
    if (speedMPH < 3 && throttlePosition > thresholdTPS && !timing) {
        startTime = millis();
        timing = true;
        // Serial.println("Start 0 to 60 Run");
    }

    // if we're not moving and the timing has been going for more than a second, reset.
    if (speedMPH < 1 && timing && (millis() - startTime) > 1000 ) {
        timing = false;
        // Serial.println("Car is stopped. 0 to 60 Run Reset.");
    }

    // if the speed is over 30 and we're timing, check the time.
    if (timing && speedMPH >= 60) {
        endTime = millis();
        timing = false;
        // Serial.println("60mph reached");
        tempRun = prevRun;
        prevRun = (endTime - startTime) / 10.0;
        // if time is less than 60 seconds, return time.
          if (prevRun < 6000) {
            // Serial.print("New Time to 60: ");
            // Serial.println(prevRun/100);
            return prevRun; // Return time in seconds
          }
        else {
          // Serial.print("Time Over 60 seconds: ");
          // Serial.println(prevRun/100);
          prevRun = tempRun;
          return 0;
        }
    }

    if (prevRun == 0) return 0; // Indicate no valid 0-60 time yet
    else return prevRun;
}

void mpgCalc()
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  unsigned long elapsedTime = currentMillis - previousMillis;
  float gph;

  if (flowRate == 0) flowRate = 1;
  if (cyl == 0) cyl = 1;

  float gphFLow = flowRate * 0.0000630901964; // flowrate conversion fuel flow from injector

  int16_t fuelTemp =  ( (getByte(SPEEDUINO_FUELTEMP_BYTE) + SPEEDUINO_TEMPERATURE_OFFSET ) * SPEEDUINO_TEMPERATURE_MULTIPLIER ) + C_TO_F;
  float density = 6.25 * (1 - 0.0004 * (fuelTemp - 60));

  if ( density > 0 ) gph = ( (gphFLow * cyl * rpm * (pw/10)) / (density * 60) );
    else gph = 0;
  
  if ( gph > 0 ) {
    if (mph > 0 && pw > 0) mpg = ( ( mph * 10 ) / gph ); // mph divided by gph
      else if (mph > 0 && pw <= 0 ) mpg = 999;
      else if (mph <= 0 ) mpg = 0;

    float gallonsUsed = (gph / 3600000) * elapsedTime;
    tripGallonsUsedA += gallonsUsed;
    tripGallonsUsedB += gallonsUsed;
  }
  if (gph <= 0) {
    if (mph > 0) mpg = 999;
    if (mph <= 0) mpg = 0;
  }

  previousMillis = currentMillis;
}

float sineWave(){
  // example to make a quick sine wave signal
  float counter;
  counter = millis()/6000.0;
  return sin(counter);
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  // Ensure that the input value is within the input range
  if (x < in_min) {
    x = in_min;
  } else if (x > in_max) {
    x = in_max;
  }
  
  // Map the input value from the input range to the output range
  float mappedValue = out_min + (x - in_min) * (out_max - out_min) / (in_max - in_min);
  
  return mappedValue;
}