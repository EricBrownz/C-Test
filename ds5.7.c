#include <stdio.h>

#define MAXN 1001
#define MINH -10001

int H[MAXN], size;

void Create()
{
    size = 0;
    H[0] = MINH; //设置岗哨
}

void Insert(int X)
{
    //不需要判断是否满了
    int i;
    for (i = ++size; X < H[i / 2]; i /= 2)
        H[i] = H[i / 2];
    H[i] = X;
}

int main()
{
    int m, n, i, j, x;
    scanf("%d %d", &n, &m);
    Create();
    for (i = 0; i < n; i++)
    {
        scanf("%d", &x);
        Insert(x);
    }
    for (i = 0; i < m; i++)
    {
        scanf("%d", &j);
        printf("%d", H[j]);
        while (j > 1)
        {
            j /= 2;
            printf(" %d", H[j]);
        }
        printf("\n");
    }
    return 0;
}