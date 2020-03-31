#include "com_queue.h"

int sendStatisticsToPublishQueue(data_struct statistics)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t result = xQueueSendFromISR(publish_queue_handle, &statistics,
                                         &xHigherPriorityTaskWoken);
    return (pdPASS == result);
}

int sendStatisticsToSubscribeQueue()
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint8_t ack = 1;
    BaseType_t result = xQueueSendToBack(subscribe_queue_handle, &ack,
                                                &xHigherPriorityTaskWoken);
    return (pdPASS == result);
}

data_struct readStatisticsFromPublishQueue()
{
    data_struct data = { .type = no_data, .value.message_num_sent = 0,
                         .value.message_num_receive = 0, .value.message = "" };
    xQueueReceive(publish_queue_handle, &data, portMAX_DELAY);
    return data;
}

uint8_t readStatisticsFromSubscribeQueue()
{
    uint8_t ack = 0;
    xQueueReceive(subscribe_queue_handle, &ack, 0);
    return ack;
}

void initStatisticsQueues()
{
    publish_queue_handle = xQueueCreate(QUEUE_LENGTH, sizeof(data_struct));
    subscribe_queue_handle = xQueueCreate(QUEUE_LENGTH, sizeof(uint8_t));
}
