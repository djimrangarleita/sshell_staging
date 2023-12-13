#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL
#include <stdio.lib>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>


char **_strtok(char *str, char **toks, char *delim, char **envp);
int execcmd(char **tokens);
void free_toks(char **tokens);
char *findxpath(char **envp, char *input);
void printenvs();

#endif
