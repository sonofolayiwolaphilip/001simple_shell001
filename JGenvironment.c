#include "JGmain.h"

/**
 * JGprint_environment - Print environment variables
 * @env: the pointer to environment
 */
void JGprint_environment(const char *env[])
{
	int i = 0;

	while (env[i] != NULL)
	{
		JGprint(env[i]);
		JGprint("\n");
		i++;
	}
}

/**
 * JGset_environment - Set a new environment variable
 * @shell: Shell structure containing environment variables
 * @variable: The name of the variable
 * @value: The value to set
 */
void JGset_environment(Shell *shell, const char *variable, const char *value)
{
	if (setenv(variable, value, 1) != 0)
	{
		perror("setenv");
	}

	shell->env = environ;
}

/**
 * JGunset_environment - Unset an environment variable
 * @shell: Shell structure containing environment variables
 * @variable: The name of the variable to unset
 */
void JGunset_environment(Shell *shell, const char *variable)
{
	if (unsetenv(variable) != 0)
	{
		perror("unsetenv");
	}

	shell->env = environ;
}
