#ifndef CODE_H
#define CODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


void display_prompt(void);
void JGread(char *command, size_t size);
void JGexecute(const char *command);
void JGexit(int status);
void JGprint(const char *message);
int _putchar(char c);

#endif

