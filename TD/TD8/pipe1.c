#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


main() {
	int tab1[10]={11,22,33,44,55,66,77,88,99,1000};
	int tab2[10];

	int pid, pip[2];

	pipe(pip);
	pid = fork();
	if (pid == 0)
	{
		write(pip[1], tab1, 10*sizeof(int));
	}
	else
	{
		read(pip[0], tab2, 10*sizeof(int));
		for (int i=0;i<10;i++)
		printf("%d,%d\n",tab2[i],tab1[i]);
	
	}
}


