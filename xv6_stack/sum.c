#include "types.h"
#include "user.h"

int sum(int n)
{
    if (n <= 0) return 0;
    return n+sum(n-1);
}

int main(int argc,char *argv[])
{
    if (argc > 2)
        malloc(atoi(argv[2]));
    int n = argc > 1 ? atoi(argv[1]) : 100;
    printf(1,"sum(%d)=%d\n",n,sum(n));
    sleep(200);
    exit();
}