#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void prompt(void)
{
    write(STDOUT_FILENO, "$ ", 2);
}

char *read_line(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread = getline(&line, &len, stdin);
    if (nread == -1)
    {
        free(line);
        return NULL;
    }
    /* remove trailing newline */
    if (line[nread - 1] == '\n')
        line[nread - 1] = '\0';
    return line;
}

char **split_line(char *line)
{
    int bufsize = 64, i = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n");
    while (token)
    {
        tokens[i++] = token;

        if (i >= bufsize)
        {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\r\n");
    }
    tokens[i] = NULL;
    return tokens;
}

int handle_builtin(char **args)
{
    if (strcmp(args[0], "exit") == 0)
    {
        return 0; /* signal shell to exit */
    }
    /* You can add more built-in commands here like 'env' */
    return 1; /* not a builtin */
}

int execute(char **args)
{
    pid_t pid;
    int status;

    if (args[0] == NULL)
        return 1;

    if (!handle_builtin(args))
        return 0;

    pid = fork();
    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("execvp");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("fork");
    }
    else
    {
        waitpid(pid, &status, 0);
    }

    return 1;
}

int main(void)
{
    char *line;
    char **args;
    int status = 1;

    while (status)
    {
        prompt();
        line = read_line();
        if (!line)
        {
            write(STDOUT_FILENO, "\n", 1);
            break; /* EOF, exit shell */
        }
        args = split_line(line);
        status = execute(args);

        free(line);
        free(args);
    }

    return 0;
}
