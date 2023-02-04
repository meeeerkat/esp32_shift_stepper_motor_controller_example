#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "shift_register.h"
#include "shift_stepper_motor_controller.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


shift_register_t sr;
shift_stepper_motor_controller_t ssmc;

void app_main(void) {
  shift_register__init(&sr, 16, 17, 18, 8);
  shift_stepper_motor_controller__init(&ssmc, 1, &sr, 10, 5);

  QueueHandle_t* queue = shift_stepper_motor_controller_finished_movement_queue(&ssmc);
  
  shift_stepper_motor_controller__move(&ssmc, 0, 1000);

  uint8_t id;
  if (xQueueReceive(*queue, &id, portMAX_DELAY))
    printf("DONE\n");
  else
    printf("ERROR\n");
}
