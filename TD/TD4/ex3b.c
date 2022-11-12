#include <stdio.h>
#define N 3
#define M 2

int matrice_creuse(int tab[N][M], int vect[N*M])
{
	int zero = 0, k = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (tab[i][j] == 0)
			{
				zero ++;
			}
			else
			{
					vect[k] = tab[i][j];
					k++;
			}
		}
	}
	if (zero / N*M > 0.8) return 1;
	return 0;
}

int main()
{
	int mat[N][M], vect[N*M];
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			printf("mat[%d][%d] = ", i, j);
			scanf("%d", &mat[i][j]);
		}
	}
	int estCreuse = matrice_creuse(mat, vect);
	if(estCreuse = 1) printf("Matrice creuse\n");
	for (int j = 0; j < N*M; j++)
	{
		printf("vect[%d] = %d\n", j, vect[j]);
	}
}
