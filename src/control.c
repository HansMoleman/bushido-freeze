
/*** control.c
 *
 * CMPL:
 * EXEC:
 * DEPN:
 *
 * ...
 *
 * ---
 *  ver
 * ---
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>



int main(int argc, char* argv[]){

	if(argc == 2){
		// only command given
		char command[sizeof(argv[1])];
		strcpy(command, argv[1]);
		
		if(strcmp(command, "new")){
			// create new token
			printf("<< create new token >>\n");
		}
		else if(strcmp(command, "view")){
			// view target token
			printf("<< view target token >>\n");
		}
		else{
			printf("ERROR: the <'%s'> command given is unrecognized, please try again.\n", command);
		}
	}
	else if(argc > 2){
		// command and arg(s) given
		char command[sizeof(argv[1])];
		strcpy(command, argv[1]);

		int argl = 0;
		for(int i = 2; i < argc; i++){
			argl += (sizeof(argv[i]) * 2);
		}
		char args[argl];
		for(int i = 2; i < argc; i++){
			strcat(args, argv[i]);
		}

		if(strcmp(command, "new")){
			// create new token
			printf("<< create new token +params >>\n");
		}
		else if(strcmp(command, "view")){
			// view target token
			printf("<< view target token +params >>\n");
		}
		else{
			printf("ERROR: the <'%s'> command is unrecognized, please try again.\n", command);
		}
	}
	else{
		// no command or arg(s) given
		printf("ERROR: no command/arguments received, please try again.\n");
	}
}