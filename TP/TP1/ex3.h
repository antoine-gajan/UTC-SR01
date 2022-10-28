#define NB_RESTAU_MAX 100
#define TAILLE_MAX 50

typedef struct Position{
    double x;
    double y;
}Position;

typedef struct Specialite
{
    char noms[5][TAILLE_MAX]; // un restaurant propose au maximum 5 spécialités
    int nb;
}Specialite;

typedef struct Restaurant{
    char nom[TAILLE_MAX];
    char adresse[TAILLE_MAX];
    Position coordonnees;
    Specialite spe;
}Restaurant;

// Prototype des fonctions
int lire_restaurant(char* chemin, Restaurant restaurants[NB_RESTAU_MAX]);
void inserer_restaurant(char* chemin, Restaurant restaurant);

double calcul_distance(double x, double y, Restaurant r);
int est_dans_le_rayon(double x, double y, Restaurant r, double rayon);

void affiche_restaurant(Restaurant restaurant);
void affiche_restaurants_distance(Restaurant liste[NB_RESTAU_MAX], int nb, double x, double y);

int cherche_restaurant(double x, double y, double rayon_recherche, Restaurant liste_depart[NB_RESTAU_MAX], int nb_restau, Restaurant results[NB_RESTAU_MAX]);
int cherche_par_specialite(double x, double y, Specialite spec, Restaurant liste_depart[NB_RESTAU_MAX], int nb_restau, Restaurant results[NB_RESTAU_MAX]);

void tri(Restaurant liste[NB_RESTAU_MAX], int nb, double x, double y);

void vider_buffer();
void enlever_newline(char* texte);
