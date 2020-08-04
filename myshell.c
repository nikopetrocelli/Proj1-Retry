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
#define BUFSIZE 64
//delimiters for splitting the text
#define TOKEN_DE " \t\r\n\a"

char **sh_parse(char *cmd){

    int size = BUFSIZE;
    int pos = 0;

    char **paramList = malloc(size * sizeof(char*));
    char *param;

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
        param = strtok(NULL, TOKEN_DE);
    }
    
    //mark the end of the parameters with a null key
    paramList[pos] = NULL;
    return paramList; //return the parsed out parameters

}

int sh_execute(char **args){
    #include "shellfuncts.h"
    //define our commands
    const char* halt = "halt";
	const char* createNew = "create";
	const char* update = "update";
	const char* list = "list";
	const char* dir = "dir";


        //Tell the user the pid		
        pid_t pid1 = getpid();
		printf("\nThe current pid is:  %d", pid1);
		printf("\n");
        pid_t pid2;

        pid_t cpid;

        //before creating a child process, check for exit
        if (strcmp(args[0], halt) == 0){
                printf("\n\n\nGoodbye!\n\n\n");
                //wait for message to be read
                sleep(1);
                 //Clean up our mess by clearing out the console
                system("clear");
                return 0;
                //exit(0);
            }

        if (fork()==0){
            //in the child process now
            pid2 = getpid();
            printf("\nThe child pid is:  %d", pid2);
		    printf("\n");
        // first arg (arg[0]) is your command
           // printf("\nin the child%s ", args[0]);
           // printf("\n");
           // printf("%s", args[0]);
            char *command = args[0];
           // printf("%s", command);
            if (strcmp(args[0], create) == 0){
                printf("\n\n\Creating!%s", args[1]);
                printf("\n");
                create(args[1]);
                //close the child
                //return 1;
            }
            else{
                printf("\nInvalid command\n");
            }

             

        }
        else{
            cpid = wait(NULL);

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
       // printf("\nThe input was %s", cmd);
        //printf("\n");
        args = sh_parse(cmd);
       //debug lines
       // printf("\nThe paramaters are %s");
       /* for(int i =0; i < 5 ; i++)
        printf("\n%s", args[i]);
        printf("\n"); */
        //check for exit
        execFlag = sh_execute(args);

        if (execFlag = 1){
            printf("\n%d", execFlag);


        }

       // free(line);
        //free(args); 


        

    }while (execFlag != 0);







    return 0;
}