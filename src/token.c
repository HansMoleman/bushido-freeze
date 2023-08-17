
/*** token.c
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


#include <stdlib.h>
#include <stdio.h>
#include <string.h>



typedef struct Token {
    char title[64];
    char descr[256];
    char value[41];
    char expiry[11];
} Token;



/**
 * METHODS
 */

Token* loadToken(){
    printf("<< load token >>\n");
}


Token* newToken(char title[], char descr[], char value[], char expiry[]){
    Token* new_token = (Token*) malloc(sizeof(Token));
    strcpy(new_token->title, title);
    strcpy(new_token->descr, descr);
    strcpy(new_token->value, value);
    strcpy(new_token->expiry, expiry);
    return new_token;
}


void saveToken(){
    printf("<< save token >>\n");
}

void printToken(Token* a_token){
    printf("Name:    %s\n", a_token->title);
    printf("Descr:   %s\n", a_token->descr);
    printf("Value:   %s\n", a_token->value);
    printf("Expires: %s\n", a_token->expiry);
}