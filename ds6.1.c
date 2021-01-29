#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 10

typedef int WeightType;
typedef int Vertex;
typedef int ElementType;
int DFSVisited[MaxVertexNum];
int BFSVisited[MaxVertexNum];

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
    Vertex AdjV; //adjnode subscript
    WeightType Weight;
    PtrToAdjVNode Next;
};

typedef struct VNode
{
    PtrToAdjVNode FirstEdge;
    //DataType Data;
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;    //vertex num
    int Ne;    //edge num
    AdjList G; //adjacency list
};
typedef PtrToGNode LGraph;

typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1, V2;
    WeightType Weight;
};
typedef PtrToENode Edge;

LGraph CreateGraph(int VertexNum);
void InsertEdge(LGraph Graph, Edge E);
LGraph BuildGraph();
void Visit(Vertex V);
void DFS(LGraph Graph, Vertex V, void (*Visit)(Vertex));
void BFS(LGraph Graph, Vertex S, void (*Visit)(Vertex));

int main()
{
    LGraph Graph;
    Graph = BuildGraph();
    DFS(Graph, Graph->Nv, Visit);
    //ListComponents_DFS(Graph);
    BFS(Graph, Graph->Nv, Visit);
    //ListComponents_BFS(Graph);
    return 0;
}

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
    //undirected graph
    PtrToAdjVNode NewNode;
    //insert V1 to V2
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;
    //insert V2 to V1
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    NewNode->Weight = E->Weight;
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}

LGraph BuildGraph()
{
    LGraph Graph;
    Edge E;
    int Nv;
    scanf("%d", &Nv);
    Graph = CreatGraph(Nv);
    scanf("%d", Graph->Ne);
    if (Graph->Ne)
    {
        E = (Edge)malloc(sizeof(struct ENode));
        for (int i = 0; i < Graph->Ne; i++)
        {
            scanf("%d %d", &E->V1, &E->V2);
            E->Weight = 1;
            InsertEdge(Graph, E);
        }
    }
    for (int V = 0; V < Graph->Nv; V++)
    {
        DFSVisited[V] = 0;
        BFSVisited[V] = 0;
    }
    return Graph;
}

void Visit(Vertex V)
{
    printf("%d", V);
}

void DFS(LGraph Graph, Vertex V, void (*Visit)(Vertex))
{
    PtrToAdjVNode W;
    Visit(V);
    DFSVisited[V] = 1;
    for (W = Graph->G[V].FirstEdge; W; W = W->Next)
        if (DFSVisited[W->AdjV] == 0)
            DFS(Graph, W->AdjV, Visit);
}

void BFS(LGraph Graph, Vertex S, void (*Visit)(Vertex))
{
    int queue[1010];
    int l = 0, r = 0;
    queue[r++] = S;
    (*Visit)(S);
    BFSVisited[S] = 1;
    PtrToAdjVNode tmp;
    while (l != r)
    {
        tmp = Graph->G[queue[l++]].FirstEdge;
        while (tmp)
        {
            Vertex pos = tmp->AdjV;
            if (!BFSVisited[pos])
            {
                Visit(pos);
                BFSVisited[pos] = 1;
                queue[r++] = pos;
            }
            tmp = tmp->Next;
        }
    }
}