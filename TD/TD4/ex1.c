#include <stdio.h>


void afficheInfos()
{
	char ch[100];
	fgets(ch, 100, stdin);
	int taille = 0;
	int car_maj = 0;
	int car_min = 0;
	int blancs = 0;
	int autres = 0;
	int i = 0;

	while(i < 100 && ch[i] != '\0')
	{
		taille ++;
		if (ch[i] >= 'A' && ch[i] <= 'Z')
		{
			car_maj ++;
		}
		else if (ch[i] >= 'a' && ch[i] <= 'z')
		{
			car_min ++;
		}
		else if (ch[i] == ' ')
		{
			blancs ++;
		}
		else
		{
			autres ++;
		}
		i++;
	}
	printf("Taille : %d \nMajuscules : %d \nMinuscules : %d\n Blancs : %d\nAutres : %d\n", taille, car_maj, car_min, blancs, autres);
}


int main()
{
	afficheInfos();
}
