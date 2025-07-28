#include "shell.h"

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *argv[2];

    while (1)
    {
        write(STDOUT_FILENO, "$ ", 2);
        read = getline(&line, &len, stdin);
        if (read == -1)
            break;

        line[read - 1] = '\0';
        argv[0] = line;
        argv[1] = NULL;

        if (access(argv[0], X_OK) == 0)
        {
            if (fork() == 0)
                execve(argv[0], argv, environ);
            else
                wait(NULL);
        }
        else
        {
            char *cmd_path = get_cmd_path(argv[0]);
            if (cmd_path)
            {
                if (fork() == 0)
                    execve(cmd_path, argv, environ);
                else
                    wait(NULL);
                free(cmd_path);
            }
            else
                write(STDERR_FILENO, "Command not found\n", 19);
        }
    }
    free(line);
    return (0);
}
