/*邻接矩阵实现*/
#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 10
#define MaxSize 10

typedef int WeightType;
typedef int Vertex;
typedef int ElementType;
int Visited_DFS[MaxVertexNum]; /* 顶点的访问标记 */
int Visited_BFS[MaxVertexNum];

struct GNode
{
    int Nv;
    int Ne;
    WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef struct GNode *PtrToGNode;
typedef PtrToGNode MGraph;

struct ENode
{
    Vertex V1, V2;
    WeightType Weight;
};
typedef struct ENode *PtrToENode;
typedef PtrToENode Edge;

struct Node
{
    ElementType Data;
    struct Node *Next;
};

struct QNode
{
    struct Node *front;
    struct Node *rear;
};
typedef struct QNode *Queue;

MGraph CreateGraph(int VertexNum);
void InsertEdge(MGraph, Edge E);
MGraph BuildGraph();
void Visit(Vertex V);
void DFS(MGraph Graph, Vertex V, void (*Visit)(Vertex));
void BFS(MGraph Graph, Vertex S, void (*Visit)(Vertex));
void ListComponents_DFS(MGraph Graph);
void ListComponents_BFS(MGraph Graph);
Queue CreateQueue();
void AddQ(Queue Q, Vertex S);
ElementType DeleteQ(Queue Q);

int main(void)
{
    MGraph Graph;
    Vertex V;
    Graph = BuildGraph();
    // DFS(Graph,V,Visit);
    ListComponents_DFS(Graph);
    // BFS(Graph,V,Visit);
    ListComponents_BFS(Graph);
    return 0;
}
/*MGraph初始化*/
MGraph CreateGraph(int VertexNum)
{
    Vertex V, W;
    MGraph Graph;
    //需加（MGraph）
    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;

    for (V = 0; V < Graph->Nv; V++)
        for (W = 0; W < Graph->Nv; W++)
            Graph->G[V][W] = 0;

    return Graph;
}
/*MGraph插入边*/
void InsertEdge(MGraph Graph, Edge E)
{
    Graph->G[E->V1][E->V2] = E->Weight;
    Graph->G[E->V2][E->V1] = E->Weight;
}
/*完整建立MGraph*/
MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    Vertex V;
    int Nv, i;
    scanf("%d", &Nv);
    Graph = CreateGraph(Nv);
    scanf("%d", &(Graph->Ne));
    if (Graph->Ne != 0)
    {
        //需加(Edge)
        E = (Edge)malloc(sizeof(struct ENode));
        for (i = 0; i < Graph->Ne; i++)
        {
            scanf("%d %d", &E->V1, &E->V2);
            E->Weight = 1;
            InsertEdge(Graph, E);
        }
    }
    for (V = 0; V < Graph->Nv; V++)
    {
        Visited_BFS[V] = 0;
        Visited_DFS[V] = 0;
    }
    return Graph;
}
/*访问节点*/
void Visit(Vertex V)
{
    printf(" %d", V);
}
/*DFS连通*/
void ListComponents_DFS(MGraph Graph)
{
    Vertex i;
    for (i = 0; i < Graph->Nv; i++)
    {
        if (!Visited_DFS[i])
        { //节点i未被访问过
            printf("{");
            DFS(Graph, i, Visit);
            printf(" }");
            printf("\n");
        }
    }
}
/*BFS连通*/
void ListComponents_BFS(MGraph Graph)
{
    Vertex i;
    for (i = 0; i < Graph->Nv; i++)
    {
        if (!Visited_BFS[i])
        {
            printf("{");
            BFS(Graph, i, Visit);
            printf(" }");
            printf("\n");
        }
    }
    //    printf("\n");
}
/*
进行搜索时，假设我们总是从编号最小的顶点出发，按编号递增的顺序访问邻接点。How??
按照"{v1v2...vk}"的格式，每行输出一个连通集。
*/
/*DFS*/
void DFS(MGraph Graph, Vertex V, void (*Visit)(Vertex V))
{
    Vertex W;
    Visited_DFS[V] = 1;
    // printf("{");
    Visit(V);
    for (W = 0; W < Graph->Nv; W++)
    {
        if (Graph->G[V][W] == 1 && !Visited_DFS[W])
        {
            DFS(Graph, W, Visit);
        }
    }
    // printf("}");
    return;
}
/*BFS*/
void BFS(MGraph Graph, Vertex S, void (*Visit)(Vertex))
{
    Queue Q;
    Vertex V, W;
    Q = CreateQueue(); //MaxSize
    Visit(S);
    Visited_BFS[S] = 1;
    AddQ(Q, S);

    while (Q->front != NULL)
    {
        V = DeleteQ(Q);
        for (W = 0; W < Graph->Nv; W++)
        {
            if (Graph->G[V][W] == 1 && !Visited_BFS[W])
            {
                Visit(W);
                Visited_BFS[W] = 1;
                AddQ(Q, W);
            }
        }
    }
}
/*建队列，假定为空*/
Queue CreateQueue()
{
    Queue Q;
    Q = (Queue)malloc(sizeof(struct QNode));
    Q->front = Q->rear = NULL;
    return Q;
}
/*进队列*/
void AddQ(Queue Q, Vertex S)
{
    struct Node *temp;
    temp = (struct Node *)malloc(sizeof(struct Node));
    temp->Data = S;
    temp->Next = NULL;
    if (Q->front == NULL)
    {
        Q->front = temp;
        Q->rear = temp;
    }
    else
    {
        Q->rear->Next = temp;
        Q->rear = temp;
    }
    // return Q;
}
/*出队列*/
ElementType DeleteQ(Queue Q)
{
    struct Node *FrontCell;
    ElementType FrontElem;
    if (Q->front == NULL)
    {
        return -1;
    }
    FrontCell = Q->front;
    if (Q->front == Q->rear)
        Q->front = Q->rear = NULL;
    else
        Q->front = Q->front->Next;
    FrontElem = FrontCell->Data;
    free(FrontCell);
    return FrontElem;
}