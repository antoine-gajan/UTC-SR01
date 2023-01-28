#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include <fcntl.h>


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

void my_system(char *chaine)
{
    pid_t pid;
    int stat;
    // Création d'un processus fils en concurrence
    pid = fork();
    if (pid == 0)
    {
        // Code à exécuter par le fils
        // Arguments pour l'écriture
        char *arguments[] = {"/bin/echo", chaine, NULL};
        // Copie de la sortie standard pour la sauvegarder (utilise emplacement 3)
        int new_stdout = dup(1);
        if (new_stdout == -1)
        {
            perror("dup");
            return;
        }
        // Création d'un descripteur de fichier à l'emplacement 4
        int fd = open("nbr_premiers.txt", O_RDWR | O_APPEND | O_CREAT, 0666);
        // Si on n'a pas réussi à ouvrir le fichier, on renvoie une erreur
        if (fd == -1)
        {
            perror("open");
            return;
        }
        // Fermeture de la sortie standard stdout
        if (close(1) == -1)
        {
            perror("close");
            return;
        }
        // On copie le descripteur vers 1 (sortie standard)
        int new_file_txt = dup(fd);
        if (new_stdout == -1)
        {
            perror("dup");
            return;
        }
        // On ferme le descripteur qui est devenu inutile
        if (close(fd) == -1)
        {
            perror("close");
            return;
        }
        // Ecriture dans la sortie standard (fichier nbr_premiers.txt)
        execv("/bin/echo", arguments);
        // On remet stdout comme sortie standard
        if (close(new_file_txt) == -1)
        {
            perror("close");
            return;
        }
        if (dup(new_stdout) == -1)
        {
            perror("dup");
            return;
        }
        if (close(new_stdout) == -1)
        {
            perror("close");
            return;
        }
        exit(0);
    }
    else
    {
        // Attente que le processus fils termine
        wait(&stat);
    }
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
