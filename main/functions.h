#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// define max word length
#define MAX_WORD_LENGTH 100

// define the structure
struct words {
    char *word;
    float score;
    float SD;
    int SIS_array[10];
};

// define functions
int read_lexicon(FILE *vader, struct words **lexicon);
void process_validation(FILE *valid, struct words *lexicon, int SIZE, float arraySol[]);
void free_lexicon(struct words *lexicon, int SIZE);

#endif /* FUNCTIONS_H */
