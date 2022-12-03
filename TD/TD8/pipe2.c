#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[], char *envp[]) 
{
	pid_t pid;
	int fd[2];
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(1);
		dup(fd[1]);
		close(fd[0]);
		execlp("ls", "ls", "-la", NULL);
		exit(2);
	}
	else
	{
		close(0);
		dup(fd[0]);
		close(fd[1]);
		execlp("wc", "wc", "-l", NULL);
	}
	return 0;
}


