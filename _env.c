#include "main.h"

/**
 * _env - read environ var and print it.
*/

void _env(void)
{
	int count = 0;

	while (environ[count])
	{
		printf("%s\n", environ[count]);
		count++;
	}
}
