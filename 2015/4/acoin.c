// STANDARD LIBRARY
#include <stdio.h>
#include <string.h>

// MD5 HASH LIBRARY
#include <openssl/md5.h>

// CONSTANTS
#define MD5_STRING_LENGTH MD5_DIGEST_LENGTH * 2 + 1
#define KEY "iwrupvqb"

// FUNCTIONS
char* md5(char*, char*);
char* chop(char*, char*);
char* numcat(char*, char*, unsigned int);

int main(void)
{
    char hash[MD5_STRING_LENGTH];
    char s[6];
    char key[17];
    unsigned int c = 0;

    while (strcmp( "000000", chop(s, md5(hash, numcat(key, KEY, c)))) != 0) {
        c++;
    }

    printf("num: %d\nmd5: %s\n", c, md5(hash, key));

    return 0;
}

/**
 * Wrapper for fancy OpenSSL MD5 hash function because my needs are much
 * simple.  I don't really need contexts and buffers and stuff because I
 * just need to hash a short string.
 * Returns the MD5 hash as a hex string!!!
 * Expects a string to store the hex string in and a string to hash.
 */
char* md5(char *md5string, char *instring)
{
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5_CTX context;

    MD5_Init(&context);
    MD5_Update(&context, instring, strlen(instring));
    MD5_Final(digest, &context);

    for(int i = 0; i < MD5_DIGEST_LENGTH; ++i)
        sprintf(&md5string[i*2], "%02x", (unsigned int)digest[i]);

    return md5string;
}

/**
 * Chops off everything after the first 5 characters of a string.
 */
char* chop(char *shortstring, char *md5string) {
    strncpy(shortstring, md5string, 6);
    shortstring[6] = '\0';
    return shortstring;
}

/**
 * Appends an unsigned integer number to the end of a string and returns
 * the result.
 */
char* numcat(char *target, char *string, unsigned int number) {
    sprintf(target, "%s%d", string, number);
    return target;
}

// vim:tw=72
