//dual linked list
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct Node *PtrToNode;
struct Node
{
    PtrToNode Front;
    ElemType Data;
    PtrToNode Next;
};
typedef struct _dulist
{
    PtrToNode front;
    PtrToNode rear;
} * DuList;

void AddList(DuList L, ElemType x)
{
    PtrToNode N;
    N = (PtrToNode)malloc(sizeof(struct Node));
    N->Data = x;
    N->Next = NULL;
    if (L->rear == NULL)
    {
        N->Front = NULL;
        L->front = N;
        L->rear = N;
    }
    else
    {
        L->rear->Next = N;
        N->Front = L->rear;
        L->rear = N;
    }
}

DuList BuildList()
{
    ElemType tmp;
    DuList L;
    L = (DuList)malloc(sizeof(struct _dulist));
    L->front = L->rear = NULL;
    do
    {
        scanf("%d", &tmp);
        if (tmp != -1)
            AddList(L, tmp);
    } while (tmp != -1);

    return L;
}

void Output(DuList L)
{
    PtrToNode p;
    for (p = L->rear; p; p = p->Front)
        printf("%d ", p->Data);
}

int main(int argc, char *argv[])
{
    DuList L;
    L = BuildList();
    Output(L);
    return 0;
}