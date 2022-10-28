#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ex3.h"


int lire_restaurant(char* chemin, Restaurant restaurants[NB_RESTAU_MAX])
{
    int num_restau = 0;
    int i = 0;
    int j;
    // Ouverture du fichier en lecture
    FILE* fichier = fopen(chemin, "r");
    if (fichier != NULL)
    {
        // Création d'un buffer ligne qui contiendra la ligne en cours
        char ligne[256];
        char *next;
        // Saut de la première ligne de présentation
        fgets(ligne, sizeof(ligne), fichier);
        // Parcours du fichier
        while (fgets(ligne, sizeof(ligne), fichier))
        {
            // Si la ligne contient un restaurant
            if (ligne[0] != '\n')
            {
                i = 0;
                char *chaine = strtok(ligne, ";");
                while (chaine != NULL && i < 4)
                {
                    if (i == 0)
                    {
                        // Copie du nom du restaurant
                        strcpy(restaurants[num_restau].nom, chaine);
                    }
                    else if (i == 1)
                    {
                        strcpy(restaurants[num_restau].adresse, chaine);
                        //printf("%s", restaurants[num_restau].adresse);
                    }
                    else if (i == 2)
                    {
                        // Initialisation de next avec ce qui suit après le ; pour pas que ce soit écrasé
                        next = strtok(NULL, ";");
                        // Split pour obtenir la coordonnée x
                        char* info_coordonnees = strtok(chaine, ",");
                        // Enlever les espaces
                        while (info_coordonnees[0] == ' ')
                        {
                            info_coordonnees++;
                        }
                        // Conversion de x en double
                        info_coordonnees = info_coordonnees + 3;
                        restaurants[num_restau].coordonnees.x = atof(info_coordonnees);

                        info_coordonnees = strtok(NULL, ",");
                        // Split pour obtenir la coordonnée y
                        info_coordonnees = info_coordonnees + 3;
                        info_coordonnees[strlen(info_coordonnees) - 1] = '\0';
                        // Conversion de y en double
                        restaurants[num_restau].coordonnees.y = atof(info_coordonnees);
                        //printf("%f\n", restaurants[num_restau].coordonnees.y);
                    }
                    else
                    {
                        // On skip le {
                        chaine += 2;
                        // on enlève le }
                        chaine[strlen(chaine) - 1] = '\0';
                        char* spe = strtok(chaine, ",");
                        j = 0;
                        while (spe != NULL)
                        {
                            strcpy(restaurants[num_restau].spe.noms[j] , spe);
                            //printf("%s\n", restaurants[num_restau].spe.noms[j]);
                            spe = strtok(NULL, ",");
                            j++;
                        }
                        restaurants[num_restau].spe.nb = j;
                    }
                    // Si on a lu les coordonnées, on change la chaine
                    if (i == 2) chaine = next;
                    else chaine = strtok(NULL, ";");
                    i++;
                }
                num_restau++;
            }
        }
        // Fermeture du fichier
        fclose(fichier);
    }
    return num_restau;
}

void inserer_restaurant(char* chemin, Restaurant restaurant)
{
    // Ouverture du fichier en lecture
    FILE* fichier = fopen(chemin, "a");
    // Si l'ouverture a fonctionné
    if (fichier != NULL)
    {
        // Ecriture dans le fichier
        fprintf(fichier, "\n\n%s; %s; (x=%f, y=%f); {", restaurant.nom, restaurant.adresse, restaurant.coordonnees.x, restaurant.coordonnees.y);
        // Ajout des spécialités
        for (int i = 0; i < restaurant.spe.nb; i++)
        {
            if (i == restaurant.spe.nb - 1) fprintf(fichier, "%s", restaurant.spe.noms[i]);
            else fprintf(fichier, "%s, ", restaurant.spe.noms[i]);
        }
        fprintf(fichier, "};");
    }
    // Fermeture du fichier
    fclose(fichier);
}

// Fonction qui calcule la distance entre un point et un restaurant
double calcul_distance(double x, double y, Restaurant r)
{
    return sqrt((x-r.coordonnees.x)*(x-r.coordonnees.x) + (y - r.coordonnees.y)*(y - r.coordonnees.y));
}

// Fonction qui renvoie si un restaurant est dans le rayon demandé par l'utilisateur
int est_dans_le_rayon(double x, double y, Restaurant r, double rayon)
{
    // Retourne 1 si on est dans le rayon
    if (calcul_distance(x, y, r) <= rayon)
    {
        return 1;
    }
    // Retourne 0 sinon
    else
    {
        return 0;
    }
}

int cherche_restaurant(double x, double y, double rayon_recherche, Restaurant liste_depart[NB_RESTAU_MAX], int nb_restau, Restaurant results[NB_RESTAU_MAX])
{
    int indice_restau_result = 0;
    for (int i = 0; i < nb_restau; i++)
    {
        // Si le restaurant est dans le rayon
        if (est_dans_le_rayon(x, y, liste_depart[i], rayon_recherche))
        {
            // Ajout du restaurant à la liste des resultats
            results[indice_restau_result] = liste_depart[i];
            indice_restau_result++;
        }
    }
    tri(results, indice_restau_result, x, y);
    // Retourne le nombre de restaurants
    return indice_restau_result;
}

// Fonction qui affiche un restaurant
void affiche_restaurant(Restaurant restaurant)
{
    // Affichage
    printf("\n\nNom : %s\nAdresse : %s\nCoordonnees :\n\t- x=%f\n\t- y=%f\nSpecialite(s):", restaurant.nom, restaurant.adresse, restaurant.coordonnees.x, restaurant.coordonnees.y);
    // Affichage des spécialités
    for (int j = 0; j < restaurant.spe.nb; j++)
    {
        printf("\n\t- %s", restaurant.spe.noms[j]);
    }
}


// Fonction qui affiche les restaurants d'une liste de restaurants
void affiche_restaurants(Restaurant liste[NB_RESTAU_MAX], int nb)
{
    // Itération sur les restaurants
    for (int i = 0; i < nb; i++)
    {
        affiche_restaurant(liste[i]);
    }
    printf("\n");
}

// Fonction qui affiche les restaurants d'une liste de restaurants avec leur distance à un point (x, y)
void affiche_restaurants_distance(Restaurant liste[NB_RESTAU_MAX], int nb, double x, double y)
{
    // Itération sur les restaurants
    for (int i = 0; i < nb; i++)
    {
        affiche_restaurant(liste[i]);
        printf("\nDistance : %lf\n", calcul_distance(x, y, liste[i]));
    }
}

int cherche_par_specialite(double x, double y, Specialite spec, Restaurant liste_depart[NB_RESTAU_MAX], int nb_restau, Restaurant results[NB_RESTAU_MAX])
{
    // Variable qui contient l'indice du restaurant actuel dans results
    int indice_restau_result = 0;

    // Variables pour parcourir les specialites
    int est_ajoute = 0;
    // Parcours pour chaque restaurant
    for (int i = 0; i < nb_restau; i++)
    {
        est_ajoute = 0;
        // Pour chaque spécialité du restaurant
        for (int j = 0; j < liste_depart[i].spe.nb && !est_ajoute; j++)
        {
            // Pour chaque spé en paramètre
            for (int k = 0; k < spec.nb && !est_ajoute; k++)
            {
                // Si la spécialité est correcte
                if (strcmp(liste_depart[i].spe.noms[j], spec.noms[k]) == 0)
                {

                    // Ajout du restaurant à la liste des résultats
                    est_ajoute = 1;
                    results[indice_restau_result] = liste_depart[i];
                    indice_restau_result ++;
                }
            }
        }
    }
    // Tri du tableau
    tri(results, indice_restau_result, x, y);
    // Retourne le nombre de restaurants
    return indice_restau_result;
}

// Fonction qui trie par sélection les restaurants dans une liste
void tri(Restaurant liste[NB_RESTAU_MAX], int nb, double x, double y)
{
    // Variable qui contient l'indice du minimum
    int indice_min;
    // Variable de copie temporaire lors du switch
    Restaurant temp;
    for (int i = 0; i < nb - 1; i++)
    {
        indice_min = i;
        for (int j = i + 1; j < nb; j++)
        {
            // Si la distance est inférieure
            if (calcul_distance(x, y, liste[indice_min]) > calcul_distance(x, y, liste[j]))
            {
                // On change l'indice_min
                indice_min = j;
            }
        }
        if (indice_min != i)
        {
            // Echanger les éléments
            temp = liste[i];
            liste[i] = liste[indice_min];
            liste[indice_min] = temp;
        }
    }
}

//Fonction pour vider le buffer
void vider_buffer()
{
    while (getchar() != '\n');
}

void enlever_newline(char* texte)
{
    // Enleve le \n à la fin d'une chaine
    if ((strlen(texte) > 0) && (texte[strlen (texte) - 1] == '\n'))
        texte[strlen(texte) - 1] = '\0';
}

int main()
{
    // Header
    printf("===== GESTION DE RESTAURANTS =====");

    // Variables globales
    int reponse = -1;
    int nb_restaurants = 0;
    int file_open = 0;
    Restaurant liste_restaurants[NB_RESTAU_MAX];
    char filename[100];
    // Menu principal
    while(reponse != 5){
        printf("\n*** INDEXATION ET RECHERCHE DANS UN FICHIER ***\n");
        printf("1. Recuperer les donnees d'un fichier contenant une liste de restaurants\n");
        printf("2. Inserer un restaurant\n");
        printf("3. Chercher les restaurants a proximite\n");
        printf("4. Chercher les restaurants par specialite\n");
        printf("5. Quitter\n");

    // Demande du choix
        do{
        printf("\nVotre choix : ");
        scanf("%d", &reponse);
        } while(reponse < 1 || reponse > 5);

        // Cas différent en fonction de la réponse
        switch(reponse)
        {
            case 1:
                printf("\n=== Recuperer les donnees d'un fichier contenant une liste de restaurants ===\n");
                //Vider le buffer par sécurité
                vider_buffer();
                // Demande du fichier à ouvrir
                printf("\nNom du fichier a charger : ");
                fgets(filename, TAILLE_MAX, stdin);
                enlever_newline(filename);
                printf("\n");
                // Lecture du fichier
                nb_restaurants = lire_restaurant(filename, liste_restaurants);
                printf("\nLe fichier %s a ete charge avec succes.\nIl contient %d restaurants.\n", filename, nb_restaurants);
                affiche_restaurants(liste_restaurants, nb_restaurants);
                file_open = 1;
                sleep(1);
                break;
            case 2:
                printf("\n=== Inserer un restaurant ===\n");
                // Si pas de fichier ouvert, on demande
                if (!file_open)
                {
                    vider_buffer();
                    printf("\nNom du fichier avec les restaurants : ");
                    scanf("%s", filename);
                    file_open = 1;
                    vider_buffer();
                }
                // Lecture du nouveau restaurant
                Restaurant nouveau;
                // Demande des informations du restaurant
                printf("\nNom du restaurant : ");
                // Vider le buffer par sécurité
                vider_buffer();
                fgets(nouveau.nom, TAILLE_MAX, stdin);
                enlever_newline(nouveau.nom);
                printf("\Adresse du restaurant : ");
                fgets(nouveau.adresse, TAILLE_MAX, stdin);
                enlever_newline(nouveau.adresse);
                printf("\nCoordonnees : ");
                printf("\n\t- x = ");
                scanf("%lf", &nouveau.coordonnees.x);
                printf("\n\t- y = ");
                scanf("%lf", &nouveau.coordonnees.y);
                // Demande des spécialités
                printf("\nSpecialite(s) du restaurant :");
                Specialite liste_spe;

                // Nombre de spécialités
                int nb_spe = 0;
                while (nb_spe < 1 || nb_spe > 5)
                {
                    printf("\nEntrez le nombre de specialites du restaurant (entre 1 et 5) : ");
                    scanf("%d", &nb_spe);
                }
                liste_spe.nb = nb_spe;
                vider_buffer();
                // Demande de chaque spécialité
                for (int i = 0; i < nb_spe; i++)
                {
                    printf("\nSpecialite %d : ", i + 1);
                    fgets(liste_spe.noms[i], TAILLE_MAX, stdin);
                    enlever_newline(liste_spe.noms[i]);
                }
                nouveau.spe = liste_spe;
                // Insertion du restaurant
                inserer_restaurant(filename, nouveau);
                // Ajout du restaurant à la liste précedemment créée
                liste_restaurants[nb_restaurants++] = nouveau;
                printf("\nLe restaurant suivant a ete ajoute :");
                // Affichage du nouveau restaurant
                affiche_restaurant(nouveau);
                sleep(2);
                break;
            case 3:
                printf("=== Chercher les restaurants à proximite ===\n");
                // Demande des informations
                double x, y, rayon_souhaite;
                Restaurant liste_resultat[NB_RESTAU_MAX];
                // Vider le buffer par sécurité
                vider_buffer();
                printf("\nVotre position : ");
                printf("\n\t- x = ");
                scanf("%lf", &x);
                printf("\n\t- y = ");
                scanf("%lf", &y);
                printf("\nRayon de recherche : ");
                scanf("%lf", &rayon_souhaite);
                int nb_res = cherche_restaurant(x, y, rayon_souhaite, liste_restaurants, nb_restaurants, liste_resultat);

                // Affichage des restaurants avec leur distance (triée par ordre croissant)
                if (nb_res != 0)
                {
                    printf("\nVoici les restaurants dans votre rayon de recherche : ");
                    affiche_restaurants_distance(liste_resultat, nb_res, x, y);
                }
                else
                {
                    printf("\nAucun restaurant ne correspond a votre recherche.\n");
                }
                sleep(2);
                break;
            case 4:
                printf("=== Chercher les restaurants par specialite ===\n");
                double x1, y1;
                // Demande des informations
                Restaurant liste_resultat2[NB_RESTAU_MAX];
                // Vidage du buffer par sécurité
                vider_buffer();
                printf("\nVotre position : ");
                printf("\n\t- x = ");
                scanf("%lf", &x1);
                printf("\n\t- y = ");
                scanf("%lf", &y1);
                printf("\nSpecialite(s) du restaurant :");
                Specialite liste_spe2;
                vider_buffer();
                // Nombre de spécialités
                int nb_spe2 = 0;
                while (nb_spe2 < 1 || nb_spe2 > 5)
                {
                    printf("\nEntrez le nombre de specialites recherchees (entre 1 et 5) : ");
                    scanf("%d", &nb_spe2);
                }
                liste_spe2.nb = nb_spe2;
                vider_buffer();
                // Demande de chaque spécialité
                for (int i = 0; i < nb_spe2; i++)
                {
                    printf("\nSpecialite %d : ", i + 1);
                    fgets(liste_spe2.noms[i], TAILLE_MAX, stdin);
                    enlever_newline(liste_spe2.noms[i]);
                }
                int nb_resu = cherche_par_specialite(x1, y1, liste_spe2, liste_restaurants, nb_restaurants, liste_resultat2);

                // Affichage des restaurants avec leur distance
                if (nb_resu != 0)
                {
                    printf("\nVoici les restaurants qui proposent au moins une de ces specialites : ");
                    affiche_restaurants_distance(liste_resultat2, nb_resu, x1, y1);
                }
                else
                {
                    printf("\nAucun restaurant ne correspond a votre recherche.\n");
                }
                sleep(2);
                break;
            case 5:
                // Quitter le programme
                printf("\nVous allez quitter le programme.\n");
                sleep(2);
                break;
        }
    }
    return 0;
}
