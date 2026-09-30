#include "condition_monitor.h"

static condition_monitor_config_t g_cfg;
static health_snapshot_t g_filtered;
static uint8_t g_initialized = 0U;

static float clampf(float value, float low, float high)
{
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

static uint8_t compute_penalty(float value, float warn, float fault)
{
    float penalty;
    if (value <= warn) return 0U;
    if (value >= fault) return 100U;

    penalty = 50.0f * (value - warn) / (fault - warn);
    if (penalty < 0.0f) penalty = 0.0f;
    if (penalty > 100.0f) penalty = 100.0f;
    return (uint8_t)penalty;
}

void ConditionMonitor_GetDefaultConfig(condition_monitor_config_t *config)
{
    if (config == 0) return;
    config->temp_warn_c = 55.0f;
    config->temp_fault_c = 70.0f;
    config->vib_warn = 2.5f;
    config->vib_fault = 4.0f;
    config->current_warn_a = 2.0f;
    config->current_fault_a = 3.0f;
    config->alpha = 0.25f;
}

void ConditionMonitor_Init(const condition_monitor_config_t *config)
{
    if (config != 0)
    {
        g_cfg = *config;
    }
    else
    {
        ConditionMonitor_GetDefaultConfig(&g_cfg);
    }
    g_filtered.temperature_c = 0.0f;
    g_filtered.vibration_rms = 0.0f;
    g_filtered.current_a = 0.0f;
    g_filtered.health_score = 100U;
    g_initialized = 0U;
}

void ConditionMonitor_Update(const motor_raw_sample_t *sample,
                             health_snapshot_t *snapshot)
{
    float health;
    if ((sample == 0) || (snapshot == 0)) return;

    if (!g_initialized)
    {
        g_filtered.temperature_c = sample->temperature_c;
        g_filtered.vibration_rms = sample->vibration_rms;
        g_filtered.current_a = sample->current_a;
        g_initialized = 1U;
    }
    else
    {
        float a = clampf(g_cfg.alpha, 0.0f, 1.0f);
        g_filtered.temperature_c = a * sample->temperature_c + (1.0f - a) * g_filtered.temperature_c;
        g_filtered.vibration_rms = a * sample->vibration_rms + (1.0f - a) * g_filtered.vibration_rms;
        g_filtered.current_a = a * sample->current_a + (1.0f - a) * g_filtered.current_a;
    }

    g_filtered.temp_penalty = compute_penalty(g_filtered.temperature_c, g_cfg.temp_warn_c, g_cfg.temp_fault_c);
    g_filtered.vib_penalty = compute_penalty(g_filtered.vibration_rms, g_cfg.vib_warn, g_cfg.vib_fault);
    g_filtered.current_penalty = compute_penalty(g_filtered.current_a, g_cfg.current_warn_a, g_cfg.current_fault_a);

    health = 100.0f
           - (0.35f * g_filtered.temp_penalty)
           - (0.40f * g_filtered.vib_penalty)
           - (0.25f * g_filtered.current_penalty);

    if (health < 0.0f) health = 0.0f;
    if (health > 100.0f) health = 100.0f;

    g_filtered.health_score = (uint8_t)health;
    *snapshot = g_filtered;
}
