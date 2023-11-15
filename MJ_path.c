#include "JGmain.h"

/**
 * search_in_path - Search for the command in the PATH.
 * @command: The command to search for.
 * @path: The PATH environment variable.
 * @full_path: The full path of the command (output parameter).
 * Return: 1 if the command is found in the PATH, 0 otherwise.
 */
int search_in_path(const char *command, const char *path, char *full_path)
{
	char *token, *path_copy;

	path_copy = strdup(path);

	if (path_copy == NULL)
	{
		perror("Error copying PATH");
		exit(EXIT_FAILURE);
	}

	token = strtok(path_copy, ":");

	while (token != NULL)
	{
		snprintf(full_path, PATH_MAX, "%s/%s", token, command);
		if (access(full_path, F_OK) == 0)
		{
			free(path_copy);
			return (1);
		}
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (0);
}

/**
 * JGexecute_with_path - Execute the given command with PATH handling.
 * @command: The command to execute.
 */
void JGexecute_with_path(const char *command)
{
	if (strcmp(command, "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else
	{
		char full_path[PATH_MAX];

		if (search_in_path(command, getenv("PATH"), full_path))
		{
			pid_t child_pid = fork();

			if (child_pid == -1)
			{
				perror("Error forking process");
				exit(EXIT_FAILURE);
			}
			else if (child_pid == 0)
			{
				execute_child_process(full_path);
			}
			else
			{
				wait(NULL);
			}
		}
		else
		{
			fprintf(stderr, "Command not found: %s\n", command);
		}
	}
}
