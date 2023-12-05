idf_component_register(SRCS "command.c" "wifi.c" "main.c" "motor.c" "ultrasound.c"
                    INCLUDE_DIRS "."
                    REQUIRES esp_http_server
                    REQUIRES esp_wifi
                    REQUIRES esp_eth
                    REQUIRES nvs_flash)