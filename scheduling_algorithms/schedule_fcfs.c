#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "schedulers.h"
#include "list.h"
#include "cpu.h"


struct node* head_taskList = NULL;


void add(char* name, int priority, int burst)
{
    Task* newTask = malloc(sizeof(Task));

    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;

    insert(&head_taskList, newTask);
}


void schedule()
{
    // take a task
    printf("Initial task states:\n");
    traverse(head_taskList);
    printf("\n\n");

    struct node* currentTask;
    currentTask = head_taskList;

    while(currentTask != NULL)
    {
        run(currentTask->task, QUANTUM);
        
        // NEEDS FIXING
        currentTask->task->burst -= QUANTUM;
        if (currentTask->task->burst <= 0)
        {
            delete(&currentTask, currentTask->task);
        }

        sleep(1);
        if (currentTask->next != NULL)
        {
            currentTask = currentTask->next;
        }
        else
        {
            currentTask = head_taskList;
        }
        
    }
}