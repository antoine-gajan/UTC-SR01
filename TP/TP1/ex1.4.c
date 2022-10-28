#include <stdio.h>
int main (){
    int p [4]={1, -2 ,3 ,4};
    int * q=p;
    int d=* q&* q ++|* q ++;
    printf ("d=%d\n", d);
    printf ("q=%d \n" ,* q);
}
