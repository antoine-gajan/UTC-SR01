#include <stdio.h>
#include "ex2.h"

int main()
{
    int tab[MAX];
    for (int i = 0; i < MAX; i++)
    {
        tab[i] = i + VAL;
    }
    for (int i = 0; i < MAX; i++)
    {
        printf("%d \n", tab[i]);
    }
}
