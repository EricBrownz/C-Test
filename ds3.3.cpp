#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef NULL
#define NULL 0
#endif // NULL
typedef int ElementType;

struct TNode
{
    ElementType Data;
    struct TNode *Left;
    struct TNode *Right;
};
typedef struct TNode *BinTree;
typedef BinTree PtrToTNode;

struct SNode
{
    ElementType Data;
    struct SNode *Next;
};
typedef struct SNode *Stack;

BinTree BuildTree(int *pre, int *in, int N);
BinTree CreateTNode();
Stack CreateStack();
void push(Stack s, ElementType e);
ElementType pop(Stack s);
void PostOrderTraversal(BinTree BT, ElementType root);

int main()
{
    BinTree BT;
    Stack S;
    int N, i, in_index, pre_index, e;
    char action[5];

    S = CreateStack();

    scanf("%d", &N);
    getchar();

    int in[N], pre[N];
    in_index = pre_index = 0;
    for (i = 0; i < 2 * N; i++)
    {
        scanf("%s", action);
        if (strcmp(action, "Push") == 0)
        {
            scanf("%d", &e);
            pre[pre_index++] = e;
            push(S, e);
        }
        else
        {
            in[in_index++] = pop(S);
        }
    }
    BT = BuildTree(pre, in, N);
    PostOrderTraversal(BT, BT->Data);
    return 0;
}

BinTree BuildTree(int *pre, int *in, int N)
{
    BinTree BT;
    ElementType root;
    int LeftNum, RightNum, flag, i;
    int Left_pre[N], Right_pre[N], Left_in[N], Right_in[N];
    if (N == 1)
    {
        BT = CreateTNode();
        BT->Data = pre[0];
        BT->Left = NULL;
        BT->Right = NULL;
        return BT;
    }
    else if (N == 0)
        return NULL;
    else
    {
        root = pre[0];
        BT = CreateTNode();
        BT->Data = root;
        flag = LeftNum = RightNum = 0;
        for (i = 0; i < N; i++)
        {
            if (in[i] != root)
            {
                if (flag)
                {
                    Right_in[RightNum++] = in[i];
                }
                else
                {
                    Left_in[LeftNum++] = in[i];
                }
            }
            else
            {
                flag = 1;
            }
        }
        for (i = 0; i < LeftNum; i++)
            Left_pre[i] = pre[i + 1];
        for (i = 0; i < RightNum; i++)
            Right_pre[i] = pre[LeftNum + i + 1];
        BT->Left = BuildTree(Left_pre, Left_in, LeftNum);
        BT->Right = BuildTree(Right_pre, Right_in, RightNum);
        return BT;
    }
}
BinTree CreateTNode()
{
    BinTree BT;
    BT = (BinTree)malloc(sizeof(struct TNode));
    BT->Left = NULL;
    BT->Right = NULL;
    BT->Data = 0;
    return BT;
}

Stack CreateStack()
{
    Stack s;
    s = (Stack)malloc(sizeof(struct SNode));
    s->Next = NULL;
    return s;
}
void push(Stack s, ElementType e)
{
    if (s == NULL)
        s = CreateStack();
    Stack PtrToSNode;
    PtrToSNode = (Stack)malloc(sizeof(struct SNode));
    PtrToSNode->Data = e;
    PtrToSNode->Next = s->Next;
    s->Next = PtrToSNode;
    return;
}
ElementType pop(Stack s)
{
    Stack tmp;
    ElementType data;
    if (s == NULL || s->Next == NULL)
    {
        printf("stack empty!\n");
        return NULL;
    }
    tmp = s->Next;
    s->Next = tmp->Next;
    data = tmp->Data;
    free(tmp);
    return data;
}

void PostOrderTraversal(BinTree BT, ElementType root)
{
    if (BT->Left)
        PostOrderTraversal(BT->Left, root);
    if (BT->Right)
        PostOrderTraversal(BT->Right, root);
    if (BT->Data == root)
        printf("%d", BT->Data);
    else
        printf("%d ", BT->Data);
}

/*
#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

// 给定前序遍历和中序遍历，求出二叉树的后序遍历
void getPostOrder(vector<int> preOrder, int preL, vector<int> inOrder, int inL,
                  vector<int> &postOrder, int postL, int n)
{
    if (n == 0)
        return;
    if (n == 1)
    {
        postOrder[postL] = preOrder[preL];
        return;
    }
    auto root = preOrder[preL];
    postOrder[postL + n - 1] = root;
    //在中序遍历数组上找出root的位置
    int i = 0;
    while (i < n)
    {
        if (inOrder[inL + i] == root)
            break;
        ++i;
    }
    // 计算出root节点左右子树节点的个数
    int L = i, R = n - i - 1;
    // 递归的进行求解
    getPostOrder(preOrder, preL + 1, inOrder, inL, postOrder, postL, L);
    getPostOrder(preOrder, preL + L + 1, inOrder, inL + L + 1, postOrder, postL + L, R);
}

vector<vector<int>> getOrder(int N)
{
    vector<int> preOrder(N, 0);
    vector<int> inOrder(N, 0);
    stack<int> st;
    int preL = 0, inL = 0;

    for (int i = 0; i < 2 * N; ++i)
    {
        string str;
        int tmp;
        cin >> str;
        if (str == "Push")
        {
            cin >> tmp;
            preOrder[preL++] = tmp;
            st.push(tmp);
        }
        else if (str == "Pop")
        {
            inOrder[inL++] = st.top();
            st.pop();
        }
    }
    return {preOrder, inOrder};
}

int main()
{
    int N;
    cin >> N;
    auto res = getOrder(N);
    vector<int> postOrder(N, 0);
    getPostOrder(res[0], 0, res[1], 0, postOrder, 0, N);

    int i = 0;
    for (; i < N - 1; ++i)
    {
        cout << postOrder[i] << " ";
    }
    cout << postOrder[i] << endl;
    return 0;
}
*/

/*
#include<cstdio>
#include<stack>
#include<string>
#include<iostream>
using namespace std;
const int maxn=100;
int pre[maxn], in[maxn], post[maxn];
 
void solve(int PreL, int inL, int postL, int n){
	if(n==0)return;
	if(n==1){
		post[postL]=pre[PreL];
		return;
	}
	int i;
	int root=pre[PreL];
	post[postL+n-1]=root;
	for(i=0; i<n; i++){
		if(in[inL+i]==root)break;
	}
	int L=i, R=n-i-1;
	solve(PreL+1, inL, postL, L);
	solve(PreL+1+L, inL+L+1, postL+L, R);
}
int main(){
	int n, num, i=0, j=0;
	scanf("%d", &n);
	string s;
	stack<int> st;
	for(int z=0; z<2*n; z++){
		cin>>s;
		if(s=="Push"){
			scanf("%d\n", &num);
			st.push(num);
			pre[i++]=num;
		}else{
			num=st.top();
			st.pop();
			in[j++]=num;
		}
	}
	solve(0,0,0,n);
	for(int i=0; i<n; i++){
		printf("%d", post[i]);
		if(i!=n-1)printf(" ");
	}
	return 0;
} 
*/