
/*
 *
 *
 */


#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/random.h>


int main(){
	
	int nran_rec;
	int nran_req;
	char buffer[2];

	nran_rec = 1;
	nran_req = 1;

	int randerr = getentropy(buffer, nran_req);

	printf("nrec: %d\nrand: %u\nnerr: %d\n", nran_rec, buffer[0], randerr);

	return 0;
}
