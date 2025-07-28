#include "shell.h"

/**
 * handle_builtin - Handles built-in commands
 * @args: Command and arguments
 *
 * Return: 0 to exit, 1 to continue
 */
int handle_builtin(char **args)
{
	if (strcmp(args[0], "exit") == 0)
		return (0);

	if (strcmp(args[0], "env") == 0)
	{
		int i = 0;

		while (environ[i])
		{
			write(STDOUT_FILENO, environ[i], strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
			i++;
		}
		return (1);
	}

	return (2);
}
