#include <stdio.h>

int main()
{
	printf("\npid = %d", getpid());
	printf("\nppid = %d", getppid());
	printf("\nuid = %d", getuid());
	printf("\ngid = %d", getgid());
}
