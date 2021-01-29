#include <stdio.h>
#include <math.h>
#include <time.h>
clock_t start, stop;
double duration;
#define MAXN 100
#define MAXK 1e4

double f1(int n, double a[], double x)
{
    int i;
    double p = a[0];
    for (i = 0; i <= MAXN; i++)
        p += a[i] * pow(x, i);
    return p;
}

double f2(int n, double a[], double x)
{
    int i;
    double p = a[MAXN];
    for (i = MAXN; i; i--)
        p = a[i - 1] + x * p;
    return p;
}

int main()
{
    int j;
    double a[MAXN];
    for (j = 0; j <= MAXN; j++)
        a[j] = (double)j;

    start = clock();
    for (j = 0; j <= MAXK; j++)
        f1(MAXN, a, 1.1);
    stop = clock();
    duration = ((double)(stop - start)) / CLOCKS_PER_SEC / MAXK;
    printf("ticks1=%f\n", (double)(stop - start));
    printf("duration1=%6.2e\n", duration);

    start = clock();
    for (j = 0; j <= MAXK; j++)
        f2(MAXN, a, 1.1);
    stop = clock();
    duration = ((double)(stop - start)) / CLOCKS_PER_SEC / MAXK;
    printf("ticks2=%f\n", (double)(stop - start));
    printf("duration2=%6.2e\n", duration);

    return 0;
}
