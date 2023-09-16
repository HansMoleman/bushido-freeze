
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


int main(){

	int buflen = 256;
	int trglen = 64;
	int buffer[buflen];
	char randstr[(trglen * 12)];

	getentropy(buffer, buflen);
	
	for(int i = 0; i < trglen; i++){
		char converted[12];
		sprintf(converted, "%u", buffer[i]);
		strcat(randstr, converted);
	}

	printf("random digits:\n%s\n", randstr);

	return 0;
}

