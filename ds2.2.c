#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode *Polynomial;
struct PolyNode
{
    int coef;
    int expon;
    Polynomial link;
};

void Attach(int c, int e, Polynomial *pRear);
Polynomial ReadPoly();
Polynomial Add(Polynomial P1, Polynomial P2);
Polynomial Mult(Polynomial P1, Polynomial P2);
void PrintPoly(Polynomial P);

int main()
{
    Polynomial P1, P2, PP, PS;

    P1 = ReadPoly();
    P2 = ReadPoly();
    PP = Mult(P1, P2);
    PrintPoly(PP);
    PS = Add(P1, P2);
    PrintPoly(PS);

    return 0;
}

void Attach(int c, int e, Polynomial *pRear)
{
    Polynomial P;
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->coef = c;
    P->expon = e;
    P->link = NULL;
    (*pRear)->link = P;
    *pRear = P;
}

Polynomial ReadPoly()
{
    Polynomial P, Rear, temp;
    int c, e, N;
    scanf("%d", &N);
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->link = NULL;
    Rear = P;
    while (N--)
    {
        scanf("%d %d", &c, &e);
        Attach(c, e, &Rear);
    }
    temp = P;
    P = P->link;
    free(temp);
    return P;
}

Polynomial Add(Polynomial P1, Polynomial P2)
{
    Polynomial P, t1, t2, Rear, temp;
    int sum;
    t1 = P1, t2 = P2;
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->link = NULL;
    Rear = P;
    while (t1 && t2)
    {
        if (t1->expon == t2->expon)
        {
            sum = t1->coef + t2->coef;
            if (sum)
            {
                Attach(sum, t1->expon, &Rear);
            }
            t1 = t1->link;
            t2 = t2->link;
        }
        else if (t1->expon > t2->expon)
        {
            Attach(t1->coef, t1->expon, &Rear);
            t1 = t1->link;
        }
        else
        {
            Attach(t2->coef, t2->expon, &Rear);
            t2 = t2->link;
        }
    }
    while (t1)
    {
        Attach(t1->coef, t1->expon, &Rear);
        t1 = t1->link;
    }
    while (t2)
    {
        Attach(t2->coef, t2->expon, &Rear);
        t2 = t2->link;
    }
    temp = P;
    P = P->link;
    free(temp);
    return P;
}

Polynomial Mult(Polynomial P1, Polynomial P2)
{
    Polynomial P, t1, t2, Rear, temp;
    int c, e;
    t1 = P1, t2 = P2;
    if (!P1 || !P2)
        return NULL;
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->link = NULL;
    Rear = P;
    while (t2)
    {
        Attach(t1->coef * t2->coef, t1->expon + t2->expon, &Rear);
        t2 = t2->link;
    }
    t1 = t1->link;
    while (t1)
    {
        t2 = P2;
        Rear = P;
        while (t2)
        {
            e = t1->expon + t2->expon;
            c = t1->coef * t2->coef;
            while (Rear->link && Rear->link->expon > e)
                Rear = Rear->link;
            if (Rear->link && Rear->link->expon == e)
                if (Rear->link->coef + c)
                    Rear->link->coef += c;
                else
                {
                    temp = Rear->link;
                    Rear->link = temp->link;
                    free(temp);
                }
            else
            {
                temp = (Polynomial)malloc(sizeof(struct PolyNode));
                temp->coef = c;
                temp->expon = e;
                temp->link = Rear->link;
                Rear->link = temp;
                Rear = Rear->link;
            }
            t2 = t2->link;
        }
        t1 = t1->link;
    }
    t2 = P;
    P = P->link;
    free(t2);
    return P;
}

void PrintPoly(Polynomial P)
{
    int flag = 0;
    if (!P)
    {
        printf("0 0\n");
        return;
    }
    while (P)
    {
        if (!flag)
            flag = 1;
        else
            printf(" ");
        printf("%d %d", P->coef, P->expon);
        P = P->link;
    }
    printf("\n");
}