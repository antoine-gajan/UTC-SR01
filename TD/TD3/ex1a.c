#include <stdio.h>

int tab1[MAX]={6,4,5,10,8,...};
int tab2[MAX]={7,8,...};
int tab3[MAX];

for (int i = 0; i < MAX; i ++)
{
    tab3[i] = tab1[i] + tab2[(MAX-1)-i];
}
