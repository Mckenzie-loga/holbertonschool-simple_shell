#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/**
 * main - Entry point of the simple shell program
 *
 * Return: Always 0 on success
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
		printf("$ ");
		nread = getline(&line, &bufsize, stdin);
		if (nread == -1) /* EOF or error */
		{
			free(line);
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		line[nread - 1] = '\0'; /* Remove trailing newline */

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

			execvp(argv[0], argv);
			perror("execvp");
			free(line);
			exit(EXIT_FAILURE);
		}
		else
		{
			/* Parent process */
			waitpid(pid, &status, 0);
		}
	}
	free(line);
	return (0);
}
