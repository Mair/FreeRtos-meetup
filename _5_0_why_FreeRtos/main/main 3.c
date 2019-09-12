#include <stdio.h>
#include <stdlib.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED1 2
#define LED2 4

typedef struct {
  int led;
  int time;
} LEDParams;

void setup()
{
  gpio_set_direction(LED1, GPIO_MODE_OUTPUT);
  gpio_set_direction(LED2, GPIO_MODE_OUTPUT);
}

void BlinkLED1(void *params)
{
  LEDParams *l = (LEDParams*) params;

  while (true)
  {
    gpio_set_level(l->led, 1);
    vTaskDelay(l->time / portTICK_PERIOD_MS);
    gpio_set_level(l->led, 0);
    vTaskDelay(l->time / portTICK_PERIOD_MS);
  }
}


void app_main(void)
{
  LEDParams ledParms1 = {
    .led = LED1,
    .time = 1000
  };
  
  LEDParams ledParms2 = {
    .led = LED1,
    .time = 1000
  };
  setup();
  xTaskCreate(BlinkLED1, "BlinkLED1", 1024 * 2, &ledParms1, 2, NULL);
  xTaskCreate(BlinkLED1,"BlinkLED2",1024 *2,&ledParms2,1, NULL);

  while (true)
  {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  
}