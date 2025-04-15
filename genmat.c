#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

struct header {
    int rows;
    int cols;
};

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("usage: %s <rows> <cols> <name>\n",argv[0]);
        return 1;
    }
    struct header hdr; 
    hdr.rows = atoi(argv[1]);
    hdr.cols = atoi(argv[2]);

    int fd = open(argv[3],O_CREAT|O_TRUNC|O_WRONLY,0666);
    if (fd < 0) {
        printf("open %s failed\n",argv[3]);
        return 1;
    }
    
    srand((unsigned)time(NULL));

    // output matrix
    if (write(fd,&hdr,sizeof(hdr)) != sizeof(hdr)) goto bad;

    for (int j=0; j<hdr.rows*hdr.cols; j++) {
        int x = rand();
        if (write(fd,&x,sizeof(x)) != sizeof(x)) goto bad;
    }

    close(fd);
    return 0;

bad:
    printf("write failed\n");
    close(fd);
    return 1;
}
