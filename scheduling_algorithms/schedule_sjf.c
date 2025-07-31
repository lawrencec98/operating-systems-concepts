#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "schedulers.h"
#include "list.h"
#include "cpu.h"


struct node* head = NULL;


void add(char* name, int priority, int burst)
{
    Task* newTask = malloc(sizeof(Task));

    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;

    insert(&head, newTask);
}


Task* searchShortestJob(struct node** head)
{
    struct node* currentNode = *head;
    Task* minTask;
    int minBurst;

    while(currentNode != NULL)
    {
        if (currentNode == *head) // initialize minBurst to first node's burst time
        {
            minBurst = currentNode->task->burst;
            minTask = currentNode->task;
        }
        else 
        {
            if (currentNode->task->burst < minBurst && currentNode->task->burst > 0) 
            {
                minBurst = currentNode->task->burst;
                minTask = currentNode->task;
            }
        }

        currentNode = currentNode->next;
    }

    return minTask;
}


void schedule()
{
    // take a task
    printf("Initial task states:\n");
    traverse(head);
    printf("\n\n");

    int timeSlicesTakenToFinishAllJobs = 0;

    while(head != NULL)
    {
        Task* shortestTask = searchShortestJob(&head);
        run(shortestTask, shortestTask->burst / QUANTUM);
        delete(&head, shortestTask);


        //Evaluation
        timeSlicesTakenToFinishAllJobs++;
    }

    printf("Scheduler took %d context switches to complete jobs.\n", timeSlicesTakenToFinishAllJobs);
}