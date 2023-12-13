#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
/****/
void simple_exit() 
{
	char *cmd_line_args[1024];
	char *argv[1024];
	char input_commands[256];
	int argc = 0;
	char command[256] = " ";
	char *token;
	int exit_status;
	int i;

	for (;;)
	{
		printf(">$ ");

		fgets(input_commands, sizeof(input_commands), stdin);

		if (input_commands[0] == '\n')
		{
			continue;
		}
		//int argc = 0;
		for (token = strtok(input_commands, " \n"); token; token = strtok(NULL, " \n")) 
		{
			cmd_line_args[argc++] = token;
		}
		if (strcmp(cmd_line_args[0], "exit") == 0) 
		{
			if (argc >1) 
			{
				exit_status = atoi(cmd_line_args[1]);
				printf("Exiting with status: %d\n", exit_status);
				exit(exit_status);
			}
			else 
			{
				printf("Usage: exit status \n");
			}
		}

		else if (strcmp(cmd_line_args[0], "cd") == 0)
		{
			if (argc > 1 && chdir(cmd_line_args[1]) != 0)
			{
				printf("Error: No such file or directory %s\n",cmd_line_args[1]);
			}
		}
		else
		{
			memset(command, 0 ,sizeof(command));
			//char command[256] = "";
		       for (i = 0; i <argc; i++)
		       {
				strcat(command, cmd_line_args[i]);
				 strcat(command, " ");
				 }

			int exit_status = system(command);
			if (exit_status != 0) 
			{
				printf("Error: command \"%s\" failed with exitcode  %d\n",(char *) cmd_line_args, exit_status);
			}
		}
	}
	//return (0);
}
int main()
{
	simple_exit();
	return (0);
}

