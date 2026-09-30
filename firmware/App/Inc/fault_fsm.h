#ifndef FAULT_FSM_H
#define FAULT_FSM_H

#include "app_types.h"

void FaultFsm_Init(fault_fsm_t *fsm);
void FaultFsm_Update(fault_fsm_t *fsm,
                     const health_snapshot_t *snapshot,
                     float temp_fault_c,
                     float vib_fault,
                     float current_fault_a);

#endif /* FAULT_FSM_H */
