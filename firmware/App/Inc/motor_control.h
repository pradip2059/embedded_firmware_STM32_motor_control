#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <stdint.h>
#include "app_types.h"

#define MOTOR_PWM_PERIOD_COUNTS 999U

uint16_t MotorControl_PercentToCompare(float percent);
void MotorControl_SetStatus(motor_control_status_t *status,
                            float pwm_percent,
                            float rpm,
                            motor_direction_t direction);
void MotorControl_GenerateDemoProfile(uint32_t tick_ms,
                                      motor_control_status_t *status);

#endif /* MOTOR_CONTROL_H */
