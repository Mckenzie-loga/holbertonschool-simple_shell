#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    pid_t pid;
    int status;

    while (1)
    {
        printf("$ ");
        fflush(stdout);

        read = getline(&line, &len, stdin);
        if (read == -1)  /* EOF (Ctrl+D) */
        {
            printf("\n");
            break;
        }

        /* Remove trailing newline */
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        if (strcmp(line, "") == 0)
            continue;

        if (strcmp(line, "exit") == 0)
            break;

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            continue;
        }
        if (pid == 0)
        {
            /* Child process executes the command */
            char *argv[] = {line, NULL};

            execve(line, argv, environ);

            /* If execve returns, there was an error */
            perror("./simple_shell");
            exit(EXIT_FAILURE);
        }
        else
        {
            /* Parent waits for child */
            waitpid(pid, &status, 0);
        }
    }

    free(line);
    return 0;
}
