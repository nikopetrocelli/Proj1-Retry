/*************************************************************************************
 * myshell - student code for Project 1 of CSCE 489 
 * Niko Petrocelli
 *
 *************************************************************************************/


#include "shellfuncts.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>




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
   
    char *cmd = NULL;
    size_t  size = 0; //getline will handle the size allocation
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

void sh_execute(char **args){
    #include "shellfuncts.h"
    //define our commands
    const char* halt = "halt";
	const char* createCMD = "create";
	const char* updateCMD = "update";
	const char* listCMD = "list";
	const char* dirCMD = "dir";


        
     pid_t cpid;
        //before creating a child process, check for exit
        if (strcmp(args[0], halt) == 0){
                printf("\n\n\nGoodbye!\n\n\n");
                //wait for message to be read
                sleep(1);
                 //Clean up our mess by clearing out the console
                system("clear");
                //close the main process
                exit(0);
            }

        if (fork()==0){
            //in the child process now
            cpid = getpid();
            printf("\nThe child pid is:  %d", cpid);
		    printf("\n");
        // first arg (arg[0]) is your command
          
          
           //If our command is to make a new file
            if (strcmp(args[0], createCMD) == 0){
                printf("\n\nCreating %s", args[1]);
                printf("\n");
                create(args[1]);
            }
            //if your command is to list
            else if (strcmp(args[0], listCMD) == 0){
                printf("\n\nlisting %s", args[1]);
                printf("\n");
                list(args[1]);
                }
            //if your command is to show directory
            else if (strcmp(args[0], dirCMD) == 0){
                dir();
            }
            else if (strcmp(args[0], updateCMD)==0){
                char buffer [500];
             
                //message data starts at 3rd arg
                int i = 3 ;
                //Concatonate the arguments to create the message
                while(args[i] != NULL){

                    strcat(strcat(buffer, args[i])," ");
                    //add space between words
                    i++;
                }
                
                
                //Arg 1 is our filename, arg 2 is our num of times and buffer is our text string we just created
                //Need to conver this to a number, i learned this the hard way.
                int num = atoi(args[2]);
                update(args[1], num, buffer);
            
            }
            
            else{
                printf("\nInvalid command\n");
                exit(0);
            }

             

        }
        else{
            cpid = wait(NULL);

        }
        return;

}




int main(int argv, const char *argc[]) {
	(void) argv; // Make compile warnings go away - be sure to delete this line if you use the param
	(void) argc; // Make compile warnings go away - be sure to delete this line if you use the param


    char *cmd;
    char **args;
   // int execFlag;
    // print the splash screen
    initialize();
    

    //loop the program
    while(1){
        //Tell the user the pid		
        pid_t pid1 = getpid();
		printf("\nThe parent pid is:  %d", pid1);
		printf("\n");
  

   
        //get the user input
        printf("> ");
        cmd = sh_read();
        //Separate out the commands and the arguments
        args = sh_parse(cmd);
        //Run the executions
        sh_execute(args);
       

    };







    return 0;
}