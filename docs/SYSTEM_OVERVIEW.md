# System Overview

## Purpose

This project demonstrates how a simple STM32 motor-control firmware can be expanded into a more industrial embedded-firmware design with basic condition monitoring and diagnostic telemetry.

## Functional Blocks

1. **Motor control** — generate PWM waveforms and control direction.
2. **Sensor acquisition** — obtain temperature, vibration, and current measurements.
3. **Signal conditioning** — filter noisy measurements.
4. **Health estimation** — convert filtered values into severity penalties and a health score.
5. **Fault state machine** — determine whether the system is in NORMAL, WARNING, FAULT, or RECOVERY.
6. **Telemetry layer** — expose data through UART and a Modbus-style register image.

## Control + Monitoring Flow

```text
PWM Command --> Timer Compare Values --> Motor Driver --> Motor Speed / Direction
                                  |
                                  v
                     Diagnostic Context / Operating Point
                                  |
Sensors --> Filter --> Health Score --> Fault FSM --> UART / Register Map
```

## Portfolio Scope

The uploaded source material included:

- a real STM32CubeIDE PWM motor-control example, and
- a separate predictive-maintenance architecture concept.

This portfolio repository combines those ideas into a coherent single project and adds a reusable application-layer firmware example to show how the features fit together in a resume-ready embedded project.
