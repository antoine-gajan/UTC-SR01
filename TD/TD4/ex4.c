#include <stdio.h>
#include <math.h>
int jeu_ordi (int nb_allum, int prise_max)
{
int prise = 0;
int s = 0;
float t = 0;
s = prise_max + 1;
t = ((float) (nb_allum - s)) / (prise_max + 1);
while (t != floor (t))
  {
   s--;
   t = ((float) (nb_allum-s)) / (prise_max + 1);
  }
prise = s - 1;
if (prise == 0)
prise = 1;
return (prise);
}

int jeu_joueur (int nb_allum, int prise, int prise_max)
{
if (prise <= nb_allum && prise <= prise_max)
{
	return 1;
}
return 0;
}

void affichage(int nb_allum)
{
	for (int i = 0; i < nb_allum; i++)
	{
		printf("o ");
	}
	printf("\n\n");
	for (int i = 0; i < nb_allum; i++)
	{
		printf("| ");
	}
	printf("\n");
}


int main ()
{
int nb_max_d=0; /*nbre d'allumettes maxi au départ*/
int nb_allu_max=0; /*nbre d'allumettes maxi que l?on peut tirer au maxi*/
int qui=0; /*qui joue? 0=Nous --- 1=PC*/
int prise=0; /*nbre d'allumettes prises par le joueur*/
int nb_allu_rest=0; /*nbre d'allumettes restantes*/

printf("\nLe nombre d'allumettes disposées entre les deux joueur (de 10 à 60) ?");
scanf("%d", &nb_max_d);
while (nb_max_d < 10 || nb_max_d > 60)
{
	printf("\nErreur : donnez le nombre d'allumettes disposées entre les deux joueur (de 10 à 60).");
	scanf("%d", &nb_max_d);
}

printf("\nLe nombre maximal d'allumettes que l'on peut retirer ?");
scanf("%d", &nb_allu_max);
while (nb_allu_max < 1 || nb_allu_max > nb_max_d)
{
	printf("\nErreur : donnez le nombre maximal d'allumettes que l'on peut retirer : ");
	scanf("%d", &nb_allu_max);
}

printf("\nQui commence (0 pour le joueur et 1 pour l'ordinateur) ?");
scanf("%d", &qui);
while (qui != 1 && qui != 0)
{
	printf("\nErreur : donnez 0 pour le joueur et 1 pour l'ordinateur : ");
	scanf("%d", &qui);
}

nb_allu_rest = nb_max_d;

while (nb_allu_rest != 0)
{
	affichage(nb_allu_rest);
	switch(qui)
	{
		case 0:
			printf("\nCombien d'allumettes voulez vous retirer ?");
			scanf("%d", &prise);
			while (jeu_joueur(nb_allu_rest, prise, nb_allu_max) == 0)
			{
				printf("\nErreur : combien d'allumettes voulez vous retirer ?");
				scanf("%d", &prise);
			}
			nb_allu_rest -= prise;
			qui = 1;
			break;
		case 1:
			prise = jeu_ordi(nb_allu_rest, nb_allu_max);
			printf("\nL'ordinateur a retiré %d allumettes\n", prise);
			nb_allu_rest -= prise;
			qui = 0;
			break;			
	}
}
if (qui == 0)
{
	printf("\nVous avez gagné !\n");
}

else
{
	printf("\nVous avez perdu !\n");
}


}
