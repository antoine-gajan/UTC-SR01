/* fop.c -- demo fopen fread ... */
#include <stdio.h>
#include <stdlib.h>
#define MAX_STRING_LENGTH 80

int main()
{ FILE *freop;
  int n;
  char buf;
 
  printf("des lignes dans stdout");
  freop = freopen("freop.log","w", stdout);
  printf("des lignes dans freop.log");
  fclose(freop);
}
