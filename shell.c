#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

/**
 * main - simple UNIX command line interpreter
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t nread;
	pid_t pid;
	int status;

	while (1)
	{
		printf("#cisfun$ ");
		nread = getline(&line, &bufsize, stdin);
		if (nread == -1) /* EOF or read error */
		{
			free(line);
			printf("\n");
			exit(EXIT_SUCCESS);
		}

		/* Remove trailing newline */
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (line[0] == '\0') /* empty command, just prompt again */
			continue;

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(line);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			/* Child process */
			char *argv[2];

			argv[0] = line;
			argv[1] = NULL;

			execve(argv[0], argv, environ);
			perror("./shell");
			free(line);
			exit(EXIT_FAILURE);
		}
		else
		{
			/* Parent waits for child */
			waitpid(pid, &status, 0);
		}
	}

	free(line);
	return (0);
}
