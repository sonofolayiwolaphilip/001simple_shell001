#include "JGmain.h"
/**
 * JGread - Function to read input
 * @command: the pointer to the array
 * @size: the soze of the array
 */
void JGread(char *command, size_t size)
{
	if (fgets(command, size, stdin) == NULL)
	{
		if (feof(stdin))
		{
			JGprint("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			JGprint("Error while reading input.\n");
			exit(EXIT_FAILURE);
		}
	}
	command[strcspn(command, "\n")] = '\0';
}
