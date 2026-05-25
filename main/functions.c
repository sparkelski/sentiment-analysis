#include "functions.h"

// function to make lexicon structure
int read_lexicon(FILE *vader, struct words **lexicon) {
    // define allocation limit and keep track of size
    int MAX = 7000;
    int SIZE = 0;
    *lexicon = malloc(MAX * sizeof(struct words));
    if (*lexicon == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // define placeholder variables
    char word[MAX_WORD_LENGTH];
    float score;
    float SD;
    int SIS_array[10];

    // fscanf function to scan whole line
    while (fscanf(vader, "%[^\t]\t%f\t%f\t[%d, %d, %d, %d, %d, %d, %d, %d, %d, %d]\n", word, &score, &SD, &SIS_array[0], &SIS_array[1], &SIS_array[2], &SIS_array[3], &SIS_array[4], &SIS_array[5], &SIS_array[6], &SIS_array[7], &SIS_array[8], &SIS_array[9]) == 13) {

        // allocate more memory as needed
        if (SIZE >= MAX) {
            *lexicon = realloc(*lexicon, (MAX * 2) * sizeof(struct words));
            if (*lexicon == NULL) {
                printf("Memory reallocation failed.\n");
                return 1;
            }
            MAX *= 2;
        }

        // allocate enough memory to copy the word
        (*lexicon)[SIZE].word = malloc(strlen(word) + 1);
        if ((*lexicon)[SIZE].word == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }

        // strcpy function to copy word1 to lexicon decimal variable
        strcpy((*lexicon)[SIZE].word, word);
        // set up indexed lexicon variables
        (*lexicon)[SIZE].score = score;
        (*lexicon)[SIZE].SD = SD;

        // since strings aren't mutable, change each character
        for (int i = 0; i < 10; i++) {
            (*lexicon)[SIZE].SIS_array[i] = SIS_array[i];
        }

        // keep track of the size
        SIZE++;
    }

    // return the size of the list
    return SIZE;
}

// function to determine the scores for each sentence
void process_validation(FILE *valid, struct words *lexicon, int SIZE, float arraySol[]) {
    // define needed variables
    // max word length
    char word[MAX_WORD_LENGTH];
    // define delimiters / characters to be removed from token
    char delimiters[] = " ,.!";
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
    while (fscanf(valid, "%s", word) == 1) {
        printf("%s ", word);
        // get token by subtarcing delimiters
        token = strtok(word, delimiters);
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
}

// function to free allocated space
void free_lexicon(struct words *lexicon, int SIZE) {
    for (int i = 0; i < SIZE; i++) {
        free(lexicon[i].word);
    }
    free(lexicon);
}
