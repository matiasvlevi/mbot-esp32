#ifndef _MBOT_ACTIONS_
#define _MBOT_ACTIONS_

#define NONE 0x00

typedef enum mbot_commad {
    NOP = 0x00,
    GPIO_CONTROL_MODE = 0x7F,
    GPIO_CONTROL_WRITE  = 0x80,
    MOTOR_CONTROL = 0xC0
} mbot_commad_t;

typedef unsigned char mbot_command_arg_t;

void handle_motor_command(mbot_command_arg_t *args);

void mbot_handle_command(mbot_commad_t action, mbot_command_arg_t *args);

#endif
