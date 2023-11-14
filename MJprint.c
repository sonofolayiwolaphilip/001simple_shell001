#include "JGmain.h"

/**
 * JGprint - function to write to stdout
 * @message: pointer to message
 */
void JGprint(const char *message)
{
	write(STDOUT_FILENO, message, strlen(message));
}

/**
 * display_prompt - Display prompt
 */
void display_prompt(void)
{
	JGprint("myshell $ ");
}
