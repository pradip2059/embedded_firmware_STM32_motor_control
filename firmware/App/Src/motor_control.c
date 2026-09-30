#include "motor_control.h"

static float clampf(float value, float low, float high)
{
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

uint16_t MotorControl_PercentToCompare(float percent)
{
    float bounded = clampf(percent, 0.0f, 100.0f);
    return (uint16_t)((bounded / 100.0f) * MOTOR_PWM_PERIOD_COUNTS);
}

void MotorControl_SetStatus(motor_control_status_t *status,
                            float pwm_percent,
                            float rpm,
                            motor_direction_t direction)
{
    if (status == 0) return;
    status->pwm_percent = clampf(pwm_percent, 0.0f, 100.0f);
    status->pwm_compare = MotorControl_PercentToCompare(status->pwm_percent);
    status->rpm = rpm;
    status->direction = direction;
}

void MotorControl_GenerateDemoProfile(uint32_t tick_ms,
                                      motor_control_status_t *status)
{
    uint32_t phase = (tick_ms / 1000U) % 20U;
    float pwm = 0.0f;
    float rpm = 0.0f;
    motor_direction_t dir = MOTOR_DIR_CW;

    if (phase < 10U)
    {
        pwm = (float)(phase * 10U);
        dir = MOTOR_DIR_CW;
    }
    else
    {
        pwm = (float)((20U - phase) * 10U);
        dir = MOTOR_DIR_CCW;
    }

    rpm = pwm * 30.0f;
    MotorControl_SetStatus(status, pwm, rpm, dir);
}
