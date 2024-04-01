
/*
*
*
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LOCALCACHE "local-cache.bin"


void addModulo2(char* destination, char* addend_a, char* addend_b);
int  binaryToInt(char* binary_rep);
void blowfishBackwards(char* destination, char* pbox, char* sboxes, char* xdata);
void blowfishForwards(char* destination, char* pbox, char* sboxes, char* xdata);
void blowfishFunction(char* destination, char* sbox0a, char* sbox1b, char* sbox2c, char* sbox3d);
void getPBox(char* destination, int index, char* pbox);
void getSBox(char* destination, int box, int index, char* sbox);
void loadFromCache(char* pbox_dest, char* sboxes_dest);
void loadPBoxBin(char* destination);
void loadSBoxBin(char* destination);
void makeKeyChunks(char destination[14][33], char* key);
//void makeSBoxes(char* destination, char* key);
void makePBoxes(char* destination, char* key);
void preparePSBoxes(char* pbox_dest, char* sbox_dest, char* pbox, char* sboxes);
void updateLocalCache(char* pbox, char* sboxes);
void xor(char* xl_new, char* xl, char* pbox_i);



int main(int argc, char* argv[]){

	char local_key[] = "0011111000100110011001010111100001101001010110010111000000111011011101000110111100101110011100110110000001011101001111000111110101100101001001010011111101100011001101100101111101001011001101100101000001110100001110100101010101001110011101100011100101101001";
	char sboxes[((32 * 256 * 4) + 1)] = "";
	char pbox[((18 * 32) + 1)] = "";

	loadSBoxBin(sboxes);
	makePBoxes(pbox, local_key);
	//char pbox_ready[((18 * 32) + 1)] = "";
	//char sbox_ready[((32 * 256 * 4) + 1)] = "";
	preparePSBoxes(pbox, sboxes, pbox, sboxes);

	//updateLocalCache(pbox, sboxes);
	//printf("local-cache updated.\n");
	loadFromCache(pbox, sboxes);
	printf("\nloaded local-cache.\n");

	//char testdata[] = "0011111000100110011001010111100001101001010110010111000000111011";
	//char encrdata[65] = "";
	//char decrdata[65] = "";
	//blowfishForwards(encrdata, pbox, sboxes, testdata);
	//printf("%s\n", encrdata);

	//blowfishBackwards(decrdata, pbox, sboxes, encrdata);

	//printf("xdata: %s\n", testdata);
	//printf("xdecr: %s\n", decrdata);

	//blowfishForwards(encrdata, pbox, sboxes, testdata);
	//printf("%s\n", encrdata);

	//char pbox_key[449] = "";
	//char key_chunks[14][33];
	//char** chunks = key_chunks;
	//makeKeyChunks(key_chunks, local_key);

	//char pbox_key[((32 * 18) + 1)] = "";
	//makePBoxes(pbox_key, local_key);
	
	//char pbox_new[((32 * 18) + 1)] = "";
	//char sbox_new[((32 * 265 * 4) + 1)] = "";
	//preparePSBoxes(pbox_new, sbox_new, pbox_key, sboxes);


	return 0;
}



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


/*
void makeSBoxes(char* destination, char* key){
	char key_chunks[14][33];
	char sbox_bin[((32 * 256 * 4) + 1)] = "";
	char new_sboxes[((32 * 256 * 4) + 1)] = "";
	int  targ_chunk = 0;

	loadSBoxBin(sbox_bin);
	makeKeyChunks(key_chunks, key);

	int box_num = 0;
	int ind_num = 0;
	for(int i = 0; i < box_num; i++){
		for(int j = 0; j < ind_num; j++){
			char chunk[33] = "";
			strcpy(chunk, key_chunks[targ_chunk]);
			if(strcmp(key_chunks[(targ_chunk + 1)], "") == 0){
				targ_chunk = 0;
			}
			else{
				targ_chunk++;
			}

			char sbox_i_j[33] = "";
			getSBox(sbox_i_j, i, j, sbox_bin);
			char sbox_xor_chunk[33] = "";
			xor(sbox_xor_chunk, sbox_i_j, chunk);
		}
	}
}
*/

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