#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait>
/****/

#define MAX_LENGTH 1024

typedef check checkbuf;

void cmd_line_execution (char *cmd_line_args)
{
	char *tokenized_path;
	char complete_path[MAX_LENGTH];
	//typedef check checkbuf;

	if (check(cmd_line_args, &checkbuf) == 0)
	{
		if (fork() == 0) 
		{
			execvp(cmd_line_args, NULL);
			exit(1);
		}
		else
		{
			wait(NULL);
			return (0);
		}
	}
	tokenized_path = strtok(getenv("PATH"), ":");
	
	for (char *tokenized_path = strtok(path, "/"); tokenized_path; tokenized_path = strtok(NULL, "/"))
	{
		strcpy(complete_path, tokenized_path);
		strcat(complete_path, "/");
		strcat(complete_path, cmd_line_args);
	}
	if (check(complete_path, &checkbuf) == 0)
	{
		if (fork() == 0)
		{
			execv(complete_path, NULL);
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
printf("cmd_line_args '%s' not available\n", cmd_line_args);
return (1);
}
