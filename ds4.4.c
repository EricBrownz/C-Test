#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct TreeNode *Tree;
struct TreeNode
{
    int value;
    Tree Left, Right;
    int flag; //flag==1表示访问过
};

Tree NewNode(int value)
{
    Tree T = (Tree)malloc(sizeof(struct TreeNode));
    T->value = value;
    T->Left = T->Right = NULL;
    T->flag = 0;
    return T;
}

Tree Insert(Tree T, int Value)
{
    if (!T)
        T = NewNode(Value);
    else
    {
        if (T->value > Value)
            T->Left = Insert(T->Left, Value);
        else
            T->Right = Insert(T->Right, Value);
    }
    return T;
}

Tree MakeTree(int N)
{
    Tree T;
    int i, Value;
    scanf("%d", &Value);
    T = NewNode(Value);
    for (i = 1; i < N; i++)
    {
        scanf("%d", &Value);
        T = Insert(T, Value);
    }
    return T;
}

int check(Tree T, int value)
{
    //如果查过当前结点
    if (T->flag)
    {
        if (value > T->value)
            return check(T->Right, value);
        else if (value < T->value)
            return check(T->Left, value);
        else
            return 0;
    }
    //如果没查过当前结点
    else
    {
        if (value == T->value)
        {
            T->flag = 1;
            return 1;
        }
        else
            return 0;
    }
}

int Judge(Tree T, int N)
{
    int i, Value, flag = 0; //flag==0表示目前还一致，1表示已经不一致 differ结构体的flag
    scanf("%d", &Value);
    if (Value != T->value)
        flag = 1;
    else
        T->flag = 1;
    for (i = 1; i < N; i++)
    {
        scanf("%d", &Value);
        if (!flag && !check(T, Value))
            flag = 1;
    }
    if (flag)
        return 0;
    else
        return 1;
}

void ResetT(Tree T)
{
    if (T->Left)
        ResetT(T->Left);
    if (T->Right)
        ResetT(T->Right);
    T->flag = 0;
}

void FreeTree(Tree T)
{
    if (T->Left)
        FreeTree(T->Left);
    if (T->Right)
        FreeTree(T->Right);
    free(T);
}

int main()
{
    Tree T;
    int N, L, i;

    scanf("%d", &N);
    while (N)
    {
        scanf("%d", &L);
        T = MakeTree(N);
        for (i = 0; i < L; i++)
        {
            if (Judge(T, N))
                printf("Yes\n");
            else
                printf("No\n");
            ResetT(T); //清除flag值
        }
        FreeTree(T); //输入下一轮要比较的序列的结点数
        scanf("%d", &N);
    }

    return 0;
}