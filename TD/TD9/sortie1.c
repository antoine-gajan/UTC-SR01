#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
	int nb;
	printf("Votre nombre : ");
	scanf("%d", &nb);	
	if ((nb >= 5) && (nb <= 10))
	{
		exit(0);
	}
	else
	{
		exit(1);
	}	
}

