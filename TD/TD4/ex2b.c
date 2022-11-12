#include <stdio.h>
#define TAILLE 10
#define NBRE 3


int main()
{
	for (int i = 0; i < TAILLE; i++)
	{
		for (int l = 0; l < NBRE; l++)
		{
			for (int j = 0; j < TAILLE - i; j++)
			{
				printf(" ");
			}
			for (int k = 0; k < 2 * i + 1; k++)
			{
				printf("*");
			}
			for (int j = 0; j < TAILLE - i - 1; j++)
			{
				printf(" ");
			}
			
		}
		printf("\n");
	}
	for (int i = 0; i < 4; i ++)
	{
		for (int l = 0; l < NBRE; l++)
		{
			for (int j = 0; j < TAILLE - 2; j++)
			{
				printf(" ");
			}
			for (int j = 0; j < 4; j++)
			{
				printf("|");
			}
			for (int j = 0; j < TAILLE - 2; j++)
			{
				printf(" ");
			}

		}			
		printf("\n");
	}
}
