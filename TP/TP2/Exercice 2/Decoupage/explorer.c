#include "my_system.h"
#include "explorer.h"
#include "premier.h"

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
                    char chaine[150];
                    sprintf(chaine,"%d est un nombre premier. Le processus qui fait appel a system() est %d et son pere est %d",i,getpid(), getppid());
                    my_system(chaine);
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
