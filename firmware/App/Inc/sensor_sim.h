#ifndef SENSOR_SIM_H
#define SENSOR_SIM_H

#include <stdint.h>
#include "app_types.h"

void SensorSim_Generate(uint32_t tick_ms,
                        const motor_control_status_t *motor,
                        motor_raw_sample_t *sample);

#endif /* SENSOR_SIM_H */
