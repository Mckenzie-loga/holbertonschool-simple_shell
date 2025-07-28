#include "main.h"

/**
 * _EXE_Cute - executes command on system
 * @args: vector with user input
 * Return: 1 on success
*/

int _EXE_Cute(char **args)
{
	pid_t pid = 0;
	int status = 1;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror("Command invalid");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("Failed to fork");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
	return (status);
}
