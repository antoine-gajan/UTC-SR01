typedef struct complexe
{
    float x;
    float y;
} Complexe;

void Afficher(Complexe cmplx)
{
    if (cmplx.y < 0)
    {
        printf("%d - %di", cmplx.x, abs(cmplx.y));
    }
    else if (cmplx.y == 0)
    {
        printf("%d", cmplx.x);
    }
    else
    {
        printf("%d + %di", cmplx.x, cmplx.y);
    }
}
