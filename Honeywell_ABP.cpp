#include "Honeywell_ABP.h"

Honeywell_ABP::Honeywell_ABP(uint8_t address, float p_min, float p_max, String unit_string) {
  _address = address;
  _p_min = p_min;
  _p_max = p_max;
  set_unit(unit_string);
}

void Honeywell_ABP::set_unit(String unit_string) {
  if (unit_string == "psi")
    _unit = UNIT_PSI;
  else if (unit_string == "pa")
    _unit = UNIT_PA;
  else if (unit_string == "kpa")
    _unit = UNIT_KPA;
  else if (unit_string == "mpa")
    _unit = UNIT_MPA;
  else if (unit_string == "mbar")
    _unit = UNIT_MBAR;
  else if (unit_string == "bar")
    _unit = UNIT_BAR;
  else
    _unit = UNIT_UNKNOWN;
}

void Honeywell_ABP::update() {
  Wire.requestFrom(_address, (uint8_t)2);
  while(Wire.available()) {
    uint8_t data_byte_1 = Wire.read();
    uint8_t data_byte_2 = Wire.read();
    _status = Honeywell_ABP::Status(data_byte_1 >> 6);
    _bridge_data = (data_byte_1 << 8 | data_byte_2) & 0x3FFF;
  }
  _pressure = raw_to_pressure(_bridge_data);
}

float Honeywell_ABP::raw_to_pressure(uint16_t output) {
  return float(constrain(output, _output_min, _output_max) - _output_min)
    * (_p_max - _p_min) / (_output_max - _output_min) + _p_min;
}

const char* Honeywell_ABP::unit() const {
  switch(_unit) {
    case UNIT_PSI:
      return "psi";
    case UNIT_PA:
      return "Pa";
    case UNIT_KPA:
      return "kPa";
    case UNIT_MPA:
      return "MPa";
    case UNIT_MBAR:
      return "mbar";
    case UNIT_BAR:
      return "bar";
    case UNIT_UNKNOWN:
      return "(unknown unit)";
    default:
      return "(unknown unit)";
  }
}

const char* Honeywell_ABP::error_msg() const {
  switch(_status) {
    case STATUS_NOERROR:
      return "No error";
    case STATUS_COMMANDMODE:
      return "Device in command mode (this mode should not be seen during normal operation)";
    case STATUS_STALEDATA:
      return "Stale data";
    case STATUS_DIAGNOTIC:
      return "Diagnostic condition";
    default:
      return "Unknown error";
  }
}
