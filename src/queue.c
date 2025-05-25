#include "player.h"
#include <stdbool.h>
#include "queue.h"

void CreateQueueMusic(QueueMusic *Q)
{
    Q->front = NULL;
    Q->rear = NULL;
}

bool is_Empty(QueueMusic Q)
{
    return (Q.front == NULL && Q.rear == NULL);
}

void EnQueueMusic(QueueMusic *Q, infotype X)
{
    address add;
    List l;
    l.First = Q->rear;

    add = Alokasi(X);
    InsertLast(&l, add);
    Q->rear = add;
    if (Q->front == NULL)
    {
        Q->front = add;
    }
}

void deQueueMusic(QueueMusic *Q, infotype *X)
{
    List l;
    l.First = Q->front;

    if (is_Empty(*Q))
        return;

    DelVFirst(&l, X);
    Q->front = l.First;
    if (Q->front == NULL)
    {
        Q->rear = NULL;
    }
}

void PrintQueueMusic(QueueMusic q)
{
    address cursor;

    cursor = q.front;
    if (is_Empty(q))
    {
        printf("Antrian Kosong...\n");
        return;
    }
    printf("Antrian sekarang: ");
    while (cursor != q.rear->next)
    {
        printf("Printing queue is not supported yet");
        // printf("%d ", cursor->info);
        cursor = cursor->next;
    }

    printf("\n");
}