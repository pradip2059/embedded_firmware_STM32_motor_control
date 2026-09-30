# Application-Layer Firmware Modules

This folder contains original application-layer example code showing how the PWM motor-control project can be extended into a condition-monitoring firmware architecture.

Modules included:

- `motor_control.*` — PWM duty and direction status helpers.
- `sensor_sim.*` — synthetic sensor-data generator used for demonstration and validation.
- `condition_monitor.*` — filtering, severity calculation, and health score generation.
- `fault_fsm.*` — NORMAL / WARNING / FAULT / RECOVERY state machine.
- `telemetry.*` — UART line formatting and Modbus-style holding-register image.
- `app_logic.*` — one-step integration example tying the pieces together.

These modules are written to be easy to port into a CubeIDE project. The original uploaded CubeIDE motor-control example did not include ADC, UART, or Modbus peripheral initialization, so those pieces are documented here at the application layer rather than claimed as a fully verified board-specific hardware implementation.
