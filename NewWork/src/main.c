
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
#define LOCALDATA  "local-data.bin"


//void   charToBinary(char* destination, char a_char);
//char   binaryToChar(char* binary_rep);
void   initLocal();

void binaryToToken(char* destination, char* token_binary);
void doLocalEncrypt();
void doLocalDecrypt();
void doTokenExport();
void doTokenImport();
void generateLocalKey(char* destination);
void loadDataCache(char* destination);
void makeDataChunks(char destination[5][65], char* xdata);
void saveDataCache();
void tokenToBinary(char* destination, char* token_characters);

void addModulo2(char* destination, char* addend_a, char* addend_b);
int  binaryToInt(char* binary_rep);
void blowfishBackwards(char* destination, char* pbox, char* sboxes, char* xdata);
void blowfishForwards(char* destination, char* pbox, char* sboxes, char* xdata);
void blowfishFunction(char* destination, char* sbox0a, char* sbox1b, char* sbox2c, char* sbox3d);
void charToBinary(char* destination, char ascii_char);
void getPBox(char* destination, int index, char* pbox);
void getSBox(char* destination, int box, int index, char* sbox);
void loadFromCache(char* pbox_dest, char* sboxes_dest);
void loadPBoxBin(char* destination);
void loadSBoxBin(char* destination);
void makeKeyChunks(char destination[14][33], char* key);
void makePBoxes(char* destination, char* key);
void preparePSBoxes(char* pbox_dest, char* sbox_dest, char* pbox, char* sboxes);
void updateLocalCache(char* pbox, char* sboxes);
void xor(char* xl_new, char* xl, char* pbox_i);


// MAIN FUNCTION

int main(int argc, char* argv[]){
	initLocal();

	char local_pbox[((32 * 18) + 1)] = "";
	char local_sboxes[((32 * 256 * 4) + 1)] = "";
	loadFromCache(local_pbox, local_sboxes);

	/*
	char sample_token[] = "ghp_1gaKhXG02bR4voIGDdllf84CCwvUz30a5jTb";
	char token_binary[((40 * 8) + 1)] = "";
	for(int i = 0; i < strlen(sample_token); i++){
		char binary[9] = "";
		charToBinary(binary, sample_token[i]);
		strcat(token_binary, binary);
	}
	printf("token binary\n%s\n\n", token_binary);
	*/

	if(argc < 2){
		printf("ERROR: insufficient arguments.\n");
	}
	else{

		if(strcmp(argv[1], "update") == 0){
			char user_input[41] = "";
			printf("This operation will overwrite existing token data.\n");
			printf("If you wish to continue enter the new 40-character token, or 'q' to abort operation:\n");
			scanf("%s", user_input);

			if(strcmp(user_input, "q") == 0){
				printf("Operation terminated.\n");
			}
			else{
				char token_binary[((40 * 8) + 1)] = "";
				char token_chunks[5][65];
				char encrypted_data[((5 * 64) + 1)] = "";

				tokenToBinary(token_binary, user_input);
				makeDataChunks(token_chunks, token_binary);

				for(int i = 0; i < 5; i++){
					char encrypted_chunk[65] = "";
					blowfishForwards(encrypted_chunk, local_pbox, local_sboxes, token_chunks[i]);
					strcat(encrypted_data, encrypted_chunk);
				}

				saveDataCache(encrypted_data);
				printf("token successfully updated.\n");
			}
		}
		else if(strcmp(argv[1], "get") == 0){
			char local_data[((64 * 5) + 1)] = "";
			loadDataCache(local_data);

			char encr_chunks[5][65];
			char decr_data[((64 * 5) + 1)] = "";
			makeDataChunks(encr_chunks, local_data);

			for(int i = 0; i < 5; i++){
				char decr_binary[65] = "";
				blowfishBackwards(decr_binary, local_pbox, local_sboxes, encr_chunks[i]);
				strcat(decr_data, decr_binary);
			}

			char token_value[41] = "";
			binaryToToken(token_value, decr_data);
			printf("%s\n", token_value);
		}
		else{
			printf("ERROR: command received is not recognized. Please try again with valid command.\n");
		}
	}
	
	return 0;
}


/*
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
*/

/*
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
*/


void binaryToToken(char* destination, char* token_binary){
	char token_value[41] = "";
	char char_binary[9] = "";
	int  binary_index = 0;
	int  token_index = 0;

	for(int i = 0; i < (40 * 8); i++){
		char_binary[binary_index] = token_binary[i];
		if(binary_index == 7){
			strcat(char_binary, "");
			char character = binaryToInt(char_binary);
			token_value[token_index] = character;
			binary_index = 0;
			token_index++;
		}
		else{
			binary_index++;
		}
	}
	strcat(token_value, "");

	strcpy(destination, token_value);
}


void doLocalEncrypt(){
	printf("local encryption...\n");
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

	/*
	char key_string[33] = "";
	for(int i = 0; i < 32; i++){
		key_string[i] = rand_ascii[i];
	}
	strcat(key_string, "");
	*/

	char key_binary[((32 * 8) + 1)] = "";
	for(int i = 0; i < 32; i++){
		char binary[9] = "";
		charToBinary(binary, rand_ascii[i]);
		strcat(key_binary, binary);
	}

	strcpy(destination, key_binary);
}


void initLocal(){

	if(!(access(LOCALCACHE, F_OK) == 0)){
		char local_key[((32 * 8) + 1)] = "";
		char sboxes[((32 * 256 * 4) + 1)] = "";
		char pbox[((18 * 32) + 1)] = "";

		generateLocalKey(local_key);
		loadSBoxBin(sboxes);
		makePBoxes(pbox, local_key);
		preparePSBoxes(pbox, sboxes, pbox, sboxes);

		updateLocalCache(pbox, sboxes);
	}
	else {
		printf("local cache already exists.\n");
	}
}


void loadDataCache(char* destination){
	char local_data[((64 * 5) + 1)] = "";
	FILE* fptr = fopen(LOCALDATA, "r");

	if(fptr == NULL){
		printf("ERROR: cannot access local-data file.\n");
	}
	else{
		fscanf(fptr, "%s", local_data);
		fclose(fptr);
	}

	strcpy(destination, local_data);
}


void makeDataChunks(char destination[5][65], char* xdata){
	char chunk_array[5][65];
	char chunk_string[65] = "";
	int  chunk_index = 0;
	int  chunk_count = 0;

	for(int i = 0; i < (64 * 5); i++){
		chunk_string[chunk_index] = xdata[i];

		if(chunk_index == 63){
			strcpy(chunk_array[chunk_count], chunk_string);
			strcpy(chunk_string, "");
			chunk_index = 0;
			chunk_count++;
		}
		else{
			chunk_index++;
		}
	}

	for(int i = 0; i < 5; i++){
		strcpy(destination[i], chunk_array[i]);
	}
}


void saveDataCache(char* data_to_write){
	FILE* fptr = fopen(LOCALDATA, "w");
	
	if(fptr == NULL){
		printf("ERROR: could not access local data file.\n");
	}
	else{
		fprintf(fptr, "%s", data_to_write);
		fclose(fptr);
	}
}


void tokenToBinary(char* destination, char* token_characters){
	char token_binary[((40 * 8) + 1)] = "";

	for(int i = 0; i < 40; i++){
		char binary_char[9] = "";
		charToBinary(binary_char, token_characters[i]);
		strcat(token_binary, binary_char);
	}

	strcpy(destination, token_binary);
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


void addModulo2(char* destination, char* addend_a, char* addend_b){
	char result[33] = "";
	char carry = '0';
	char digit = '0';

	for(int i = 31; 0 <= i; i--){
		char state[4] = "";
		sprintf(state, "%c%c%c", addend_a[i], addend_b[i], carry);
		//printf("%s", state);

		if(strcmp(state, "000") == 0){
			digit = '0';
		}
		else if(strcmp(state, "001") == 0){
			digit = '1';
			carry = '0';
		}
		else if(strcmp(state, "010") == 0){
			digit = '1';
		}
		else if(strcmp(state, "011") == 0){
			digit = '0';
			carry = '1';
		}
		else if(strcmp(state, "100") == 0){
			digit = '1';
		}
		else if(strcmp(state, "101") == 0){
			digit = '0';
			carry = '1';
		}
		else if(strcmp(state, "110") == 0){
			digit = '0';
			carry = '1';
		}
		else if(strcmp(state, "111") == 0){
			digit = '1';
			carry = '1';
		}
		else{
			printf("--error--");
		}
		//printf("%c\n", digit); 

		result[i] = digit;
	}

	strcpy(destination, result);

}

int binaryToInt(char* binary_rep){
	int power = 0;
    int sum = 0;
    for(int i = 7; 0 <= i; i--){
        int base = binary_rep[i] - '0';
        sum += (base * (1 << power));
        power++;
    }

    return sum;
}

void blowfishBackwards(char* destination, char* pbox, char* sboxes, char* xdata){
	char xl[33] = "";
	char xr[33] = "";

	for(int i = 0; i < strlen(xdata); i++){
		if(i < 32){
			char chr[2] = "";
			sprintf(chr, "%c", xdata[i]);
			strcat(xl, chr);
		}
		else{
			char chr[2] = "";
			sprintf(chr, "%c", xdata[i]);
			strcat(xr, chr);
		}
	}

	//printf("xl: %s\n", xl);
	//printf("xr: %s\n", xr);
	int p_i = 17;
	for(int i = 0; i < 16; i++){
		char xl_new[33] = "";
		char pbox_i[33] = "";

		getPBox(pbox_i, p_i, pbox);
		xor(xl_new, xl, pbox_i);
		strcpy(xl, xl_new);
		p_i--;

		// get required sub-boxes
		char abin[9] = "";
		char bbin[9] = "";
		char cbin[9] = "";
		char dbin[9] = "";
		for(int j = 0; j < 32; j++){
			if(0 <= j && j < 8){
				// a
				char digit[2] = "";
				sprintf(digit, "%c", xl[j]);
				strcat(abin, digit);
			}
			else if(8 <= j && j < 16){
				// b
				char digit[2] = "";
				sprintf(digit, "%c", xl[j]);
				strcat(bbin, digit);
			}
			else if(16 <= j && j < 24){
				// c
				char digit[2] = "";
				sprintf(digit, "%c", xl[j]);
				strcat(cbin, digit);
			}
			else{
				// d
				char digit[2] = "";
				sprintf(digit, "%c", xl[j]);
				strcat(dbin, digit);
			}
		}
		int aind = binaryToInt(abin);
		int bind = binaryToInt(bbin);
		int cind = binaryToInt(cbin);
		int dind = binaryToInt(dbin);
		
		char sbox0a[33] = "";
		char sbox1b[33] = "";
		char sbox2c[33] = "";
		char sbox3d[33] = "";
		getSBox(sbox0a, 0, aind, sboxes);
		getSBox(sbox1b, 1, bind, sboxes);
		getSBox(sbox2c, 2, cind, sboxes);
		getSBox(sbox3d, 3, dind, sboxes);

		//printf("(0, %i):  %s\n", aind, sbox0a);
		//printf("(1, %i):  %s\n", bind, sbox1b);
		//printf("(2, %i):  %s\n", cind, sbox2c);
		//printf("(3, %i):  %s\n", dind, sbox3d);

		char f_xl[33] = "";
		blowfishFunction(f_xl, sbox0a, sbox1b, sbox2c, sbox3d);
		//printf("%s\n", f_xl);
		char fxl_xor_xr[33] = "";
		xor(fxl_xor_xr, f_xl, xr);
		strcpy(xr, fxl_xor_xr);

		// swap xl & xr
		//printf("\nbefore\n");
		//printf("xl: %s\n", xl);
		//printf("xr: %s\n", xr);
		char temp[33] = "";
		strcpy(temp, xl);
		strcpy(xl, xr);
		strcpy(xr, temp);
		//printf("after\n");
		//printf("xl: %s\n", xl);
		//printf("xr: %s\n", xr);
	}

	// undo last swap
	char temp[33] = "";
	strcpy(temp, xl);
	strcpy(xl, xr);
	strcpy(xr, temp);

	char pbox_1[33] = "";
	char pbox_0[33] = "";
	getPBox(pbox_1, 1, pbox);
	getPBox(pbox_0, 0, pbox);

	char new_xr[33] = "";
	char new_xl[33] = "";
	xor(new_xr, xr, pbox_1);
	xor(new_xl, xl, pbox_0);
	strcpy(xr, new_xr);
	strcpy(xl, new_xl);

	// recombine xl & xr
	char encx[65] = "";
	strcat(encx, xl);
	strcat(encx, xr);

	strcpy(destination, encx);
}

void blowfishForwards(char* destination, char* pbox, char* sboxes, char* xdata){
	char xl[33] = "";
	char xr[33] = "";

	for(int i = 0; i < strlen(xdata); i++){
		if(i < 32){
			char chr[2] = "";
			sprintf(chr, "%c", xdata[i]);
			strcat(xl, chr);
		}
		else{
			char chr[2] = "";
			sprintf(chr, "%c", xdata[i]);
			strcat(xr, chr);
		}
	}

	//printf("xl: %s\n", xl);
	//printf("xr: %s\n", xr);
	for(int i = 0; i < 16; i++){
		char xl_new[33] = "";
		char pbox_i[33] = "";

		getPBox(pbox_i, i, pbox);
		xor(xl_new, xl, pbox_i);
		strcpy(xl, xl_new);

		// get required sub-boxes
		char abin[9] = "";
		char bbin[9] = "";
		char cbin[9] = "";
		char dbin[9] = "";
		for(int j = 0; j < 32; j++){
			if(0 <= j && j < 8){
				// a
				char digit[2] = "";
				sprintf(digit, "%c", xl[j]);
				strcat(abin, digit);
			}
			else if(8 <= j && j < 16){
				// b
				char digit[2] = "";
				sprintf(digit, "%c", xl[j]);
				strcat(bbin, digit);
			}
			else if(16 <= j && j < 24){
				// c
				char digit[2] = "";
				sprintf(digit, "%c", xl[j]);
				strcat(cbin, digit);
			}
			else{
				// d
				char digit[2] = "";
				sprintf(digit, "%c", xl[j]);
				strcat(dbin, digit);
			}
		}
		int aind = binaryToInt(abin);
		int bind = binaryToInt(bbin);
		int cind = binaryToInt(cbin);
		int dind = binaryToInt(dbin);
		
		char sbox0a[33] = "";
		char sbox1b[33] = "";
		char sbox2c[33] = "";
		char sbox3d[33] = "";
		getSBox(sbox0a, 0, aind, sboxes);
		getSBox(sbox1b, 1, bind, sboxes);
		getSBox(sbox2c, 2, cind, sboxes);
		getSBox(sbox3d, 3, dind, sboxes);

		//printf("(0, %i):  %s\n", aind, sbox0a);
		//printf("(1, %i):  %s\n", bind, sbox1b);
		//printf("(2, %i):  %s\n", cind, sbox2c);
		//printf("(3, %i):  %s\n", dind, sbox3d);

		char f_xl[33] = "";
		blowfishFunction(f_xl, sbox0a, sbox1b, sbox2c, sbox3d);
		//printf("%s\n", f_xl);
		char fxl_xor_xr[33] = "";
		xor(fxl_xor_xr, f_xl, xr);
		strcpy(xr, fxl_xor_xr);

		// swap xl & xr
		//printf("\nbefore\n");
		//printf("xl: %s\n", xl);
		//printf("xr: %s\n", xr);
		char temp[33] = "";
		strcpy(temp, xl);
		strcpy(xl, xr);
		strcpy(xr, temp);
		//printf("after\n");
		//printf("xl: %s\n", xl);
		//printf("xr: %s\n", xr);
	}

	// undo last swap
	char temp[33] = "";
	strcpy(temp, xl);
	strcpy(xl, xr);
	strcpy(xr, temp);

	char pbox_16[33] = "";
	char pbox_17[33] = "";
	getPBox(pbox_16, 16, pbox);
	getPBox(pbox_17, 17, pbox);

	char new_xr[33] = "";
	char new_xl[33] = "";
	xor(new_xr, xr, pbox_16);
	xor(new_xl, xl, pbox_17);
	strcpy(xr, new_xr);
	strcpy(xl, new_xl);

	// recombine xl & xr
	char encx[65] = "";
	strcat(encx, xl);
	strcat(encx, xr);

	strcpy(destination, encx);
}

void blowfishFunction(char* destination, char* sbox0a, char* sbox1b, char* sbox2c, char* sbox3d){
	char sbox0_mod_sbox1[33] = "";
	char sbox0m1_xor_sbox2[33] = "";
	char sbox0m1xor2_mod_sbox3[33] = "";

	addModulo2(sbox0_mod_sbox1, sbox0a, sbox1b);
	xor(sbox0m1_xor_sbox2, sbox0_mod_sbox1, sbox2c);
	addModulo2(sbox0m1xor2_mod_sbox3, sbox0m1_xor_sbox2, sbox3d);

	strcpy(destination, sbox0m1xor2_mod_sbox3);
}

void charToBinary(char* destination, char ascii_char){
    char binary_rep[9] = "";
    int remainders[9];
    int quotient = ascii_char;
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

    int binstr_len = 0;
    char target = binary_rep[binstr_len];
    while(target != '\0'){
        binstr_len++;
        target = binary_rep[binstr_len];
    }

    while(binstr_len < 8){
        char tempstr[9] = "";
        tempstr[0] = '0';
        strcat(tempstr, binary_rep);
        strcpy(binary_rep, tempstr);
        binstr_len++;
    }

    strcpy(destination, binary_rep);
}

void getPBox(char* destination, int index, char* pbox){
	char pbox_i[33] = "";
	int start = (index * 32);
	int finish = (start + 32);

	for(int i = start; i < finish; i++){
		char digit[2] = "";
		sprintf(digit, "%c", pbox[i]);
		strcat(pbox_i, digit);
	}

	//printf("pbox-%i: %s\n", index, pbox_i);
	strcpy(destination, pbox_i);
}

void getSBox(char* destination, int box, int index, char* sbox){
	char sbox_i[33] = "";
	int  start  = ((box * (32 * 256)) + (index * 32));
	int  finish = (start + 32);

	for(int i = start; i < finish; i++){
		char digit[2] = "";
		sprintf(digit, "%c", sbox[i]);
		strcat(sbox_i, digit);
	}

	strcpy(destination, sbox_i);
}

void loadFromCache(char* pbox_dest, char* sboxes_dest){
	char pbox[((32 * 18) + 1)] = "";
	char sbox[((32 * 256 * 4) + 1)] = "";
	char str_in[((32 * 18) + (32 * 256 * 4) + 1)] = "";
	FILE* fptr;

	fptr = fopen(LOCALCACHE, "r");
	if(fptr == NULL){
		printf("ERROR: local-cache file not found!\n");
	}
	else{
		fscanf(fptr, "%s", str_in);
		strcat(str_in, "");
		fclose(fptr);
	}

	for(int i = 0; i < (32 * 18); i++){
		pbox[i] = str_in[i];
		if(i == ((32 * 18) - 1)){
			pbox[(i + 1)] = '\0';
		}
	}

	for(int i = (32 * 18); i < ((32 * 256 * 4) + (32 * 18)); i++){
		int si = (i - (32 * 18));
		sbox[si] = str_in[i];

		if(i == ((32 * 256 * 4) - 1)){
			sbox[(si + 1)] = '\0';
		}
	}

	strcpy(pbox_dest, pbox);
	strcpy(sboxes_dest, sbox);
}

void loadSBoxBin(char* destination){
	char sbox1path[] = "Pi/bin/sbox1.bin";
	char sbox2path[] = "Pi/bin/sbox2.bin";
	char sbox3path[] = "Pi/bin/sbox3.bin";
	char sbox4path[] = "Pi/bin/sbox4.bin";
	char sbox1vals[((32 * 256) + 1)] = "";
	char sbox2vals[((32 * 256) + 1)] = "";
	char sbox3vals[((32 * 256) + 1)] = "";
	char sbox4vals[((32 * 256) + 1)] = "";
	char sboxes[((32 * 256 * 4) + 1)] = "";
	FILE* fptr;

	if((fptr = fopen(sbox1path, "r")) == NULL){
		printf("ERROR");
	}
	else {
		fscanf(fptr, "%s", sbox1vals);
		fclose(fptr);
	}

	if((fptr = fopen(sbox2path, "r")) == NULL){
		printf("ERROR");
	}
	else {
		fscanf(fptr, "%s", sbox2vals);
		fclose(fptr);
	}

	if((fptr = fopen(sbox3path, "r")) == NULL){
		printf("ERROR");
	}
	else {
		fscanf(fptr, "%s", sbox3vals);
		fclose(fptr);
	}

	if((fptr = fopen(sbox4path, "r")) == NULL){
		printf("ERROR");
	}
	else {
		fscanf(fptr, "%s", sbox4vals);
		fclose(fptr);
	}

	strcat(sboxes, sbox1vals);
	strcat(sboxes, sbox2vals);
	strcat(sboxes, sbox3vals);
	strcat(sboxes, sbox4vals);
	strcpy(destination, sboxes);
}

void loadPBoxBin(char* destination){
	char filepath[] = "Pi/bin/pbox.bin";
	char pvalues[((18 * 32) + 1)] = "";

	FILE* fptr = fopen(filepath, "r");

	if(fptr == NULL){
		printf("ERROR: could not load file.\n");
	}
	else {
		fscanf(fptr, "%s", pvalues);
		fclose(fptr);
		strcpy(destination, pvalues);
	}
}

void makeKeyChunks(char destination[14][33], char* key){
	char key_chunks[14][33];
	int  key_length = strlen(key);
	int  digit_counter = 0;
	int  chunk_counter = 0;

	for(int i = 0; i < 14; i++){
		strcpy(key_chunks[i], "");
	}

	for(int i = 0; i < key_length; i++){
		char digit = key[i];
		key_chunks[chunk_counter][digit_counter] = digit;
		//printf("chunk: %i, digit: %i, value: %c\n", chunk_counter, digit_counter, digit);

		if(digit_counter == 31){
			key_chunks[chunk_counter][(digit_counter + 1)] = '\0';
			chunk_counter++;
			digit_counter = 0;
		}
		else{
			digit_counter++;
		}
	}

	for(int i = 0; i < 14; i++){
		//printf("%i:  %s\n", i, key_chunks[i]);
		strcpy(destination[i], key_chunks[i]);
	}
}

void makePBoxes(char* destination, char* key){
	char key_chunks[14][33];
	char pbox_bin[((32 * 18) + 1)] = "";
	char new_pboxes[((32 * 18) + 1)] = "";
	int  targ_chunk = 0;

	loadPBoxBin(pbox_bin);
	makeKeyChunks(key_chunks, key);

	for(int i = 0; i < 18; i++){
		char chunk[33] = "";
		strcpy(chunk, key_chunks[targ_chunk]);
		if(strcmp(key_chunks[(targ_chunk + 1)], "") == 0){
			targ_chunk = 0;
		}
		else{
			targ_chunk++;
		}

		char pbox_i[33] = "";
		getPBox(pbox_i, i, pbox_bin);
		char pbox_xor_chunk[33] = "";
		xor(pbox_xor_chunk, pbox_i, chunk);
		strcat(new_pboxes, pbox_xor_chunk);
		//printf("Pi: %s\nKi: %s\nPk: %s\n", pbox_i, chunk, pbox_xor_chunk);
	}

	strcpy(destination, new_pboxes);
}

void preparePSBoxes(char* pbox_dest, char* sbox_dest, char* pbox, char* sboxes){
	char zero_string[65] = "";
	for(int i = 0; i < 64; i++){
		zero_string[i] = '0';
	}
	zero_string[64] = '\0';

	char pbox_new[((32 * 18) + 1)] = "";
	char sbox_new[((32 * 256 * 4) + 1)] = "";
	strcpy(pbox_new, pbox);
	strcpy(sbox_new, sboxes);
	//printf("before\n%s\n", pbox_new);

	char x_encr[65] = "";
	blowfishForwards(x_encr, pbox_new, sbox_new, zero_string);

	// do p-boxes
	for(int i = 0; i < 9; i++){
		int start_i = (64 * i);
		int finsh_i = (start_i + 64);
		int counter = 0;
		for(int j = start_i; j < finsh_i; j++){
			pbox_new[j] = x_encr[counter];
			counter++;
		}

		char new_xencr[65] = "";
		strcpy(new_xencr, x_encr);
		blowfishForwards(x_encr, pbox_new, sbox_new, new_xencr);
	}
	//printf("after\n%s\n", pbox_new);

	// do s-boxes
	//printf("sbox-before\n%s\n", sbox_new);
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < (256 / 2); j++){
			int start_j = (i * 256) + (j * 64);
			int finsh_j = (start_j + 64);
			int counter = 0;
			for(int k = start_j; k < finsh_j; k++){
				sbox_new[k] = x_encr[counter];
				counter++;
			}

			char new_xencr[65] = "";
			strcpy(new_xencr, x_encr);
			blowfishForwards(x_encr, pbox_new, sbox_new, new_xencr);
		}
	}
	//printf("sbox-after\n%s\n", sbox_new);

	strcpy(pbox_dest, pbox_new);
	strcpy(sbox_dest, sbox_new);
}

void updateLocalCache(char* pbox, char* sboxes){
	// write pbox chunk, then sboxes chunk, to file
	//int pbox_size = (32 * 18);
	//int sbox_size = (32 * 256 * 4);
	char str_out[((32 * 18) + (32 * 256 * 4) + 1)] = "";
	FILE* fptr;

	strcpy(str_out, pbox);
	strcat(str_out, sboxes);

	fptr = fopen(LOCALCACHE, "w");

	if(fptr == NULL){
		printf("ERROR: local-cache file not found!\n");
	}
	else{
		fprintf(fptr, "%s", str_out);
		fclose(fptr);
	}
}

void xor(char* xl_new, char* xl, char* pbox_i){
	int xlen = strlen(xl);
	char xorv[33] = "";

	for(int i = 0; i < xlen; i++){
		if(xl[i] == pbox_i[i]){
			char digit[2] = "0";
			strcat(xorv, digit);
		}
		else{
			char digit[2] = "1";
			strcat(xorv, digit);
		}
	}

	strcpy(xl_new, xorv);
}