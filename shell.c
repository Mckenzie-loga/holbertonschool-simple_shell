#include "main.h"

/**
 * main - execute a simple shell
 * @argc: a count of argumentos on argv
 * @argv: vector of arguments given to shell
 * Return: 0 on success and stat on exit
*/

int main(__attribute__((unused)) int argc, char *argv[])
{	int count = 1, status = 1, free_;
	ssize_t _exit_ = 0;
	token_t *args_token = NULL, *path_token = NULL, *command = NULL;
	char *line = NULL, **array = NULL;

	while (status >= 0)
	{	free_ = 0;
		line = Read_line(&_exit_);
		if (strcmp(line, "env\n") == 0)
		{	_env();
			free(line);
			continue; }
		args_token = tokenicer(line, " \t\r\n\a");
		if (!args_token)
		{	free(line);
			continue; }
		path_token = _getenv("PATH=");
		command = _stat_checker(args_token, path_token);
		if (!command)
		{	_exit_ = 1;
			fprintf(stderr, "%s: %d: %s: not found\n", argv[0], count, line);
			free(line);
			count++;
			continue; }
		else
			_exit_ = 0;
		array = _list_to_array(args_token);
		status = _EXE_Cute(array);
		if (status == 512)
			_exit_ = 2;
		while (array[free_])
		{
			free(array[free_]);
			free_++;
		}
		free(array);
		free(line);
		count++; }
	return (0); }

/**
 * Read_line - prints a prompt and read user input
 * @_exit_: a count of argumentos on argv
 * Return: 0 on success and stat on exit
*/

char *Read_line(ssize_t *_exit_)
{
	int num = 0;
	char *str = NULL;
	size_t size = 0;
	int fd = isatty(num);

	if (fd == 1)
		printf("DEPS -> ");

	if (getline(&str, &size, stdin) == -1)
	{
		free(str);
		if (*_exit_ == 0)
			exit(0);
		else if (*_exit_ == 1)
			exit(127);
		exit(2);
	}
	else if (strcmp(str, "exit\n") == 0)
	{
		free(str);
		if (*_exit_ == 0)
			exit(0);
		else if (*_exit_ == 1)
			exit(127);
		exit(2);
	}
	return (str);
}
