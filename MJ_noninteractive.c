#include "JGmain.h"

/**
 * execute_commands_from_file - Execute commands from a file
 * in non-interactive mode.
 * @file_path: Path to the file containing commands.
 */
void execute_commands_from_file(const char *file_path)
{
	char command[256];

	FILE *input_file = fopen(file_path, "r");

	if (!input_file)
	{
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}

	while (fgets(command, sizeof(command), input_file) != NULL)
	{
		command[strcspn(command, "\n")] = '\0';
		execute_command(command);
	}

	if (ferror(input_file))
	{
		perror("Error reading from input file");
		fclose(input_file);
		exit(EXIT_FAILURE);
	}

	fclose(input_file);
}
