// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h> // the OBD2 library depends on the CAN library
#include <OBD2.h>

// array of PID's to print values of
const int PIDS[] = {
ABSOLUTE_THROTTLE_POSITION_B,
ABSOLUTE_THROTTLE_POSITION_D,
ABSOLUTE_THROTTLE_POSITION_E,
AIR_INTAKE_TEMPERATURE,
CALCULATED_ENGINE_LOAD,
COMMANDED_EVAPORATIVE_PURGE,
COMMANDED_THROTTLE_ACTUATOR,
DISTANCE_TRAVELED_WITH_MIL_ON,
ENGINE_COOLANT_TEMPERATURE,
ENGINE_OIL_TEMPERATURE,
ENGINE_RPM,
FUEL_SYSTEM_STATUS,
FUEL_TYPE,
INTAKE_MANIFOLD_ABSOLUTE_PRESSURE,
MONITOR_STATUS_SINCE_DTCS_CLEARED,
OBD_STANDARDS_THIS_VEHICLE_CONFORMS_TO,
OXYGEN_SENSOR_1_SHORT_TERM_FUEL_TRIM,
OXYGEN_SENSORS_PRESENT_IN_2_BANKS,
RELATIVE_THROTTLE_POSITION,
SHORT_TERM_FUEL_TRIM_BANK_1,
THROTTLE_POSITION,
VEHICLE_SPEED,
};

const int NUM_PIDS = sizeof(PIDS) / sizeof(PIDS[0]);

void setup() {
  Serial.begin(9600);
  CAN.setClockFrequency(8E6);
  while (!Serial);

  Serial.println(F("OBD2 Key Stats"));

  while (true) {
    Serial.print(F("Attempting to connect to OBD2 CAN bus ... "));

    if (!OBD2.begin()) {
      Serial.println(F("failed!"));

      delay(1000);
    } else {
      Serial.println(F("success"));
      break;
    }
  }

  Serial.println();
}

void loop() {
  // loop through all the PID's in the array
  // 
  for (int i = 0; i < NUM_PIDS; i++) {
    int pid = PIDS[i];

    printPID(pid);
  }
  Serial.println();

  delay(1000);
}

void printPID(int pid) {
  // print PID name
  Serial.print(OBD2.pidName(pid));
  Serial.print(F(" = "));

  // read the PID value
  float pidValue = OBD2.pidRead(pid);

  if (isnan(pidValue)) {
    Serial.print("error");
  } else {
    // print value with units
    Serial.print(pidValue);
    Serial.print(F(" "));
    Serial.print(OBD2.pidUnits(pid));
  }

  Serial.println();
}
