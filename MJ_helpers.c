#include "JGmain.h"

#define MAX_ARGS 128

/**
 * execute_external_command - Execute an external command in a child process
 * @args: Array of strings representing the command and its arguments
 */
void execute_external_command(char *const args[])
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error forking process");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		execvp(args[0], args);

		perror("Error executing command");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}

/**
 * parse_command - Parse a command string into an array of strings
 * @command: The command string to parse
 *
 * Return: An array of strings representing the command and its arguments
 */
char **parse_command(const char *command)
{
	char *command_copy = strdup(command);

	char **args = malloc(MAX_ARGS + 1 * sizeof(char *));
	char *token = strtok(command_copy, " ");
	int i = 0;

	if (args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	while (token != NULL)
	{
		args[i++] = strdup(token);
		token = strtok(NULL, " ");
	}

	args[i] = NULL;

	free(command_copy);

	return (args);
}

/**
 * redirect_input - Redirect input from a file
 * @input_file: The name of the input file
 */
void redirect_input(const char *input_file)
{
	int fd = open(input_file, O_RDONLY);

	if (fd == -1)
	{
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}

	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Error redirecting input");
		exit(EXIT_FAILURE);
	}

	close(fd);
}

/**
 * redirect_output - Redirect output to a file
 * @output_file: The name of the output file
 */
void redirect_output(const char *output_file)
{
	int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);

	if (fd == -1)
	{
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}

	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error redirecting output");
		exit(EXIT_FAILURE);
	}

	close(fd);
}

/**
 * execute_command - Execute a command string
 * @command: The command string to execute
 */
void execute_command(const char *command)
{
	int i;

	char **args = parse_command(command);

	execute_external_command(args);

	for (i = 0; args[i] != NULL; i++)
	{
		free(args[i]);
	}
	free(args);
}
