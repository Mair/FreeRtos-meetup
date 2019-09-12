#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static TaskHandle_t receiverHandler = NULL;

static void sender(void *params)
{
  while (true)
  {
    xTaskNotifyGive(receiverHandler);
    xTaskNotifyGive(receiverHandler);
    xTaskNotifyGive(receiverHandler);
    xTaskNotifyGive(receiverHandler);
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

static void receiver(void *params)
{
  int notificationValue;

  while (true)
  {
    notificationValue = ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
    printf("received %d\n", notificationValue);
    
  }
}

void app_main(void)
{
  xTaskCreate(receiver, "task2", 2048 * 3, NULL, 1, &receiverHandler);
  xTaskCreate(sender, "task1", 2048 * 3, NULL, 1, NULL);
}