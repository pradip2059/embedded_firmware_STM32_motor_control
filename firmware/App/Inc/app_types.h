#ifndef APP_TYPES_H
#define APP_TYPES_H

#include <stdint.h>

typedef enum
{
    MOTOR_DIR_CW = 0,
    MOTOR_DIR_CCW = 1
} motor_direction_t;

typedef struct
{
    float pwm_percent;
    uint16_t pwm_compare;
    float rpm;
    motor_direction_t direction;
} motor_control_status_t;

typedef struct
{
    float temperature_c;
    float vibration_rms;
    float current_a;
} motor_raw_sample_t;

typedef struct
{
    float temperature_c;
    float vibration_rms;
    float current_a;
    uint8_t temp_penalty;
    uint8_t vib_penalty;
    uint8_t current_penalty;
    uint8_t health_score;
} health_snapshot_t;

typedef enum
{
    FAULT_CODE_NONE = 0,
    FAULT_CODE_OVER_TEMPERATURE = 1,
    FAULT_CODE_HIGH_VIBRATION = 2,
    FAULT_CODE_OVER_CURRENT = 3,
    FAULT_CODE_SENSOR_RANGE = 4
} fault_code_t;

typedef enum
{
    FAULT_STATE_NORMAL = 0,
    FAULT_STATE_WARNING = 1,
    FAULT_STATE_FAULT = 2,
    FAULT_STATE_RECOVERY = 3
} fault_state_t;

typedef struct
{
    fault_state_t state;
    fault_code_t active_fault;
    uint16_t warning_count;
    uint16_t fault_count;
    uint8_t persistence_counter;
} fault_fsm_t;

#endif /* APP_TYPES_H */
