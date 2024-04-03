
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



#include <stdbool.h>
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
void   generateLocalKey(char* destination);


// MAIN FUNCTION

int main(int argc, char* argv[]){
	char random_key[33] = "";
	generateLocalKey(random_key);
	printf("%s\n", random_key);
	
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


void generateLocalKey(char* destination){
	int min_ascii = 33;
	int max_ascii = 126;
	int exclusions[] = {34, 39, 92, 96, 124};
	int rand_ascii[32];

	int rand_value;
	srand(time(NULL));
	for(int i = 0; i < 32; i++){
		rand_value = rand();
		rand_value = (rand_value % (max_ascii - min_ascii)) + min_ascii;

		bool is_good = true;
		for(int i = 0; i < 5; i++){
			if(exclusions[i] == rand_value){
				is_good = false;
			}
		}

		while(!(is_good)){
			rand_value = rand();
			rand_value = (rand_value % (max_ascii - min_ascii)) + min_ascii;

			is_good = true;
			for(int i = 0; i < 5; i++){
				if(exclusions[i] == rand_value){
					is_good = false;
				}
			}
		}
		rand_ascii[i] = rand_value;
	}

	char key_string[33] = "";
	for(int i = 0; i < 32; i++){
		key_string[i] = rand_ascii[i];
	}
	strcat(key_string, "");

	strcpy(destination, key_string);
}


void initLocal(){

	if(!(access(LOCALCACHE, F_OK) == 0)){
		printf("need to build local cache...\n");
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