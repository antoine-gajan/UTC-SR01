#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t pid;	
	pid = fork();
	if (pid == 0)
	{
		// C'est le 1er fils
		printf("\nMon pid (1er fils) est %d, le pid de mon père est %d\n", getpid(), getppid());
	}
	else
	{
		pid_t pid2;
		pid2 = fork();
		if (pid2 == 0)
		{
			// C'est le 2ème fils
			printf("\nMon pid (2ème fils) est %d, le pid de mon père est %d\n", getpid(), getppid());
		}
		else
		{
			// C'est le père
			printf("\nMon pid est %d, le pid de mes fils sont %d et %d\n", getpid(), pid, pid2);
		} 
		

	}
	return 0;
}
