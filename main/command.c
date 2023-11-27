#include "command.h"


#include "driver/gpio.h"
#include "esp_log.h"

#include "motor.h"

void handle_motor_command(mbot_command_arg_t *args) 
{

    if ((int8_t)args[1] < 0) 
    {
        args[0] &= ~(1 << 7);
        mbot_motor_set_dir_right(0);
    } 
    else
    { 
        mbot_motor_set_dir_right(1);
    }

    // If sign bit on, motor goes backwars
    if ((int8_t)args[1] < 0) 
    {
        args[1] &= ~(1 << 7);
        mbot_motor_set_dir_left(0); 
    } 
    else 
    { 
        mbot_motor_set_dir_right(1);
    }
   
    mbot_motor_set_duty((float)(char)args[0], (float)(char)args[1]);
}

void mbot_handle_command(mbot_commad_t command, mbot_command_arg_t *args) {

  ESP_LOGE("Recieved Command: ", " >>> %d", command);
  ESP_LOGE("Recieved Command: ", "Arguments: %x %x", args[0], args[1]);

  switch (command) {
  case NONE:
    break;

  case GPIO_CONTROL_MODE:
    if (!args[0])
      args[0] = 12;

    if (!args[1])
      args[1] = 0;

    gpio_reset_pin(args[0]);
    gpio_set_direction(args[0], args[1]);

    break;

  case GPIO_CONTROL_WRITE:
    if (!args[0])
      args[0] = 12;

    gpio_set_level(args[0], args[1]);
    break;

  case MOTOR_CONTROL:
    handle_motor_command(args);
    break;
  }
}
