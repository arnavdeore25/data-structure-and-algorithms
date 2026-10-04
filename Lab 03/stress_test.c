#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "orderqueue.h"

long long getTimeNanoseconds()
{
    static LARGE_INTEGER frequency;
    LARGE_INTEGER counter;
    if (frequency.QuadPart == 0)
    {
        QueryPerformanceFrequency(&frequency);
    }

    QueryPerformanceCounter(&counter);

    return (counter.QuadPart * 1000000000LL)
           / frequency.QuadPart;
}


int main()
{
    OrderQueue queue;
    initQueue(&queue);
    srand((unsigned int)GetTickCount());

    int totalOperations = 10 + rand() % 41;

    long long totalTime = 0;
    long long maxTime = 0;

    int enqueueCount = 0;
    int dequeueCount = 0;


    printf("============================================\n");
    printf("          ORDER QUEUE STRESS TEST\n");
    printf("============================================\n");

    printf("Total operations: %d\n\n", totalOperations);


    printf("%-6s %-10s %-12s %-15s\n",
           "No.",
           "Operation",
           "Queue Size",
           "Time (ns)");

    printf("--------------------------------------------\n");


    for (int i = 0; i < totalOperations; i++)
    {
        int operation;
        if (isEmpty(&queue))
        {
            operation = 0;
        }
        else
        {
            operation = rand() % 2;
        }
        if (operation == 0)
        {
            Order order;

            order.order_id = i + 1;
            long long start = getTimeNanoseconds();
            int success = enqueue(&queue, order);
            long long end = getTimeNanoseconds();
            long long elapsed = end - start;
            if (success)
            {
                printf("%-6d %-10s %-12zu %-15lld\n",
                       i + 1,
                       "ENQUEUE",
                       queue.size,
                       elapsed);

                enqueueCount++;
            }
            totalTime += elapsed;


            if (elapsed > maxTime)
            {
                maxTime = elapsed;
            }
        }
        else
        {
            Order order;
            long long start = getTimeNanoseconds();
            int success = dequeue(&queue, &order);
            long long end = getTimeNanoseconds();
            long long elapsed = end - start;


            if (success)
            {
                printf("%-6d %-10s %-12zu %-15lld\n",
                       i + 1,
                       "DEQUEUE",
                       queue.size,
                       elapsed);

                dequeueCount++;
            }


            totalTime += elapsed;
            if (elapsed > maxTime)
            {
                maxTime = elapsed;
            }
        }
    }
    printf("\n============================================\n");
    printf("             STRESS TEST RESULTS\n");
    printf("============================================\n");

    printf("Total operations : %d\n",
           totalOperations);

    printf("Enqueues         : %d\n",
           enqueueCount);

    printf("Dequeues         : %d\n",
           dequeueCount);

    printf("Final queue size : %zu\n",
           queue.size);

    printf("Maximum latency  : %lld ns\n",
           maxTime);

    printf("Average latency  : %.2f ns\n",
           (double)totalTime / totalOperations);

    printf("============================================\n");
    destroyQueue(&queue);


    return 0;
}