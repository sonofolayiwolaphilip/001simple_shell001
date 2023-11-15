#include "JGmain.h"

/**
 * create_pipe - Create a pipe and return the file descriptors.
 * @pipe_fds: Array to store the read and write file descriptors.
 */
void create_pipe(int pipe_fds[2])
{
	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

/**
 * execute_pipeline - Execute a pipeline of commands separated by pipes.
 * @pipeline: Array of strings representing the commands in the pipeline.
 */
void execute_pipeline(char **pipeline)
{
	int pipe_fds[2];
	pid_t pid;
	int status;

	create_pipe(pipe_fds);

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		close(pipe_fds[0]);

		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[1]);

		execute_child_process(pipeline[0]);

		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		close(pipe_fds[1]);

		dup2(pipe_fds[0], STDIN_FILENO);
		close(pipe_fds[0]);

		execute_child_process(pipeline[1]);
	}
}

/**
 * handle_pipeline - Handle a command with pipes.
 * @command: The command string containing pipes.
 */
void handle_pipeline(const char *command)
{
	char **commands = tokenize_input(command);

	if (commands == NULL || commands[0] == NULL || commands[1] == NULL)
	{
		JGprint("Error: Invalid pipeline command.\n");
		return;
	}

	execute_pipeline(commands);

	free_tokens(commands);
}
