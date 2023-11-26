/* WebSocket Echo Server Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <unistd.h>
#include <esp_wifi.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_eth.h"
#include <esp_http_server.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#include "command.h"

#include "motor.h"

#include "wifi.h"

/* A simple example that demonstrates using websocket echo server
 */
static const char *TAG = "ws_echo_server";

/*
 * Structure holding server handle
 * and internal socket fd in order
 * to use out of request send
 */
struct async_resp_arg {
  httpd_handle_t hd;
  int fd;
};


/*
 * async send function, which we put into the httpd work queue
 */
static void ws_async_send(void *arg) {
  static const char *data = "Async data";
  struct async_resp_arg *resp_arg = arg;
  
  httpd_handle_t hd = resp_arg->hd;
  
  int fd = resp_arg->fd;

  httpd_ws_frame_t ws_pkt;
  memset(&ws_pkt, 0, sizeof(httpd_ws_frame_t));
  
  ws_pkt.payload = (uint8_t *)data;
  ws_pkt.len = strlen(data);
  ws_pkt.type = HTTPD_WS_TYPE_TEXT;

  httpd_ws_send_frame_async(hd, fd, &ws_pkt);
  free(resp_arg);
}

static esp_err_t trigger_async_send(httpd_handle_t handle, httpd_req_t *req) {
  struct async_resp_arg *resp_arg = malloc(sizeof(struct async_resp_arg));
  resp_arg->hd = req->handle;
  resp_arg->fd = httpd_req_to_sockfd(req);
  return httpd_queue_work(handle, ws_async_send, resp_arg);
}

/*
 * This handler echos back the received ws data
 * and triggers an async send if certain message received
 */
static esp_err_t echo_handler(httpd_req_t *req)
{
    if (req->method == HTTP_GET) {
        ESP_LOGI(TAG, "Handshake done, the new connection was opened");
        return ESP_OK;
    }

    httpd_ws_frame_t ws_pkt;
    memset(&ws_pkt, 0, sizeof(httpd_ws_frame_t));
    ws_pkt.type = HTTPD_WS_TYPE_TEXT;
    /* Set max_len = 0 to get the frame len */
    esp_err_t ret = httpd_ws_recv_frame(req, &ws_pkt, 0);

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "httpd_ws_recv_frame failed to get frame len with %d", ret);
        return ret;
    }

    ESP_LOGI(TAG, "frame len is %d", ws_pkt.len);

    /* ws_pkt.len + 1 is for NULL termination as we are expecting a string */
    uint8_t *buf = calloc(1, ws_pkt.len + 1);
    if (buf == NULL) {
        ESP_LOGE(TAG, "Failed to calloc memory for buf");
        return ESP_ERR_NO_MEM;
    }
    ws_pkt.payload = buf;

    /* Set max_len = ws_pkt.len to get the frame payload */
    ret = httpd_ws_recv_frame(req, &ws_pkt, ws_pkt.len);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "httpd_ws_recv_frame failed with %d", ret);
        return ret;
    }

    ESP_LOGI(TAG, "Got packet with message: %s", ws_pkt.payload);
    ESP_LOGI(TAG, "Packet type: %d", ws_pkt.type);
    if (ws_pkt.type == HTTPD_WS_TYPE_TEXT &&
        strcmp((char*)ws_pkt.payload,"Trigger async") == 0) {
        free(buf);
        buf = NULL;
        return trigger_async_send(req->handle, req);
    }

    // Cast 1st Byte as Command Byte
    mbot_commad_t command = ws_pkt.payload[0];

    mbot_handle_command(command, ws_pkt.payload + 1);

    uint8_t response[] = "Ok";
    ws_pkt.len = sizeof(response);
    ws_pkt.payload = response;

    ret = httpd_ws_send_frame(req, &ws_pkt);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "httpd_ws_send_frame failed with %d", ret);
    }
    free(buf);
    buf = NULL;
    return ret;
}

static esp_err_t homepage_handler(httpd_req_t *req) {
  ESP_LOGE(TAG, "Hit on homepage!");

  const char resp[] = "<h1>HELLO FROM ESP32</h1>";
  return httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
}


static const httpd_uri_t ws = {.uri = "/ws",
                               .method = HTTP_GET,
                               .handler = echo_handler,
                               .user_ctx = NULL,
                               .is_websocket = true};

static const httpd_uri_t page = {.uri = "/",
                               .method = HTTP_GET,
                               .handler = homepage_handler,
                               .user_ctx = NULL,
                               .is_websocket = false};

static httpd_handle_t start_webserver(void) {
  httpd_handle_t server = NULL;
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.lru_purge_enable = true;

  // Start the httpd server
  ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
  if (httpd_start(&server, &config) == ESP_OK) {
    // Registering the ws handler
    ESP_LOGI(TAG, "Registering URI handlers");
    httpd_register_uri_handler(server, &ws);
    httpd_register_uri_handler(server, &page);
    return server;
  }

  ESP_LOGI(TAG, "Error starting server!");
  return NULL;
}

static void stop_webserver(httpd_handle_t server) {
  // Stop the httpd server
  httpd_stop(server);
}

static void disconnect_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data) {
  httpd_handle_t *server = (httpd_handle_t *)arg;
  if (*server) {
    ESP_LOGI(TAG, "Stopping webserver");
    stop_webserver(*server);
    *server = NULL;
  }
}

static void connect_handler(void *arg, esp_event_base_t event_base,
                            int32_t event_id, void *event_data) {
  httpd_handle_t *server = (httpd_handle_t *)arg;
  if (*server == NULL) {
    ESP_LOGI(TAG, "Starting webserver");
    *server = start_webserver();
  }
}

static esp_err_t init_nvram(void) {
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    return (ret);
}

void app_websockets(void) 
{
  static httpd_handle_t server = NULL;
  
  wifi_init_sta();

  ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &connect_handler, &server));
  ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &disconnect_handler, &server));

  server = start_webserver();
}

static void example_motor() {

  mbot_motor_drive(0, 0);

  vTaskDelay(2000 / portTICK_PERIOD_MS);
 
  for (int i = 0; i < 2; i++) {
    mbot_motor_drive(100, 100);

    vTaskDelay(1000 / portTICK_PERIOD_MS);

    if (i % 2) mbot_motor_drive(0, 100);
    else mbot_motor_drive(100, 0);

    vTaskDelay(650 / portTICK_PERIOD_MS);

    mbot_motor_drive(45, 45);

    vTaskDelay(650 / portTICK_PERIOD_MS);
  }


  mbot_motor_drive(100, 100);

  vTaskDelay(800 / portTICK_PERIOD_MS);

  mbot_motor_drive(0, 100);

  vTaskDelay(3500 / portTICK_PERIOD_MS);




  mbot_motor_drive(0, 0);
  mbot_motor_stop();

  while (true) {
    vTaskDelay(1);
  }


}

void app_main(void) 
{
  ESP_ERROR_CHECK(nvs_flash_init());
  ESP_ERROR_CHECK(esp_netif_init());


  mbot_motor_init();
  app_websockets();
}
