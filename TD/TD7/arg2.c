#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	extern char **environ;
	int i = 0;
	while(*environ)
	{
		printf("\nenviron[%d] = %s", i, *environ);
		i++;
		environ++;
	}
	return 0;
}
