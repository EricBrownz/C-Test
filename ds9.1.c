#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

void Shell_sort(int a[], int n)
{
    int tmp;
    int Si, i, P, D;
    int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};
    /* for (D = n / 2; D > 0; D /= 2)
        for (P = D; P < n; P++)
        {
            tmp = a[P];
            for (i = P; i > D && tmp < a[i - D]; i -= D)
                a[i] = a[i - D];
            a[i] = tmp;
        } 
    */
    for (Si = 0; Sedgewick[Si] >= n; Si++)
        ;
    for (D = Sedgewick[Si]; D > 0; D = Sedgewick[++Si])
        for (P = D; P < n; P++)
        {
            tmp = a[P];
            for (i = P; i >= D && tmp < a[i - D]; i -= D)
                a[i] = a[i - D];
            a[i] = tmp;
        }
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void PercDown(int A[], int p, int N)
{
    int Parent, Child;
    int X;

    X = A[p];
    for (Parent = p; 2 * Parent + 1 < N; Parent = Child)
    {
        Child = Parent * 2 + 1;
        if (Child != N - 1 && A[Child] < A[Child + 1])
            Child++;
        if (X >= A[Child])
            break;
        else
            A[Parent] = A[Child];
    }
    A[Parent] = X;
}

void Heap_sort(int A[], int N)
{
    int i;
    for (i = N / 2 - 1; i >= 0; i--)
        PercDown(A, i, N);

    for (i = N - 1; i > 0; i--)
    {
        swap(&A[0], &A[i]);
        PercDown(A, 0, i);
    }
}

void Merge(int A[], int TmpA[], int L, int R, int RightEnd)
{
    int LeftEnd, NumElem, Tmp;
    int i;
    LeftEnd = R - 1;
    Tmp = L;
    NumElem = RightEnd - L + 1;
    while (L <= LeftEnd && R <= RightEnd)
    {
        if (A[L] <= A[R])
            TmpA[Tmp++] = A[L++];
        else
            TmpA[Tmp++] = A[R++];
    }
    while (L <= LeftEnd)
        TmpA[Tmp++] = A[L++];
    while (R <= RightEnd)
        TmpA[Tmp++] = A[R++];
    Tmp--;
    for (i = 0; i < NumElem; i++, Tmp--)
        A[Tmp] = TmpA[Tmp];
    /* for (i = 0; i < NumElem; i++, RightEnd--)
        A[RightEnd] = TmpA[RightEnd]; */
}

void Msort_rec(int A[], int TmpA[], int L, int RightEnd)
{
    int Center;
    if (L < RightEnd)
    {
        Center = (L + RightEnd) / 2;
        Msort_rec(A, TmpA, L, Center);
        Msort_rec(A, TmpA, Center + 1, RightEnd);
        Merge(A, TmpA, L, Center + 1, RightEnd);
    }
}

void Merge_sort(int A[], int N)
{
    int *TmpA;
    TmpA = (int *)malloc(sizeof(int) * N);

    if (TmpA)
    {
        Msort_rec(A, TmpA, 0, N - 1);
        free(TmpA);
    }
}

int main(int argc, char *argv[])
{
    int n;
    int *array = NULL;
    scanf("%d", &n);
    array = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++)
        scanf("%d", array + i);

    //qsort(array, n, sizeof(int), cmp);
    //Shell_sort(array, n);
    //Heap_sort(array, n);
    Merge_sort(array, n);

    for (int i = 0; i < n; i++)
        if (i == 0)
            printf("%d", array[i]);
        else
            printf(" %d", array[i]);

    free(array);
    return 0;
}