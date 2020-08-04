/*************************************************************************************
 * shellfuncts.c - code definitions for your functions
 *
 *************************************************************************************/

#include <stdio.h>
#include "shellfuncts.h"

/*************************************************************************************
 * hello - sends hello world to the user! I'm doing proper function commenting so future
 *         coders might not find my code as painful.
 *
 *		Params:	param1 - I explain my parameters, like this is 1 for American, 2 for
 *                      Australian
 *
 *		Returns: always returns 1, no matter what. Fairly useless.
 *
 *************************************************************************************/
/*
int hello(int param1) {
	// I'm commenting to explain that this checks param and changes the message
	if (param1 == 1)
		send_msg("Hello world!\n");
	else
		send_msg("G'day world!\n");

	// Return 1 because, why not.
	return 1;
}

*/
/*************************************************************************************
 * hello - sends hello world to the user! I'm doing proper function commenting so future
 *         coders might not find my code as painful.
 *
 *    Params:  param2 - not a very good parameter name - something better might be
 *                      say, msgstr or sendtext
 *
 *************************************************************************************/
/*
void send_msg(const char *param2) {
	printf("%s", param2);
	
}*/
void create(const char *name){
	FILE *file;
	//does the file exist already?
	if ((file = fopen(name,"r"))){
		fclose(file);
		printf("\nThis file already exists\n");
		//Close the child
		exit(0);
	}
	else{
		file = fopen(name, "w");
		fclose(file);
		//otherwise make the file then close the child
		exit(0);}

	

}

void list (const char*name){



}
void dir(){
	//List the current files in the directory
	execl("/bin/ls", "ls", NULL);
	//close the child
	exit(0);
}


