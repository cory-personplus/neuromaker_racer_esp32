//GOAL: SWITCH FROM ARDUINO FRAMEWORK TO ESP FRAMEWORK FOR CODE MANIPULATION

//TEST

//NECESSARY FILES TO INCLUDE FOR MOTOR PWM 
#include "MotorPWM.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//SEPERATE CODE INTO DIFF FILES -> MOTOR PWM.h FILE, MOTOR PWM.c, HUD DISPLAY, ITEM ACQUISIITON (START / FINISH), INCOMING EEG ALGORITHM file?
void app_main() {

    motor_init(&motor);

    updateMotor(&motor, motorForward, 25.0f);

    vTaskDelay(pdMS_TO_TICKS(6000));

    updateMotor(&motor, motorForward, 50.0f);


}



