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


void schedule()
{
    // take a task
    printf("Initial task states:\n");
    traverse(head);
    printf("\n\n");

    struct node* currentNode;
    currentNode = head;
    int timeSlicesTakenToFinishAllJobs = 0;

    while(currentNode != NULL)
    {
        run(currentNode->task, currentNode->task->burst / QUANTUM);

        struct node* copy_currentNode;
        copy_currentNode = currentNode;

        delete(&head, currentNode->task);
        currentNode = copy_currentNode->next;


        // Evaluation
        timeSlicesTakenToFinishAllJobs++;
    }

    printf("Scheduler took %d context switches to complete jobs.\n", timeSlicesTakenToFinishAllJobs);
}