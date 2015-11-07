#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void) {
string i = GetString();
char c = 'A';
    if(i[0] >= 'a' && i[0] <= 'z' ) {
        printf("%c",i[0] - ('a' - 'A'));
    } else {
        printf("%c",i[0]);
    }
for(int x = 0; x<strlen(i); i++) {
    if(i[x] == ' ') {
    c = i[x+1];
      if(c >= 'a' && c <= 'z' ) {
        printf("%c",c - ('a' - 'A'));
    } else {
        printf("%c",c);
    }

    }
}
printf("\n");

}
