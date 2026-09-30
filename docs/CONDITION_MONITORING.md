# Condition Monitoring

## Signals

The monitoring layer works with three diagnostic inputs:

- **Temperature**
- **Vibration RMS**
- **Motor current**

## Filtering

The example application layer uses a simple exponential smoothing filter to reduce the effect of noisy samples before fault decisions are made.

```text
filtered = alpha * new_sample + (1 - alpha) * previous_filtered
```

Default smoothing factor:

- `alpha = 0.25`

## Health Score

Each signal is converted into a bounded penalty, then combined into a 0–100 health score.

### Reference weights

- Temperature: **0.35**
- Vibration: **0.40**
- Current: **0.25**

### Interpretation

| Score | Meaning |
|---:|---|
| 80–100 | Healthy / Normal |
| 60–79 | Observe |
| 30–59 | Warning |
| 0–29 | Critical |

## Example thresholds

| Variable | Warning | Fault |
|---|---:|---:|
| Temperature | 55 °C | 70 °C |
| Vibration RMS | 2.5 | 4.0 |
| Current | 2.0 A | 3.0 A |

## Fault-state machine

```text
NORMAL -> WARNING -> FAULT -> RECOVERY -> NORMAL
```

### Logic summary

- A single mild issue can place the system in **WARNING**.
- Persistent or clearly out-of-range conditions place the system in **FAULT**.
- Once conditions clear, the machine passes through **RECOVERY** before returning to **NORMAL**.

This style of logic is common in embedded diagnostics because it avoids reacting to every noisy sample as if it were a true equipment fault.
