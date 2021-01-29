//simple
#include <stdio.h>

int main()
{
    int N, tmp;
    int a[51] = {0};
    scanf("%d", &N);
    while (N--)
    {
        scanf("%d", tmp);
        a[tmp]++;
    }
    for (int i = 0; i < 51; i++)
    {
        if (a[i])
            printf("%d:%d\n", i, a[i]);
    }
    return 0;
}