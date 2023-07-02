
/** ghpat.c  ***
 *
 * CMPL:  gcc ghpat.c -Wall -o ghpat
 * EXEC:  ./ghpat
 * DEPN:  none
 *
 * (description)
 *
 * ---
 *  ver-0.0.0  |  (c) 07.02.2023 (GPL-3)
 * ---
 **/

#include<stdio.h>
#include<unistd.h>



int main(int argc, char* argv[]){
	int   tkn_size = 40;
	char  value[(tkn_size + 1)];
	char* fpath = "data.txt";

	if (access(fpath, F_OK) == 0){
		// read in existing token
		FILE* file_ptr;
		file_ptr = fopen(fpath, "r");
		fgets(value, (tkn_size + 1), (FILE*) file_ptr);

		printf("%s\n", value);
		fclose(file_ptr);
	}
	else {
		printf("Error: no token to access.\n");
	}

	return 0;
}

