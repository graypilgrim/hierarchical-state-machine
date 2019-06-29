#include "QueueLibrary.h"

QueueHandle_t QueueCreate(const size_t queueLength, const size_t itemSize)
{
    (void)queueLength;
    (void)itemSize;
    return NULL;
}

void QueueSend(QueueHandle_t queue, const void* msg)
{
    (void)queue;
    (void)msg;
}

void QueueReceive(QueueHandle_t queue, void* msg)
{
    (void)queue;
    (void)msg;
}
