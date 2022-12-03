/* fop.c -- demo fopen fread ... */
#include <stdio.h>
#include <stdlib.h>
#define MAX_STRING_LENGTH 80

int main()
{ FILE *fopin, *fopout;
  int n;
  char buf;
  fopin = fopen("fop.in","r");
  if (fopin==NULL) {
    perror("fop erreur :");
    exit(0);
  }

  fopout = fopen("fop.out","w");


  while (!feof(fopin))
  {
 	n = fread(&buf,1,1,fopin);
	if (n == 1)
	{
		if (buf != '\n')
		{			
			n = fwrite(&buf, 1, 1, fopout); 
		}
		else
		{
			n = fwrite ("xxx\n",1,4,fopout);
		}
	}
  }
  fclose(fopin);
  fclose(fopout);
}
