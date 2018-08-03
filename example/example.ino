#include "Honeywell_ABP.h"

// create Honeywell_ABP instance
// refer to datasheet for parameters
Honeywell_ABP abp(
  0x28,   // I2C address
  0,      // minimum pressure
  1,      // maximum pressure
  "psi"   // pressure unit
);

void setup() {
  // open serial communication
  Serial.begin(9600);

  // open I2C communication
  Wire.begin();
}

void loop() {
  // update sensor reading
  abp.update();

  // print sensor reading via serial
  Serial.print("Pressure: ");
  Serial.print(abp.pressure());
  Serial.print(" ");
  Serial.println(abp.unit());

  delay(500);
}
