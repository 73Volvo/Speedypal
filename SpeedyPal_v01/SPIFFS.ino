#include <SPIFFS.h>
#include <FS.h>

// File path in SPIFFS
const char *filePath = "/data.txt";

struct VariableInfo {
  void* pointer;
  const char* dataType; // "int", "float", etc.
};

VariableInfo variableInfos[] = {
  {&odometer, "uint32_t"},
  {&thousandthsCounter, "float"},
  {&tripDistanceA, "float"},
  {&tripDistanceB, "float"},
  {&tripGallonsUsedA, "float"},
  {&tripGallonsUsedB, "float"},
  {&totalCountMPGa, "uint32_t"},
  {&sumMPGa, "uint32_t"},
  {&totalCountMPGb, "uint32_t"},
  {&sumMPGb, "uint32_t"},
  {&totalCountMPHa, "uint32_t"},
  {&sumMPHa, "uint32_t"},
  {&totalCountMPHb, "uint32_t"},
  {&sumMPHb, "uint32_t"},
  {&SCREEN_ROTATION, "uint8_t"},
  {&customScreen, "uint8_t"},
  {&customScreenSelect, "uint8_t"},
  {&customScreenSwitch, "bool"},
  {&customScreenSelectA, "uint8_t"},
  {&customScreenSelectB, "uint8_t"},
  {&pageNum, "uint8_t"},
  {&flowRate, "uint16_t"},
  {&cyl, "uint8_t"},
  {&smoothMPH, "uint8_t"},
  {&smoothPerf, "uint8_t"},
  {&SHIFTLIGHT_ON_RPM, "uint16_t"},
  {&ecuWait, "uint8_t"},
  {&fps, "uint8_t"}
};

const int numVariables = sizeof(variableInfos) / sizeof(variableInfos[0]);

void setupSPIFFS() {
  if (!SPIFFS.begin(true)) {
    Serial.println("An error occurred while mounting SPIFFS");
    return;
  }
  else Serial.println("SPIFFS started");

  // Check if the file exists
  if (!SPIFFS.exists(filePath)) {
    // If the file doesn't exist, create and initialize it
    writeToSPIFFS();
  }
}

bool SPIFFSconnected() {
  if (SPIFFS.begin()) {
    return true;
  } else {
    return false;
  }
}

void writeToSPIFFS() {
  File file = SPIFFS.open(filePath, FILE_WRITE);

  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }

  // Convert variables to strings and write them to the file
  for (int i = 0; i < numVariables; i++) {
    VariableInfo info = variableInfos[i];
    if (strcmp(info.dataType, "int") == 0) {
      file.print(*(reinterpret_cast<int*>(info.pointer))); // Use appropriate cast based on dataType
    } else if (strcmp(info.dataType, "bool") == 0) {
      file.print(*(reinterpret_cast<bool*>(info.pointer)) ? 1 : 0); // Map true to 1, false to 0
    } else if (strcmp(info.dataType, "float") == 0) {
      file.print(*(reinterpret_cast<float*>(info.pointer)), 6); // Specify precision
    } else if (strcmp(info.dataType, "uint8_t") == 0) {
      file.print(*(reinterpret_cast<uint8_t*>(info.pointer)));
    } else if (strcmp(info.dataType, "uint16_t") == 0) {
      file.print(*(reinterpret_cast<uint16_t*>(info.pointer)));
    } else if (strcmp(info.dataType, "uint32_t") == 0) {
      file.print(*(reinterpret_cast<uint32_t*>(info.pointer)));
    } else if (strcmp(info.dataType, "long") == 0) {
      file.print(*(reinterpret_cast<long*>(info.pointer)));
    }
    file.print("\t");
  }
  file.println();

  file.close();

  Serial.println("Prefs Written to SPIFFS");
}

void readFromSPIFFS() {
  File file = SPIFFS.open(filePath, FILE_READ);

  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  // Read variables from the file
  for (int i = 0; i < numVariables; i++) {
    VariableInfo info = variableInfos[i];
    if (strcmp(info.dataType, "int") == 0) {
      *(reinterpret_cast<int*>(info.pointer)) = file.readStringUntil('\t').toInt();
    } else if (strcmp(info.dataType, "bool") == 0) {
      *(reinterpret_cast<bool*>(info.pointer)) = (file.readStringUntil('\t').toInt() == 1);
    } else if (strcmp(info.dataType, "float") == 0) {
      *(reinterpret_cast<float*>(info.pointer)) = file.readStringUntil('\t').toFloat();
    } else if (strcmp(info.dataType, "uint8_t") == 0) {
      *(reinterpret_cast<uint8_t*>(info.pointer)) = file.readStringUntil('\t').toInt();
    } else if (strcmp(info.dataType, "uint16_t") == 0) {
      *(reinterpret_cast<uint16_t*>(info.pointer)) = file.readStringUntil('\t').toInt();
    } else if (strcmp(info.dataType, "uint32_t") == 0) {
      *(reinterpret_cast<uint32_t*>(info.pointer)) = file.readStringUntil('\t').toInt();
    } else if (strcmp(info.dataType, "long") == 0) {
      *(reinterpret_cast<long*>(info.pointer)) = file.readStringUntil('\t').toInt();
    }
  }

  file.close();

  Serial.println("Prefs loaded from SPIFFS");
}
