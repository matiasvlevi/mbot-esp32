#ifndef _MBOT_ACTIONS_
#define _MBOT_ACTIONS_

#define NONE 0x00

#ifndef _ESP_HTTP_SERVER_INC_
#define _ESP_HTTP_SERVER_INC_
#include <esp_http_server.h>
#endif /* _ESP_HTTP_SERVER_INC_ */

#define RESPONSE(buffer)          \
	ws_pkt->len = sizeof(buffer); \
	ws_pkt->payload = buffer;

typedef enum mbot_commad {
	NOP = 0x00,
	GPIO_CONTROL_MODE = 0x7F,
	GPIO_CONTROL_WRITE = 0x80,
	MOTOR_CONTROL = 0xC0,
	SENSOR_ULTRASOUND = 0xD0
} mbot_commad_t;

typedef unsigned char mbot_command_arg_t;

void handle_motor_command(mbot_command_arg_t *args);

void mbot_handle_command(mbot_commad_t action, mbot_command_arg_t *args,
						 httpd_ws_frame_t *ws_pkt);

#endif
