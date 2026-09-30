# Pin Map and Peripheral Notes

## STM32 device

- **MCU:** STM32F103C8T6
- **Toolchain:** STM32CubeIDE / STM32 HAL

## Timer outputs from uploaded motor-control project

| Function | Peripheral | Pin |
|---|---|---|
| Motor PWM 1 | TIM1 CH2 | PA9 |
| Motor PWM 2 | TIM2 CH1 | PA0 |
| Motor PWM 3 | TIM3 CH1 | PA6 |

## Direction GPIOs

| Function | Pin |
|---|---|
| Motor 1 direction | PA11 |
| Motor 2 direction | PA12 |
| Motor 3 direction | PA13 |

## Timer configuration notes

The uploaded PWM example configures a timer period of **999**, which makes it convenient to treat compare values as a 0–999 duty range.

Example:

- compare = 0   → 0%
- compare = 500 → 50%
- compare = 999 → ~100%

## Monitoring-layer peripheral ideas

The combined project documentation assumes typical peripheral expansion such as:

- **ADC** for analog current measurement
- **I2C / SPI** for temperature or vibration sensors
- **UART** for debug telemetry
- **RS-485 transceiver** for Modbus RTU
- **DMA** for low-overhead acquisition or logging

These are documented as next-step integration items rather than claimed as fully validated board-specific hardware in the uploaded CubeIDE project.
