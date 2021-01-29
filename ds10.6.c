//table sort
//but there is no need to sort when read
#include <stdio.h>
#include <stdlib.h>
//#define MaxN 100000

void SwapZero(int A[], int T[], int N) {
	int i, cnt = 0;
	int S = 0, K = 0;
	int init, nexti, Tmp;

	if (A[0] == 0) //change 0 to other place +1 and Ni+1 so Sum+=2
		K += 2;

	for (i = 0; i < N; i++)
		if (A[i] == i)
			S++;

	for (i = 0; i < N; i++) {
		if (A[i] != i) {
			init = i;
			Tmp = A[i];
			while (T[i] != init) {
				nexti = T[i];
				A[i] = A[T[i]]; //A[Ti]==i
				i = nexti;
				cnt++;
			}
			A[i] = Tmp;
			i = init;
			if (cnt) {
				cnt = 0;
				K++;
			}
		}
	}

	printf("%d\n", N - S + K - 2);
}

int main() {
	int N;
	int *A, *Table;
	//int A[MaxN], Table[MaxN];
	scanf("%d", &N);
	A = (int *)calloc(N, sizeof(int));
	Table = (int *)calloc(N, sizeof(int));

	for (int i = 0; i < N; i++) {
		scanf("%d", A + i);
		Table[A[i]] = i; //because num readed are all [0,N)
	}

	/* for (int i = 0; i < N; i++)
		printf("%d ", Table[i]); */

	SwapZero(A, Table, N);

	return 0;
}
