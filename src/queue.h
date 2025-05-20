#ifndef QUEUE_H
#define QUEUE_H
#include "player.h"
#include <stdbool.h>
#include "linked.h"

void CreateQueueMusic(QueueMusic *Q);

bool is_Empty(QueueMusic Q);

void EnQueueMusic(QueueMusic *Q, infotype X);

void deQueueMusic(QueueMusic *Q, infotype *X);

void PrintQueueMusic(QueueMusic q);

#endif