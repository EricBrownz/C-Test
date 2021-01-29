#include <iostream>
#include <stdio.h>
#include <queue>

using namespace std;
typedef struct BiTree *BT;
struct BiTree {
	int left;
	int right;
};
queue<int> queueList;
int cnt = 0;

void readTree(BiTree bt[], int len);
int findRoot(BiTree bt[], int len);
void findLeaves(BiTree bt[], int root);

int main() {
	int len;
	BiTree *bt;

	cin >> len;
	if (len != 0) {
		bt = (BiTree*)malloc(len * sizeof(BiTree));
		readTree(bt, len);
		int root = findRoot(bt, len);
		findLeaves(bt, root);
	}
	return 0;
}

void readTree(BiTree bt[], int len) {
	char left, right;
	for (int i = 0; i < len; i++) {
		cin >> left >> right;
		if (left != '-')
			bt[i].left = left - '0';
		else
			bt[i].left = -1;
		if (right != '-')
			bt[i].right = right - '0';
		else
			bt[i].right = -1;
	}
}
int findRoot(BiTree bt[], int len) {
	int record[10] = { 0 };
	for (int i = 0; i < len; i++) {
		if (bt[i].left != -1)
			record[bt[i].left] = 1;
		if (bt[i].right != -1)
			record[bt[i].right] = 1;
	}
	for (int i = 0; i < len; i++)
		if (record[i] == 0)
			return i;
	return -1;
}
void findLeaves(BiTree bt[], int root) {
	//使用层序遍历的思想，将整个二叉树遍历一遍，将左右儿子都为空的节点打印出来
	//每碰到一个节点将它的左右孩子入队（若有的话），然后依次从队头取出判断是否为叶子节点
	int temp;
	if (root == -1) return;
	queueList.push(root);
	while (!queueList.empty()) {
		temp = queueList.front();
		queueList.pop();
		if (bt[temp].left == -1 && bt[temp].right == -1) { //如果出队的节点左右孩子为空
			if (cnt++ != 0) printf(" "); //不是第一个节点的话，输出空格作为分隔符
			printf("%d", temp);
		}
		if (bt[temp].left != -1) queueList.push(bt[temp].left);
		if (bt[temp].right != -1) queueList.push(bt[temp].right);
	}
}