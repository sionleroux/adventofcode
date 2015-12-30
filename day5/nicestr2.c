/* Does the same as the previous one but with different rules */
/* Forgive my creative function naming */

// STANDARD LIBRARY
#include <stdio.h>
#include <string.h>

int nicestring(char *string);
int pairs_recur(char *string);
int has_split_doubles(char *string);

int main(int argc, char *argv[])
{
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    unsigned int count = 0;

    while ((read = getline(&line, &len, stdin)) != -1) {
        if (nicestring(line))
            count++;
    }

    printf("%d\n", count);

    return 0;
}

/**
 * Checks if a given is string is naught or nice based on strange
 * criteria.  Returns 0 for naughty and 1 for nice.
 */
int nicestring(char *string) {

    if (pairs_recur(string) && has_split_doubles(string)) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * Checks if the given string contains non-overlapping recurring pairs
 * of characters e.g. xyxy or aabcdaae. Returns 1 if found or 0 if not.
 */
int pairs_recur(char *string) {
    for (int i = 1; i < strlen(string); ++i) {
        for (int j = i+2; j < strlen(string); ++j) {
            if (string[i] == string[j] && string[i-1] == string[j-1])
                return 1;
        }
    }

    return 0;
}

/**
 * Checks if the given string countains doubled characters, separated by
 * one character e.g. xyx or aaa.  Returns 1 if found or 0 if not.
 */
int has_split_doubles(char *string) {
    for (int i = 2; i < strlen(string); ++i) {
        if (string[i] == string[i-2])
            return 1;
    }

    return 0;
}

// vim:tw=72
