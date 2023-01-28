#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void main (int argc, char *argv[])
{
	FILE * fp;
	char c;
	pid_t parent_pid = getppid();

	while(1)
	{
		if (argc != 3) exit(EXIT_FAILURE);
		fp = fopen (argv[1], "r");
		if (fp == NULL) exit(EXIT_FAILURE);
		c = fgetc(fp);
		fclose(fp);
		if (c =='1')
		{
			printf("[power manager] Mise en veille en cours...\n");
			fp = fopen (argv[1], "w");
			fputs("0", fp);
			fclose(fp);
			if (kill(parent_pid, SIGUSR1) == -1) exit(EXIT_FAILURE);
		}
		sleep(atoi(argv[2]));
	}
}
