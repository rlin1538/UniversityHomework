#include <stdio.h>

int main()
{
    int *a;
    int *b, i = 0;
    a = (int *)malloc(sizeof(int));
    for (i = 1;; i++)
    {
        if (getchar() != '\n')
        {
            scanf("%d", a);
            a = (int *)malloc(sizeof(int));
        }
        else
            break;
    }

    printf("%d", i);

    return 0;
}