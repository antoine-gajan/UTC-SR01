#include <stdio.h>
#include <stdlib.h>

int main(int nb, char* arg[])
{
	double result = 0;
	switch(arg[1][1])
	{
	char * stopstring;
	case 'a':
		for (int i = 2; i < nb; i++)
		{
			result += strtod(arg[i], &stopstring);
		}
		break;
	case 'p':
		result = 1;
		for (int i = 2; i < nb; i++)
		{
			result *= strtod(arg[i], &stopstring);
		}
		break;
	case 'd':
		if (nb == 4)
		{
			result = strtod(arg[2], &stopstring)/strtod(arg[3], &stopstring);
		}

	}
	printf("%f", result);
	return 0;
}
