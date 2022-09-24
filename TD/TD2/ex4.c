#include <stdio.h>

struct complexe{
	float x;
	float y;
	};

union valeur{
	int entier;
	float reel;
	struct complexe complexe;
	};

enum genre {entier, reel, complexe};

typedef struct nombre{
	enum genre  type;
	union valeur valeur;
}nombre;

nombre saisir_nombre();
void afficher_nombre(nombre);
void afficher_complexe(struct complexe);

nombre saisir_nombre()
{
    char type;
    printf("Type de nombre voulu : (E)ntier, (R)éel, (C)omplexe \n");
    scanf("%c", &type);
    nombre n;
    switch(type)
    {
    case 'E':
        n.type = 0;
        printf("Entrez l'entier : ");
        scanf("%d", &(n.valeur.entier));
        printf("\n");
        break;
    case 'R':
        n.type = 1;
        printf("Entrez le réel : ");
        scanf("%f", &(n.valeur.reel));
        printf("\n");
        break;
    case 'C':
        n.type = 2;
        struct complexe c;
        printf("Entrez x : ");
        scanf("%f", &(n.valeur.complexe.x));
        printf("\n");
        printf("Entrez y : ");
        scanf("%f", &(n.valeur.complexe.y));
        printf("\n");
        break;
    }
    return n;
}

void AfficherComplexe(struct complexe cmplx)
{
    if (cmplx.y < 0)
    {
        printf("%.2f - %.2fi\n", cmplx.x, -(cmplx.y));
    }
    else if (cmplx.y == 0)
    {
        printf("%.2f\n", cmplx.x);
    }
    else
    {
        printf("%.2f + %.2fi\n", cmplx.x, cmplx.y);
    }
}

void Afficher_Nombre(nombre n)
{
    if (n.type == entier)
    {
        printf("%d\n", n.valeur.entier);
    }
    else if (n.type == reel)
    {
        printf("%f\n", n.valeur.reel);
    }
    else
    {
        AfficherComplexe(n.valeur.complexe);
    }
}

int main()
{
    nombre n = saisir_nombre();
    Afficher_Nombre(n);
}
