/*************************************************************************************
 * myshell - student code for Project 1 of CSCE 489 
 * Niko Petrocelli
 *
 *************************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "shellfuncts.h"



#define MAXINPUT 100 // max number of input characters
#define MAXCMDS 5 // for this project we have 5 commands to support

void initialize(){
	//Initialize the shell	
	printf("\n\n\n****************************************************");
	printf("\n\n\nWelcome to Niko's Shell\n\n\n");
	printf("******************************************************\n\n\n");
	//wait a bit
	sleep(2);
	//clear the screen
	system("clear");
	printf("\nInput a command \n");

    return;

}

#define LINESIZE 500
char *sh_read(void){
    char buff[LINESIZE];
    
	


   int size = LINESIZE;
    int pos = 0;

    char *buff = malloc(sizeof(char)*size);
    int c;

    if (!buff){
        fprintf(stderr,"shell: mem error\n");
        exit(0);

    }

    while (1){
        // read a character
        c = getchar();
        //if we are at the end set a null and return 
        if (c==EOF || c =='\n'){
            buff[pos] = '\0';
            return buff;

        }
        else{
            buff[pos] = c;
        }
        pos++;
    }


}

int main(int argv, const char *argc[]) {
	(void) argv; // Make compile warnings go away - be sure to delete this line if you use the param
	(void) argc; // Make compile warnings go away - be sure to delete this line if you use the param


    char *cmd;
    char **args;
    int execFlag;
    // print the splash screen
    initialize();
    

    //loop the program
    do{

        //get the user input
        printf("> ");
        cmd = sh_read();
        printf("\n%s", cmd);
        //args = sh_split_line(cmd);
       // execFlag = sh_execute(args);

       // free(line);
        //free(args); 


        

    }while (execFlag);







    return 0;
}