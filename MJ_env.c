#include "JGmain.h"

/**
 * JGenv - Print the current environment variables
 * @shell: Shell structure containing environment variables
 */
void JGenv(Shell *shell)
{
	JGprint_environment((const char **)shell->env);
}

/**
 * JGgetenv - Get the value of an environment variable
 * @shell: Shell structure containing environment variables
 * @variable: The name of the environment variable
 *
 * Return: The value of the environment variable, or NULL if not found
 */
const char *JGgetenv(const Shell *shell, const char *variable)
{
	(void)shell;

	return (getenv(variable));
}

/**
 * JGpopulate_env_list - Populate the environment linked list
 * @shell: Shell structure containing environment variables
 */
void JGpopulate_env_list(Shell *shell)
{
	int i = 0;

	while (shell->env[i] != NULL)
	{
		JGprint(shell->env[i]);
		JGprint("\n");

		i++;
	}
}
