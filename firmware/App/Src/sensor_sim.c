#include "sensor_sim.h"

static float absf(float x)
{
    return (x < 0.0f) ? -x : x;
}

void SensorSim_Generate(uint32_t tick_ms,
                        const motor_control_status_t *motor,
                        motor_raw_sample_t *sample)
{
    float duty_norm;
    float t;
    if ((motor == 0) || (sample == 0)) return;

    duty_norm = motor->pwm_percent / 100.0f;
    t = (float)(tick_ms % 10000U) / 1000.0f;

    sample->temperature_c = 30.0f + (28.0f * duty_norm) + 1.5f * (t / 10.0f);
    sample->current_a = 0.35f + (2.20f * duty_norm);
    sample->vibration_rms = 0.40f + (2.8f * duty_norm);

    /* Inject a demo fault window. */
    if ((tick_ms > 14000U) && (tick_ms < 17000U))
    {
        sample->vibration_rms += 2.0f;
        sample->current_a += 0.5f;
    }

    if (motor->direction == MOTOR_DIR_CCW)
    {
        sample->vibration_rms += 0.15f;
    }

    sample->temperature_c += 0.2f * absf((float)((tick_ms / 250U) % 4U) - 1.5f);
}
