// STANDARD LIBRARY
#include <stdio.h>
#include <string.h>

// MD5 HASH LIBRARY
#include <openssl/md5.h>

// CONSTANTS
#define MD5_STRING_LENGTH MD5_DIGEST_LENGTH * 2 + 1

// FUNCTIONS
char* md5(char*, char*);

int main(void)
{
    char hash[MD5_STRING_LENGTH];
    char* string = "Hello World";

    printf("md5: %s\n", md5(hash, string));

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

// vim:tw=72
