#include "JGmain.h"

/**
 * JGexecute - Execute the given command.
 * @command: The command to execute.
 * @shell: Pointer to the shell structure.
 */
void JGexecute(const char *command)
{
	if (strcmp(command, "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else
	{
		pid_t child_pid = fork();

		if (child_pid == -1)
		{
			perror("Error forking process");
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			execute_child_process(command);
		}
		else
		{
			wait(NULL);
		}
	}
}

/**
 * execute_child_process - Execute the command in the child process.
 * @command: The command to execute.
 */
void execute_child_process(const char *command)
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

