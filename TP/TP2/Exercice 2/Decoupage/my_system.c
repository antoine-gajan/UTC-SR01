#include "my_system.h"

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
