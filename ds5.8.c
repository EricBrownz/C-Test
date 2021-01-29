#include <stdio.h>
#include <stdlib.h>
#define MaxSize 10001

typedef int ElementType;
typedef int SetName;
typedef ElementType SetType[MaxSize];

void Initialize(SetType S, int n)
{
    for (int i = 1; i <= n; i++)
        S[i] = -1;
}

SetName Find(SetType S, ElementType X)
{
    if (S[X] < 0)
        return X;
    else
        return S[X] = Find(S, S[X]);
}

void Union(SetType S, SetName Root1, SetName Root2)
{
    if (S[Root2] < S[Root1])
        S[Root1] = Root2;
    else
    {
        if (S[Root1] == S[Root2])
            S[Root1]--;
        S[Root2] = Root1;
    }
}

void InputConnect(SetType S)
{
    ElementType u, v;
    SetName Root1, Root2;
    scanf("%d %d\n", &u, &v);
    Root1 = Find(S, u);
    Root2 = Find(S, v);
    if (Root2 != Root1)
        Union(S, Root1, Root2);
}

void CheckConnect(SetType S)
{
    ElementType u, v;
    SetName Root1, Root2;
    scanf("%d %d\n", &u, &v);
    Root1 = Find(S, u);
    Root2 = Find(S, v);
    if (Root2 == Root1)
        printf("yes\n");
    else
        printf("no\n");
}

void SumComponent(SetType S, int n)
{
    int i, cnt = 0;
    for (i = 1; i <= n; i++)
        if (S[i] < 0)
            cnt++;
    if (cnt == 1)
        printf("The network is connected.\n");
    else
        printf("There are %d components.\n", cnt);
}

int main()
{
    //initial aggregate
    SetType S;
    int n;
    char Ist; //instruction
    scanf("%d\n", &n);
    Initialize(S, n);

    do
    {
        scanf("%c", &Ist);
        switch (Ist)
        {
        case 'I':
            InputConnect(S); //Union(Find)
            break;
        case 'C':
            CheckConnect(S); //Find
            break;
        case 'S':
            SumComponent(S, n); //sum roots
            break;
        }
    } while (Ist != 'S');

    return 0;
}