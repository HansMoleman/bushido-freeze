
/*** token.h
 * 
 * CMPL:
 * EXEC:
 * DEPN:
 * 
 * ...
 * 
 * ---
 *  ver
 * ---
 */


#ifndef token
#define token

typedef struct Token {
    char title[64];
    char descr[256];
    char value[41];
    char expiry[11];
} Token;


Token* loadToken();
Token* newToken(char title[], char descr[], char value[], char expiry[]);
void saveToken(Token* a_token);
void printToken(Token* a_token);

#endif