#include <stdio.h>
#include <cs50.h>
#include <math.h>
int main(void) {
float dollars;
int amount;
printf("Enter your amount");
dollars = GetFloat();
amount = roundf(dollars*100);
int counter = 0;
if(amount>0) {
    while(amount>=25) {
    amount -= 25;
    counter++;
    }
    while(amount>=10) {
    amount -= 10;
    counter++;
    }
    while(amount>=5) {
    amount -= 5;
    counter++;
    }
    while(amount>=1) {
    amount -= 1;
    counter++;
}
printf( "%d\n" ,counter);
} else {
printf("Your input cannot be negative or string\n");
}

}
