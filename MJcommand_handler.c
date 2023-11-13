#include "JGmain.h"

/**
 * handle_variables - Handle variable replacements ($? and $$)
 * @input: The user input string.
 * @status: The exit status of the last command.
 */
void handle_variables(char *input, int status)
{
	char *token = strtok(input, " ");

	while (token != NULL)
	{
		if (strcmp(token, "$?") == 0)
		{
			char exit_status_str[5];

			sprintf(exit_status_str, "%d", status);
			strcat(input, exit_status_str);
		}
		else if (strcmp(token, "$$") == 0)
		{
			char process_id_str[10];

			sprintf(process_id_str, "%d", getpid());
			strcat(input, process_id_str);
		}

		token = strtok(NULL, " ");
	}
}

/**
 * handle_logical_operators - Handle logical operators '&&' and '||'
 * @input: The user input string.
 */
void handle_logical_operators(const char *input)
{
	char *commands[MAX_ARGS];
	int i = 0;
	int status = 0;
	int j;


	char *token = strtok((char *)input, "&|");

	while (token != NULL)
	{
		commands[i++] = strdup(token);
		token = strtok(NULL, "&|");
	}

	for (j = 0; j < i; j++)
	{
		if (j % 2 == 0)
		{
			execute_command(commands[j]);
			free(commands[j]);
		}
		else
		{
			if ((commands[j - 1][strlen(commands[j - 1]) - 1] == '&')
					&& (status != 0))
				break;

			if ((commands[j - 1][strlen(commands[j - 1]) - 1]
						== '|') && (status == 0))
				break;
		}
	}
}

/**
 * handle_commands - Handle commands separated by ';'
 * @input: The user input string.
 */
void handle_commands(const char *input)
{
	char *commands[MAX_ARGS];
	int i = 0;
	int j;

	char *token = strtok((char *)input, ";");

	while (token != NULL)
	{
		commands[i++] = strdup(token);
		token = strtok(NULL, ";");
	}

	for (j = 0; j < i; j++)
	{
		execute_command(commands[j]);
		free(commands[j]);
	}
}

/**
 * handle_comments - Remove comments from the input string
 * @input: The user input string.
 */
void handle_comments(char *input)
{
	char *comment = strchr(input, '#');

	if (comment != NULL)
	{
		*comment = '\0';
	}
}
