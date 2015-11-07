#include <stdio.h>
#include <cs50.h>

int main(void) {
printf("Enter a number between from 1 to 23");
bool flag = true;
do {

int height = GetInt();
int space = height-1;
int hash = 2;

if(height<=23&&height>0) {
for(int i = 0; i<height; i++) {
    for(int w = 0; w<space ; w++) {
     printf(" ");
    }
    for(int x = 0; x<hash; x++){
     printf("#");
    }
    space--;
    hash++;
    printf("\n");
 }
 flag = false;
 } else if(height ==0) {
 flag = false;
 } else {
 printf("Out of range. Try again\n");
 }
} while(flag);














}
