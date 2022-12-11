#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
	system("/bin/ls -la");
	system("/bin/ls *.c");
}


