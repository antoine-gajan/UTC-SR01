#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
	
	pid_t pid;	
	pid = fork();
	if (pid == 0)
	{
		// C'est le 1er fils
		printf("\nMon pid (1er fils) est %d, le pid de mon père est %d\n", getpid(), getppid());
		exit(1);
	}
	else
	{
		pid_t pid2;
		pid2 = fork();
		if (pid2 == 0)
		{
			// C'est le 2ème fils
			printf("\nMon pid (2ème fils) est %d, le pid de mon père est %d\n", getpid(), getppid());
			exit(2);
		}
		else
		{
			// C'est le père
			printf("\nMon pid est %d, le pid de mes fils sont %d et %d\n", getpid(), pid, pid2);
			int stat1;
			int stat2;
			waitpid(pid, &stat1,0);
			waitpid(pid2, &stat2,0);
			printf("\nMes fils ont retourné %d et %d\n", WEXITSTATUS(stat1), WEXITSTATUS(stat2));
		} 
		

	}
	return 0;
}
