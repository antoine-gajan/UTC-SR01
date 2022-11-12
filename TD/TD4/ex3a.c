#include <stdio.h>
#define N 3
#define M 2

void matrice_info(int tab[N][M])
{
	int pos = 0;
	int neg = 0;
	int zero = 0;
	int nb_elts = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			nb_elts++;
			if(tab[i][j] > 0)
			{
				pos++;
			}
			else if(tab[i][j] < 0)
			{
				neg++;
			}
			else
			{
				zero++;
			}
		}
	}

	if ((double)zero / (double)nb_elts > 0.8) printf("La matrice est creuse\n");
	printf("Positifs : %d\n Negatifs : %d\n Zero : %d\n", pos, neg, zero);
}

int main()
{
	int mat[N][M];
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			printf("mat[%d][%d] = ", i, j);
			scanf("%d", &mat[i][j]);
		}
	}
	matrice_info(mat);
}
