#include "types.h"
#include "user.h"
#include "fcntl.h"

int main(int argc,char *argv[])
{
  int N = atoi(argv[1]);

  int p[2];
  if (pipe(p)<0) {
    printf(2,"pipe failed\n");
    exit();
  }

  for (int i=0; i<N; i++) {
    int pid = fork();
    if (pid < 0) {
      printf(2,"fork failed\n");
      exit();
    }
    if (pid == 0) {
      // parallel code
      for (int j=0; j<10000; j++)
        write(p[1],&j,4);
      exit();
    }
  }

  int r;
  for (int i=0; i<N*10000; i++)
    if (read(p[0],&r,4) != 4) {
      printf(2,"read failed\n");
      exit();
    }

  int pid,level,ticks;
  for(int i=0; i<N; i++){
    if((pid=wait(&ticks,&level)) < 0)
      exit();
    printf(1,"%d: %d,%d\n",pid,level,ticks);
  }
  exit();
}