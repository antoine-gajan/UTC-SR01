#include <stdio.h>

char  *jour[7]={"lundi", "mardi", "mercredi", "jeudi", "vendredi", "samedi","dimanche"};

unsigned int jourActuel(unsigned int premierJour, unsigned int date)
{
    return (date + premierJour - 1)%7;
}

int main()
{
    unsigned int premierJour;
    unsigned int date;
    printf("\nDonner l'indice du premier jour du mois : ");
    scanf("%u", &premierJour);
    printf("\nDonner la date : ");
    scanf("%u", &date);
    int j = jourActuel(premierJour,  date);
    printf("Le %d est un %s\n", date, jour[j]);
}
