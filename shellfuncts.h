/*************************************************************************************
 * shellfuncts.h - header file for your shell functions
 * create - Create a new file in the current directory with the given name. If the file already exists, print an error message on the workstation screen.
 * update - Append lines of text to the named file. In particular, the text string <text> is appended to the end of the file, <number> times. To simulate a (very) slow device, the update command sleeps 		    for several seconds after appending each line.
 * list - Display the contents of the named file on the workstation screen. If the file does not exist, print an error message on the workstation screen and terminate the command.
 * dir - List the names of all files in the current directory. Note that since there is no command to change to a new directory, the current directory is the only directory.
 *
 *************************************************************************************/

// Replace these with something useful
//int hello(int param1);
//void send_msg(const char *param2);
void create(const char *name);
void update(const char *name, int num, const char *text);
void list (const char*name);
void dir();


