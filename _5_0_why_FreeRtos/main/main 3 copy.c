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

void BlinkLED1()
{
  while (true)
  {
    gpio_set_level(LED1, 1);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    gpio_set_level(LED1, 0);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void BlinkLED2()
{
  while (true)
  {
    gpio_set_level(LED2, 1);
    vTaskDelay(200 / portTICK_PERIOD_MS);
    gpio_set_level(LED2, 0);
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

void app_main(void)
{
  setup();
  xTaskCreate(BlinkLED1, "BlinkLED1", 1024 * 2, NULL, 2, NULL);
  xTaskCreate(BlinkLED2,"BlinkLED2",1024 *2,NULL,1, NULL);
}