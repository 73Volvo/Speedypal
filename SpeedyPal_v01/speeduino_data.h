// Updated on 2023-01-11

#define SPEEDUINO_DATA_LEN 123

#define SPEEDUINO_BYTE_SECL               0   // Simple counter, incremented each second
  // SPEEDUINO_STATUS_BITFIELD            // Status Register, see single bits below
  #define SPEEDUINO_STATUS_INJ1_BIT         1
  #define SPEEDUINO_STATUS_INJ2_BIT         2
  #define SPEEDUINO_STATUS_INJ3_BIT         3
  #define SPEEDUINO_STATUS_INJ4_BIT         4
  #define SPEEDUINO_STATUS_DFCO_BIT         5 // Deceleration Fuel Cut Off
  #define SPEEDUINO_STATUS_BOOSTCUT_BIT     6
  #define SPEEDUINO_STATUS_TOOTH1_BIT       7 // Tooth Log 1 Ready
  #define SPEEDUINO_STATUS_TOOTH2_BIT       8 // Tooth Log 2 Ready
  // SPEEDUINO_ENGINE_BITFIELD            // Engine Register, see single bits below
  #define SPEEDUINO_ENGINE_RUNNING_BIT      9
  #define SPEEDUINO_ENGINE_CRANKING_BIT     10
  #define SPEEDUINO_ENGINE_ASE_BIT          11 // Afterstart Enrichment
  #define SPEEDUINO_ENGINE_WARMUP_BIT       12 // Warmup Enrichment
  #define SPEEDUINO_ENGINE_TPSAE_BIT        13 // TPS-based Acceleration Enrichment
  #define SPEEDUINO_ENGINE_TPSDE_BIT        14 // TPS-based Deceleration Enleanment
  #define SPEEDUINO_ENGINE_MAPAE_BIT        15 // MAP-based Acceleration Enrichment
  #define SPEEDUINO_ENGINE_MAPDE_BIT        16 // MAP-based Deceleration Enleanment
#define SPEEDUINO_DWELL_BYTE                17   // Dwell (ms, divide by 10)
#define SPEEDUINO_MAP_WORD                  18   // MAP (kPa, 2 bytes)
#define SPEEDUINO_IAT_BYTE                  19   // Intake Air Temperature (Degrees, subtract 40)
#define SPEEDUINO_CLT_BYTE                  20   // Coolant Temperature (Degrees, subtract 40)
#define SPEEDUINO_VOLTAGE_BYTE              21   // Battery Voltage (Volts, divide by 10)
#define SPEEDUINO_AFR_BYTE                  22  // Air-Fuel Ratio (divide by 10)
#define SPEEDUINO_EGOCORR_BYTE              23  // EGO Correction (%)
#define SPEEDUINO_IATCORR_BYTE              24  // Air Temperature Correction (%)
#define SPEEDUINO_WUECORR_BYTE              25  // Warmup Enrichment Correction (%)
#define SPEEDUINO_RPM_WORD                  26  // RPM (2 bytes)
#define SPEEDUINO_AECORR_BYTE               27  // Acceleration Enrichment Correction (%)
#define SPEEDUINO_GAMMAE_BYTE               28  // Gamma Correction (%)
#define SPEEDUINO_CURRENTVE_BYTE            29  // Current VE
#define SPEEDUINO_AFRTARGET_BYTE            30  // AFR Target (divide by 10)
#define SPEEDUINO_PW1_WORD                  31  // PulseWidth 1 (ms, divide by 10)
#define SPEEDUINO_TPSDOT_BYTE               32  // TPSdot (%/s, multiply by 10)
#define SPEEDUINO_ADVANCE                   33  // (Degrees BTDC)
#define SPEEDUINO_TPS_BYTE                  34  // Throttle Position (%, divide by 2, 0.5% resolution)
#define SPEEDUINO_LOOPSPERSEC_WORD          35  // (Loops/s, 2 bytes)
#define SPEEDUINO_FREERAM_WORD              36  // (Bytes, 2 bytes)
#define SPEEDUINO_BOOSTTARGET               37  // (kPa, multiply by 2)
#define SPEEDUINO_BOOSTDUTY                 38  // Boost PWM duty (%)
  // SPEEDUINO_SPARK_BITFIELD            // Spark Register, see single bits below
  #define SPEEDUINO_SPARK_HARDLAUNCH_BIT    39 // Launch Control limiter, hard
  #define SPEEDUINO_SPARK_SOFTLAUNCH_BIT    40 // Launch Control limiter, soft
  #define SPEEDUINO_SPARK_HARDLIMIT_BIT     41 // Rev limiter, hard
  #define SPEEDUINO_SPARK_SOFTLIMIT_BIT     42 // Rev limiter, soft
  #define SPEEDUINO_SPARK_BOOSTCUT_BIT      43 
  #define SPEEDUINO_SPARK_ERROR_BIT         44
  #define SPEEDUINO_SPARK_IDLECTRL_BIT      45
  #define SPEEDUINO_SPARK_SYNC_BIT          46
#define SPEEDUINO_RPMDOT_WORD               47  // RPMdot (rpm/s, 2 bytes)
#define SPEEDUINO_ETHANOLPCT_BYTE           48  // Ethanol content (%, 0 if not used)
#define SPEEDUINO_FLEXCORR_BYTE             49  // Flex fuel Correction (%)
#define SPEEDUINO_FLEXIGNCORR_BYTE          50  // Flex fuel advance correction (Degrees)
#define SPEEDUINO_IDLELOAD_BYTE             51  // Idle valve load (PWM duty or Steps)
  // SPEEDUINO_TESTOUTPUTS_BITFIELD      // Test Outputs Register, see single bits below
  #define SPEEDUINO_TESTOUTPUTS_ENABLED_BIT 52
  #define SPEEDUINO_TESTOUTPUTS_ACTIVE_BIT  53
#define SPEEDUINO_02_2_BYTE                 54  // Secondary AFR Sensor (divide by 10)
#define SPEEDUINO_BARO_BYTE                 55  // Berometric pressure (kPa)
#define SPEEDUINO_CANIN0_WORD               56  // CAN Input 0 (2 bytes)
#define SPEEDUINO_CANIN1_WORD               57  // CAN Input 1 (2 bytes)
#define SPEEDUINO_CANIN2_WORD               58  // CAN Input 2 (2 bytes)
#define SPEEDUINO_CANIN3_WORD               59  // CAN Input 3 (2 bytes)
#define SPEEDUINO_CANIN4_WORD               60  // CAN Input 4 (2 bytes)
#define SPEEDUINO_CANIN5_WORD               61  // CAN Input 5 (2 bytes)
#define SPEEDUINO_CANIN6_WORD               62  // CAN Input 6 (2 bytes)
#define SPEEDUINO_CANIN7_WORD               63  // CAN Input 7 (2 bytes)
#define SPEEDUINO_CANIN8_WORD               64  // CAN Input 8 (2 bytes)
#define SPEEDUINO_CANIN9_WORD               65  // CAN Input 9 (2 bytes)
#define SPEEDUINO_CANIN10_WORD              66  // CAN Input 10 (2 bytes)
#define SPEEDUINO_CANIN11_WORD              67  // CAN Input 11 (2 bytes)
#define SPEEDUINO_CANIN12_WORD              68  // CAN Input 12 (2 bytes)
#define SPEEDUINO_CANIN13_WORD              69  // CAN Input 13 (2 bytes)
#define SPEEDUINO_CANIN14_WORD              70  // CAN Input 14 (2 bytes)
#define SPEEDUINO_CANIN15_WORD              71  // CAN Input 15 (2 bytes)
#define SPEEDUINO_TPSADC_BYTE               72  // TPS ADC Value (0...255)
#define SPEEDUINO_ERROR_BYTE                73  // Error code (Error Number 0:1, Current Error 2:7)
#define SPEEDUINO_LAUNCHCORR_BYTE           74  // Launch Correction (%)
#define SPEEDUINO_PW2_WORD                  75  // PulseWidth 2 (ms, divide by 10)
#define SPEEDUINO_PW3_WORD                  76  // PulseWidth 3 (ms, divide by 10)
#define SPEEDUINO_PW4_WORD                  77  // PulseWidth 4 (ms, divide by 10)
  // SPEEDUINO_STATUS3_BITFIELD          // Status3 Register, see single bits below
  #define SPEEDUINO_STATUS3_RESETLOCKON_BIT 78
  #define SPEEDUINO_STATUS3_NITROUSON_BIT   79
  #define SPEEDUINO_STATUS3_FUEL2ACTIVE_BIT 80 // Secondary VE Table
  #define SPEEDUINO_STATUS3_VSSREFRESH_BIT  81
  #define SPEEDUINO_STATUS3_HALFSYNC_BIT    82
  #define SPEEDUINO_STATUS3_NSQUIRTS_BITS   83 // Bits 5:7
  // SPEEDUINO_ENGINEPROTECT_BITFIELD    // Engine Protect Register, see single bits below
  #define SPEEDUINO_ENGINEPROTECT_RPM_BIT   84
  #define SPEEDUINO_ENGINEPROTECT_MAP_BIT   85
  #define SPEEDUINO_ENGINEPROTECT_OIL_BIT   86
  #define SPEEDUINO_ENGINEPROTECT_AFR_BIT   87
  #define SPEEDUINO_ENGINEPROTECT_CLT_BIT   88
#define SPEEDUINO_FUELLOAD_WORD             89  // Fuel Table load (kPa or TPS%, 2 bytes)
#define SPEEDUINO_IGNLOAD_WORD              90  // Spark Table load (kPa or TPS%, 2 bytes)
#define SPEEDUINO_INJANGLE_WORD             91  // Injection angle (2 bytes)
#define SPEEDUINO_IDLELOAD_BYTE             92  // DUPLICATE OF ADDRESS 37 - HOPEFULLY WILL BE FIXED IN THE SPEEDUINO FIRMWARE
#define SPEEDUINO_CLIDLETARGET_BYTE         93  // Closed-Loop Idle Target RPM (multiply by 10)
#define SPEEDUINO_MAPDOT_BYTE               94  // MAPdot (kPa/s, multiply by 10)
#define SPEEDUINO_VVT1ANGLE_BYTE            95  // VVT1 Angle (Degrees, SIGNED)
#define SPEEDUINO_VVT1TARGET_BYTE           96  // VVT1 Target Angle (Degrees)
#define SPEEDUINO_VVT1DUTY_BYTE             97  // VVT1 PWM Duty (%)
#define SPEEDUINO_FLEXBOOSTCORR_WORD        98  // Flex fuel Boost Correction, 2 bytes)
#define SPEEDUINO_BAROCORR_BYTE             99  // Barometric Correction (%)
#define SPEEDUINO_ASECORR_BYTE              100  // After Start Enrichment Correction (%)
#define SPEEDUINO_VSS_WORD                  101 // Speed reading via VSS (2 bytes)
#define SPEEDUINO_GEAR_BYTE                 102 // Current gear
#define SPEEDUINO_FUELPRESSURE_BYTE         103 // (PSI or Bar)
#define SPEEDUINO_OILPRESSURE_BYTE          104 // (PSI or Bar)
#define SPEEDUINO_WMIPW_BYTE                105 // Water-Meth Injection Pulsewidth
  // SPEEDUINO_STATUS4_BITFIELD         // Status4 Register, see single bits below
  #define SPEEDUINO_STATUS4_WMIEMPTY_BIT    106 // Water-Meth Tank empty
  #define SPEEDUINO_STATUS4_VVT1ERROR_BIT   107
  #define SPEEDUINO_STATUS4_VVT2ERROR_BIT   108
  #define SPEEDUINO_STATUS4_FAN_BIT         109 // Cooling fan
#define SPEEDUINO_VVT2ANGLE_BYTE            110 // VVT2 Angle (Degree, SIGNED)
#define SPEEDUINO_VVT2TARGET_BYTE           111 // VVT2 Target Angle (Degrees)
#define SPEEDUINO_VVT2DUTY_BYTE             112 // VVT2 PWM Duty (%)
#define SPEEDUINO_OUTPUTSSTATUS_BYTE        113 // Programmable Outputs
#define SPEEDUINO_FUELTEMP_BYTE             114 // Fuel Temperature from Flex Sensor (Degrees, subtract 40)
#define SPEEDUINO_FUELTEMPCORR_BYTE         115 // Fuel Temperature Correction (%)
#define SPEEDUINO_VE1_BYTE                  116 // VE from Primary Fuel Table
#define SPEEDUINO_VE2_BYTE                  117 // VE from Secondary Fuel Table
#define SPEEDUINO_ADVANCE1_BYTE             118 // Advance from Primary Spark Table (Degrees BTDC)
#define SPEEDUINO_ADVANCE2_BYTE             119 // Advance from Secondary Spark Table (Degrees BTDC)
  // SPEEDUINO_NITROUSSTATUS_BYTE       // N2O status, see values below
  #define SPEEDUINO_NITROUSSTATUS_OFF       120
  #define SPEEDUINO_NITROUSSTATUS_STAGE1    121
  #define SPEEDUINO_NITROUSSTATUS_STAGE2    122
  #define SPEEDUINO_NITROUSSTATUS_BOTH      123
  // SPEEDUINO_SDCCARD_BITFIELD         // SD Card Register, see single bits below
  #define SPEEDUINO_SDCARD_PRESENT_BIT      124 // SD Card is inserted
  #define SPEEDUINO_SDCARD_TYPE_BIT         125 // SD Card type (0=SD, 1=SDHC)
  #define SPEEDUINO_SDCARD_READY_BIT        126
  #define SPEEDUINO_SDCARD_LOGGING_BIT      127
  #define SPEEDUINO_SDCARD_ERROR            128
  #define SPEEDUINO_SDCARD_VERSION_BIT      129 // SD Card version (0=1.x, 1=2.x)
  #define SPEEDUINO_SDCARD_FS_BIT           130 // SD Card filesystem (0=no FAT16, 1=FAT32)
  #define SPEEDUINO_SDCARD_UNUSED           131
#define SPEEDUINO_EMAP_WORD                 132 // EMAP (kPa, 2 bytes)
#define SPEEDUINO_FANDUTY_BYTE              133 // Cooling Fan PWM duty (%)
  // SPEEDUINO_AIRCON_BITFIELD          // Air Conditioning register, see single bits below
  #define SPEEDUINO_AIRCON_REQUEST_BIT      134
  #define SPEEDUINO_AIRCON_COMPRESSOR_BIT   135
  #define SPEEDUINO_AIRCON_RPMLOCKOUT_BIT   136
  #define SPEEDUINO_AIRCON_TPSLOCKOUT_BIT   137
  #define SPEEDUINO_AIRCON_TURNINGON_BIT    138
  #define SPEEDUINO_AIRCON_CLTLOCKOUT_BIT   139
  #define SPEEDUINO_AIRCON_FAN_BIT          140
// CALCULATED STATS
#define CALCULATED_FRAME_RATE               141
#define CALCULATED_MPG                      142
#define CALCULATED_MPH                      143
#define CALCULATED_ODOMETER                 144
#define CALCULATED_ACCELERATION             145
#define CALCULATED_HORSEPOWER               146
#define CALCULATED_TORQUE                   147
#define CALCULATED_TIME_TO_30               148
#define CALCULATED_TIME_TO_60               149


// Stat struct settings
struct stat2{
    int number; // the number of the stat on the Speeduino serial connection
    int subNumber; // sub-number if the stat is a bit from a whole byte
    String name; // used for logging
    int type; // 0=bit / 1=byte / 2=word / 3=three bits / 4 = signed word / 5 = calculated variable (float) / 6 = signed byte
    int multiplier; // 0 = temp, divide by 10 then multiply stat with resulting number. If the multiplier is "0" the stat goes through temp conversion
    int decimal; // 0 for no decimal, 1 for a single decimal, 2 for two decimal places.
    String fullName; // name to be used in log
    String unit; // unit to be used in log
    float* calculated; // points to a calculated variable (or a null for speeduino variables)
};

stat2 speeduino[] = {
  {0,0,"SECL",1,10,0, "SecL", "sec", &null},// 0 - Simple counter, incremented each second
  {1,0,"INJ1",0,10,0, "INJ1", " ", &null},// 1 - Status Register, see single bits below
  {1,1,"INJ2",0,10,0, "INJ2", " ", &null},// 2
  {1,2,"INJ3",0,10,0, "INJ3", " ", &null},// 3
  {1,3,"INJ4",0,10,0, "INJ4", " ", &null},// 4
  {1,4,"DFCO",0,10,0, "DCFO", " ", &null},// 5 - Deceleration Fuel Cut Off
  {1,5,"BST CUT",0,10,0, "Boost cut", " ", &null},// 6
  {1,6,"TOOTH1",0,10,0, "TOOTH1", " ", &null},// 7 - Tooth Log 1 Ready
  {1,7,"TOOTH2",0,10,0, "TOOTH2", " ", &null},// 8 - Tooth Log 2 Ready
  {2,0,"RUNNING",0,10,0, "RUNNING", " ", &null},// 9 - Engine Register, see single bits below
  {2,1,"CRANK",0,10,0, "CRANK", " ", &null},// 10
  {2,2,"ASE",0,10,0, "Afterstart Enrichment", " ", &null},// 11 - Afterstart Enrichment
  {2,3,"WARMUP",0,10,0, "Warmup Enrichment", " ", &null},// 12 - Warmup Enrichment
  {2,4,"TPSAE",0,10,0, "TPS Accel Enrichment", " ", &null},// 13 - TPS-based Acceleration Enrichment
  {2,5,"TPSDE",0,10,0, "TPS Decel Enrichment", " ", &null},// 14 - TPS-based Deceleration Enleanment
  {2,6,"MAPAE",0,10,0, "MAP Accel Enrichment", " ", &null},// 15 - MAP-based Acceleration Enrichment
  {2,7,"MAPDE",0,10,0, "MAP Decel Enrichment", " ", &null},// 16 - MAP-based Deceleration Enleanment
  {3,0,"DWELL",1,1,1, "Dwell", "ms", &null},// 17 - Dwell (ms, divide by 10)
  {4,0,"MAP",2,10,0, "MAP", "kpa", &null},// 18 - MAP (kPa, 2 bytes)
  {6,0,"IAT",1,0,0, "IAT", " ", &null},// 19 - Intake Air Temperature (Degrees, subtract 40)
  {7,0,"CLT",1,0,0, "CLT", " ", &null},// 20 - Coolant Temperature (Degrees, subtract 40)
  {9,0,"BAT",1,10,1, "Battery V", "V", &null},// 21 - Battery Voltage (Volts, divide by 10)
  {10,0,"AFR",1,10,1, "AFR", "O2", &null},// 22 - Air-Fuel Ratio (divide by 10)
  {11,0,"EGOCORR",1,10,0, "Gego", "%", &null},// 23 - EGO Correction (%)
  {12,0,"IATCORR",1,10,0, "Gair", "%", &null},// 24 - Air Temperature Correction (%)
  {13,0,"WUECORR",1,10,0, "Gwarm", "%", &null},// 25 - Warmup Enrichment Correction (%)
  {14,0,"RPM",2,10,0, "RPM", "rpm", &null},// 26 - RPM (2 bytes)
  {16,0,"AECORR",1,10,0, "Accel Enrich", "%", &null},// 27 - Acceleration Enrichment Correction (%)
  {17,0,"GAMMAE",1,10,0, "Gammae", "%", &null},// 28 - Gamma Correction (%)
  {18,0,"CURRENT VE",1,10,0, "VE (Current", "%", &null},// 29 - Current VE
  {19,0,"AFR TGT",1,10,1, "AFR Target", "O2", &null},// 30 - AFR Target (divide by 10)
  {20,0,"PW1",2,1,2, "PW", "ms", &null},// 31 - PulseWidth 1 (ms, divide by 10)
  {22,0,"TPSDOT",1,100,0, "TPS DOT", "%/s", &null},// 32 - TPSdot (%/s, multiply by 10)
  {23,0,"ADVANCE",1,10,0, "Advance (Current", "deg", &null},// 33 - (Degrees BTDC)
  {24,0,"TPS",1,50,1, "TPS", "%", &null},// 34 - Throttle Position (%, divide by 2, 0.5% resolution)
  {25,0,"LOOPSEC",2,10,0, "Loops/s", "loops", &null},// 35 - (Loops/s, 2 bytes)
  {27,0,"FREE RAM",2,10,0, "Free RAM", " ", &null},// 36 - (Bytes, 2 bytes)
  {29,0,"BST TGT",1,20,0, "Boost Target", " ", &null},// 37 - Boost Target - (kPa, multiply by 2)
  {30,0,"BST DTY",1,10,0, "Boost Duty", " ", &null},// 38 - Boost PWM duty (%)
  {31,0,"HRDLNCH",0,10,0, "Hard Launch", " ", &null},// 39 - Launch Control limiter, hard // Spark Register, see single bits below
  {31,1,"SFTLNCH",0,10,0, "Soft Launch", " ", &null},// 40 - Launch Control limiter, soft
  {31,2,"HRDLIMT",0,10,0, "Hard Limiter", " ", &null},// 41 - Rev limiter, hard
  {31,3,"SFTLMIT",0,10,0, "Rev Limiter", " ", &null},// 42 - Rev limiter, soft
  {31,4,"BST CUT",0,10,0, "Boost Cut", " ", &null},// 43
  {31,5,"ERROR",0,10,0, "Error #", " ", &null},// 44
  {31,6,"IDLCTRL",0,10,0, "Idle Control", " ", &null},// 45
  {31,7,"SYNC",0,10,0, "Sync Status", " ", &null},// 46
  {32,0,"RPMDOT",4,10,0, "Idle RPM Delta", " ", &null},// 47 - RPMdot (rpm/s, 2 bytes) signed
  {34,0,"ETH PCT",1,10,0, "Ethanol Content", " ", &null},// 48 - Ethanol content (%, 0 if not used)
  {35,0,"FLXCORR",1,10,0, "Flex Fuel Correction", " ", &null},// 49 - Flex fuel Correction (%)
  {36,0,"FLICORR",1,10,0, "Flex Fuel Advance Correction", " ", &null},// 50 - Flex fuel advance correction (Degrees)
  {37,0,"IDLE LD",1,10,0, "IAC Value", "7", &null},// 51 - Idle valve load (PWM duty or Steps)
  {38,0,"OUTENBL",0,10,0, "Test Outputs Register", " ", &null},// 52 - Test Outputs Register, see single bits below
  {38,1,"OUTACTV",0,10,0, "Out Active", " ", &null},// 53
  {39,0,"AFR2",1,10,1, "AFR 2", " ", &null},// 54 - Secondary AFR Sensor (divide by 10)
  {40,0,"BARO",1,10,0, "Baro Pressure", "kpa", &null},// 55 - Berometric pressure (kPa)
  {41,0,"CAN0",2,10,0, "CAN0", " ", &null},// 56 - CAN Input 0 (2 bytes)
  {43,0,"CAN1",2,10,0, "CAN1", " ", &null},// 57 - CAN Input 1 (2 bytes)
  {45,0,"CAN2",2,10,0, "CAN2", " ", &null},// 58 - CAN Input 2 (2 bytes)
  {47,0,"CAN3",2,10,0, "CAN3", " ", &null},// 59 - CAN Input 3 (2 bytes)
  {49,0,"CAN4",2,10,0, "CAN4", " ", &null},// 60 - CAN Input 4 (2 bytes)
  {51,0,"CAN5",2,10,0, "CAN5", " ", &null},// 61 - CAN Input 5 (2 bytes)
  {53,0,"CAN6",2,10,0, "CAN6", " ", &null},// 62 - CAN Input 6 (2 bytes)
  {55,0,"CAN7",2,10,0, "CAN7", " ", &null},// 63 - CAN Input 7 (2 bytes)
  {57,0,"CAN8",2,10,0, "CAN8", " ", &null},// 64 - CAN Input 8 (2 bytes)
  {59,0,"CAN9",2,10,0, "CAN9", " ", &null},// 65 - CAN Input 9 (2 bytes)
  {61,0,"CAN10",2,10,0, "CAN10", " ", &null},// 66 - CAN Input 10 (2 bytes)
  {63,0,"CAN11",2,10,0, "CAN11", " ", &null},// 67 - CAN Input 11 (2 bytes)
  {65,0,"CAN12",2,10,0, "CAN12", " ", &null},// 68 - CAN Input 12 (2 bytes)
  {67,0,"CAN13",2,10,0, "CAN13", " ", &null},// 69 - CAN Input 13 (2 bytes)
  {69,0,"CAN14",2,10,0, "CAN14", " ", &null},// 70 - CAN Input 14 (2 bytes)
  {71,0,"CAN15",2,10,0, "CAN15", " ", &null},// 71 - CAN Input 15 (2 bytes)
  {73,0,"TPSADC",1,10,0, "TPS ADC", " ", &null},// 72 - TPS ADC Value (0...255)
  {74,0,"ERROR",1,10,0, "Error ID", " ", &null},// 73 - Error code (Error Number 0:1, Current Error 2:7)
  {75,0,"LNCHCOR",1,10,0, "Launch Correction", "%", &null},// 74 - Launch Correction (%)
  {76,0,"PW2",2,1,2, "PW2", "ms", &null},// 75 - PulseWidth 2 (ms, divide by 10)
  {78,0,"PW3",2,1,2, "Pulsewidth 3", "ms", &null},// 76 - PulseWidth 3 (ms, divide by 10)
  {80,0,"PW4",2,1,2, "Pulsewidth 4", "ms", &null},// 77 - PulseWidth 4 (ms, divide by 10)
  {82,0,"RST LCK",0,10,0, "RST LOCK", " ", &null},// 78 - Status3 Register, see single bits below
  {82,1,"NIT ON",0,10,0, "Nitrous On", " ", &null},// 79
  {82,2,"FL2 ACT",0,10,0, "Fuel 2 Active", " ", &null},// 80 - Secondary VE Table
  {82,3,"VSS RF",0,10,0, "VSS Signal", " ", &null},// 81 - VSS Refresh
  {82,4,"HF SYNC",0,10,0, "Half Sync", " ", &null},// 82
  {82,5,"#SQRTS",3,10,0, "Number of Squirts", " "},// 83 - listed as Bits 6:7 but probably 5:6:7
  {83,0,"PRO RPM",0,10,0, "Engine Prot. RPM", "Act/Inact", &null},// 84 - Engine Protect Register, see single bits below
  {83,1,"PRO MAP",0,10,0, "Engine Prot. MAP", "Act/Inact", &null},// 85
  {83,2,"PRO OIL",0,10,0, "Engine Prot. OIL", "Act/Inact", &null},// 86
  {83,3,"PRO AFR",0,10,0, "Engine Prot. AFR", "Act/Inact", &null},// 87
  {83,4,"PRO CLT",0,10,0, "Engine Prot. CLT", "Act/Inact", &null},// 88 
  {84,0,"FUEL LOAD",2,10,0, "FuelLoad", "kpa", &null},// 89 - Fuel Table load (kPa or TPS%, 2 bytes)
  {86,0,"IGN LOAD",2,10,0, "IgnitionLoad", "kpa", &null},// 90 - Spark Table load (kPa or TPS%, 2 bytes)
  {88,0,"INJ ANGLE",2,10,0, "Injection Angle", " ", &null},// 91 - Injection angle (2 bytes)
  {90,0,"IDLE LOAD",1,10,0, "Idle Load", " ", &null},// 92 - DUPLICATE OF ADDRESS 37 - HOPEFULLY WILL BE FIXED IN THE SPEEDUINO FIRMWARE
  {91,0,"IDLE TARGET",1,100,0, "Idle Target RPM", "RPM", &null},// 93 - Closed-Loop Idle Target RPM (multiply by 10)
  {92,0,"MAP DOT",1,100,0, "MAP DOT", "kpa/s", &null},// 94 - MAPdot (kPa/s, multiply by 10)
  {93,0,"VVT1ANG",6,10,0, "VVT1 Angle", "deg", &null},// 95 - VVT1 Angle (Degrees, SIGNED)
  {94,0,"VVT1TGT",1,10,0, "VVT1 Target Angle", "deg", &null},// 96 - VVT1 Target Angle (Degrees)
  {95,0,"VVT1DUTY",1,10,0, "VVT1 PWM Duty", "%", &null},// 97 - VVT1 PWM Duty (%)
  {96,0,"FLXBSTCORR",2,10,0, "Flex Fuel Boost Correction", " ", &null},// 98 - Flex fuel Boost Correction, 2 bytes)
  {98,0,"BARO CORR",1,10,0, "Gbaro", "%", &null},// 99 - Barometric Correction (%)
  {99,0,"ASE CORR",1,10,0, "ASE Correction", "%", &null},// 100 - After Start Enrichment Correction (%)
  {100,0,"VSS",2,10,0, "KPH", "kph", &null},// 101 - Speed reading via VSS (2 bytes)
  {102,0,"GEAR",1,10,0, "Gear", " ", &null},// 102 - Current gear
  {103,0,"FUELPRSS",1,10,0, "Fuel Pressure", "PSI", &null},// 103 - (PSI or Bar)
  {104,0,"OILPRSS",1,10,0, "Oil Pressure", "PSI", &null},// 104 - (PSI or Bar)
  {105,0,"WMI_PW",1,10,0, "Water-Meth Injection PW", "ms", &null},// 105 - Water-Meth Injection Pulsewidth
  {106,0,"WM_EMPT",0,10,0, "Water-Meth Tank Empty", " ", &null},// 106 - Water-Meth Tank empty // Status4 Register, see single bits below
  {106,1,"VVT1_ER",0,10,0, "VVT1 Error", " ", &null},// 107
  {106,2,"VVT2_ER",0,10,0, "VVT2 Error", " ", &null},// 108
  {106,3,"FAN",0,10,0, "Fan", " ", &null},// 109 - Cooling fan
  {107,0,"VVT2ANG",6,10,0, "VVT2 Angle", "deg", &null},// 110 - VVT2 Angle (Degree, SIGNED)
  {108,0,"VVT2TGT",1,10,0, "VVT2 Target Angle", "deg", &null},// 111 - VVT2 Target Angle (Degrees)
  {109,0,"VVT2DUTY",1,10,0, "VVT2 Duty", "%", &null},// 112 - VVT2 PWM Duty (%)
  {110,0,"OUTSTAT",1,10,0, "Out Status", " ", &null},// 113 - Programmable Outputs
  {111,0,"FUELTEMP",1,0,0, "Fuel Temp", "deg", &null},// 114 - Fuel Temperature from Flex Sensor (Degrees, subtract 40)
  {112,0,"FUELTEMP CORR",1,10,0, "Fuel Temp Correction", "%", &null},// 115 - Fuel Temperature Correction (%)
  {113,0,"VE1",1,10,0, "VE1", "%", &null},// 116 - VE from Primary Fuel Table
  {114,0,"VE2",1,10,0, "VE2", "%", &null},// 117 - VE from Secondary Fuel Table
  {115,0,"ADV1",1,10,0, "Advance 1", "deg", &null},// 118 - Advance from Primary Spark Table (Degrees BTDC)
  {116,0,"ADV2",1,10,0, "Advance 2", "deg", &null},// 119 - Advance from Secondary Spark Table (Degrees BTDC)
  {117,0,"NIT_OFF",0,10,0, "Nitrous Off", " ", &null},// 120 - N2O status, see values below
  {117,1,"NIT_ST1",0,10,0, "Nitrous ST1", " ", &null},// 121
  {117,2,"NIT_ST2",0,10,0, "Nitrous ST2", " ", &null},// 122
  {117,3,"NITBOTH",0,10,0, "Nitrous Both", " ", &null},// 123
  {118,0,"SDPRES",0,10,0, "SD Card Inserted", " ", &null},// 124 - SD Card is inserted // SD Card Register, see single bits below
  {118,1,"SDTYPE",0,10,0, "SD Type", " ", &null},// 125 - SD Card type (0=SD, 1=SDHC)
  {118,2,"SDREADY",0,10,0, "SD Ready", " ", &null},// 126
  {118,3,"SDLOGG",0,10,0, "SD Logg", " ", &null},// 127
  {118,4,"SD_ERR",0,10,0, "SD Error", " ", &null},// 128
  {118,5,"SD_VER",0,10,0, "SD Version", " ", &null},// 129 - SD Card version (0=1.x, 1=2.x)
  {118,6,"SD_FS",0,10,0, "SD Filesystem", " ", &null},// 130 - SD Card filesystem (0=no FAT16, 1=FAT32)
  {118,7,"SD_UNU",0,10,0, "SD Unused", " ", &null},// 131 - SD Unused

  {119,0,"EMAP",2,10,0, "EMAP", " kpa", &null},// 132 - EMAP (kPa, 2 bytes)
  {121,0,"FAN DUTY",1,10,0, "FAN PWM Duty", "%", &null},// 133 - Cooling Fan PWM duty (%)
  {122,0,"AC REQ",0,10,0, "AC Request", " ", &null},// 134 - Air Conditioning register, see single bits below
  {122,1,"AC COMP",0,10,0, "AC Compressor", " ", &null},// 135
  {122,2,"AC RPM",0,10,0, "AC RPM Lock", " ", &null},// 136 - AC RPM LOCK
  {122,3,"AC TPS",0,10,0, "AC TPS Lock", " ", &null},// 137 - AC TPS LOCK
  {122,4,"AC ON",0,10,0, "AC Signal", " ", &null},// 138
  {122,5,"AC CLT",0,10,0, "AC CLT Lock", " ", &null},// 139 - AC CLT LOCK
  {122,6,"AC FAN",0,10,0, "AC Fan", " ", &null},// 140

  // calculated stats, not in buffer
  {123,0,"FRAMERATE",5,10,0,"Current Frame Rate","fps",&currentFrameRate},//141
  {124,0,"MPG",5,10,1,"MPG","mpg",&mpg},//142 - divide by ten
  {125,0,"MPH",5,10,0,"MPH","mph",&mph},//143
  {126,0,"ODO",5,10,2,"Odometer","mi",&odometerFloat},//144
  {127,0,"ACCEL",5,10,0,"Acceleration","mph/s",&acceleration},//145
  {128,0,"HP",5,10,0,"Horsepower","hp",&horsepower},//146
  {129,0,"TORQUE",5,10,0,"Torque","ftlbs",&torque},//147
  {130,0,"to30",5,10,2,"Time to 30","sec",&timeTo30},//148
  {131,0,"to60",5,10,2,"Time to 60","sec",&timeTo60}//149
};
