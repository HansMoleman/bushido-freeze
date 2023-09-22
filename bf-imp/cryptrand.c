
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


void decimalToHex(char destination[], int decimal_val);


int main(){

	int buflen = 256;
	int trglen = 64;
	int buffer[buflen];
	char randstr[(trglen * 12)];
	int  numhex = (strlen(randstr) / 2) + 2;
	//char hexvals[numhex][3];

	strcpy(randstr, "");
	getentropy(buffer, buflen);
	
	for(int i = 0; i < trglen; i++){
		char converted[12];
		sprintf(converted, "%u", buffer[i]);
		strcat(randstr, converted);

		//printf("%d >  %s\n", i, randstr);

		if(i == 0) {
			printf("%s\n", converted);
			int clen = strlen(converted);
			char cstr[3];
			
			printf(" str  --  char\n");
			printf("-----    ------\n");
			for(int j = 0; j < clen; j++){
				sprintf(cstr, "%c", converted[j]);
				printf("  %s         %c\n", cstr, converted[j]);
			}
		}
	}

	/*
	int hexcnt = 0;
	for(int i = 0; i < numhex; i += 2){
		char decv[3];
		strcat(decv, randstr[i]);
		strcat(decv, randstr[i+1]);
		strcpy(hexvals[i], decv);
		hexcnt++;
	}

	int hsize = sizeof(hexvals[0]) / sizeof(hexvals[0][0]);
	for(int i = 0; i < hsize; i++){
		printf("%d:  %s\n", i, hexvals[i]);
	}
	*/

	printf("randstr[0:10]:  ");
	for(int i = 0; i < 10; i++){
		printf("%c", randstr[i]);
		if(i == 9){
			printf("\n");
		}
	}
	
	char dig1;
	char dig2;
	dig1 = (char) randstr[0];
	dig2 = (char) randstr[1];
	printf(">> %c%c\n", dig1, dig2);

	/*
	char char1[2];
	char char2[2];
	sprintf(char1, "%d", dig1);
	sprintf(char2, "%d", dig2);
	strcat(rawv, char1);
	strcat(rawv, char2);
	printf("raw: %s\n", rawv);
	*/
	
	char hexv[8];
	char dstr[8];
	int  decv;

	strcpy(dstr, "");
	strcpy(hexv, "");
	
	printf("<A>\n");
	strncat(dstr, &randstr[0], 1);
	printf("dstr:  %s\n", dstr);
	printf("<B>\n");
	strncat(dstr, &randstr[1], 1);
	printf("<C>\n");
	decv = atoi(dstr);
	printf("<D>\n");
	printf("dstr: %s -- dint: %d\n", dstr, decv);
	printf("<E>\n");
	
	decimalToHex(hexv, decv);

	if(strlen(hexv) == 1){
		hexv[1] = hexv[0];
		hexv[0] = '0';
	}

	printf("hex: %s\n", hexv);

	return 0;
}


void decimalToHex(char destination[], int decimal_val){
	int  quo;
	int  rem;
	char temp[3] = "";
	char hexv[3] = "";

	printf("decv:  %d\n", decimal_val);

	strcpy(temp, "");
	strcpy(hexv, "");
	quo = decimal_val / 16;
	rem = decimal_val % 16;
	
	while(!((quo == 0) && (rem == 0))){
		char hexd[2] = "";
		
		if(rem == 10){
			//hexd = 'A';
			strcpy(hexd, "A");
		}
		else if(rem == 11){
			//hexd = 'B';
			strcpy(hexd, "B");
		}
		else if(rem == 12){
			//hexd = 'C';
			strcpy(hexd, "C");
		}
		else if(rem == 13){
			//hexd = 'D';
			strcpy(hexd, "D");
		}
		else if(rem == 14){
			//hexd = 'E';
			strcpy(hexd, "E");
		}
		else if(rem == 15){
			//hexd = 'F';
			strcpy(hexd, "F");
		}
		else {
			sprintf(hexd, "%d", rem);
			printf("(hexd): %s\n", hexd);
		}

		strcat(temp, hexd);
		rem = quo % 16;
		quo = quo / 16;
	}

	if(strlen(temp) == 1){
		strcat(temp, "0\0");
	}
	else{
		strcat(temp, "\0");
	}

	int hexc = 0;
	for(int i = (strlen(temp) - 1); 0 <= i; i--){
		strncat(hexv, &temp[i], 1);
		printf("<%d>:  %s\n", i, hexv);
		hexc++;
	}

	printf("hexv:  %s\n\n", hexv);
	strcpy(destination, hexv);
}

