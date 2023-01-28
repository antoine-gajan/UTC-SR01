#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
    int stat;
    pid_t pid2, pid3, pid4, pid5, pid6, pid7, pid8, pid9, pid10, pid11, pid12, pid13, pid14, pid15, pid16;
    pid2 = fork();
    if (pid2 == 0)
    {

        // C'est le processus 2
        printf("\nMon pid est %d, le pid de mon pere est %d\n", getpid(), getppid());
        fflush(stdout);
        pid6 = fork();
        if (pid6 == 0)
        {
            // C'est le processus 6
            printf("\nMon pid est %d, le pid de mon pere est %d\n", getpid(), getppid());
            fflush(stdout);
            pid12 = fork();
            if (pid12 == 0)
            {
                // C'est le processus 12
                printf("\nMon pid est %d, le pid de mon pere est %d\n", getpid(), getppid());
                fflush(stdout);
                pid16 = fork();
                if (pid16 == 0)
                {
                    // C'est le processus 16
                    printf("\nMon pid est %d, le pid de mon pere est %d\n", getpid(), getppid());
                    fflush(stdout);
                    exit(0);
                }
                else
                {
                    waitpid(pid16, &stat, 0);
                }
                exit(0);
            }
            else
            {
                pid13 = fork();
                if (pid13 == 0)
                {
                    // C'est le processus 13
                    printf("\nMon pid est %d, le pid de mon pere est %d\n", getpid(), getppid());
                    fflush(stdout);
                    exit(0);
                }
                else
                {
                    waitpid(pid13, &stat, 0);
                }
                waitpid(pid12, &stat, 0);
            }
            exit(0);
        }
        else
        {
            pid7 = fork();
            if (pid7 == 0)
            {
                // C'est le processus 7
                printf("\nMon pid est %d, le pid de mon pere est %d\n", getpid(), getppid());
                fflush(stdout);
                pid14 = fork();
                if (pid14 == 0)
                {
                    // C'est le processus 14
                    printf("\nMon pid est %d, le pid de mon pere est %d\n", getpid(), getppid());
                    fflush(stdout);
                    exit(0);
                }
                else
                {
                    waitpid(pid14, &stat, 0);
                }
                exit(0);
            }
            else
            {
                pid8 = fork();
                if (pid8 == 0)
                {
                    // C'est le processus 8
                    printf("\nMon pid est %d, le pid de mon pere est %d\n", getpid(), getppid());
                    fflush(stdout);
                    exit(0);
                }
                else
                {
                    waitpid(pid8, &stat, 0);
                }
                waitpid(pid7, &stat, 0);
            }
            waitpid(pid6, &stat, 0);
        }
        exit(0);
    }
    else
    {
        pid3 = fork();
        if (pid3 == 0)
        {
            // C'est le processus 3
            printf("\nMon pid est %d, le pid de mon pere est %d\n", getpid(), getppid());
            fflush(stdout);
            pid9 = fork();
            if (pid9 == 0)
            {
                // C'est le processus 9
                printf("\nMon pid est %d, le pid de mon pere est %d\n", getpid(), getppid());
                fflush(stdout);
                pid15 = fork();
                if (pid15 == 0)
                {
                    // C'est le processus 15
                    printf("\nMon pid est %d, le pid de mon pere est %d\n", getpid(), getppid());
                    fflush(stdout);
                    exit(0);
                }
                else
                {
                    waitpid(pid15, &stat, 0);
                }
                exit(0);
            }
            else
            {
                pid10 = fork();
                if (pid10 == 0)
                {
                    // C'est le processus 10
                    printf("\nMon pid est %d, le pid de mon pere est %d\n", getpid(), getppid());
                    fflush(stdout);
                    exit(0);
                }
                else
                {
                    waitpid(pid10, &stat, 0);
                }
                waitpid(pid9, &stat, 0);
            }
            exit(0);
        }
        else
        {
            pid4 = fork();
            if (pid4 == 0)
            {
                // C'est le processus 4
                printf("\nMon pid est %d, le pid de mon pere est %d\n", getpid(), getppid());
                fflush(stdout);
                pid11 = fork();
                if (pid11 == 0)
                {
                    // C'est le processus 11
                    printf("\nMon pid est %d, le pid de mon pere est %d\n", getpid(), getppid());
                    fflush(stdout);
                    exit(0);
                }
                else
                {
                    waitpid(pid11, &stat, 0);
                }
                exit(0);
            }
            else
            {
                pid5 = fork();
                if (pid5 == 0)
                {
                    // C'est le processus 5
                    printf("\nMon pid est %d, le pid de mon pere est %d\n", getpid(), getppid());
                    fflush(stdout);
                    exit(0);
                }
                else
                {
                    waitpid(pid5, &stat, 0);
                }
                // Attente que les processus fils se terminent
                waitpid(pid2, &stat, 0);
                waitpid(pid3, &stat, 0);
                waitpid(pid4, &stat, 0);
            }
        }
    }
    return 0;
}
