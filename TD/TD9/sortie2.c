#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

void fonction()
{
	printf("Bonjour");
}

int main()
{
	atexit(fonction);
	sleep(5);
	exit(0);
}


