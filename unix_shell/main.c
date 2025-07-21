/*
This project consists of designing a program to serve as a shell interface that accepts user commands
and then executes each command in a separate process. This implementation will support input and output
redirection, as well as pipes as a form of IPC between a pair of commands.

I'll call the shell 'lash' (LA-wrence SH-ell)

build: g++ -g -o out.exe main.c
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>


#define MAX_LINE 80   // The maximum length command.
#define MAX_ARGS 41


int tokenize_input(char *input, char *args[MAX_ARGS]) 
{
    int i = 0;
    char *token = strtok(input, " \t\n");
    while (token != NULL && i < MAX_ARGS) 
	{
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }

    args[i] = NULL;

	return i;
}


int main(void)
{
	char inputs[MAX_LINE];
	char *args[MAX_ARGS];
	bool shouldRun = true;

	while(shouldRun)
	{
		printf("lash> ");
		fflush(stdout);

		if (fgets(inputs, MAX_LINE, stdin) == NULL)
			break;

		int num_tokens = tokenize_input(inputs, args);

		if (num_tokens == 0) continue;

		int pid = fork();
		
		if (pid < 0)
		{
			printf("Error! Fork failed, no child process is created.\n");
			return -1;
		}
		else if (pid == 0)
		{
			// do something inside the child process
			execvp(args[0], args);
			return 0;
		}
		else // pid > 0
		{
			// do something in the parent process
			if (strcmp(args[0], "exit") == 0)
			{
				shouldRun = 0;
				continue;
			}

			wait(&pid);
		}

	}

	printf("exiting...\n");
	return 0;
	
}