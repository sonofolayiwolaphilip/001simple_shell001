#include "JGmain.h"

/**
 * JGcd - Change current working directory
 * @path: The path to change to
 */
void JGcd(const char *path)
{
	if (path == NULL)
	{
		JGprint("cd: missing argument\n");
	}
	else
	{
		if (chdir(path) != 0)
		{
			perror("cd");
		}
	}
}

/**
 * JGexit - Exit the shell
 * @status: The exit status
 */
void JGexit(const char *status)
{
	int exit_status = EXIT_SUCCESS;

	if (status != NULL)
	{
		char *endptr;

		exit_status = (int)strtol(status, &endptr, 10);

		if (*endptr != '\0')
		{
			JGprint("exit: invalid status\n");
			return;
		}
	}

	exit(exit_status);
}

/**
 * JGhelp - Display help information
 */
void JGhelp(void)
{
	JGprint("Built-in commands:\n");
	JGprint("cd [directory] - Change the current working directory\n");
	JGprint("echo [arguments] - Print arguments to the standard output\n");
	JGprint("exit - Exit the shell\n");
	JGprint("help - Display this help message\n");
}

/**
 * handle_builtin - Execute built-in commands
 * @command: The command to check
 */
void handle_builtin(const char *command)
{
	if (strcmp(command, "cd") == 0)
	{
		const char *path = command + 3;

		JGcd(path);
	}
	else if (strcmp(command, "exit") == 0)
	{
		JGexit(EXIT_SUCCESS);
	}
	else if (strcmp(command, "help") == 0)
	{
		JGhelp();
	}
}
