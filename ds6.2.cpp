#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 150 //最多150个点
int visited[MAXN] = {0};

//建立邻接矩阵
struct port
{
    int x;
    int y;
} G[MAXN]; //坐标

int NV;       //节点数
int distance; //007能跳的距离

bool jump(int v1, int v2); //计算007一条能不能成功
bool issafe(int v);        //从v点能否跳上岸
bool DFS(int v);           //DFS
void ListComponentsDFS();  //DFS连通集
bool FirstJump(int v);     //第一跳的可能
void save007();            //007 主程序

int main()
{
    //freopen("in.txt","r",stdin);

    int i;
    int x, y;
    scanf("%d %d", &NV, &distance); //输入的是鳄鱼数

    for (i = 0; i < NV; i++)
    {
        scanf("%d %d", &x, &y); //读入坐标
        G[i].x = x;
        G[i].y = y;
    }
    save007();

    //freopen("out.txt","w",stdout);
    return 0;
}

//计算007一条能不能成功,排除第一跳和最后一跳
bool jump(int v1, int v2)
{
    int x, y, d;
    bool answer;

    x = abs(G[v1].x - G[v2].x);
    y = abs(G[v1].y - G[v2].y);
    d = pow(x, 2) + pow(y, 2); //求两点的距离

    if (d <= pow(distance, 2))
        answer = true;
    else
        answer = false;

    return answer;
}

//从v点能否跳上岸
bool issafe(int v)
{
    int x, y;
    bool answer;

    x = abs(G[v].x);
    y = abs(G[v].y);

    if ((x + distance >= 50) || (y + distance >= 50))
        answer = true;
    else
        answer = false;

    return answer;
}

//DFS
bool DFS(int v)
{
    bool answer = false;
    visited[v] = 1;
    if (issafe(v))
        answer = true;
    else
    {
        for (int i = 0; i < NV; i++)
        {
            if ((!visited[i]) && (jump(v, i))) //如果联通这个点且没有访问过
                answer = DFS(i);
            if (answer == true)
                break;
        }
    }

    return answer;
}

void ListComponentsDFS()
{
    int i;
    for (i = 0; i < NV; i++)
    {
        if (!visited[i])
            DFS(i);
    }
}
//第一跳的可能
bool FirstJump(int v)
{
    int x, y;
    double d;
    bool answer;

    x = abs(G[v].x);
    y = abs(G[v].y); //用绝对值
    d = sqrt(pow(x, 2) + pow(y, 2));

    if (d <= (distance + 7.5)) //小岛半径7.5，直径15
        answer = true;
    else
        answer = false;

    return answer;
}
//007 主程序
void save007()
{
    bool answer;
    for (int v = 0; v < NV; v++)
    {
        if (!visited[v] && FirstJump(v))
        {
            answer = DFS(v);
            if (answer == true)
                break;
        }
    }
    if (answer == true)
        printf("Yes\n");
    else
        printf("No\n");
}