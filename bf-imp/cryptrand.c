
/** cryptrand.c **
 *
 * CMPL:
 * EXEC:
 * DPND:
 *
 * This module defines functionality for generating cryptography-safe
 * random values for use with the blowfish algorithm.
 *
 * ---
 *  ver.
 * ---
 **/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <unistd.h>
#include "utilities.h"




typedef struct RandManager{
	int  buff_size;
	int  digit_size;
	int  targ_size;
	int* buffer;
	int  num_digits_available;
	int  offset;
} RandManager;


void initRandManager(RandManager* destination);
void fillBuffer(RandManager* randmanager);
void getHexValue(RandManager* randmanager, char destination[], int ndigits);



int main(){

	/*
	int buflen = 256;
	int trglen = 64;
	int buffer[buflen];
	char randstr[(trglen * 12)];

	strcpy(randstr, "");
	getentropy(buffer, buflen);
	
	for(int i = 0; i < trglen; i++){
		char converted[12];
		sprintf(converted, "%u", buffer[i]);
		strcat(randstr, converted);
	}
	
	char hexv[8];
	char dstr[8];
	int  decv;

	strcpy(dstr, "");
	strcpy(hexv, "");
	
	strncat(dstr, &randstr[0], 1);
	strncat(dstr, &randstr[1], 1);
	decv = atoi(dstr);
	printf("dstr: %s -- dint: %d\n", dstr, decv);
	
	decimalToHex(hexv, decv, 2);
	printf("hex: %s, ", hexv);

	decimalToHex(hexv, decv, 4);
	printf("%s\n", hexv);
	*/

	RandManager* randman = (RandManager*) malloc(sizeof(RandManager));
	initRandManager(randman);

	printf("random values:\n");
	fillBuffer(randman);

	for(int i = 0; i < (randman->digit_size * randman->targ_size); i++){
		printf("%u", randman->buffer[i]);

		if(i == (randman->digit_size * randman->targ_size) - 1){
			printf("\n");
		}
	}
	printf("num rand digits:  %d\n", randman->num_digits_available);

	printf("hex value:\n");
	char* hexv = malloc(9 * sizeof(char));
	getHexValue(randman, hexv, 8);
	printf("%s\n", hexv);

	return 0;
}


void initRandManager(RandManager* destination){
	destination->buff_size = 256;
	destination->digit_size = 11;
	destination->targ_size = 64;
	destination->buffer = (int*) malloc((destination->targ_size * destination->digit_size * sizeof(int)) + 1);
	destination->num_digits_available = 0;
	destination->offset = 0;

	for(int i = 0; i < (destination->digit_size * destination->targ_size); i++){
		destination->buffer[i] = 0;
	}
}


void fillBuffer(RandManager* randmanager){
	char* raw_string = (char*) malloc((randmanager->targ_size * randmanager->digit_size * sizeof(char *)));
	int* raw_buffer = (int *) malloc(randmanager->buff_size);
	
	getentropy(raw_buffer, randmanager->buff_size);

	for(int i = 0; i < randmanager->targ_size; i++){
		char converted[randmanager->digit_size];
		strcpy(converted, "");
		sprintf(converted, "%u", raw_buffer[i]);
		strcat(raw_string, converted);
	}

	for(int i = 0; i < strlen(raw_string); i++){
		char digit[2] = "";
		sprintf(digit, "%c", raw_string[i]);
		randmanager->buffer[i] = atoi(digit);
		randmanager->num_digits_available++;
	}

	free(raw_string);
	free(raw_buffer);
}


void getHexValue(RandManager* randmanager, char destination[], int ndigits){
	char* temp_decv;
	int*  digits_fetched;
	int   fetch_count;
	int   decimal_value;

	digits_fetched = (int*) malloc(((ndigits * 2) + 1) * sizeof(int));
	fetch_count = 0;
	for(int i = 0; i < (ndigits * 2); i++){
		int i_targ = randmanager->offset + i;
		digits_fetched[i] = randmanager->buffer[i_targ];
		fetch_count++;
	}
	randmanager->num_digits_available -= fetch_count;
	randmanager->offset += fetch_count;
	printf("fetch-count:  %d\n", fetch_count);
	printf("digits:  ");
	for(int i = 0; i < (ndigits * 2); i++){
		printf("%u", digits_fetched[i]);
	}
	printf("\n");

	temp_decv = (char *) malloc((ndigits + 1) * sizeof(char));
	strcpy(temp_decv, "");
	for(int i = 0; i < fetch_count; i++){
		char digit[2];
		strcpy(digit, "");
		sprintf(digit, "%u", digits_fetched[i]);
		strcat(temp_decv, digit);
	}
	printf("temp_decv:  %s\n", temp_decv);

	decimal_value = atoi(temp_decv);
	printf("decv:  %u\n", decimal_value);
	decimalToHex(destination, decimal_value, ndigits);

	free(digits_fetched);
	free(temp_decv);
}

