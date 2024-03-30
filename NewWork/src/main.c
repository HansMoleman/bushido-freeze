
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


void   charToBinary(char* destination, char a_char);
char   binaryToChar(char* binary_rep);
char** doLocalEncrypt();
char** doLocalDecrypt();
void   generateLocalKey();


// MAIN FUNCTION

int main(int argc, char* argv[]){
	char test_key[] = "abcdefghijklmnopabcdefghijklmnop";
	//int  key_length = sizeof(test_key) / sizeof(test_key[0]);
	int key_length = strlen(test_key);
	printf("key-length: %i", key_length);
	char binary_key[(key_length * 9)];
	
	for(int i = 0; i < key_length; i++){
		char bin_val[9];
		charToBinary(bin_val, test_key[i]);
		printf("%s\n", bin_val);
		strcat(binary_key, bin_val);
	}

	printf("%s\n", binary_key);
	int binkey_length = sizeof(binary_key) / sizeof(binary_key[0]);
	int binkey_len = strlen(binary_key);
	printf("size: %i\n", binkey_length);
	printf("size: %i\n", binkey_len);
	
	return 0;
}


void charToBinary(char* destination, char a_char){
	char binary_rep[9];
    int remainders[9];
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
        char digit[2];
        sprintf(digit, "%d", remainders[i]);
        strcat(binary_rep, digit);
    }

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

    strcpy(destination, binary_rep);
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