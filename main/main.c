#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "shift_register.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"



uint8_t stepper_command[] = {
  0b11000000,
  0b01100000,
  0b00110000,
  0b10010000
};


void stepper_task(void* args) {
  
  shift_register_t sr;
  shift_register__init(&sr, 16, 17, 18, 8);

  while (1) {
    for (uint8_t i=0; i < 4; i++) {
      shift_register__send(&sr, stepper_command[i]);
      vTaskDelay(pdMS_TO_TICKS(10));
    }
  }
}


void app_main(void) {
  xTaskCreate(stepper_task, "stepper_task", 2048, NULL, 5, NULL);
}
