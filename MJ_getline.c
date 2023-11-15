#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#define BUFF_SIZE 1024

/**
 * sigint_handler - Signal handler for SIGINT (Ctrl-C)
 * @sig: Signal number
 */
void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\nmyshell $ ", 11);
}

/**
 * MJ_getline - Read a line of input from either stdin or a file descriptor
 * @ptr: Pointer to the buffer where the line will be stored
 * @len: Pointer to the variable that will store the length of the line
 * @file: File pointer to read from (use stdin for stdin)
 * Return: The number of bytes read, or -1 on failure or EOF
 */
ssize_t MJ_getline(char **ptr, size_t *len, FILE *file)
{
	ssize_t read_bytes;

	if (!ptr || !len)
		return (-1);

	*len = 0;

	signal(SIGINT, sigint_handler);

	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "myshell $ ", 11);
	}

	read_bytes = getline(ptr, len, file);

	if (read_bytes == -1)
	{
		return (-1);
	}

	if (read_bytes > 0 && (*ptr)[read_bytes - 1] == '\n')
	{
		(*ptr)[read_bytes - 1] = '\0';
	}

	return (read_bytes);
}

/**
 * MJ_getline_buffered - Read a line of input using a static buffer
 * @ptr: Pointer to the buffer where the line will be stored
 * @len: Pointer to the variable that will store the length of the line
 * Return: The number of bytes read, or -1 on failure or EOF
 */
ssize_t MJ_getline_buffered(char **ptr, size_t *len)
{
	ssize_t read_bytes;

	if (!ptr || !len)
		return (-1);

	signal(SIGINT, sigint_handler);

	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "myshell $ ", 11);
	}

	read_bytes = getline(ptr, len, stdin);

	if (read_bytes == -1)
	{
		return (-1);
	}

	if (read_bytes > 0 && (*ptr)[read_bytes - 1] == '\n')
	{
		(*ptr)[read_bytes - 1] = '\0';
	}

	return (read_bytes);
}
