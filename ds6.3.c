#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxVertexNum 1000 //? V<=10^3 for memset

typedef int Vertex;
typedef int ElementType;
int Visited[MaxVertexNum] = {0};

typedef struct Node *PtrToNode;
struct Node
{
    ElementType Data;
    PtrToNode Next;
};
typedef struct QNode *PtrToQueue;
struct QNode
{
    PtrToNode front, rear;
};
typedef PtrToQueue Queue;

typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1, V2;
};
typedef PtrToENode Edge;
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
    Vertex AdjV;
    PtrToAdjVNode Next;
};
typedef struct VNode
{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph CreateGraph(int VertexNum)
{
    Vertex V;
    LGraph Graph;

    Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for (V = 0; V < Graph->Nv; V++)
        Graph->G[V].FirstEdge = NULL;

    return Graph;
}

void InsertEdge(LGraph Graph, Edge E)
{
    PtrToAdjVNode NewNode;

    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;

    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}

LGraph BuildGraph()
{
    LGraph Graph;
    Edge E;
    Vertex V;
    int Nv, i;

    scanf("%d", &Nv);
    Graph = CreateGraph(Nv);
    scanf("%d", &Graph->Ne);
    if (Graph->Ne)
    {
        E = (PtrToENode)malloc(sizeof(struct ENode));
        for (i = 0; i < Graph->Ne; i++)
        {
            scanf("%d %d", &E->V1, &E->V2);
            E->V1--;
            E->V2--;
            InsertEdge(Graph, E);
        }
    }

    return Graph;
}

Queue CreateQueue()
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->front = Q->rear = NULL;
    return Q;
}

void Enqueue(Vertex V, Queue Q)
{
    PtrToNode N;
    N = (PtrToNode)malloc(sizeof(struct Node));
    N->Data = V;
    N->Next = NULL;
    if (Q->rear == NULL)
    {
        Q->front = N;
        Q->rear = N;
    }
    else
    {
        Q->rear->Next = N;
        Q->rear = N;
    }
}

int IsEmpty(Queue Q)
{
    return Q->front == NULL;
}

Vertex Dequeue(Queue Q)
{
    PtrToNode N;
    Vertex V;
    N = Q->front;
    if (Q->front == Q->rear)
        Q->front = Q->rear = NULL;
    else
        Q->front = Q->front->Next;
    V = N->Data;
    free(N);
    return V;
}

void SDS(LGraph Graph)
{
    int count;
    for (Vertex V = 0; V < Graph->Nv; V++)
    {
        memset(Visited, 0, sizeof(Visited));
        count = BFS(V, Graph);
        Output(count, V, Graph);
    }
}

void Output(int count, Vertex V, LGraph Graph)
{
    double rate;
    rate = (double)count / (double)Graph->Nv * 100;
    printf("%d: %.2f%%\n", ++V, rate);
}

int BFS(Vertex V, LGraph Graph)
{
    Queue Q = CreateQueue();
    Visited[V] = 1;
    Vertex count = 1, level = 0, last = V, tail;
    Enqueue(V, Q);
    while (!IsEmpty(Q))
    {
        V = Dequeue(Q);
        for (PtrToAdjVNode W = Graph->G[V].FirstEdge; W != NULL; W = W->Next)
            if (Visited[W->AdjV] == 0)
            {
                Visited[W->AdjV] = 1;
                Enqueue(W->AdjV, Q);
                count++;
                tail = W->AdjV;
            }
        if (V == last)
        {
            level++;
            last = tail;
        }
        if (level == 6)
            break;
    }
    return count;
}

int main()
{
    LGraph Graph = BuildGraph();
    SDS(Graph);

    return 0;
}