#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t pid;	
	pid = fork();
	if (pid == 0)
	{
		// C'est le fils
		printf("\nMon pid est %d, le pid de mon père est %d\n", getpid(), getppid());
	}
	else
	{
		// C'est le père
		printf("\nMon pid est %d, le pid de mon fils est %d\n", getpid(), pid);
	}

	
	return 0;
}
