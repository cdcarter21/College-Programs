#include "types.h"
#include "stat.h"
#include "user.h"
#include "parse.h"
#include "fcntl.h"

//I am defining NULL for simplicity sake
#ifndef NULL
#define NULL ((void *)0)
#endif

int main(int argc, char *argv[]) 
{
    if(argc <= 1){
        printf(2, "usage: batch <script>\n");
        exit();
    }

    int fd; 
    char buffer[255];
    command cmd; 

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        printf(2, "%s not found\n", argv[1]);
    }

    //this loop will run forever until buffer is equal to '\0' which 
    //in our case indicates EOF
    while (1) {
        gets(fd, buffer, sizeof(buffer));
        if (buffer[0] == '\0') {
            close(fd);
            exit(); 
        }
        if ((parse(buffer, &cmd)) == -1) {
            printf(2, "syntax error\n");
            exit(); 
        }
        //this would be if there is a blank line between lines
        if (cmd.argc == 0) {
            continue; 
        }

        //see if we have an input file or output file
        int fd_input; 
        if (cmd.input) {
            if ((fd_input = open(cmd.input, O_RDONLY)) == -1) {
                printf(2, "open failed: %s\n", cmd.input);
                exit(); 
            }
        }
        int fd_output = 0; 
        if (cmd.output) {
            if ((fd_output = open(cmd.output, O_CREATE | O_WRONLY)) == -1) {
                printf(2, "create failed: %s\n", cmd.output);
                exit(); 
            }
        }

        int rc = fork();
        char *args[] = {buffer, NULL};
        int exec_code = 0; 
        if (rc < 0) {
            // fork failed
            printf(2, "fork failed\n");
            exit(); 
        }
        else if (rc == 0) {
            // child -- "restart"

            exec_code = exec(cmd.argv[0], args);

            close(fd_output);
            printf(2, "exec failed: %s\n", cmd.argv[0]);
            exit(); 
        } 
        else {
            // parent -- wait and report
            //if exec didn't fail
            if (exec_code != -1) {
                printf(2, "%d: %s started\n", rc, cmd.argv[0]);
                if (cmd.wait)
                    wait();
                printf(2, "%d: %s finished\n", rc, cmd.argv[0]); 
            }
        }       
    }
    close(fd); 
    exit(); 
}