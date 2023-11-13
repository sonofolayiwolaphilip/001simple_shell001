#include "JGmain.h"

/**
 * tokenize_input - Tokenize user input into an array of tokens.
 * @input: The user input string.
 *
 * Return: An array of tokens (strings).
 */
char **tokenize_input(const char *input)
{
	char *token;
	char **tokens = malloc(MAX_ARGS * sizeof(char *));
	int i = 0;

	if (tokens == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok((char *)input, " \t\n");

	while (token != NULL)
	{
		tokens[i++] = strdup(token);

		if (i >= MAX_ARGS)
		{
			JGprint("Error: Too many arguments.\n");
			free_tokens(tokens);
			exit(EXIT_FAILURE);
		}

		token = strtok(NULL, " \t\n");
	}

	tokens[i] = NULL;

	return (tokens);
}

/**
 * free_tokens - Free memory allocated for tokens.
 * @tokens: The array of tokens.
 */
void free_tokens(char **tokens)
{
	int i;

	for (i = 0; tokens[i] != NULL; i++)
		free(tokens[i]);

	free(tokens);
}

/**
 * print_tokens - Print tokens for debugging purposes.
 * @tokens: The array of tokens.
 */
void print_tokens(char **tokens)
{
	int i;

	for (i = 0; tokens[i] != NULL; i++)
		JGprint(tokens[i]);

	JGprint("\n");
}
