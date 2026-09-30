# Telemetry and Modbus Register Map

## UART telemetry

The app-layer example formats a UART debug line similar to:

```text
PWM=60% DIR=CW RPM=1800 TEMP=43.2C VIB=1.85 CURR=1.24A HEALTH=91 STATE=NORMAL
```

This is useful for:

- serial monitor demos
- debug logging
- validation of health-score behavior
- quick bench testing before HMI integration

## Example holding registers

| Register | Meaning | Scaling |
|---:|---|---|
| 40001 | Temperature | °C × 10 |
| 40002 | Vibration RMS | value × 100 |
| 40003 | Current | A × 10 |
| 40004 | Health score | direct |
| 40005 | Active fault code | enum |
| 40006 | Fault state | enum |
| 40007 | Sample counter | direct |
| 40008 | RPM | direct |
| 40009 | PWM duty | % |
| 40010 | Fault count | direct |

## Intended integration

A future hardware iteration could expose these registers through:

- UART protocol framing,
- a simple PC tool,
- or a full **Modbus RTU** stack with an RS-485 transceiver.

That would make the node easier to connect to a PLC, SCADA package, or HMI for higher-level monitoring.
