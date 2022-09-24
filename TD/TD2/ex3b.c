#include <stdio.h>

typedef struct complexe
{
    float x;
    float y;
}Complexe;

Complexe Somme(Complexe c1, Complexe c2)
{
    Complexe sum;
    sum.x = c1.x + c2.x;
    sum.y = c1.y + c2.y;
    return sum;
}

Complexe Produit(Complexe c1, Complexe c2)
{
    Complexe prod;
    prod.x = c1.x * c2.x - c1.y * c2.y;
    prod.y = c1.y * c2.x + c1.x * c2.y;
    return prod;
}

void Afficher(Complexe cmplx)
{
    if (cmplx.y < 0)
    {
        printf("%f - %fi\n", cmplx.x, -(cmplx.y));
    }
    else if (cmplx.y == 0)
    {
        printf("%f\n", cmplx.x);
    }
    else
    {
        printf("%f + %fi\n", cmplx.x, cmplx.y);
    }
}

int main()
{
    Complexe c1, c2;
    printf("C1 : x et y ? ");
    scanf("%f %f", &(c1.x), &(c1.y));
    printf("C2 : x et y ? ");
    scanf("%f %f", &(c2.x), &(c2.y));
    Afficher(Somme(c1, c2));
    Afficher(Produit(c1, c2));
    return 0;
}
