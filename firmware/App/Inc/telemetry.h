#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <stdint.h>
#include <stddef.h>
#include "app_types.h"

#define TELEMETRY_REGISTER_COUNT 10U

typedef struct
{
    uint16_t holding[TELEMETRY_REGISTER_COUNT];
} telemetry_register_image_t;

void Telemetry_UpdateRegisters(telemetry_register_image_t *image,
                               const motor_control_status_t *motor,
                               const health_snapshot_t *health,
                               const fault_fsm_t *fsm,
                               uint16_t sample_counter);

int Telemetry_FormatUartLine(char *buffer,
                             size_t length,
                             const motor_control_status_t *motor,
                             const health_snapshot_t *health,
                             const fault_fsm_t *fsm);

#endif /* TELEMETRY_H */
