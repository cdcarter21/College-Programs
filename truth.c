#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int count = atoi(argv[1]);
    int n = 1 << count;

    //printing the letters for the first line
    for (int i=0; i<count; i++) {
        printf("  %c  |", 'A' + i);
    }
    //printing the operations for the first line
    for (int j=2; j<argc; j++) {
        if (argv[j][0] == '~')
            printf("  %s |", argv[j]);
        else
            printf(" %s |", argv[j]);
    }
    printf("\n");

    //prints each line
    for (int i=0; i<n; i++) {
        int dec = i; 
        int num[26]; 
        int length = 0; 

        //finds each binary digit 
        while (dec > 0) {
            num[length++] = dec % 2;
            dec /= 2;
        }
        //fills in the rest of the digits up to "Z" with 0
        for (int a = length; a<26; a++) {
            num[a] = 0; 
        }
        //prints the letter columns 
        for (int k=0; k<count; k++) {
            printf("  %d  |", num[k]);
        }
        int counter = count; 
        //prints the operation columns 
        for (int j=2; j<argc; j++) {
            char op = argv[j][1];
            int ans; 
            if (op == '*') {
                ans = num[(argv[j][0]) - 65] & num[(argv[j][2]) - 65];
            }
            else if (op == '+') {
                ans = num[(argv[j][0]) - 65] | num[(argv[j][2]) - 65];
            }
            else if (op == '^') {
                ans = num[(argv[j][0]) - 65] ^ num[(argv[j][2]) - 65];
            }
            //not operation 
            else {
                ans = 1 - num[(argv[j][1]) - 65];
            }
            num[counter] = ans; 
            counter++;
            printf("  %d  |", ans);
        }
        printf("\n");
    }
}