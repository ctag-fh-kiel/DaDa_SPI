# DaDa_SPI Arduino Library

## Overview
DaDa_SPI is an Arduino library designed for efficient SPI DMA (Direct Memory Access) transmissions on the RP2040 & RP2350 microcontroller (Raspberry Pi Pico and compatible boards). It provides a dedicated interface for high-speed, non-blocking SPI data transfers, making it ideal for applications that require fast and reliable communication with SPI peripherals.

## Features
- Easy-to-use API for SPI DMA transmissions
- Supports RP2040, RP2350 (Raspberry Pi Pico and similar)
- Non-blocking, high-speed data transfer
- Designed for integration with custom audio, sensor, or display projects

## Installation
1. Download or clone this repository.
2. Copy the `DaDa_SPI` folder to your Arduino `libraries` directory.
3. Restart the Arduino IDE and include the library in your project.

## Usage
Include the library in your Arduino sketch:

```cpp
#include <DaDa_SPI.h>
```

Refer to the `examples/` directory for sample code and usage patterns.

## Documentation
- **API Reference:** See `DaDa_SPI.h` for available functions and usage.
- **Examples:** The `examples/` folder contains sample sketches demonstrating typical use cases.

## License
This library is released under the MIT License. See `LICENSE.txt` for details.