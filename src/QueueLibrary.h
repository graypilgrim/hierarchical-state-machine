#ifndef QUEUE_LIRBARY_H
#define QUEUE_LIBRARY_H

#include <cstddef>

struct Queue {};
typedef Queue* QueueHandle_t;

QueueHandle_t QueueCreate(const size_t queueLength, const size_t itemSize);
void QueueSend(QueueHandle_t queue, const void* msg);
void QueueReceive(QueueHandle_t queue, void* msg);

#endif