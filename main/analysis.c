// include necessary library(s)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

// main function with arguments
int main(int argc, char *argv[]) {

    // check if the number of arguments is correct
    if (argc != 3) {
        printf("Usage: %s <lexicon_file> <validation_file>\n", argv[0]);
        return 1;
    }

    // open files and check if opened sucessfully
    FILE *vader = fopen(argv[1], "r");
    FILE *valid = fopen(argv[2], "r");
    if (vader == NULL || valid == NULL) {
        printf("Error opening the files.\n");
        return 1;
    }

    // define lexicon structure variable and send its address
    struct words *lexicon;
    // call function to get the size and perform oprations on lexicon
    int SIZE = read_lexicon(vader, &lexicon);

    // saves the scores
    float arraySol[20];
    // performs comparisons and prints the scores
    process_validation(valid, lexicon, SIZE, arraySol);

    // close files and frees memory as needed
    fclose(vader);
    fclose(valid);
    free_lexicon(lexicon, SIZE);

    // return working
    return 0;
}
