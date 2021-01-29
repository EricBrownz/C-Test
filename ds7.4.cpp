/*并查集相关*/
#include <iostream>
#include <cstdio>

using namespace std;
const int N = 105;
const int MAX = 0x7ffffff;
int graph[N][N] = {0};
int set[N];

bool isLinked(int n)
{
	int num = 0;
	for (int i = 1; i <= n; i++)
	{
		if (set[i] < 0)
			num++;
	}
	if (num == 1)
		return true;
	else
		return false;
}

int findRoot(int a)
{
	while (set[a] >= 0)
		a = set[a];
	return a;
}

void setUnion(int a, int b)
{
	int rootA = findRoot(a);
	int rootB = findRoot(b);
	if (rootA == rootB)
		return;
	if (set[rootA] >= set[rootB])
	{ //如果A中的元素较少，则把A集合并到B集合
		set[rootB] += set[rootA];
		set[rootA] = rootB;
	}
	else
	{
		set[rootA] += set[rootB];
		set[rootB] = rootA;
	}
}

int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		set[i] = -1;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			graph[i][j] = MAX;
			if (i == j)
				graph[i][j] = 0;
		}
	}

	while (m--)
	{
		int x, y, w;
		cin >> x >> y >> w;
		graph[x][y] = w;
		graph[y][x] = w;
		setUnion(x, y);
	}
	if (!isLinked(n))
	{ //是否为连通图
		cout << "0" << endl;
		return 0;
	}
	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (graph[i][j] > graph[i][k] + graph[j][k])
				{
					graph[i][j] = graph[i][k] + graph[j][k];
					graph[j][i] = graph[i][j];
				}
			}
		}
	}

	int ans = MAX;
	int *max = new int[n + 1];
	for (int i = 1; i <= n; i++)
	{
		max[i] = -1;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (graph[i][j] > max[i])
			{
				max[i] = graph[i][j];
			}
		}
	}
	int min = MAX;
	for (int i = n; i >= 1; i--)
	{
		if (min >= max[i])
		{
			min = max[i];
			ans = i;
		}
	}
	cout << ans << " " << min << endl;
	return 0;
}