// include necessary library(s)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// #include "functions.h" placeholder for now

// define the structure
struct words {
    char *word;
    float score;
    float SD;
    int SIS_array[10];
};

// main function with arguments
int main(int argc, char *argv[]) {

    // define max word length
    #define MAX_WORD_LENGTH 100
    // saves the scores
    float arraySol[20];

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

    // define allocation limit and keep track of size
    int MAX = 7000;
    int SIZE = 0;
    struct words *lexicon = malloc(MAX * sizeof(struct words));
    if (lexicon == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // define placeholder variables
    char word1[MAX_WORD_LENGTH];
    float score1;
    float SD1;
    int SIS_array1[10];

    // fscanf function to scan whole line
    while (fscanf(vader, "%[^\t]\t%f\t%f\t[%d, %d, %d, %d, %d, %d, %d, %d, %d, %d]\n", word1, &score1, &SD1, &SIS_array1[0], &SIS_array1[1], &SIS_array1[2], &SIS_array1[3], &SIS_array1[4], &SIS_array1[5], &SIS_array1[6], &SIS_array1[7], &SIS_array1[8], &SIS_array1[9]) == 13) {

        // don't need this for now
        /*
        if (SIZE >= MAX) {
            lexicon = realloc(lexicon, (SIZE + 1) * sizeof(struct words));
            MAX++;
        }
        */
        
        // allocate more memory as needed
        if (SIZE >= MAX) {
            lexicon = realloc(lexicon, (MAX * 2) * sizeof(struct words));
            if (lexicon == NULL) {
                printf("Memory reallocation failed.\n");
                return 1;
            }
            MAX *= 2;
        }

        // prints vairables out just to check / make sure
        printf("%s ", word1);
        printf("%.1f ", score1);
        printf("%.5f ", SD1);
        printf("%d ", SIS_array1[0]);

        // allocate enough memory to copy the word
        lexicon[SIZE].word = malloc(strlen(word1) + 1);
        if (lexicon[SIZE].word == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }

        // strcpy function to copy word1 to lexicon decimal variable
        strcpy(lexicon[SIZE].word, word1);
        
        // lexicon[SIZE].word = word1; don't need this for now
        // set up indexed lexicon variables
        lexicon[SIZE].score = score1;
        lexicon[SIZE].SD = SD1;

        // since strings aren't mutable, change each character
        for (int i = 0; i < 10; i++) {
            lexicon[SIZE].SIS_array[i] = SIS_array1[i];
        }

        // print just to make sure, don't need for now
        /*
        printf("%s ", lexicon[SIZE].word);
        printf("%.1f ", lexicon[SIZE].score);
        printf("%.5f ", lexicon[SIZE].SD);
        printf("%d ", lexicon[SIZE].SIS_array[0]);
        */

        // keep track of the size
        SIZE++;
        // print just to make sure
        printf("%d\n", SIZE);
    }

    printf("\n");

    // define needed variables
    // max word length
    char word2[MAX_WORD_LENGTH];
    // define delimiters / characters to be removed from token
    char delimiters[] = " ,.!"; // Define delimiters as spaces, comma, period, and exclamation mark
    // token variable to obtain a single word
    char *token;
    // sum = total score
    float sum = 0;
    // value to hold individual word score
    float value;
    // keep track of how many words
    int wordCounter = 0;
    // keep track of index to assign value to arraySol[20]
    int index = 0;

    // fscanf to get word
    while (fscanf(valid, "%s", word2) == 1) {
        printf("%s ", word2);
        // get token by subtarcing delimiters
        token = strtok(word2, delimiters);
        // lowercase
        for (int i = 0; token[i]; i++) {
            token[i] = tolower(token[i]);
        }
        // printf("%s ", token);
        // find matching word in the lexicon list
        // if no matching word found, default is 0
        value = 0;
        for (int i = 0; i < SIZE; i++) {
            if (strcmp(lexicon[i].word, token) == 0) {
                printf("(%.1f) ", lexicon[i].score);
                value = lexicon[i].score;
                break;
            }
        }
        // add word score to total score
        sum += value;
        // increment word counter
        wordCounter++;
        // Read the next character
        char ch = fgetc(valid);
        // record the total score when at the end of the line
        if (ch == '\n' || ch == EOF) {
            arraySol[index] = sum/wordCounter;
            printf("%f/%d = ", sum, wordCounter);
            printf("%f\n", arraySol[index]);
            // reset variables
            sum = 0;
            wordCounter = 0;
        }
    }
    
    // close and free allocated memory
    fclose(vader);
    fclose(valid);
    free(lexicon);

    // return working
    return 0;
}
