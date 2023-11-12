#ifndef CODE_H
#define CODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

extern char **environ;

typedef struct
{
	char **env;
} Shell;

void display_prompt(void);
void JGread(char *command, size_t size);
void JGexecute(const char *command);
void JGexit(int status);
void JGprint(const char *message);
int _putchar(char c);
void JGcd(const char *path);
void JGexit(int status);
void JGhelp(void);
void handle_builtin(const char *command);
void JGprint_environment(const char *env[]);
void JGset_environment(Shell *shell, const char *variable, const char *value);
void JGunset_environment(Shell *shell, const char *variable);
void execute_external_command(char *const args[]);
char **parse_command(const char *command);
void redirect_input(const char *input_file);
void redirect_output(const char *output_file);
void execute_command(const char *command);

#endif
