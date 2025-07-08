/*
This project consists of designing a program to serve as a shell interface that accepts user commands
and then executes each command in a separate process. This implementation will support input and output
redirection, as well as pipes as a form of IPC between a pair of commands.

The shell shall be called 'lash' (LA-wrence SH-ell)
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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
		
		// if (pid < 0)
		// {
		// 	printf("Error! Fork failed, no child process is created.\n");
		// 	return -1;
		// }

		// if (pid > 0)
		// {
		// 	printf("Child process created.\n");
		// }
	}
	
}