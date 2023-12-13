#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

char **_strtok(char *str, char **toks, char *delim, char **envp);
int execcmd(char **tokens);
void free_toks(char **tokens);
char *findxpath(char **envp, char *input);
void printenvs();

int main(int ac, char *argv[], char **envp)
{
	size_t len = 0;
	char *line = NULL;
	ssize_t rchars;
	char *toks[32];
	int execres;

	pid_t child_pid;

	if (isatty(STDIN_FILENO) != 1)
	{
		rchars = getline(&line, &len, stdin);
		_strtok(line, toks, " \t\n", envp);
		execres = execcmd(toks);

		dprintf(STDERR_FILENO, "%s: ", argv[0]);
		perror("");
		free(line);
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		printf("$ ");
		rchars = getline(&line, &len, stdin);
		if (rchars == -1)
		{
			perror("Error:");
			free(line);
			exit(EXIT_FAILURE);
		}
		else if (rchars != -1 && line[0] != '\n')
		{
			_strtok(line, toks, " \t\n", envp);

			// check for all built-ins instead
			if (strcmp(toks[0], "env") == 0)
			{
				printenvs();
			}
			else if (toks[0][0] != '/')
			{
				execres = execcmd(toks);
				dprintf(STDERR_FILENO, "%s: ", argv[0]);
				perror("");
			}
			else
			{
				child_pid = fork();
				if (child_pid == -1)
				{
					perror("Error:");
					free(line);
				}
				else if (child_pid == 0)
				{
					execres = execcmd(toks);
					dprintf(STDERR_FILENO, "%s: ", argv[0]);
					perror("");
				}
				else
				{
					wait(NULL);
					free(toks[0]);
				}
			}
		}
	}
	return (0);
}

char **_strtok(char *str, char **toks, char *delim, char **envp)
{
	char *tok = strtok(str, delim);
	int i;
	
	i = 0;
	while (tok != NULL)
	{
		toks[i] = tok;
		tok = strtok(NULL, delim);
		i++;
	}
	toks[i] = NULL;
	if (strcmp(toks[0], "env") == 0)
	{
		return (toks);
	}
	toks[0] = findxpath(envp, toks[0]);
	
	return (toks);
}

int execcmd(char **tokens)
{	

	return (execve(tokens[0], tokens, NULL));
}

void free_toks(char **tokens)
{
	int i = 0;

	while (tokens[i] != NULL)
		free(tokens[i]);
}

char *findxpath(char **envp, char *input)
{
	int i;
	char *key, *val, *path, *tmp, *tmpcat, *pathexec, *tmpenv = NULL;
	struct stat buf;

	if (*input == '/')
	{
		return (input);
	}

	i = 0;
	while (envp[i] != NULL)
	{
		tmpenv = strdup(envp[i]);
		key = strtok(tmpenv, "=");
		val = strtok(NULL, "=");
		if (strcmp(key, "PATH") == 0)
		{
			path = strtok(val, ":");
			while (path != NULL)
			{
				tmp = strdup(path);
				tmp = strcat(tmp, "/");
				tmpcat = strcat(tmp, input);
				if (stat(tmpcat, &buf) == 0)
				{
					pathexec = malloc(strlen(tmpcat) * sizeof(char));
					pathexec = strcpy(pathexec, tmpcat);

					return (pathexec);
				}
				path = strtok(NULL, ":");
			}
		}
		i++;
	}

	return (input);
}

void printenvs()
{
	int i;

	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i++]);
	}
}
