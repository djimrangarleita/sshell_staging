#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
/****/

#define MAX_LENGTH 1024



void cmd_line_execution (char **cmd_line_args)
{
	char *tokenized_path;
	char complete_path[MAX_LENGTH];
	struct stat statbuffer;

	if (stat(cmd_line_args, &statbuffer) == 0)
	{
		if (fork() == 0) 
		{
			execv(cmd_line_args[0], cmd_line_args,  NULL);
			exit(1);
		}
		else
		{
			wait(NULL);
			return (0);
		}
	}
	tokenized_path = strtok(getenv("PATH"), ":");
	
	for (tokenized_path = strtok(path, "/"); tokenized_path; tokenized_path = strtok(NULL, "/"))
	{
		strcpy(complete_path, tokenized_path);
		strcat(complete_path, "/");
		strcat(complete_path, cmd_line_args);
	}
	if (stat(complete_path, &statbuffer) == 0)
	{
		if (fork() == 0)
		{
			execvp(complete_path, NULL);
			exit(1);
		}
		else
		{
			wait(NULL);
			return (0);
		}
	}
	tokenized_path = strtok(NULL, ":");
}
	printf("cmd_line_args %s not available\n", (char *) cmd_line_args);
	return (1);
	}
}

int main(void)
{
	char **argv[] = {"/bin/ls", "-l", "/usr/", NULL};
	cmd_line_execution (char **argv[]);
	return (0);

