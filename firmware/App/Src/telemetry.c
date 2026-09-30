#include "telemetry.h"
#include <stdio.h>

static const char *direction_to_string(motor_direction_t direction)
{
    return (direction == MOTOR_DIR_CCW) ? "CCW" : "CW";
}

static const char *fault_state_to_string(fault_state_t state)
{
    switch (state)
    {
        case FAULT_STATE_NORMAL: return "NORMAL";
        case FAULT_STATE_WARNING: return "WARNING";
        case FAULT_STATE_FAULT: return "FAULT";
        case FAULT_STATE_RECOVERY: return "RECOVERY";
        default: return "UNKNOWN";
    }
}

void Telemetry_UpdateRegisters(telemetry_register_image_t *image,
                               const motor_control_status_t *motor,
                               const health_snapshot_t *health,
                               const fault_fsm_t *fsm,
                               uint16_t sample_counter)
{
    if ((image == 0) || (motor == 0) || (health == 0) || (fsm == 0)) return;

    image->holding[0] = (uint16_t)(health->temperature_c * 10.0f);     /* 40001 */
    image->holding[1] = (uint16_t)(health->vibration_rms * 100.0f);    /* 40002 */
    image->holding[2] = (uint16_t)(health->current_a * 10.0f);         /* 40003 */
    image->holding[3] = health->health_score;                          /* 40004 */
    image->holding[4] = (uint16_t)fsm->active_fault;                   /* 40005 */
    image->holding[5] = (uint16_t)fsm->state;                          /* 40006 */
    image->holding[6] = sample_counter;                                /* 40007 */
    image->holding[7] = (uint16_t)(motor->rpm);                        /* 40008 */
    image->holding[8] = (uint16_t)(motor->pwm_percent);                /* 40009 */
    image->holding[9] = (uint16_t)fsm->fault_count;                    /* 40010 */
}

int Telemetry_FormatUartLine(char *buffer,
                             size_t length,
                             const motor_control_status_t *motor,
                             const health_snapshot_t *health,
                             const fault_fsm_t *fsm)
{
    if ((buffer == 0) || (length == 0U) || (motor == 0) || (health == 0) || (fsm == 0))
    {
        return 0;
    }

    return snprintf(buffer,
                    length,
                    "PWM=%lu%% DIR=%s RPM=%.0f TEMP=%.1fC VIB=%.2f CURR=%.2fA HEALTH=%u STATE=%s\r\n",
                    (unsigned long)motor->pwm_percent,
                    direction_to_string(motor->direction),
                    motor->rpm,
                    health->temperature_c,
                    health->vibration_rms,
                    health->current_a,
                    health->health_score,
                    fault_state_to_string(fsm->state));
}
