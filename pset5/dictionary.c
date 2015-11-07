/****************************************************************************
 * dictionary.c
 *
 * CS50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
int counter;
char buffer[LENGTH+2];

int doHash(char* word) {
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
        hash = (hash << 2)^word[i];
        return hash%1024;
}


typedef struct node {
	char word[LENGTH+1];
	struct node* next;
} node;

node* hashTable[1024]; 


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word) {

    char *temp = malloc(strlen(word));
    for (int i = 0; i < strlen(word); i++) {
        temp[i] = tolower(word[i]);
    }
    temp[strlen(word)] = '\0';
    int index = doHash(temp);
    node* nodee = hashTable[index];
    
    if (nodee) {
        node* position = nodee;
        while (position->next != NULL) {
                if (!strcmp(temp, position->word))
                    position = position->next;
                    return true;
            };
        if (!strcmp(temp, position->word))
			position = position->next;
			return true;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary) {

    FILE* file = fopen(dictionary, "r");
    if (file == NULL) {
    		printf("File cannot be open");
    		return false;
    }

    while (fgets(buffer, sizeof(buffer),file)) {
        buffer[strlen(buffer)-1] ='\0';
    	node* temp = malloc(sizeof(node));
    	
    	strncpy(temp->word, buffer, LENGTH + 1);
    	int index = doHash(buffer);
    	temp->next = NULL;

 
    	if (hashTable[index] == NULL) {
    		hashTable[index] = temp;
    	} 
    	
    	
    	if(hashTable[index] != NULL) {
    		node* position = hashTable[index];
    		while (position->next != NULL) {
    			position = position->next;
    		}
    		position->next = temp;
    	}
        counter++;
    }

    fclose(file);

    return true;
}

/**
 * Returns number of counter in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void) {
    return counter;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void) {

    for (int i = 0; i < 1024; i++) {
        node* position = hashTable[i];
        if (position) {
            node* temp = position->next;
            free(position);
            position = temp;
        }
    }
    return true;
}

