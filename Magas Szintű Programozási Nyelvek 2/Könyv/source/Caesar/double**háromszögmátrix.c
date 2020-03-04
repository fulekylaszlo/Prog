#include <stdio.h>
#include <stdlib.h>

int
main ()
{
    int rs = 5;
    double **tb;
    
    printf("%p\n", &tb);
    
    if ((tb = (double **) malloc (rs * sizeof (double *))) == NULL)
    {
        return -1;
    }

    printf("%p\n", tb);
    
    for (int i = 0; i < rs; ++i)
    {
        if ((tb[i] = (double *) malloc ((i + 1) * sizeof (double))) == NULL)
        {
            return -1;
        }

    }

    printf("%p\n", tb[0]);    
    
    for (int i = 0; i < rs; ++i)
        for (int j = 0; j < i + 1; ++j)
            tb[i][j] = i * (i + 1) / 2 + j;

    for (int i = 0; i < rs; ++i)
    {
        for (int j = 0; j < i + 1; ++j)
            printf ("%f, ", tb[i][j]);
        printf ("\n");
    }

    tb[3][0] = 42.0;
    (*(tb + 3))[1] = 43.0;
    *(tb[3] + 2) = 44.0;
    *(*(tb + 3) + 3) = 45.0;

    for (int i = 0; i < rs; ++i)
    {
        for (int j = 0; j < i + 1; ++j)
            printf ("%f, ", tb[i][j]);
        printf ("\n");
    }

    for (int i = 0; i < rs; ++i)
        free (tb[i]);

    free (tb);

    return 0;
}
