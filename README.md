# `Honeywell_ABP` library

Arduino library for communication with Honeywell ABP Series digital pressure sensors via I<sup>2</sup>C.

## Usage
- Download and copy the `Honeywell_ABP` folder to your Arduino libraries folder (usually `C:\Users\<user_name>\Documents\Arduino\libraries`).
- Include the library in your Arduino code:
```
#include "Honeywell_ABP.h"
```

## Limitations
- Only works with I<sup>2</sup>C - SPI has not been implemented in this library.
- Does not work with ABP2 series, as its protocol is different from ABP - see [issue #6](https://github.com/ij96/Honeywell_ABP/issues/6)

## Reference
- [I<sup>2</sup>C Communications with Honeywell Digital Output Pressure Sensors](https://prod-edam.honeywell.com/content/dam/honeywell-edam/sps/siot/fr-ca/products/sensors/pressure-sensors/board-mount-pressure-sensors/common/documents/sps-siot-i2c-comms-digital-output-pressure-sensors-tn-008201-3-en-ciid-45841.pdf) (applicable to ABP but not ABP2)
- [ABP Series datasheet](https://prod-edam.honeywell.com/content/dam/honeywell-edam/sps/siot/en-us/products/sensors/pressure-sensors/board-mount-pressure-sensors/basic-abp-series/documents/sps-siot-basic-board-mount-pressure-abp-series-datasheet-32305128-ciid-155789.pdf)
