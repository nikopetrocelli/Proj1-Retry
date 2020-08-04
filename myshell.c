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
	//printf("\nInput a command \n");

    return;

}

#define LINESIZE 500
char *sh_read(void){
   
   //This first implementation is code I got from a tutorial online, then I found out there is a way to use the getline() function to implement this code so I swapped to that. 
   //I left it in here as reference for myself in the future, to understand better what is actually happening
   /*
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
        //if we aren't at the end, then add the character to the string
        else{
            buff[pos] = c;
        }
        //advance to the next position in the string
        pos++;
    }*/

    char *cmd = NULL;
    ssize_t size = 0; //getline will handle the size allocation
    //use get line to scan it in until it reaches the end and then return it as cmd, it will later be parsed for arguments
    if(getline(&cmd, &size, stdin)== -1){
        if (feof(stdin)){
            exit(0); //EOF
        }
        else{
            perror("failure");
            exit(0);
        }

    }

    return cmd;


}


//This code is also referenced from an online tutorial from brennan.io on how to split a message
//size of the tokens
//#define BUFSIZE 64
//delimiters for splitting the text
//#define TOKEN_DE " \t\r\n\a"
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
char **sh_parse(char *cmd){
/*
    int size = BUFSIZE;
    int pos = 0;

    char **paramList = malloc(size * sizeof(char*));
    char *param;
*/
/*
    if (!paramList){
        printf("Error allocating memory\n");
        exit(0);
    }
*/
    /*
    //start to separate the string based on the previously defined delimiters
    param = strtok(cmd, TOKEN_DE);
    //loop through until the end
    while (param != NULL){
        //set this element equal to the first input parameter
        paramList[pos] = param;
        pos++; //increment to the next spot for the next parameter

        //if the position goes past the max size, error
        if (pos >= size){
            printf("\nToo much stuff entered\n");
            exit(0);
        }

        
        //printf("\n%s", param);
        printf("\n%s", paramList[pos]);
        printf("\nthe pos is %d", pos);
        param = strtok(NULL, TOKEN_DE);
    }
    
    //mark the end of the parameters with a null key
    paramList[pos] = NULL;
    return paramList; //return the parsed out parameters
    */

  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(cmd, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  printf("%n%s", tokens);
  return tokens;

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

        //Tell the user the pid		
        pid_t pid1 = getpid();
		printf("\nThe current pid is:  %d", pid1);
		printf("\n");
        //get the user input

        printf("> ");
        cmd = sh_read();
        printf("\nThe input was %s", cmd);
        printf("\n");
        args = sh_parse(cmd);
        printf("\nThe paramaters are %s", args);
        printf("\n");
       // execFlag = sh_execute(args);

       // free(line);
        //free(args); 


        

    }while (execFlag);







    return 0;
}