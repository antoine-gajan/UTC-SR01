#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[])
{
	char nom_variable[50];
	char modif[50];
	printf("\nNom de la variable : ");
	scanf("%s", nom_variable);
	strcpy(modif, nom_variable);

	printf("\n%s=%s\n", nom_variable, getenv(nom_variable));

	putenv(strcat(nom_variable, "=Exemple2"));

	printf("\n%s=%s", modif, getenv(modif));
	return 0;
}
