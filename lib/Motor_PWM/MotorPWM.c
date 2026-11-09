#include "MotorPWM.h"
//SET DUTY
gpio_set_direction(PWM_PIN, OUTPUT);

static const char* TAG = "MyModule";

void motor_init(struct Motor *m)
{
    mcpwm_comparator_config_t cmpr_cfg = {};
    cmpr_cfg.flags.update_cmp_on_tez = true;
    ESP_ERROR_CHECK(mcpwm_new_comparator(m->oper, &cmpr_cfg, &m->cmpr));
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(m->cmpr, 0));

    mcpwm_generator_config_t gen_cfg = {};
    gen_cfg.gen_gpio_num = m->gpio;
    ESP_ERROR_CHECK(mcpwm_new_generator(m->oper, &gen_cfg, &m->gen));

    // timer empty -> HIGH, compare match -> LOW
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(
        m->gen,
        MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP,
                                     MCPWM_TIMER_EVENT_EMPTY,
                                     MCPWM_GEN_ACTION_HIGH)));
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(
        m->gen,
        MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP,
                                       m->cmpr,
                                       MCPWM_GEN_ACTION_LOW)));

    ESP_ERROR_CHECK(mcpwm_timer_enable(m->timer));
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(m->timer, MCPWM_TIMER_START_NO_STOP));

    ESP_LOGI(TAG, "GPIO configured", m->gpio);
}

void updateMotor(struct Motor *m, motorState_t state, float duty)
{
    switch(state)
    {
        case motorOFF:
            setDuty(m, 0);
            break;

        case motorForward:
            setDuty(m, duty);    
            break;
    }
}
static void setDuty(struct Motor *m, float dutyPercent)
{
    if (dutyPercent < 0)   dutyPercent = 0;
    if (dutyPercent > 100) dutyPercent = 100;
    uint32_t cmp = (uint32_t)(dutyPercent / 100.0f * PWM_PERIOD_TICKS);
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(m->cmpr, cmp));
}
