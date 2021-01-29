#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node
{
    ElementType Data;
    PtrToNode Next;
};
typedef PtrToNode List;

List Read();
void Print(List L);

List Merge(List L1, List L2);

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

List Read()
{
    int n;
    scanf("%d", &n);
    List L = (List)malloc(sizeof(PtrToNode));
    L->Next = NULL;
    if (n)
    {
        List r = L;
        for (int i = 0; i < n; i++)
        {
            List p = (List)malloc(sizeof(struct Node));
            scanf("%d", &(p->Data));
            r->Next = p;
            r = p;
        }
        r->Next = NULL;
    }
    return L;
}

void Print(List L)
{
    L = L->Next;
    if (L == NULL)
        printf("NULL\n");
    else
    {
        for (int i = 0;; i++)
        {
            if (i)
                printf(" ");
            printf("%d", L->Data);
            L = L->Next;
            if (L == NULL)
                break;
        }
        printf("\n");
    }
}

List Merge(List L1, List L2)
{
    PtrToNode L, t1, t2, Rear;
    t1 = L1->Next;
    t2 = L2->Next;
    L = (PtrToNode)malloc(sizeof(struct Node));
    Rear = L;
    while (t1 && t2)
    {
        if (t1->Data > t2->Data)
        {
            Rear->Next = t2;
            Rear = t2;
            t2 = t2->Next;
        }
        else
        {
            Rear->Next = t1;
            Rear = t1;
            t1 = t1->Next;
        }
    }
    if (t1)
        Rear->Next = t1;
    else
        Rear->Next = t2;//or Rear->Next = t1 ? t1 :t2;
    L1->Next = NULL;
    L2->Next = NULL;
    return L;
}