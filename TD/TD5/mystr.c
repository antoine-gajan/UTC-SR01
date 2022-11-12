#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mystr.h"

/* inverse les majuscules et les minuscules de s1 et retourne le resultat dans s2 exemple: s1="TiCtAc"  s2="tIcTaC" */
void mystrupdown(char *s1, char *s2)
{

	while (*s1 != '\0')
	{
		if (*s1 >= 'A' && *s1 <= 'Z')
		{
			*s2 = *s1 + 'a' - 'A';
		}
		else if (*s1 >= 'a' && *s1 <= 'z')
		{
			*s2 = *s1 + 'A' - 'a';
		}
		else *s2 = *s1;
		s1++;
		s2++;
	}
}          

/* inverse la chaîne s1 et retoune le résultat dans s2:   exemple  s1="tac" s2="cat" */
void mystrinv(char *s1, char *s2)     
{
	int taille = strlen(s1);
	for (int i = 0; i < taille; i++)
	{
		s2[i] = s1[taille - i];
	}
}   
   
/* retourne le nombre d'occurrences de c dans  la chaîne s */
int mystrchrn(char *s, char c)   
{
	int nb = 0;
	for (int i = 0; i < strlen(s); i++)
	{
		if (s[i] == c) nb++;
	}
	return nb;
}
                     
/* copie les n derniers caractères de s1 dans s2 et retourne s2 */
void mystrncpy(char *s1, char *s2, int n)      
{
	int j = 0;
	if (strlen(s1) >= n)
	{
		for (int i = strlen(s1) - n; i < strlen(s1); i++)
		{
			s2[j] = s1[i];
			j++;
		}
	}
	else
	{
		printf("La chaine de caracteres est trop courte ! \n");
	}
}

/* concatène au plus les n derniers caractères de s1 à la chaîne s2 */
void mystrncat(char *s1, char *s2, int n)     
{
	int min = (strlen(s1) > n) ? strlen(s1) -n : 0;
	strcat(s2, (s1+min));
}


 
