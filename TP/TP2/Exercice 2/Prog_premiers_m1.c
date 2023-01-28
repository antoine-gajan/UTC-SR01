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
    int etat,pid,pid2;
    pid=fork();
    if(pid==0)
    {
        for (int i=debut; i<=fin; i++)
        {
            if (premier(i)==1)
            {
                pid2=fork();
                if (pid2==0)
                {
                    char chaine[250];
                    sprintf(chaine,"echo '%d est un nombre premier dont le processus qui fait appel a la fonction system est %d, dont le pere qui execute la boucle for est %d et est ecrit par le processus $$' >> nbr_premiers.txt",i,getpid(), getppid());
                    system(chaine);
                    sleep(2);
                    exit(0);
                }
                else wait(&etat);// instruction 41
            }
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
