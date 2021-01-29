#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//memset can only initail array with 0/-1
#define MaxVertexNum 500
#define INFINITY 65535

typedef int Vertex;
typedef int WeightType;

typedef struct ENode *PtrToENode;
struct ENode
{
	Vertex V1, V2;
	WeightType Cost, Dist;
};
typedef PtrToENode Edge;

typedef struct GNode *PtrToGNode;
struct GNode
{
	int Nv;
	int Ne;
	Vertex S, D;
	WeightType GD[MaxVertexNum][MaxVertexNum];
	WeightType GC[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

MGraph CreateGraph(int VertexNum)
{
	Vertex V, W;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;

	for (V = 0; V < Graph->Nv; V++)
		for (W = 0; W < Graph->Nv; W++)
		{
			Graph->GD[V][W] = INFINITY;
			Graph->GC[V][W] = INFINITY;
		}

	return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
	Graph->GD[E->V1][E->V2] = E->Dist;
	Graph->GC[E->V1][E->V2] = E->Cost;

	Graph->GD[E->V2][E->V1] = E->Dist;
	Graph->GC[E->V2][E->V1] = E->Cost;
}

MGraph BuildGraph()
{
	MGraph Graph;
	Edge E;
	int Nv;
	scanf("%d", &Nv);
	Graph = CreateGraph(Nv);
	scanf("%d", &Graph->Ne);
	scanf("%d %d", &Graph->S, &Graph->D);

	if (Graph->Ne)
	{
		E = (Edge)malloc(sizeof(struct ENode));
		for (int i = 0; i < Graph->Ne; i++)
		{
			scanf("%d %d %d %d", &E->V1, &E->V2, &E->Dist, &E->Cost);
			InsertEdge(Graph, E);
		}
	}

	return Graph;
}

Vertex FindMinDist(MGraph Graph, int *dist, int *collected)
{
	Vertex MinV, V;
	int MinDist = INFINITY;

	for (V = 0; V < Graph->Nv; V++)
	{
		if (collected[V] == 0 && dist[V] < MinDist)
		{
			MinDist = dist[V];
			MinV = V;
		}
	}

	if (MinDist < INFINITY)
		return MinV;
	else
		return -1;
}

void Dijkstra(MGraph Graph, int *dist, int *cost, int *path, Vertex S, Vertex D)
{
	int collected[MaxVertexNum];
	Vertex V, W;
	/* for (V = 0; V < Graph->Nv; V++)
		collected[V] = 0; */
	memset(collected, 0, sizeof(collected)); //MaxVertexNum is wrong must sizeof

	for (V = 0; V < Graph->Nv; V++)
	{
		dist[V] = Graph->GD[S][V];
		cost[V] = Graph->GC[S][V];
		if (dist[V] < INFINITY)
			path[V] = S;
	}

	dist[S] = 0;
	collected[S] = 1;

	while (1)
	{
		V = FindMinDist(Graph, dist, collected);
		if (V == -1)
			break;
		collected[V] = 1;
		for (W = 0; W < Graph->Nv; W++)
		{
			if (collected[W] == 0 && Graph->GD[V][W] < INFINITY)
			{
				if (dist[V] + Graph->GD[V][W] < dist[W])
				{
					dist[W] = dist[V] + Graph->GD[V][W];
					cost[W] = cost[V] + Graph->GC[V][W];
					path[W] = V;
				}
				else if (dist[V] + Graph->GD[V][W] == dist[W] && cost[V] + Graph->GC[V][W] < cost[W])
					cost[W] = cost[V] + Graph->GC[V][W];
			}
		}
	}

	printf("%d %d", dist[D], cost[D]);
}

int main()
{
	int dist[MaxVertexNum], cost[MaxVertexNum], path[MaxVertexNum]; //path is no need
	for (int i = 0; i < MaxVertexNum; i++)
	{
		dist[i] = INFINITY;
		cost[i] = INFINITY;
	}
	memset(path, -1, sizeof(path));
	MGraph Graph;
	Graph = BuildGraph();
	Dijkstra(Graph, dist, cost, path, Graph->S, Graph->D);

	return 0;
}