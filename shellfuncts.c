/*************************************************************************************
 * shellfuncts.c - code definitions for your functions
 *
 *************************************************************************************/

#include <stdio.h>
#include "shellfuncts.h"


void create(const char *name){
	FILE *file;
	//does the file exist already?
	if (doesFileExist(name)){
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
		//does the file exist?
		if(doesFileExist(name)){
			char command[500];
			snprintf(command, 256, "cat %s", name);
			//read it
			execl("/bin/cat", "cat", name);
			exit(0);
		}
		else{
			printf("\nThe file does not exist");
			exit(0);
		}

}
void dir(){
	//List the current files in the directory
	execl("/bin/ls", "ls", NULL);
	//close the child
	exit(0);
}

void update(const char *name, int num, const char *text){
FILE *file;
	//does the file exist already?
	if (doesFileExist(name)){
		
		//Open the file in append mode
		file = fopen(name,"a");
		//loop through and append num of times
			for (int i = 0; i < num; i++){
				fprintf(file, text);
			}
			fflush(file); //write file
			sleep(strlen(text)/5); //sleep a bit
			fclose(file);
			printf("\nUpdate is complete");
			exit(0);

		//Close the child
		exit(0);
	}
	else{
		printf("\nThis file does not exist\n");
		//otherwise make the file then close the child
		exit(0);}


}
//If the file opens, it exists and return a 1 else, return a 0
int doesFileExist(const char* name){
	FILE *file;
	if (file = fopen(name, "r")){
		fclose(file);
		return 1;

	}
	return 0;

}

