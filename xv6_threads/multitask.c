#include "types.h"
#include "user.h"

void f(void *arg)
{
    int *p = (int *)arg;
    while (*p != 10000000)
        (*p)++;
    exit();
}

int main(int argc,char *argv[])
{
    int n = argc > 1 ? atoi(argv[1]) : 10;
    int *counters = malloc(n*sizeof(int));
    for (int i=0; i<n; i++)
        counters[i] = 0;
    for (int i=0; i<n; i++) {
        if (thread(f,counters+i) < 0) {
            printf(1,"thread %d failed\n",i);
            exit();
        }
    }
    for (int i=0; i<n; i++) {
        if (wait() < 0) {
            printf(1,"wait %d failed\n",i);
            exit();
        }
    }
    for (int i=0; i<n; i++) {
        printf(1,"%d: %d\n",i,counters[i]);
    }
    exit();
}
