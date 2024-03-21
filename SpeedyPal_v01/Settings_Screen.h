enum IntType {
    INT_8,
    INT_16,
    INT_32
};

struct settingsInfo{
    int number;
    int subNumber;
    String name; // displayed name
    void* pointer; // the variable connected
    IntType type;
    int min;
    int max; 
    int multiplier; // which digit is adjusted
    int CR; // 0 = normal, 1 = carriage return
};

settingsInfo settingsScreen[] = {
  {1, 1, "", &hour, INT_8, 0, 2, 10, 0}, // 0
  {1, 0, "", &hour, INT_8, 0, 9, 1, 0}, // 1
  {2, 1, ":", &minute, INT_8, 0, 5, 10, 0}, // 2
  {2, 0, ":", &minute, INT_8, 0, 9, 1, 0}, // 3
  {3, 1, ":", &second, INT_8, 0, 5, 10, 0},// 4
  {3, 0, ":", &second, INT_8, 0, 9, 1, 1},// 5

  {4, 1, "", &month, INT_8, 0, 1, 10, 0}, // 6
  {4, 0, "", &month, INT_8, 0, 9, 1, 0}, // 7
  {5, 1, "/", &day, INT_8, 0, 3, 10, 0}, // 8
  {5, 0, "/", &day, INT_8, 0, 9, 1, 0}, // 9
  {6, 1, "/", &year, INT_16, 0, 9, 10, 0}, // 10
  {6, 0, "/", &year, INT_16, 0, 9, 1, 1}, // 11

  {7, 0, "ROTATION ", &SCREEN_ROTATION, INT_8, 0, 3, 1, 1}, //12

  {8, 7, "ODO ", &odometer, INT_32, 0, 9, 10000000, 0}, // 13
  {8, 6, "ODO ", &odometer, INT_32, 0, 9, 1000000, 0}, // 14
  {8, 5, "ODO ", &odometer, INT_32, 0, 9, 100000, 0}, // 15
  {8, 4, "ODO ", &odometer, INT_32, 0, 9, 10000, 0}, // 16
  {8, 3, "ODO ", &odometer, INT_32, 0, 9, 1000, 0}, // 17
  {8, 2, "ODO ", &odometer, INT_32, 0, 9, 100, 1}, // 18

  {9, 3, "SHIFT ", &SHIFTLIGHT_ON_RPM, INT_16, 0, 9, 1000, 0}, //19
  {9, 2, "SHIFT ", &SHIFTLIGHT_ON_RPM, INT_16, 0, 9, 100, 0}, //20
  {9, 1, "SHIFT ", &SHIFTLIGHT_ON_RPM, INT_16, 0, 9, 10, 0}, //21
  {9, 0, "SHIFT ", &SHIFTLIGHT_ON_RPM, INT_16, 0, 9, 1, 1}, //22

  {10, 0, "SM MPH ", &smoothMPH, INT_8, 0, 9, 1, 1}, //23

  {11, 0, "SM PRF ", &smoothPerf, INT_8, 0, 9, 1, 1}, //24

  {12, 1, "ECU ", &ecuWait, INT_8, 0, 9, 10, 0}, //25
  {12, 0, "ECU ", &ecuWait, INT_8, 0, 9, 1, 1}, //26

  {13, 1, "FPS ", &fps, INT_8, 0, 9, 10, 0}, //27
  {13, 0, "FPS ", &fps, INT_8, 0, 9, 1, 1}, //28

  {14, 0, "VAR1 ", &VAR1, INT_8, 0, 1, 1, 1}, //29

};