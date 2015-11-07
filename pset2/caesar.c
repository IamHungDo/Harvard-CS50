#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
                        
int main(int argc, string argv[]) {
    bool flag = true;
    string userInput = NULL;
    int k = 0;
    int capA = 65;
    int lowA = 97;
    int alpha = 26;
    do {
        if(argc != 2) {
            printf("Invalid. Please try again\n");
            return 1;
        }
        else {
            k = atoi(argv[1]);
            flag = false;
        }
    } while(flag);
    
    userInput = GetString();
    for(int x = 0; x < strlen(userInput); x++) {
        if(isalpha(userInput[x]))
        {
            if(islower(userInput[x])) {
                printf("%c",(((userInput[x]-lowA)+k)%alpha)+lowA);
            }
            else {
                printf("%c",(((userInput[x]-capA)+k)%alpha)+capA);
            }
        }
        else {
            printf("%c", userInput[x]);
        }
    }
    printf("\n");
    return 0;  
}
