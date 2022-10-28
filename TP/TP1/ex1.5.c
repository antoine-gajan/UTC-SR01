#include <stdio.h>
int main (){
    int a=-8 , b =3;
    int c= ++a&&-- b ? b --: a ++;
    printf ("a=%d b=%d c=%d\n",a, b, c);
}
