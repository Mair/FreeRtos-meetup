#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void task1(void *params)
{
  while (true)
  {
    printf("from core 0 from\n");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void task2(void *params)
{
  while (true)
  {
     printf("from core 1 from\n");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void app_main(void)
{
  xTaskCreatePinnedToCore(task1, "humidity reading", 2048, NULL, 2, NULL,0);
  xTaskCreatePinnedToCore(task2, "humidity reading", 2048, NULL, 2, NULL,1);
}