
/** utilities.c **
 *
 * CMPL:
 * EXEC:
 * DEPN:
 *
 * (descr.)
 *
 * ---
 *  ver.
 * ---
 **/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void decimalToHex(char destination[], int decimal_value, int num_hex_digits){
	int  quotient;
	int  remainder;
	char tmpvalue[(num_hex_digits + 1)];
	char hexvalue[(num_hex_digits + 1)];

	// initialize strings and int vals
	strcpy(tmpvalue, "");
	strcpy(hexvalue, "");
	quotient = decimal_value / 16;
	remainder = decimal_value % 16;

	while(!((quotient == 0) && (remainder == 0))){
		char hexd[2];
		strcpy(hexd, "");

		if(remainder == 10){
			strcpy(hexd, "A");
		}
		else if(remainder == 11){
			strcpy(hexd, "B");
		}
		else if(remainder == 12){
			strcpy(hexd, "C");
		}
		else if(remainder == 13){
			strcpy(hexd, "D");
		}
		else if(remainder == 14){
			strcpy(hexd, "E");
		}
		else if(remainder == 15){
			strcpy(hexd, "F");
		}
		else{
			sprintf(hexd, "%d", remainder);
		}

		strcat(tmpvalue, hexd);
		remainder = quotient % 16;
		quotient  = quotient / 16;
	}

	if(strlen(tmpvalue) < num_hex_digits){
		while(strlen(tmpvalue) < num_hex_digits){
			strcat(tmpvalue, "0");
		}
	}
	strcat(tmpvalue, "\0");
	
	for(int i = (strlen(tmpvalue) - 1); 0 <= i; i--){
		strncat(hexvalue, &tmpvalue[i], 1);
	}

	strcpy(destination, hexvalue);
}

