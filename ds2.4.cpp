#include <stdlib.h>
#include <cstdio>
const int maxsize = 1001;
struct SNode
{
    int *data;
    int top;
    int MaxSize;
};

typedef struct SNode *Stack;

Stack CreateStack(int MaxSize)
{
    Stack s = (Stack)malloc(sizeof(struct SNode));
    s->data = (int *)malloc(MaxSize * sizeof(int));
    s->top = -1;
    s->MaxSize = MaxSize;
    return s;
}

bool isFull(Stack s)
{
    return (s->top == s->MaxSize - 1);
}
bool isEmpty(Stack s)
{
    return (s->top == -1);
}

bool push(Stack s, int x)
{
    if (isFull(s))
    {
        return false;
    }
    else
    {
        s->data[++(s->top)] = x;
        return true;
    }
}

int pop(Stack s)
{
    return s->data[(s->top)--];
}

int main()
{
    int m, n, k, a[maxsize];
    scanf("%d %d %d", &m, &n, &k);

    while (k--)
    {
        Stack s1 = CreateStack(m);
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &a[i]);
        }
        int j = 0, flag;
        for (int i = 1; i <= n; i++)
        {
            flag = push(s1, i);
            if (!flag)
                break;
            while (!isEmpty(s1) && a[j] == s1->data[s1->top])
            {
                j++;
                pop(s1);
            }
        }
        if (flag == false)
        {
            printf("NO\n");
        }
        else if (isEmpty(s1))
        {
            printf("YES\n");
        }
        else
            printf("NO\n");
    }
}