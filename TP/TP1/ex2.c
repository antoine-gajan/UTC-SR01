#include <stdio.h>
#include <stdlib.h>

// Fonction qui demande à l'utilisateur N notes et les stocke dans un tableau
int* lecture(int N)
{
    // Allocation dynammique du tableau points
    int *points =  malloc(sizeof(int) * N);
    printf("\nEntrez des notes entre 0 et 60.");
    for (int i = 0; i < N; i++)
    {
        printf("\nNote n°%d : ", i+1);
        scanf("%d", &points[i]);
        // Tant que la note n'est pas dans l'intervalle
        while (points[i] < 0 || points[i] > 60)
        {
            // On affiche erreur et on redemande
            printf("\nErreur : la note doit etre comprise entre 0 et 60.\nNote n°%d : ", i + 1);
            scanf("%d", &points[i]);
        }
    }
    return points;
}

// Fonction qui retourne la note minimale du tableau d'une taille donnée
int min(int* tab, int taille)
{
    int indice_min = 0;
    for (int i = 0; i < taille; i++)
    {
        // Si la valeur actuelle est inférieure à la valeur min, on change le min
        if (tab[i] < tab[indice_min])
        {
            indice_min = i;
        }
    }
    // Retourne le min
    return tab[indice_min];
}

// Fonction qui retourne le max du tableau d'une taille donnée
int max(int* tab, int taille)
{
    int indice_max = 0;
    for (int i = 0; i < taille; i++)
    {
        // Si la valeur actuelle est supérieure à la valeur max, on change le max
        if (tab[i] > tab[indice_max])
        {
            indice_max = i;
        }
    }
    // Retourne le max
    return tab[indice_max];
}

// Fonction qui retourne la moyenne d'un tableau d'entiers
double moyenne(int* tab, int taille)
{
    double somme = 0.0;
    for (int i = 0; i < taille; i++)
    {
        somme += tab[i];
    }
    return somme/taille;
}

// Fonction de répartition en intervalles de dizaines
int* repartition(int* points, int taille)
{
    int *notes = malloc(sizeof(int)*7);
    // Initialisation du tableau
    for (int i = 0; i < 7; i++) notes[i] = 0;
    // Mise à jour du tableau de notes pour chaque note dans points
    for (int i = 0; i < taille; i++)
    {
        int intervalle_appartenance = points[i] / 10;
        // Incrémentation du nombre de notes dans l'intervalle voulu
        notes[intervalle_appartenance] ++;
    }
    return notes;
}

void affichage_notes(int* tab, int taille)
{
    for (int i = 0; i < taille; i++)
    {
        printf("\nNOTES[%d] = %d", i, tab[i]);
    }
    printf("\n\n");
}

// Fonction qui affiche en nuage de points le tableau
void nuage_points(int* tab, int taille)
{
    int maxn = max(tab, taille);
    // Affichage des ordonnées
    for (int i = maxn; i > 0; i--)
    {
        printf("%d >\t", i);
        for (int j = 0; j < taille; j++)
        {
            // Affichage du o si nécessaire
            if (tab[j] == i)
            {
                printf("    o   ");
            }
            // Sinon affichage espace blanc
            else
            {
                printf("        ");
            }
        }
        printf("\n\n");
    }
    printf("  \t");
    // Affichage de l'axe des abscisses
    for (int i = 0; i < 7; i++)
    {
        if (tab[i] == 0)
        {
            printf("+---o---");
        }
        else
        {
            printf("+-------");
        }
        // Si c'est les notes 60, on ajoute le + final de l'affichage puis retour à la ligne
        if (i == 6) printf("+\n");
    }
    printf("  \t");
    // Affichage des valeurs en abscisse
    for (int i = 0; i < 7; i++)
    {
        if (i == 0)
        {
            printf("| %d - %d ", i*10, i*10+9);
        }
        else if (i == 6)
        {
            printf("|  60   |\n\n");
        }
        else
        {
            printf("|%d - %d", i*10, i*10+9);
        }
    }
}

// Fonction qui affiche un graphique en batons associé au tableau
void graphique_batons(int* tab, int taille)
{
    int maxn = max(tab, taille);
    // Affichage des ordonnées
    for (int i = maxn; i > 0; i--)
    {
        printf("%d >\t", i);
        for (int j = 0; j < taille; j++)
        {
            // Affichage du o si nécessaire
            if (tab[j] >= i)
            {
                printf(" ###### ");
            }
            // Sinon affichage espace blanc
            else
            {
                printf("        ");
            }
        }
        printf("\n\n");
    }
    printf("  \t");
    // Affichage de l'axe des abscisses
    for (int i = 0; i < 7; i++)
    {
        printf("+-------");
        // Si c'est les notes 60, on ajoute le + final de l'affichage puis retour à la ligne
        if (i == 6) printf("+\n");
    }
    printf("  \t");
    // Affichage des valeurs en abscisse
    for (int i = 0; i < 7; i++)
    {
        if (i == 0)
        {
            printf("| %d - %d ", i*10, i*10+9);
        }
        else if (i == 6)
        {
            printf("|  60   |\n");
        }
        else
        {
            printf("|%d - %d", i*10, i*10+9);
        }
    }
}

int main()
{
    // Nombre de notes à lire
    int N;
    // Demande du nombre de notes
    printf("\nLes notes seront des valeurs entieres comprises entre 0 et 60.\nCombien de notes souhaitez-vous lire ? ");
    scanf("%d", &N);
    // Lecture des notes
    int* points = lecture(N);

    // Calcul des statistiques usuelles
    printf("\n\n=== STATISTIQUES USUELLES ===\n");
    printf("\nMin : %d\n", min(points, N));
    printf("\nMax : %d\n", max(points, N));
    printf("\nMoyenne : %f\n", moyenne(points, N));

    // Création de NOTES et affichage
    int *notes = repartition(points, N);
    printf("\n\n=== REPARTITION DES NOTES ===\n\n");
    affichage_notes(notes, 7);

    //Affichage graphique
    printf("\n\n=== NUAGE DE POINTS ===\n\n");
    nuage_points(notes, 7);
    printf("\n\n=== GRAPHIQUE EN BATONS ===\n\n");
    graphique_batons(notes, 7);
    free(points);
    return 0;
}
