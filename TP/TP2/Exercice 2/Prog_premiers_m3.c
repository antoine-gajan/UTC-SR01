#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

int premier(int nb)
{
    int r=0;
    for(int i = 1 ; i <= nb ; i++ )
    {
        if(nb % i == 0) r++;
    }
    if(r>2)
        return 0;
    else
        return 1;
}

void explorer(int debut, int fin)
{
    // Ajout d'une variable qui compte le nombre de nombres premiers rencontrés
    int etat,pid,pid2,num_nb_prem = 0;
    pid=fork();
    if(pid==0)
    {
        for (int i=debut; i<=fin; i++)
        {
            if (premier(i)==1)
            {
                // On augmente le nombre de nombre premiers rencontrés
                num_nb_prem++;
                pid2=fork();
                if (pid2==0)
                {
                    char chaine[100];
                    sprintf(chaine,"echo ' %d est un nombre premier ecrit par le processus %d'>>nbr_premiers.txt",i,getpid());
                    system(chaine);
                    sleep(2);
                    exit(0);
                }
            }
        }
        // On attend que tous les processus fils aient terminés pour éviter les zombies
        for (int i = 0; i < num_nb_prem; i++)
        {
            wait(&etat);
        }
        exit(0);
    }
    else wait(&etat);  // instruction 46
}

int main()
{
    int grp=1;
    while(grp<=11)
    {
        explorer(grp+1,grp+10);
        grp=grp+10;
    }
    return 0;
}
