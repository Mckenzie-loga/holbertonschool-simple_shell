#include <sys/stat.h>

/* Helper to check if file is executable */
int is_executable(char *path)
{
	struct stat st;

	if (stat(path, &st) == 0)
	{
		if ((st.st_mode & S_IFREG) && (access(path, X_OK) == 0))
			return 1;
	}
	return 0;
}

/* Find command in PATH */
char *find_command(char *cmd)
{
	char *path_env, *path_dup, *token, *full_path;
	size_t len;

	if (strchr(cmd, '/'))
	{
		if (is_executable(cmd))
			return strdup(cmd);
		return NULL;
	}

	path_env = getenv("PATH");
	if (!path_env || path_env[0] == '\0')
		return NULL;

	path_dup = strdup(path_env);
	if (!path_dup)
		return NULL;

	token = strtok(path_dup, ":");
	while (token)
	{
		len = strlen(token) + strlen(cmd) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_dup);
			return NULL;
		}
		snprintf(full_path, len, "%s/%s", token, cmd);

		if (is_executable(full_path))
		{
			free(path_dup);
			return full_path;
		}
		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_dup);
	return NULL;
}

int execute(char **args)
{
	pid_t pid;
	int status;
	char *cmd_path;

	if (args[0] == NULL)
		return 1;

	if (handle_builtin(args) == 0)
		return 0;

	cmd_path = find_command(args[0]);
	if (!cmd_path)
	{
		/* Command not found, print error and do NOT fork */
		dprintf(STDERR_FILENO, "%s: No such file or directory\n", args[0]);
		return 1;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, args, environ);
		perror("execve");
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
		free(cmd_path);
		return 1;
	}
	else
	{
		free(cmd_path);
		waitpid(pid, &status, 0);
	}

	return 1;
}
