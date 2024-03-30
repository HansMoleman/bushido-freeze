
/** main.c  ***
 *
 * CMPL:  gcc main.c -Wall -o ghpat
 * EXEC:  ./ghpat
 * DEPN:  none
 *
 * (description)
 *
 * ---
 *  ver-0.0.0  |  (c) 03.28.2024 (GPL-3)
 * ---
 **/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


#define LOCALCACHE "local-cache.bin"


void   charToBinary(char* destination, char a_char);
char   binaryToChar(char* binary_rep);

void   initLocal();

char** doLocalEncrypt();
char** doLocalDecrypt();
void   generateLocalKey();


// MAIN FUNCTION

int main(int argc, char* argv[]){
	initLocal();
	
	return 0;
}


void charToBinary(char* destination, char a_char){
	char binary_rep[9] = "";
    int remainders[8];
    int quotient = a_char;
    int remainder = 0;
    int count = 0;

    while(quotient > 0){
        remainder = quotient % 2;
        quotient = quotient / 2;
        remainders[count] = remainder;
        count++;
    }

    for(int i = (count - 1); 0 <= i; i--){
        char digit[2] = "";
        sprintf(digit, "%d", remainders[i]);
        strcat(binary_rep, digit);
    }
    //printf("bin_rep: %s\n", binary_rep);

    /*
    int binstr_len = 0;
    char target = binary_rep[binstr_len];
    while(target != '\0'){
        binstr_len++;
        target = binary_rep[binstr_len];
    }

    //printf("%i\n", binstr_len);
    while(binstr_len < 8){
        char tempstr[9];
        tempstr[0] = '0';
        strcat(tempstr, binary_rep);
        strcpy(binary_rep, tempstr);
        binstr_len++;
    }
    */

    int binstr_len = strlen(binary_rep);
    while(binstr_len < 8){
    	char tempstr[9] = "0";
    	strcat(tempstr, binary_rep);
    	strcpy(binary_rep, tempstr);
    	binstr_len = strlen(binary_rep);
    }

    //printf("pre-copy\n");
    strcpy(destination, binary_rep);
    //printf("post-copy\n");
}


char  binaryToChar(char* binary_rep){
	int power = 0;
    int sum = 0;
    for(int i = 7; 0 <= i; i--){
        int base = binary_rep[i] - '0';
        sum += (base * (1 << power));
        power++;
    }

    char ascii = sum;
    return ascii;
}


void initLocal(){
	//char filepath[] = "local-cache.bin";
	char chb[9] = "";
	int min_ascii = 33;
	int max_ascii = 126;

	if(!(access(LOCALCACHE, F_OK) == 0)){
		int rand_ascii[32];
		int randv;

		srand(time(NULL));
		for(int i = 0; i < 32; i++){
			randv = rand();
			//printf("%i\n", randv);
			randv = (randv % (max_ascii - min_ascii)) + min_ascii;
			rand_ascii[i] = randv;
		}

		printf("\n");
		int  rsize = sizeof(rand_ascii) / sizeof(rand_ascii[0]);
		char key[33] = "";
		char bin[((32 * 8) + 1)] = "";
		for(int j = 0; j < rsize; j++){
			strcpy(chb, "");
			//printf("%s\n", chb);
			char chr = rand_ascii[j];
			//printf("%c\n", chr);
			charToBinary(chb, chr);
			//printf("%s\n", chb);
			printf("%i -> %c -> %s\n", rand_ascii[j], chr, chb);
			char chr_str[2] = "";
			sprintf(chr_str, "%c", chr);
			strcat(key, chr_str);
			strcat(bin, chb);
		}

		printf("key: %s\n", key);
		printf("bin: %s\n", bin);

		FILE* fptr = fopen(LOCALCACHE, "w");
		fprintf(fptr, "%s\n", bin);
		fclose(fptr);
	}
	else {
		printf("local cache already exists.\n");
	}
}


/*

##### Main Success Scenario

1. User prompts system to update the stored token value.
2. System requests new token value from the user.
3. User enters the new token value and submits it to the system. [Exc-1: submission is an unexpected length]
4. System loads key data stored in local storage.
5. System uses key data to encrypt the new token data.
6. System writes new encrypted token data to local storage, overwriting (any) previous token data.
7. System confirms operation has completed successfully and then exits.

*/

/*
char** doLocalEncrypt() {
}
*/