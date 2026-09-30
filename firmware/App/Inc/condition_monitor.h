#ifndef CONDITION_MONITOR_H
#define CONDITION_MONITOR_H

#include <stdint.h>
#include "app_types.h"

typedef struct
{
    float temp_warn_c;
    float temp_fault_c;
    float vib_warn;
    float vib_fault;
    float current_warn_a;
    float current_fault_a;
    float alpha;
} condition_monitor_config_t;

void ConditionMonitor_GetDefaultConfig(condition_monitor_config_t *config);
void ConditionMonitor_Init(const condition_monitor_config_t *config);
void ConditionMonitor_Update(const motor_raw_sample_t *sample,
                             health_snapshot_t *snapshot);

#endif /* CONDITION_MONITOR_H */
