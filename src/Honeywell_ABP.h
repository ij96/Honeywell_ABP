/*
    Arduino library for Honeywell ABP Amplified Basic digital pressure sensor

    Reference:
    - I2C Communications with Honeywell Digital Output Pressure Sensors
      https://sensing.honeywell.com/index.php?ci_id=45841
    - ABP Series datasheet
      https://sensing.honeywell.com/honeywell-sensing-basic-board-mount-pressure-abp-series-datasheet-2305128-e-en.pdf

    Author: ij96 (https://github.com/ij96)
    Date: 2018-08-03
*/

#ifndef HONEYWELL_ABP_H
#define HONEYWELL_ABP_H

#include <Arduino.h>
#include <Wire.h>

class Honeywell_ABP {
public:
  enum Unit {
    UNIT_PSI,
    UNIT_PA,
    UNIT_KPA,
    UNIT_MPA,
    UNIT_MBAR,
    UNIT_BAR,
    UNIT_UNKNOWN
  };

  enum Status {
    STATUS_NOERROR     = 0,
    STATUS_COMMANDMODE = 1,
    STATUS_STALEDATA   = 2,
    STATUS_DIAGNOTIC   = 3
  };

  Honeywell_ABP(uint8_t address, float p_min, float p_max, String unit_string);

  void set_unit(String unit_string);

  float raw_to_pressure(uint16_t output);
  void update();

  // getter functions
  uint8_t address() const {return _address;}
  uint8_t status() const {return _status;}
  uint16_t bridge_data() const {return _bridge_data;}
  float pressure() const {return _pressure;}
  const char* unit() const;
  const char* error_msg() const;

private:
  // I2C address (refer to datasheet)
  uint8_t _address;

  // pressure range (refer to datasheet)
  float _p_min; // minimum pressure
  float _p_max; // maximum pressure

  // pressure unit (refer to datasheet)
  Unit _unit;

  // sensor 14-bit output range
  uint16_t _output_min = 0x0666; // 10% of 2^14
  uint16_t _output_max = 0x399A; // 90% of 2^14

  // sensor reading
  Status _status;         // sensor status
  uint16_t _bridge_data;  // raw bridge data (14-bit)
  float _pressure;        // pressure converted from raw data
};

#endif //HONEYWELL_ABP_H
