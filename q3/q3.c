#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Maximum size of lines read from file
#define MAX_LINE_SIZE 100
#define MAX_WORDS 1000000

// Define a struct to store a word and its count
typedef struct {
    char* word;
    int count;
} word_count_t;

// Compare function for sorting the word counts in descending order
int compare_word_counts(const void* a, const void* b) {
    const int l = ((const word_count_t*)a)->count;
    const int r = ((const word_count_t*)b)->count;
    return r - l;
}

// Find the n most frequent words in the TensorFlow Shakespeare dataset
char** find_frequent_words(const char* path, int32_t n) {
    // Initialize an array to store the word counts
    word_count_t* word_counts = calloc(MAX_WORDS, sizeof(word_count_t));
    int num_words = 0;

    // Read the file and count the occurrences of each word
    FILE* fp = fopen(path, "r");
    char line[MAX_LINE_SIZE];
    // read one line from the text file
    while (fgets(line, MAX_LINE_SIZE, fp)) {
        // Remove non-alphabetic characters from the line
        for (int i = 0; line[i]; i++) {
            if (!isalpha(line[i])) {
                line[i] = ' ';
            }
        }

        // Split the line according to the provided delimiters
        char* word = strtok(line, " \n");
        while (word != NULL) {
            // Convert the word to lowercase
            for (int i = 0; word[i]; i++) {
                word[i] = tolower(word[i]);
            }

            // Find the word in the array of word counts
            // Reset the word index
            int index = -1;
            for (int i = 0; i < num_words; i++) {
                if (strcmp(word_counts[i].word, word) == 0) {
                    index = i;
                    break;
                }
            }

            // Increment the count of the word or add it to the array of word counts
            if (index >= 0) {
                word_counts[index].count++;
            // Check that the index is within bounds
            } else if (num_words < MAX_WORDS) {
                // duplicate the word
                word_counts[num_words].word = strdup(word);
                word_counts[num_words].count = 1;
                num_words++;
            }

            // Go to the next tokenized word in the line
            word = strtok(NULL, " \n");
        }
    }
    fclose(fp);

    // Sort the array of word counts in descending order and return the n most frequent words
    qsort(word_counts, num_words, sizeof(word_count_t), compare_word_counts);

    // Initializing an array for the top n repeated words
    char** result = calloc(n, sizeof(char*));
    for (int i = 0; i < n && i < num_words; i++) {
        result[i] = word_counts[i].word;
        // Nulling the pointer to make sure it won't get freed twice
        word_counts[i].word = NULL;
    }

    // Free the memory used by the array of word counts
    for (int i = 0; i < num_words; i++) {
        if (word_counts[i].word != NULL) {
            free(word_counts[i].word);
        }
    }
    free(word_counts);

    return result;
}


int main() {
    // Finding the n top words
    int32_t n = 100;
    char** frequent_words = find_frequent_words("shakespeare.txt", n);

    printf("The %d most frequent words in the TensorFlow Shakespeare dataset are:\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d. %s\n", i+1, frequent_words[i]);
        free(frequent_words[i]);
    }

    free(frequent_words);
    return 0;
}
