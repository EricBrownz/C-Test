//linked list
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxN 1000

typedef int Vertex;

typedef struct Node *PtrToNode;
struct Node
{
    int Data;
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
} AdjList[MaxN];
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv, Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

void InsertEdge(Edge E, LGraph Graph)
{
    Graph->Ne++;
    PtrToAdjVNode NewNode;
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;
}

LGraph BuildGraph(int N, int *H)
{
    int Index, init;
    LGraph Graph;
    Edge E;
    Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Nv = N;
    Graph->Ne = 0;
    for (int i = 0; i < N; i++)
        Graph->G[i].FirstEdge = NULL;

    E = (PtrToENode)malloc(sizeof(struct ENode));
    for (int i = 0; i < N; i++)
    {
        Index = H[i] % N;
        init = Index;
        while (H[Index] != H[i])
            Index = (Index + 1) % N;
        while (H[init] != H[Index])
        {
            E->V1 = init;
            E->V2 = Index;
            InsertEdge(E, Graph);
            init = (init + 1) % N;
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

void AddQ(Queue Q, Vertex V)
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

Vertex DeleteQ(Queue Q)
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

bool TopSort(LGraph Graph, Vertex TopOrder[], int H[])
{ /* 对Graph进行拓扑排序,  TopOrder[]顺序存储排序后的顶点下标 */
    int Indegree[MaxN], cnt;
    Vertex V;
    PtrToAdjVNode W;
    Queue Q = CreateQueue(Graph->Nv);

    /* 初始化Indegree[] */
    for (V = 0; V < Graph->Nv; V++)
        Indegree[V] = 0;

    /* 遍历图，得到Indegree[] */
    for (V = 0; V < Graph->Nv; V++)
        for (W = Graph->G[V].FirstEdge; W; W = W->Next)
            Indegree[W->AdjV]++; /* 对有向边<V, W->AdjV>累计终点的入度 */

    /* 将所有入度为0的顶点入列 */
    for (V = 0; V < Graph->Nv; V++)
        if (Indegree[V] == 0)
            AddQ(Q, V);

    /* 下面进入拓扑排序 */
    cnt = 0;
    while (!IsEmpty(Q))
    {
        V = DeleteQ(Q);         /* 弹出一个入度为0的顶点 */
        TopOrder[cnt++] = H[V]; /* 将之存为结果序列的下一个元素 */
        /* 对V的每个邻接点W->AdjV */
        for (W = Graph->G[V].FirstEdge; W; W = W->Next)
            if (--Indegree[W->AdjV] == 0) /* 若删除V使得W->AdjV入度为0 */
                AddQ(Q, W->AdjV);         /* 则该顶点入列 */
    }                                     /* while结束*/

    if (cnt != Graph->Nv)
        return false; /* 说明图中有回路, 返回不成功标志 */
    else
        return true;
}

int main()
{
    int flag = 1;
    int N;
    int H[MaxN], TopOrder[MaxN];
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
        scanf("%d", H + i);

    LGraph G;
    G = BuildGraph(N, H);
    TopSort(G, TopOrder, H);

    for (int i = 0; i < N; i++)
        if (TopOrder[i]>0)
        {
            if (flag == 1)
            {
                printf("%d", TopOrder[i]);
                flag--;
            }
            else
                printf(" %d", TopOrder[i]);
        }

    return 0;
}