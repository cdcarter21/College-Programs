#include "types.h"
#include "user.h"
#include "fcntl.h"

int main(int argc,char *argv[])
{
  int N = atoi(argv[1]);

  for (int i=0; i<N; i++) {
    int pid = fork();
    if (pid < 0) {
      printf(2,"fork failed\n");
      exit();
    }
    if (pid == 0) {
      // parallel code
      int s = 0;
      for (int i=0; i<1000000; i++)
        for (int j=0; j<1000; j++)
          s++;
      exit();
    }
  }

  int pid,level,ticks;
  for(int i=0; i<N; i++){
    if((pid=wait(&ticks,&level)) < 0) {
        printf(1, "failed\n");
      exit();
    }
    printf(1,"%d: %d,%d\n",pid,level,ticks);
  }
  exit();
}
