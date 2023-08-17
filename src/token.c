
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


const char VAL_PATH[] = "valudata.bin";
//const char MET_PATH = "metadata.bin";



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
    FILE* fptr_val = fopen(VAL_PATH, "rb");

    if(fptr_val == NULL){
        Token* null_token = (Token*) NULL;
        return null_token;
    }
    else{
        char tvalue[41];
        fread(&tvalue, sizeof(tvalue), 1, fptr_val);
        fclose(fptr_val);

        Token* new_token = (Token*) malloc(sizeof(Token));
        strcpy(new_token->value, tvalue);
        return new_token;
    }
}


Token* newToken(char title[], char descr[], char value[], char expiry[]){
    Token* new_token = (Token*) malloc(sizeof(Token));
    strcpy(new_token->title, title);
    strcpy(new_token->descr, descr);
    strcpy(new_token->value, value);
    strcpy(new_token->expiry, expiry);
    return new_token;
}


void saveToken(Token* a_token){
    FILE* fptr_val = fopen(VAL_PATH, "wb");

    if (fptr_val == NULL){
        printf("ERROR: cannot open token value file.\n");
    }
    else{
        char tvalue[41];
        strcpy(tvalue, a_token->value);
        fwrite(&tvalue, sizeof(tvalue), 1, fptr_val);
        fclose(fptr_val);
    }
}


void printToken(Token* a_token){
    printf("Name:    %s\n", a_token->title);
    printf("Descr:   %s\n", a_token->descr);
    printf("Value:   %s\n", a_token->value);
    printf("Expires: %s\n", a_token->expiry);
}



int main(int argc, char* argv[]){
    //Token* test_token = newToken("", "", "ghp_this4is?a8sample_authorization!token", "");

    // save
    //saveToken(test_token);
    //printf("Test token registered.\n");

    // load
    Token* test_token;
    test_token = loadToken();
    printf("%s\n", test_token->value);

    return 0;
}