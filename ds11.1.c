//hash
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define KEYLENGTH 11
#define MAXD 5
#define MAXTABLESIZE 1000000

typedef char ElementType[KEYLENGTH + 1];
typedef int Index;

typedef struct LNode *PtrToNode;
struct LNode
{
    ElementType Data;
    int Count;
    PtrToNode Next;
};
typedef PtrToNode List, Position;

typedef struct TNode *HashTable;
struct TNode
{
    int TableSize;
    PtrToNode Heads;
};

void ScanAndOutput(HashTable H)
{
    int CntMax = 0, SameNum = 0;
    PtrToNode Ptr;
    ElementType MinPhone = "\0";
    //MinPhone; MinPhone[0] = '\0';

    for (int i = 0; i < H->TableSize; i++)
    {
        Ptr = H->Heads[i].Next; //made mistake
        while (Ptr)
        {
            if (Ptr->Count > CntMax)
            {
                CntMax = Ptr->Count;
                strcpy(MinPhone, Ptr->Data);
                SameNum = 1;
            }
            else if (Ptr->Count == CntMax)
            {
                SameNum++;
                if (strcmp(Ptr->Data, MinPhone) < 0)
                    strcpy(MinPhone, Ptr->Data);
            }
            Ptr = Ptr->Next;
        }
    }
    printf("%s %d", MinPhone, CntMax);
    if (SameNum > 1)
        printf(" %d", SameNum);
    printf("\n");
}

int NextPrime(int N)
{
    int i, p = (N % 2) ? N + 2 : N + 1;
    while (p <= MAXTABLESIZE)
    {
        for (i = (int)sqrt(N); i > 2; i--) //if i>1
        {
            if (p % i == 0)
                break;
        }
        if (i == 2) //i==1 also right
            break;
        else
            p += 2;
    }
    return p;
}

HashTable CreateTable(int N)
{
    HashTable H;

    H = (HashTable)malloc(sizeof(struct TNode));
    H->TableSize = NextPrime(N);
    H->Heads = (PtrToNode)malloc(H->TableSize * sizeof(struct LNode));

    for (int i = 0; i < H->TableSize; i++)
    {
        H->Heads[i].Data[0] = '\0'; //error: assignment to expression with array type
                                    //H->Heads[i].Data = "\0";
        H->Heads[i].Count = 0;
        H->Heads[i].Next = NULL;
    }

    return H;
}

int Hash(int Key, int p)
{
    return Key % p;
}

PtrToNode Find(HashTable H, ElementType Key)
{
    PtrToNode P;
    Index Pos;

    Pos = Hash(atoi(Key + KEYLENGTH - MAXD), H->TableSize);
    P = H->Heads[Pos].Next;
    while (P && strcmp(P->Data, Key))
        P = P->Next;

    return P;
}

int Insert(HashTable H, ElementType Key)
{
    PtrToNode P, NewNode;
    Index Pos; //subscript

    P = Find(H, Key);
    if (!P)
    {
        NewNode = (PtrToNode)malloc(sizeof(struct LNode));
        strcpy(NewNode->Data, Key);
        NewNode->Count = 1;
        Pos = Hash(atoi(Key + KEYLENGTH - MAXD), H->TableSize);
        NewNode->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewNode;
        return 1;
    }
    else
    {
        P->Count++;
        return 0;
    }
}

void DeleteTable(HashTable H)
{
    PtrToNode P, tmp;

    for (int i = 0; i < H->TableSize; i++)
    {
        P = H->Heads[i].Next; //P=&H->Heads[i] wrong
        while (P)
        {
            tmp = P;
            P = P->Next;
            free(tmp);
        }
    }
    free(H->Heads);
    free(H);
}

int main()
{
    int N;
    ElementType Key;
    HashTable H;

    scanf("%d", &N);
    H = CreateTable(N * 2);
    for (int i = 0; i < 2 * N; i++)
    {
        scanf("%s", Key);
        Insert(H, Key);
    }
    ScanAndOutput(H);
    DeleteTable(H);

    return 0;
}


//sort
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b)
{
    return strcmp(*(char **)a, *(char **)b);
}

int main()
{
    int n;
    int cnt = 1, cnttmp = 1, same = 1;
    char **PhoneNumStr;
    char strtmp[12], str[12];
    scanf("%d", &n);
    PhoneNumStr = (char **)calloc(2 * n, sizeof(char *));
    for (int i = 0; i < 2 * n; i++)
        PhoneNumStr[i] = (char *)calloc(12, sizeof(char));

    for (int i = 0; i < 2 * n; i++)
    {
        scanf("%s", str);
        strcpy(PhoneNumStr[i], str);
    }

    qsort(PhoneNumStr, 2 * n, sizeof(PhoneNumStr[0]), cmp);

    for (int i = 0; i < 2 * n - 1; i++)
    {
        if (strcmp(PhoneNumStr[i], PhoneNumStr[i + 1]) == 0)
        {
            strcpy(strtmp, PhoneNumStr[i]);
            cnttmp++;
        }
        else
            cnttmp = 1;
        if (cnttmp > cnt)
        {
            same = 1;
            cnt = cnttmp;
            strcpy(str, strtmp);
        }
        else if (cnttmp == cnt)
            same++;
    }

    printf("%s %d", str, cnt);
    if (same > 1)
        printf(" %d", same);
    return 0;
}
