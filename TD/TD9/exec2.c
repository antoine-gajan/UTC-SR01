#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

char * argv1[] = {"ls", "-la", NULL};
char * argv2[] = {"ls", "*.c", NULL};

int my_system(char* path, char *argv[])
{
	execv(path, argv);
}

int main()
{
		printf("Affichage 1");
		my_system("/bin/ls", argv1);
		my_system("/bin/ls", argv2);
}
