#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include "ApplicationManager.h"
#define NB_MAX_APP 10

// Variables globales
Application tab_app[NB_MAX_APP];
pid_t pid_power_manager;
int nb_app;

int lecture_fichier(FILE *fichier, Application *tab_app)
{
    /// Fonction pour lire un fichier
    // Variables utiles
	int nb_app, i = 0, j = 0, k, nb_arguments;
	unsigned char buffer[TAILLE_MAX_STRING], nom[TAILLE_MAX_STRING], valeur[TAILLE_MAX_STRING], c;

	// Lecture et vérification de la première ligne (nombre d'applis)
	c = fgetc(fichier);
	while (c != '\n' && c != EOF)
	{
		buffer[i] = c;
		c = fgetc(fichier);
		i++;
	}
	buffer[i] = '\0';

	// SI buffer vide, erreur
	if (buffer[0] == '\0')
    {
        return -1;
    }

	// Conversion du buffer en chaine1=chaine2
	if(convertir(buffer, nom, valeur) < 0)
    {
        return -1;
    }
	// Gestion d'erreur
	if(strcmp("nombre_applications", nom) != 0)
		{
			printf("Ce n'est pas le bon argument.\n");
			return -1;
		}

	// Convertir chaine en nombre
	nb_app = atoi(valeur);
	// Si trop d'applications, erreur
	if (nb_app > NB_MAX_APP)
		return -2;

	for (i = 0; i < nb_app; i++)
	{
		// Lecture du nom
		j = 0;
		c = fgetc(fichier);
		while (c != '\n' && c != EOF)
		{
			buffer[j] = c;
			c = fgetc(fichier);
			j++;
		}
		buffer[j] = '\0';
		// Si pas de chaine de caractères, erreur
		if (buffer[0] == '\0')
			return -1;
		// Conversion de la chaine
		if (convertir(buffer, nom, valeur) < 0)
        {
            return -1;
        }
		// Gestion d'erreur
		if(strcmp("name", nom) != 0)
		{
			printf("Ce n'est pas le bon argument.\n");
			return -1;
		}
		// Copie de la valeur dans la structure
		strcpy(tab_app[i].name, valeur);

		// Lecture du path
		j = 0;
		c = fgetc(fichier);
		while (c != '\n' && c != EOF)
		{
			buffer[j] = c;
			c = fgetc(fichier);
			j++;
		}
		buffer[j] = '\0';
		// Gestion d'erreur
		if (buffer[0] == '\0')
			return -1;
        // Conversion de la chaine
		if (convertir(buffer, nom, valeur) < 0)
        {
            return -1;
        }
		// Gestion d'erreur
		if(strcmp("path", nom) != 0)
		{
			printf("Ce n'est pas le bon argument.\n");
			return -1;
		}
		// Copie de la valeur dans la structure
		strcpy(tab_app[i].path, valeur);

		// Lecture du nombre d'arguments
		j = 0;
		c = fgetc(fichier);
		while (c != '\n' && c != EOF)
		{
			buffer[j] = c;
			c = fgetc(fichier);
			j++;
		}
		buffer[j] = '\0';
        // Gestion d'erreurs
		if (buffer[0] == '\0')
        {
            return -1;
        }
		if (convertir(buffer, nom, valeur) < 0)
        {
            return -1;
        }
		if(strcmp("nombre_arguments", nom) != 0)
		{
			printf("Ce n'est pas l'argument attendu.\n");
			return -1;
		}
        // Conversion de chaine en nombre
		nb_arguments = atoi(valeur);
        // Copie de l'argument dans la structure
		tab_app[i].nb_arguments = nb_arguments;
        // Gestion d'erreur
		if (nb_arguments > NB_MAX_ARG)
        {
            return -1;
        }
		// Saut de la ligne arguments=
		j = 0;
		c = fgetc(fichier);
		while (c != '\n' && c != EOF)
		{
			buffer[j] = c;
			c = fgetc(fichier);
			j++;
		}
		buffer[j] = '\0';

		// Pour chaque argument
		for (k = 0; k < nb_arguments; k++)
		{
			j = 0;
			c = fgetc(fichier);
			while(c != '\n' && c != EOF)
			{
				buffer[j] = c;
				c = fgetc(fichier);
				j++;
			}
			buffer[j] = '\0';
			// Copie de l'argument dans la structure
			strcpy(tab_app[i].arguments[k], buffer);
		}
		// Saut de la ligne entre 2 applications
		c = fgetc(fichier);
	}
	// Retourne le nombre d'applications
	return nb_app;
}


int convertir(unsigned char *buffer, unsigned char *chaine1, unsigned char *chaine2)
{
    /// Fonction pour convertir buffer en chaine1=chaine2
	int i = 0, j = 0;
	// Partie avant le =
	while(buffer[i] != '=' && buffer[i] != '\0' && i <= TAILLE_MAX_STRING)
	{
		chaine1[i] = buffer[i];
		i++;
	}
	// Fin de chaine
	chaine1[i] = '\0';
	// Gestion d'erreur
	if (i > TAILLE_MAX_STRING || buffer[i] != '=')
    {
        return -1;
    }
	i++;
	// Partie après le =
	while(buffer[i] != '\0')
	{
		chaine2[j] = buffer[i];
		j++;
		i++;
	}
	// Fin ce chaine de caracteres
	chaine2[j] = '\0';
	return 0;
}

void arret(int sig, siginfo_t *info, void *context)
{
	int i;
    // On vérifie que c'est le bon signal envoyé par le bon emetteur
	if (sig == SIGUSR1 && info->si_pid == pid_power_manager)
    {
        printf("Fermeture de toutes les applications\n");
        // Pour chaque application
        for (i = 0; i < nb_app; i++)
            // Si elle est en état de marche
            if (tab_app[i].en_marche == 1)
            {
                // On met fin à son fonctionnement
                if (kill(tab_app[i].pid, SIGUSR1) != 0)
                {
                    perror("kill");
                    exit(EXIT_FAILURE);
                }
                // MAJ attributs
                printf("L'application %s, executee par le processus %d va s'arreter\n", tab_app[i].name, tab_app[i].pid);
                tab_app[i].en_marche = 0;
                tab_app[i].pid = -1;
            }
        exit(EXIT_SUCCESS);
    }
}

// Fonction d'affichage d'une application
void afficher(Application *app)
{
	int i;
	printf("Nom : %s\n", app->name);
	printf("Path : %s\n", app->path);
	printf("Nombre d'arguments : %d\n", app->nb_arguments);
	for (i = 0; i < app->nb_arguments; i++)
		printf("\t %d) %s\n", i, app->arguments[i]);
	printf("Pid : %d\n", app->pid);
	printf(app->en_marche == 1 ? "Fonctionnement : ok\n\n" : "\tFonctionnement : arret\n\n");
}

int main(void)
{
    // Variables utiles
	FILE *liste_app = fopen("list_appli.txt", "r");
	struct sigaction handler_app_manager;
	int i, statut, continuer = 1;
	pid_t pid;

	// Si echec dans l'ouverture
	if (liste_app == NULL)
	{
		printf("Probleme pour ouvrir list_appli.txt\n");
		exit(EXIT_FAILURE);
	}

	// Lecture du fichier
	nb_app = lecture_fichier(liste_app, tab_app);
	fclose(liste_app);

	// Si erreur dans la lecteur
	if (nb_app < 0)
	{
		printf("Echec lors de la lecture de list_appli.txt\n");
		exit(EXIT_FAILURE);
	}

	// Masquage de tous les signaux
	if (sigfillset(&handler_app_manager.sa_mask) != 0)
	{
		perror("main/sigfillset");
		exit(EXIT_FAILURE);
	}

	// Sauf SIGQUIT (controle c)
	if (sigdelset(&handler_app_manager.sa_mask, SIGQUIT) != 0)
	{
		perror("sigdelset");
		exit(EXIT_FAILURE);
	}

	// Siginfo pour connaître le nom du processus emetteur d'un signal
	handler_app_manager.sa_flags = SA_SIGINFO;

	// Redéfinition de la fonction à appliquer en cas de signal
	handler_app_manager.sa_sigaction = arret;

	// Redéfinition du comportement de SIGUSR1
	if (sigaction(SIGUSR1, &handler_app_manager, NULL) != 0)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

	// Lancement des applications
	for (i = 0; i < nb_app; i++)
	{
        // Création d'un processus
		pid = fork();
        // Erreur
		if (pid < 0)
		{
			printf("Failed to fork !\n");
			exit(EXIT_FAILURE);
		}
        // C'est le processus fils
		if (pid == 0)
		{
            printf("Je suis le processus %d et j'execute %s\n", getpid(), tab_app[i].name);
			char *arguments[NB_MAX_ARG];
			int num_argument = 1;

			arguments[0] = tab_app[i].path;

			// Initilalisation du tableau d'arguments
			while (tab_app[i].arguments[num_argument-1][0] != '\0')
			{
				arguments[num_argument] = tab_app[i].arguments[num_argument-1];
				num_argument++;
			}
			// Mise à NULL du dernier argument de execv
			arguments[num_argument] = NULL;
			// Execution de l'application
			execv(tab_app[i].path, arguments);
		}
        // Si c'est l'application Power Manager
		if (strcmp("Power Manager", tab_app[i].name) == 0)
        {
            pid_power_manager = pid;
        }
		// MAJ des attributs
		tab_app[i].pid = pid;
		tab_app[i].en_marche = 1;
	}

	// Tant qu'il reste des applications en état de marche
	while (continuer == 1)
	{
        // On suppose qu'on arrête
		continuer = 0;
        // Pour chaque application
		for (i = 0; i < nb_app; i++)
			// Si elle est en fonctionnement
			if (tab_app[i].en_marche == 1)
			{
				// On attend de manière non bloquante
				pid = waitpid(tab_app[i].pid, &statut, WNOHANG);
                // Si l'attente a échoué
				if (pid == -1)
                {
                    printf("Erreur pendant l'attente\n");
                }
                // Si l'état de l'application a changé
				else if (pid > 0)
				{
                    // Sortie normale avec une valeur de retour
					if(WIFEXITED(statut))
						printf("L'application %s s'est terminee avec le code %d\n", tab_app[i].name, WEXITSTATUS(statut));
                    // Sortie avec signal
					else if (WIFSIGNALED(statut))
						printf("L'application %s s'est terminee avec le signal %d\n", tab_app[i].name, WTERMSIG(statut));

					// Modification des attributs
					tab_app[i].en_marche = 0;
					tab_app[i].pid = -1;
				}
				// L'application continue de tourner
				else
					continuer = 1;
			}
	}
	return 0;
}



