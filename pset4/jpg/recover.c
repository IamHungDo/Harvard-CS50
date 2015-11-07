/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;
int main(void) {
int counter = 0;
BYTE bufferReader[512];
FILE* output = NULL;
FILE* f = fopen("card.raw","r");
char name[8];

if(f == NULL) {
    fclose(f);
    printf("Cannot open the f");
    return 1;
    }
  while(!feof(f)) {
     if (bufferReader[0] == 0xff && bufferReader[1] == 0xd8 && bufferReader[2] == 0xff && (bufferReader[3] == 0xe0 || bufferReader[3] == 0xe1)) {
       if (output != NULL) {
                fclose(output);
            }
        sprintf(name,"%03d.jpg",counter);
        output = fopen(name,"w");
        fwrite(bufferReader, sizeof(bufferReader), 1, output);
        counter++;
     } else if(counter>0) {
            fwrite(bufferReader, sizeof(bufferReader), 1, output);
     }
     fread(bufferReader, sizeof(bufferReader), 1, f);
  }


  fclose(f);
  return 0;
}
