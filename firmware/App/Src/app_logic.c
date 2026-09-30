#include "app_logic.h"

void AppLogic_Init(app_context_t *context)
{
    condition_monitor_config_t cfg;
    if (context == 0) return;

    ConditionMonitor_GetDefaultConfig(&cfg);
    ConditionMonitor_Init(&cfg);
    FaultFsm_Init(&context->fsm);
    MotorControl_SetStatus(&context->motor, 0.0f, 0.0f, MOTOR_DIR_CW);
    context->sample_counter = 0U;
}

void AppLogic_Step(app_context_t *context, uint32_t tick_ms)
{
    condition_monitor_config_t cfg;
    if (context == 0) return;

    ConditionMonitor_GetDefaultConfig(&cfg);
    MotorControl_GenerateDemoProfile(tick_ms, &context->motor);
    SensorSim_Generate(tick_ms, &context->motor, &context->raw_sample);
    ConditionMonitor_Update(&context->raw_sample, &context->health);
    FaultFsm_Update(&context->fsm,
                    &context->health,
                    cfg.temp_fault_c,
                    cfg.vib_fault,
                    cfg.current_fault_a);
    Telemetry_UpdateRegisters(&context->registers,
                              &context->motor,
                              &context->health,
                              &context->fsm,
                              context->sample_counter++);
}
