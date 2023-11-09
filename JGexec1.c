#include "JGmain.h"

/**
 * JGexecute - Execute a command as a child process
 * @command: The command to be executed
 */
void JGexecute(const char *command)
{
	pid_t child_pid;

	if (strcmp(command, "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error forking process");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		char *args[128];
		int arg_count = 0;
		char *token = strtok((char *)command, " ");

		while (token != NULL)
		{
			args[arg_count++] = token;
			token = strtok(NULL, " ");
		}
		args[arg_count] = NULL;

		execvp(args[0], args);

		perror("Error executing command");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}
