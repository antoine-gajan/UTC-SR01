#include <stdio.h>
#include <stdlib.h>
#include "mystr.h"
#define TAILLE_MAX 100

int main()
{
	int reponse = 0;
	char s1[TAILLE_MAX];
	strcpy(s1, "bonjour");
	char s2[TAILLE_MAX];
	printf("TEST LIBRAIRIE\n1 mystrupdown\n2 mystrinv\n3 mystrchrn\n4 mystrncpy\n5 mystrncat\n");
	printf("Votre choix : ");
	scanf("%d", &reponse);
	while (reponse <= 0 || reponse > 5)
	{
		printf("\nErreur : reponse non valide !\nVotre choix :");
		scanf("%d", &reponse);
	}
	
	switch (reponse)
	{
		case 1 :
			mystrupdown(s1, s2);
			printf("\n%s", s2);
			break;
		case 2 :
			mystrinv(s1, s2);
			printf("\n%s", s2);
			break;
		case 3 :
			printf("\nCaractere recherche : ");
			char c = getchar();			
			int nb = mystrchrn(s1, c);
			printf("\nLa lettre %c est presente %d fois dans %s.", c, nb, s1); 
			break;
		case 4 :
			printf("\nCombien de caractères à copier ? ");
			int n;
			scanf("%d", &n);
			mystrncpy(s1, s2, n);
			printf("\n%s", s2);
			break;
		case 5 :
			printf("\nCombien de caractères à concatener ? ");
			int n2;
			scanf("%d", &n2);
			mystrncat(s1, s2, n2);
			printf("\n%s", s2);
			break;
		default:
			printf("Sortie du programme.");
			exit(1);
	}
}
