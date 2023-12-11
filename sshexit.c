#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/****/
void simple_exit() 
{
	char *cmd_line_args[1024];
	char input_commands[256];

	for (;;)
	{
		printf(">$ ");

		fgets(input_commands, sizeof(input_commands), stdin);

		if (input_commands[0] == '\n')
		{
			continue;
		}
		int argc = 0;
		for (char *token = strtok(input_commands, " \n"); token; token = strtok(NULL, " \n")) 
		{
			cmd_line_args[argc++] = token;
		}
		if (strcmp(cmd_line_args[0], "exit") == 0) 
		{
			exit(0);
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
			char command[256] = "";
		       for (int i = 0; i <argc; i++)
		       {
				strcat(command, cmd_line_args[i]);
				 strcat(command, " ");
				 }

			int exit_status = system(command);
			if (exit_status != 0) 
			{
				printf("Error: command \"%s\" failed with exitcode  %d\n", cmd_line_args, exit_status);
			}
		}
	}
	return (0);
}
