#include "shell.h"

/**
 * main - Entry point of the shell
 *
 * Return: 0 on success
 */
int main(void)
{
	char *line;
	char **args;
	int status = 1;

	while (status)
	{
		if (isatty(STDIN_FILENO))
			prompt();

		line = read_line();
		if (line == NULL)
		{
			free(line);
			break;
		}
		args = split_line(line);
		if (args == NULL)
		{
			free(line);
			continue;
		}
		status = execute(args);

		free(line);
		free(args);
	}

	return (0);
}
