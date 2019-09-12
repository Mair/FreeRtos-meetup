#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

xSemaphoreHandle binSemaphore;

void listenForHTTP(void *params)
{
  while (true)
  {
    printf("received http message\n");
    xSemaphoreGive(binSemaphore);
    printf("processed http message\n");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void task1(void *params)
{
  while (true)
  {
    if(xSemaphoreTake(binSemaphore, 2000 / portTICK_PERIOD_MS))
    {
      printf("doing something with http\n");
    }
    else
    {
       printf("time out\n");
    }
    
  }
}

void app_main(void)
{
  binSemaphore = xSemaphoreCreateBinary();
  xTaskCreate(&task1, "do something with http", 2048, NULL, 1, NULL);
  xTaskCreate(&listenForHTTP, "get http", 2048, NULL, 1, NULL);
}