#include <stdio.h>
#define TAILLE 10


int main()
{
	for (int i = 0; i < TAILLE; i++)
	{
		for (int j = 0; j < TAILLE - i; j++)
		{
			printf(" ");
		}
		for (int k = 0; k < 2 * i + 1; k++)
		{
			printf("*");
		}
		printf("\n");
	}
	for (int i = 0; i < 4; i ++)
	{
		for (int j = 0; j < TAILLE - 2; j++)
		{
			printf(" ");
		}
		for (int j = 0; j < 4; j++)
		{
			printf("|");
		}
		printf("\n");
	}
}
