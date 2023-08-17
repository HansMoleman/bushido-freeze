// Online C compiler to run C program online
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct Token {
    char title[64];
    char descr[256];
    char value[41];
    char expiry[11];
} Token;

Token* newToken(char title[], char descr[], char value[], char expiry[]){
    Token* new_token = (Token*) malloc(sizeof(Token));
    strcpy(new_token->title, title);
    strcpy(new_token->descr, descr);
    strcpy(new_token->value, value);
    strcpy(new_token->expiry, expiry);
    return new_token;
}

void printToken(Token* a_token){
    printf("Name:    %s\n", a_token->title);
    printf("Descr:   %s\n", a_token->descr);
    printf("Value:   %s\n", a_token->value);
    printf("Expires: %s\n", a_token->expiry);
}

int main() {
    // Write C code here
    printf("Creating new token...\n");
    Token* token = newToken("Sample Token", "This is a sample token to demonstrate the token structure.", "ghp_SomEAmouNtoFraNdomChAracteRs123", "09-13-2023");
    
    printToken(token);

    return 0;
}