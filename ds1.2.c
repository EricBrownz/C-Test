//Maximum Subsequence Sum
#include <stdio.h>
#define MAXN 100000

int main()
{
    int i, N;
    int a[MAXN] = {0};
    scanf("%d", &N);
    for (i = 0; i < N; i++)
        scanf("%d", &a[i]);
    MaxSubseqSum4(a, N);
    return 0;
}

int MaxSubseqSum4(int a[], int N)
{
    int i, tmp = 0;
    int first = 0, last = N - 1;
    int MaxSum, TempSum;
    TempSum = 0, MaxSum = a[0]; //for subsequence with negative and 0
    for (i = 0; i < N; i++)
    {
        TempSum += a[i];
        if (TempSum > MaxSum)
        {
            MaxSum = TempSum;
            first = tmp;
            last = i;
        }
        if (TempSum < 0)
        {
            TempSum = 0;
            tmp = i + 1;
        }
    }
    if (MaxSum > 0)
        printf("%d %d %d\n", MaxSum, a[first], a[last]);
    else if (MaxSum == 0)
        printf("0 0 0\n");
    else
        printf("%d %d %d\n", 0, a[first], a[last]);
}

int MaxSubseqSum2(int a[], int N)
{
    int i, j, start = a[0], stop = a[N - 1];
    int MaxSum = a[0], TempSum;
    for (i = 0; i < N; i++)
    {
        TempSum = 0;
        for (j = i; j < N; j++)
        {
            TempSum += a[j];
            if (TempSum > MaxSum)
            {
                MaxSum = TempSum;
                start = a[i];
                stop = a[j];
            }
        }
    }
    if (MaxSum > 0)
        printf("%d %d %d\n", MaxSum, start, stop);
    else if (MaxSum == 0)
        printf("0 0 0\n");
    else
        printf("%d %d %d\n", 0, start, stop);
}