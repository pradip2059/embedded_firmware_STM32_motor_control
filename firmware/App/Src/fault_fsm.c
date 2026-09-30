#include "fault_fsm.h"

void FaultFsm_Init(fault_fsm_t *fsm)
{
    if (fsm == 0) return;
    fsm->state = FAULT_STATE_NORMAL;
    fsm->active_fault = FAULT_CODE_NONE;
    fsm->warning_count = 0U;
    fsm->fault_count = 0U;
    fsm->persistence_counter = 0U;
}

void FaultFsm_Update(fault_fsm_t *fsm,
                     const health_snapshot_t *snapshot,
                     float temp_fault_c,
                     float vib_fault,
                     float current_fault_a)
{
    uint8_t fault_detected = 0U;
    fault_code_t fault_code = FAULT_CODE_NONE;

    if ((fsm == 0) || (snapshot == 0)) return;

    if (snapshot->temperature_c >= temp_fault_c)
    {
        fault_detected = 1U;
        fault_code = FAULT_CODE_OVER_TEMPERATURE;
    }
    else if (snapshot->vibration_rms >= vib_fault)
    {
        fault_detected = 1U;
        fault_code = FAULT_CODE_HIGH_VIBRATION;
    }
    else if (snapshot->current_a >= current_fault_a)
    {
        fault_detected = 1U;
        fault_code = FAULT_CODE_OVER_CURRENT;
    }

    if (fault_detected)
    {
        if (fsm->persistence_counter < 255U)
        {
            fsm->persistence_counter++;
        }

        if (fsm->persistence_counter >= 3U)
        {
            fsm->state = FAULT_STATE_FAULT;
            fsm->active_fault = fault_code;
            fsm->fault_count++;
        }
        else
        {
            fsm->state = FAULT_STATE_WARNING;
            fsm->active_fault = fault_code;
            fsm->warning_count++;
        }
        return;
    }

    if (snapshot->health_score < 80U)
    {
        fsm->state = FAULT_STATE_WARNING;
        fsm->active_fault = FAULT_CODE_NONE;
        fsm->warning_count++;
        if (fsm->persistence_counter > 0U) fsm->persistence_counter--;
        return;
    }

    if (fsm->state == FAULT_STATE_FAULT || fsm->state == FAULT_STATE_WARNING)
    {
        fsm->state = FAULT_STATE_RECOVERY;
    }
    else
    {
        fsm->state = FAULT_STATE_NORMAL;
    }

    fsm->active_fault = FAULT_CODE_NONE;
    fsm->persistence_counter = 0U;
}
