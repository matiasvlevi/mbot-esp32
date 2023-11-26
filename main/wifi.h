#ifndef _WIFI_
#define _WIFI_
#include <stdint.h>

struct esp_event_base_t {};

static void event_handler(
    void* arg, 
    esp_event_base_t event_base,
    int32_t event_id, 
    void* event_data
);

void wifi_init_sta(void);

#endif /* _WIFI_ */