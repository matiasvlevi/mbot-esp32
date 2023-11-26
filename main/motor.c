#include "motor.h"
#include <esp_log.h>
#include "driver/mcpwm.h"

void mbot_motor_init(void) 
{
    // Init 2 MCPWM
    ESP_ERROR_CHECK(mcpwm_gpio_init(
        MCPWM_UNIT_0, MCPWM0A, MOTOR_LEFT_GPIO));

    ESP_ERROR_CHECK(mcpwm_gpio_init(
        MCPWM_UNIT_0, MCPWM0B, MOTOR_RIGHT_GPIO));


    mcpwm_config_t pwm_config;
    pwm_config.frequency = 1000;  // Frequency of PWMxA
    pwm_config.cmpr_a = 0;        // Duty cycle of PWMxA
    pwm_config.cmpr_b = 0;        // Duty cycle of PWMxB
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;

    // Set the configurations
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config); 
      
}

void mbot_motor_drive(float left, float right) 
{
  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, left);
  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, right);

  //Start MCPWM unit 0 on both signals
  mcpwm_start(MCPWM_UNIT_0, MCPWM_TIMER_0);
}

void mbot_motor_stop(void)
{
  mcpwm_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
}


