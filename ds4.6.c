#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MaxN 1000
int A[MaxN], T[MaxN];

int GetLeftLength(int n)
{
    //return n / 2 + 1;
    double h, x, L, t;
    h = (double)(int)(log((double)n + 1) / log(2.0));
    //h = floor( log((double)n+1) / log(2.0) );
    x = n - pow(2.0, h) + 1;
    t = pow(2.0, h - 1.0);
    x = x < t ? x : t;
    L = t - 1 + x;
    return (int)L;
}

void BuildAVLTree(int ALeft, int ARight, int TRoot)
{
    // initial 0,N-1,0
    int LeftRoot, RightRoot, L;
    int n = ARight - ALeft + 1; //数组中的总个数
    if (!n)                     //递归退出的条件
        return;
    L = GetLeftLength(n);    //计算出左子树总个数
    T[TRoot] = A[ALeft + L]; //将算得根结点放入根节点数组
    LeftRoot = 2 * TRoot + 1;
    RightRoot = LeftRoot + 1;
    BuildAVLTree(ALeft, ALeft + L - 1, LeftRoot);
    BuildAVLTree(ALeft + L + 1, ARight, RightRoot);
}

int compar(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int main()
{
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", A + i);
    qsort(A, N, sizeof(int), compar);
    BuildAVLTree(0, N - 1, 0);
    for (int i = 0; i < N; i++)
    {
        if (i != 0)
            printf(" ");
        printf("%d", T[i]);
    }
    return 0;
}