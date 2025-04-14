#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
    int n = atoi(argv[1]);
    int rows = argc-2; 
    int cols = 32; 
    int* arr = malloc((rows * cols) * sizeof(int)); 
    int width = 0; 

    //this loop goes through each command line number and converts
    //to an array of 0's and 1's which we can view as a binary number 
    for (int i=0; i<(argc-2); i++) {
        int dec = atoi(argv[i+2]);
        int length = 0;
        while(dec > 0)
        {
            arr[i * cols + length] = dec % 2; 
            length++; 
            dec = dec / 2; 
        }
        if (length > width) 
            width = length; 
        //fills the rest of the array with 0's in case we have a 
        //"binary" number that is larger 
        for (int a = length; a<32; a++) {
            arr[i * cols + a] = 0; 
        }
    }
    
    //loop for the number of times we print a picture
    for(int i=0; i<(n*width+1); i++) {
        printf("\ec");
        //loop for going through each number 
        for (int j=0; j<(argc-2); j++) {
            //loop for printing each 0 or 1
            for (int k=width-1; k>=0; k--) {
                if (arr[j * cols + k] == 0)
                    printf("  ");
                else 
                    printf("██");
            }
            printf("\n");
            int temp = arr[j * cols + 0];
            for (int l=0; l<(width-1); l++) {
                arr[j * cols + l] = arr[j * cols + (l+1)];
            }
            arr[j * cols + width-1] = temp; 
        }
        usleep(100000);
    }
    free(arr);
}