#ifndef _MOTOR_H_
#define _MOTOR_H_

#define MOTOR_LEFT_GPIO 18
#define MOTOR_RIGHT_GPIO 26

void mbot_motor_init(void);

void mbot_motor_drive(float left, float right);

void mbot_motor_stop(void);

#endif /* _MOTOR_H_ */
