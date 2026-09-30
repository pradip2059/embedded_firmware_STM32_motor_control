#ifndef APP_LOGIC_H
#define APP_LOGIC_H

#include <stdint.h>
#include "telemetry.h"
#include "fault_fsm.h"
#include "condition_monitor.h"
#include "motor_control.h"
#include "sensor_sim.h"

typedef struct
{
    motor_control_status_t motor;
    motor_raw_sample_t raw_sample;
    health_snapshot_t health;
    fault_fsm_t fsm;
    telemetry_register_image_t registers;
    uint16_t sample_counter;
} app_context_t;

void AppLogic_Init(app_context_t *context);
void AppLogic_Step(app_context_t *context, uint32_t tick_ms);

#endif /* APP_LOGIC_H */
