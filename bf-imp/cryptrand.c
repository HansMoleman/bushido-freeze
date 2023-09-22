
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



int main(){

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

	return 0;
}

