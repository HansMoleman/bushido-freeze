
/*
*
*
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LOCALCACHE "local-cache.bin"


void loadPBoxBin(char* destination);
void loadSBoxBin();
void makeSBoxes(char* destination, char* key);
void makePBoxes(char* destination, char* key);
void updateLocalCache(char* sboxes, char* pboxes);



int main(int argc, char* argv[]){

	char local_key[] = "0011111000100110011001010111100001101001010110010111000000111011011101000110111100101110011100110110000001011101001111000111110101100101001001010011111101100011001101100101111101001011001101100101000001110100001110100101010101001110011101100011100101101001";
	char sboxes[((32 * 256 * 4) + 1)];
	char pbox[((18 * 32) + 1)];

	loadPBoxBin(pbox);
	printf("%s\n", pbox);

	return 0;
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