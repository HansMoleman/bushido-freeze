
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
void blowfishForwards(char* destination, char* pbox, char* sboxes, char* xdata);
void getPBox(char* destination, int index, char* pbox);
void getSBox(char* destination, int box, int index, char* sbox);
void loadPBoxBin(char* destination);
void loadSBoxBin(char* destination);
void makeSBoxes(char* destination, char* key);
void makePBoxes(char* destination, char* key);
void updateLocalCache(char* sboxes, char* pboxes);
void xor(char* xl_new, char* xl, char* pbox_i);



int main(int argc, char* argv[]){

	char local_key[] = "0011111000100110011001010111100001101001010110010111000000111011011101000110111100101110011100110110000001011101001111000111110101100101001001010011111101100011001101100101111101001011001101100101000001110100001110100101010101001110011101100011100101101001";
	char sboxes[((32 * 256 * 4) + 1)] = "";
	char pbox[((18 * 32) + 1)] = "";

	loadPBoxBin(pbox);
	//printf("%s\n", pbox);
	loadSBoxBin(sboxes);
	//printf("%s\n", sboxes);

	char testdata[] = "0011111000100110011001010111100001101001010110010111000000111011";
	char encrdata[65] = "";
	blowfishForwards(encrdata, pbox, sboxes, testdata);

	//char test_l[] = "00111110001001100110010101111000";
	//char test_r[] = "01101001010110010111000000111011";
	//char test_xor[33] = "";
	//xor(test_xor, test_l, test_r);
	//printf("%s\n", test_xor);

	/*
	char pbox_0[33] = "";
	char pbox_8[33] = "";
	char pbox_17[33] = "";
	getPBox(pbox_0, 0, pbox);
	getPBox(pbox_8, 8, pbox);
	getPBox(pbox_17, 17, pbox);
	printf("0: %s\n", pbox_0);
	printf("8: %s\n", pbox_8);
	printf("17: %s\n", pbox_17);
	*/

	/*
	char sbox0_0[33] = "";
	char sbox0_127[33] = "";
	char sbox0_255[33] = "";
	getSBox(sbox0_0, 0, 0, sboxes);
	getSBox(sbox0_127, 0, 127, sboxes);
	getSBox(sbox0_255, 0, 255, sboxes);
	*/

	/*
	char sbox2_0[33] = "";
	char sbox2_127[33] = "";
	char sbox2_255[33] = "";
	getSBox(sbox2_0, 2, 0, sboxes);
	getSBox(sbox2_127, 2, 127, sboxes);
	getSBox(sbox2_255, 2, 255, sboxes);

	printf("2,  %i: %s\n", 0, sbox2_0);
	printf("2,  %i: %s\n", 127, sbox2_127);
	printf("2, %i: %s\n", 255, sbox2_255);
	*/

	//char addend_a[] = "01001000011111001010110001100000";
	//char addend_b[] = "11100110101110100000110110011001";
	//                   00101111001101101011100111111001
	//                 0100101111001101101011100111111001
	//char addmodul[33] = "";
	//addModulo2(addmodul, addend_a, addend_b);
	//printf("modulo 2^32: %s\n", addmodul);


	return 0;
}



void addModulo2(char* destination, char* addend_a, char* addend_b){
	char result[33] = "";
	char carry = '0';
	char digit = '0';

	for(int i = 31; 0 <= i; i--){
		char state[4] = "";
		sprintf(state, "%c%c%c", addend_a[i], addend_b[i], carry);
		printf("%s", state);

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
		printf("%c\n", digit); 

		result[i] = digit;
	}

	strcpy(destination, result);

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

	}
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


void blowfishFunction(char* destination, char* sbox0a, char* sbox1b, char* sbox2c, char* sbox3d, char* xl){
	// yeet
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


void makeSBoxes(char* destination, char* key){
	printf("yeet\n");
}


void makePBoxes(char* destination, char* key){
	printf("yeet\n");
}


void updateLocalCache(char* sboxes, char* pboxes){
	printf("yetet\n");
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