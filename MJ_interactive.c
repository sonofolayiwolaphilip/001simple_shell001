#include "JGmain.h"

/**
 * interactive_mode - Run the shell in interactive mode.
 */
void interactive_mode(void)
{
	char command[256];

	while (1)
	{
		display_prompt();
		JGread(command, sizeof(command));

		if (command[0] == '\0')
			continue;

		if (strcmp(command, "exit") == 0)
			break;

		JGexecute(command);
	}
}
