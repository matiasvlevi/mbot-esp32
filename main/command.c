#include "command.h"

#include "esp_log.h"
#include "driver/gpio.h"

#include "motor.h"

void mbot_handle_motor_control(mbot_command_arg_t *args) {
    // Default to none
    if (!args[0]) args[0] = 0x00;

    switch (args[0]) {
        case NONE: break;
        
        case FORWARD:
            mbot_motor_drive(80, 80);
            break;

        case LEFT:
            mbot_motor_drive(0, 80);
            break;

        case RIGHT:
            mbot_motor_drive(80, 0);
            break;

        case BRAKE:
            mbot_motor_drive(0, 0);
            mbot_motor_stop();
            break;
    }
}

void mbot_handle_command(mbot_commad_t command, mbot_command_arg_t *args) 
{

    ESP_LOGE("Recieved Command: ", " >>> %d", command);

    ESP_LOGE("Recieved Command: ", "Arguments: %x %x", args[0], args[1]);


    switch(command) {
        case NONE: break;
        
        case GPIO_CONTROL_MODE:
            if (!args[0]) args[0] = 12;
            if (!args[1]) args[1] = 0;

            gpio_reset_pin(args[0]);
            gpio_set_direction(args[0], args[1]);

            break;

        case GPIO_CONTROL_WRITE:
            if (!args[0]) args[0] = 12;
            // if (!args[1]) args[1] = 1;

            gpio_set_level(args[0], args[1]);
            break;

        case MOTOR_CONTROL:
            mbot_handle_motor_control(args);
            break;


    }
}
