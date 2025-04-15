#include "types.h"
#include "stat.h"
#include "user.h"

char globe;                                                         //global variable used for our global probing

//this function will probe through memory addresses given the starting address(data) and will write to the pipe given as a parameter
void probe(int pipe, char* data) {
    while (1) {
        *data = 'b';                                                //try to put a char at this spot in memory to see if it's legal
        write(pipe, &data, sizeof(int));                            //write the address to pipe
        data++;                                                     //increase global variable to the next address
    }
}

int main(int argc, char *argv[])
{
    int fd[2];
    int pid;

    if (pipe(fd) == -1) {
        printf(2, "pipe 1 failed\n");
        exit();
    }

    pid = fork();
    if (pid < 0) {
        printf(2, "fork 1 failed\n");
        exit();
    }
    //parent process
    else if (pid > 0) {
        int answer = 0;                                                 //variable where we will store the address 
        close(fd[1]);                                                   //close writing end of pipe
        while (1) {
            //read until we can't anymore: 
            if (read(fd[0], &answer, sizeof(int)) <= 0) {
                close(fd[0]);                                           //close reading end of pipe
                printf(1, "last global: %p\n", answer);                 //print the last address
                wait();                                                 //wait on the child just in case

                // now to take care of the local addresses:
                int fd2[2];                                             //new pipe
                int pid2; 
                if (pipe(fd2) == -1) {
                    printf(2, "pipe 2 failed\n");
                    exit();
                }
                pid2 = fork();
                if (pid2 < 0) {
                    printf(2, "fork 2 failed\n");
                    exit();
                }
                //parent process
                else if (pid2 > 0) {
                    int answer2 = 0;                                    //variable where we store the address
                    close(fd2[1]);                                      //close writing end of pipe
                    while (1) {
                        //read until we can't anymore:
                        if (read(fd2[0], &answer2, sizeof(int)) <= 0) {
                            close(fd2[0]);                              //close reading end of pipe
                            printf(1, "last local: %p\n", answer2);     //print the last available address
                            wait();                                     //wait on the child just in case
                            exit(); 
                        }
                    }
                }
                //child 2 process for probing local variable addresses
                else {
                    close(fd2[0]);                                      //close reading end of pipe
                    char* data2;                                        //this variable will point to the address we want
                    if (argc > 1) 
                        data2 = (char*)malloc(atoi(argv[1]));           //malloc the data if we need to
                    else 
                        data2 = (char*)&data2 + 4;                      //if no parameter, this will point after itself
                    printf(1, "first local: %p\n", &data2);             //print the first address
                    probe(fd2[1], data2);                               //probe the addresses
                    exit();
                }
                exit(); 
            }
        }
    }
    //child process for probing global variable addresses 
    else {
        close(fd[0]);                                                   //close reading end of pipe
        char* data = &globe;                                            //this variable points to the address of the global variable
        printf(1, "first global: %p\n", &globe);                        //print the first address
        probe(fd[1], data);                                             //probe the addresses
        exit();
    }
}