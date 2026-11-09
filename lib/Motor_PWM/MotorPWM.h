#include <stdio.h>
#include "driver/mcpwm_timer.h"
#include "driver/mcpwm_prelude.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/gpio.h"


#define PWM_PIN GPIO_NUM_9  //Pin for one motor
#define PWM_PERIOD_TICKS 1000   //Period of 1KHZ

typedef enum {motorOFF, motorForward} motorState_t; //motor OFF or motor FORWARD

struct Motor {
    int gpio;
    mcpwm_timer_handle_t timer;
    mcpwm_oper_handle_t oper;
    mcpwm_cmpr_handle_t cmpr;
    mcpwm_gen_handle_t gen;
};

struct Motor motor  = {PWM_PIN, NULL, NULL, NULL, NULL };

//MAIN FUNCTIONS
static void motor_init(struct Motor *m);
void updateMotor(struct Motor *m, motorState_t state, float duty);
static void setDuty(struct Motor *m, float dutyPercent);
