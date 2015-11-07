#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int main(int argc, string argv[]) {
    bool flag = true;
    string userInput = "";
    string key = "";
    int kLength = 0;
    int counter = 0;
    int temp = 0;
    int capA = 65;
    int lowA = 97;
    int alpha = 26;
    int keyArray[kLength];
    
    do {
        if(argc != 2) {
            printf("Invalid. Try Again.\n");
            return 1;
        }
        else if(argv[1]) {
            int length = strlen(argv[1]);
            for(int x = 0; x < length; x++) {
                if(!isalpha(argv[1][x])) {
                    printf("Input can't be recognized\n");
                    return 1;
                }
                else {
                    flag= false;
                    key = argv[1];
                }
              }
            }
          } while(flag);

    kLength = strlen(key);
    for(int x = 0; x < kLength;x++) {
        keyArray[x] = toupper(key[x]) - capA;
    }

    userInput = GetString();
 
    for (int x = 0; x < strlen(userInput); x++) {
        if(!isalpha(userInput[x])) {
            printf("%c", userInput[x]);
        }
        else {
            if(islower(userInput[x])) {
                temp = (((userInput[x]- lowA)+keyArray[counter])%alpha)+lowA;
                }
           else {
                temp =(((userInput[x] - capA)+keyArray[counter])%alpha)+capA;
            }
            printf("%c", temp);
 
            if(counter < kLength - 1) {
                counter++;
            }
            else {
                counter = 0;
            }
          }
        }
    printf("\n");
    return 0;
}


