#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#define MaxN 100

typedef int ElementType;

ElementType *ReadArray(int N) //(int *Array , ) is wrong
{
    ElementType *Array;
    Array = (ElementType *)malloc(N * sizeof(ElementType));
    for (int i = 0; i < N; i++)
        scanf("%d", Array + i);
    return Array;
}

int isInsert(ElementType *Initial, ElementType *SortPart, int N)
{
    int i, JumpPoint;
    ElementType Tmp;

    for (i = 1; i < N - 1; i++)
        if (SortPart[i] < SortPart[i - 1])
        {
            JumpPoint = i;
            break;
        }

    for (; i < N; i++)
        if (Initial[i] != SortPart[i])
            break;

    if (i != N)
        return false;

    Tmp = SortPart[JumpPoint];
    for (i = JumpPoint; i > 0 && Tmp < SortPart[i - 1]; i--)
        SortPart[i] = SortPart[i - 1];
    SortPart[i] = Tmp;

    return true;
}

int FindLength(ElementType *Initial, ElementType *SortPart, int N)
{
    int l, i, JumpPoint = 0;
    for (l = 2; l <= N; l *= 2) //==N!
    {
        for (int i = l / 2; i < N; i += l)
            if (SortPart[i - 1] > SortPart[i])
            {
                JumpPoint = i;
                break;
            }
        if (JumpPoint)
            break;
    }

    return l / 2; //l是下一次merge的length
}

void Merge(ElementType A[], ElementType TmpA[], int L, int R, int RightEnd)
{
    int i;
    int LeftEnd, Sum, Tmp;

    Tmp = L;
    LeftEnd = R - 1;
    Sum = RightEnd - L + 1;
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

    for (i = 0; i < Sum; i++, RightEnd--)
        A[RightEnd] = TmpA[RightEnd];
    //memcpy(TmpA, A,Sum * sizeof(int)); //wrong
}

int IsMerge(ElementType *Initial, ElementType *SortPart, int N)
{
    int i;
    int Length;
    ElementType *TmpSort;

    TmpSort = (ElementType *)malloc(N * sizeof(ElementType));
    Length = FindLength(Initial, SortPart, N); //length must be last term
    //printf("length %d\n", Length);
    for (i = 0; i <= N - 2 * Length; i += 2 * Length)
        Merge(SortPart, TmpSort, i, i + Length, i + 2 * Length - 1);
    if (i + Length < N)
        Merge(SortPart, TmpSort, i, i + Length, N - 1);
    /* else
        for (i; i < N; i++)
            TmpSort[i] = SortPart[i]; */

    return true;
}

void PrintArray(ElementType *Array, int N)
{
    for (int i = 0; i < N; i++)
    {
        if (i == 0)
            printf("%d", Array[i]);
        else
            printf(" %d", Array[i]);
    }
    printf("\n");
}

int main()
{
    int N, Judge;
    ElementType *Initial = NULL;
    ElementType *SortPart = NULL;
    scanf("%d", &N);

    Initial = ReadArray(N);
    SortPart = ReadArray(N);

    if (isInsert(Initial, SortPart, N))
    {
        printf("Insertion Sort\n");
        PrintArray(SortPart, N);
    }
    else if (IsMerge(Initial, SortPart, N))
    {
        printf("Merge Sort\n");
        PrintArray(SortPart, N);
    }

    return 0;
}
