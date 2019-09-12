#include <stdio.h>
#include <stdlib.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED1 2
#define LED2 4

void setup()
{
  gpio_set_direction(LED1, GPIO_MODE_OUTPUT);
  gpio_set_direction(LED2, GPIO_MODE_OUTPUT);
}

void loop()
{
  gpio_set_level(LED1,1);
  vTaskDelay(500 / portTICK_PERIOD_MS);
  gpio_set_level(LED2,1);
  vTaskDelay(500 / portTICK_PERIOD_MS);

  gpio_set_level(LED1,0);
  vTaskDelay(500 / portTICK_PERIOD_MS);
  gpio_set_level(LED2,0);
  vTaskDelay(500 / portTICK_PERIOD_MS);
}










void app_main(void)
{
  setup();
  while (1)
  {
    loop();
  }
}