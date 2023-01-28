#define NB_MAX_ARG 10
#define TAILLE_MAX_STRING 200

typedef struct Application
{
    char name[TAILLE_MAX_STRING];
    char path[TAILLE_MAX_STRING];
    int nb_arguments;
    char arguments[NB_MAX_ARG][TAILLE_MAX_STRING];
    pid_t pid;
    int en_marche;
}Application;

// Fonction pour décoder le fichier
int lecture_fichier(FILE *fichier, Application *tab_app);
// Fonction pour convertir un buffer en chaine1=chaine2
int convertir(unsigned char *buffer, unsigned char *chaine1, unsigned char *chaine2);
