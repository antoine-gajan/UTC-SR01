#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	int i = 0;
	while(*envp)
	{
		printf("\nenvp[%d] = %s", i, *envp);
		i++;
		envp++;
	}
	return 0;
}
