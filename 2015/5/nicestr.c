// STANDARD LIBRARY
#include <stdio.h>
#include <string.h>

int nicestring(char *string);
int count_vowels(char *string);
int has_doubles(char *string);
int bad_combos(char *string);

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

    if (
        has_doubles(string)
        && count_vowels(string) > 2
        && !bad_combos(string)
    ) {
        return 1;
    }

    return 0;
}

/**
 * Counts the number of vowels in the provided string.  Returns the
 * number of vowels found or 0 if none were found.
 */
int count_vowels(char *string) {
    const char vowels[6] = {'a', 'e', 'i', 'o', 'u', 0};
    int count = 0;

    for (int i = 0; i < strlen(string); ++i) {
        for (int j = 0; j < strlen(vowels); ++j) {
            if (string[i] == vowels[j])
                count++;
        }
    }

    return count;
}

/**
 * Checks if the given string countains consecutive doubled characters,
 * e.g. aa or bb.  Returns 1 if found or 0 if not.
 */
int has_doubles(char *string) {
    for (int i = 1; i < strlen(string); ++i) {
        if (string[i] == string[i-1])
            return 1;
    }

    return 0;
}

/**
 * Checks if the given string contains any of certain "bad" strings.
 * Returns 1 if found or 0 if not.
 */
int bad_combos(char *string) {
    const char *bads[4] = {"ab", "cd", "pq", "xy"};
    for (int i = 0; i < 4; ++i) {
       if (strstr(string, bads[i]) != NULL)
           return 1;
    }

    return 0;
}

// vim:tw=72
