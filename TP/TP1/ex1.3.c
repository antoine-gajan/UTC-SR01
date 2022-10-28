# include <stdio.h>
int main (){
    int p [4]={1 , -2 ,3 ,4};
    int * q=p;
    printf ("c=%d\n", *++ q** q ++) ;
    printf ("c=%d \n" ,* q);
}
