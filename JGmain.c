#include "JGmain.h"

/**
 * _putchar - Writes a character to the standard output.
 * @c: The character to be written.
 *
 * Return: On success, 1. On error, -1, and errno is set appropriately.
 */
int _putchar(char c)
{
	return write(1, &c, 1);
}

/**
 * main - Entry point for the shell program.
 * @argc: The number of command-line arguments.
 * @argv: An array containing the command-line arguments.
 *
 * Return: On success, EXIT_SUCCESS. On failure, EXIT_FAILURE.
 */
int main(int argc, char *argv[])
{
	char command[256];

	if (argc == 1)
	{
		while (1)
		{
			display_prompt();
			JGread(command, sizeof(command));
			if (command[0] == '\0')
			{
				continue;
			}
			if (strcmp(command, "exit") == 0)
			{
				break;
			}
			JGexecute(command);
		}
	}
	else if (argc == 2)
	{
		FILE *input_file = fopen(argv[1], "r");

		if (input_file == NULL)
		{
			perror("Error opening input file");
			return EXIT_FAILURE;
		}
		while (fgets(command, sizeof(command), input_file) != NULL)
		{
			command[strcspn(command, "\n")] = '\0';
			JGexecute(command);
		}
		fclose(input_file);
	}
	else
	{
		fprintf(stderr, "Usage: %s [input_file]\n", argv[0]);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
