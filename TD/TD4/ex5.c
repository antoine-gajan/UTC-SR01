#include <stdio.h>
#include <stdlib.h>

#define NBLIG 50
#define NBCOL 50

void initialisation_damier(int matrice[NBLIG][NBCOL])
{
	for (int i = 0; i < NBLIG; i++)
	{
		for (int j = 0 ; j < NBCOL; j++)
		{	
			matrice[i][j] = rand()%2;
		}
	}
}

int nb_voisins(int matrice[NBLIG][NBCOL], int i , int j)
{
	int nb_voisins_en_vie = 0;

	for (int lig = i - 1; lig < i + 2; i++)
	{
		for (int col = j - 1; col < j + 2; col ++)
		{
			int lig_reel = lig;
			int col_reel = col;
			if (col == -1) col_reel = NBCOL - 1;
			if (col == NBCOL) col_reel = 0;
			if (lig == -1) lig_reel = NBLIG - 1;
			if (lig == NBLIG) lig_reel = 0;
			nb_voisins_en_vie += matrice[lig_reel][col_reel];
		}
	}
	nb_voisins_en_vie -= matrice[i][j];
	return nb_voisins_en_vie;
}


void affichage(int matrice[NBLIG][NBCOL])
{
	for (int i = 0; i < NBLIG; i++)
	{
		for (int j = 0 ; j < NBCOL; j++)
		{	
			printf("%d ", matrice[i][j]);
		}
		printf("\n");
	}
}

void jeu_de_la_vie(int matrice[NBLIG][NBCOL])
{
	int temp[NBLIG][NBCOL];

	for (int i = 0; i < NBLIG; i++)
	{
		for (int j = 0 ; j < NBCOL; j++)
		{	
			int voisins = nb_voisins(matrice, i, j);
			if (matrice[i][j] == 1 && (voisins == 2 || voisins == 3))
			{
				temp[i][j] = 1;
			}
			else if (matrice[i][j] == 0 && voisins == 3)
			{
				temp[i][j] = 1;
			}
			else
			{
				temp[i][j] = 0;
			}
		}

	}
	return temp;
}



