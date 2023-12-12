/usr/local/sbin

/usr/local/bin

/usr/sbin

/usr/bin

/sbin

/bin

tokenized_path = strtok(getenv("PATH"), ":");
tokenized_path = "PATH=/usr/local/sbin";

for (tokenized_path = strtok(path, ":")){
	tokenized_path = "/bin";
	tokenized_path = "local";
	tokenized_path = "sbin:";

	strcpy(complete_path, tokenized_path);
	complete_path = "/bin";

	strcat(complete_path, "/");
	complete_path = "/bin/";

	strcat(complete_path, cmd_line_args[0] = "ls");
	complete_path = "/bin/ls";

	if(stat(complete_path, &statbuffer))
	{
		//int execv(const char *path, char *const argv[]);
		execv(complete_path, cmd_line_args);

		//complete_path = "/bin/ls"
		//cmd_line_args = {"ls", "-l", "/usr", NULL};
		//cmd_line_args[0] = strcpy(complete_path);
		//cmd_line_args = {"/bin/ls", "-l", "/usr", NULL};
	}
}
