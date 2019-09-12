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
    xTaskNotify(receiverHandler, (1<<0), eSetValueWithOverwrite);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    xTaskNotify(receiverHandler, (1<<1), eSetValueWithOverwrite);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    xTaskNotify(receiverHandler, (1<<2), eSetValueWithOverwrite);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

static void receiver(void *params)
{
  uint notificationValue;

  while (true)
  {
    if (xTaskNotifyWait(0, 0, &notificationValue, portMAX_DELAY))
    {
      printf("received %d\n", notificationValue);
    }
  }
}

void app_main(void)
{
  xTaskCreate(receiver, "task2", 2048 * 3, NULL, 1, &receiverHandler);
  xTaskCreate(sender, "task1", 2048 * 3, NULL, 1, NULL);
}