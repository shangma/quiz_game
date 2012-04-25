#include <stdlib.h>
#include <stdio.h>
#include <cnaiapi.h>

#define BUFFSIZE		256
#define INPUT_PROMPT		"Answer > "
#define RECEIVED_PROMPT		"Alex Trebek > "

int readln(char *, int);                // WHERE IS THIS DEFINED?
int timeout();
int verify_input(char);
char convert_case(char);
computer make_connection(int, char*[]);

//      Connect to Server, Appnum is 20001


/*
 Client Behavior
 * 
 * read question from server
 * store input from user for answer
 * 
 * timeout function
 * 
 * read answer from server
 * 
 * verify user input
 * 
 * display winner/loser from server 
 
 */

int main(int argc, char *argv[]){
    computer comp;
    appnum app = 20001;
    connection conn;
    char buff[BUFFSIZE];
    int	expect, received, len;
    
    if (argc < 1 || argc > 2) {
        (void) fprintf(stderr, "usage: %s <compname>\n", argv[0]);
        exit(1);
    }
    
    comp = make_connection(argc, argv);
    
    return 0;
}



 computer make_connection(int argc, char *argv[]){
    computer comp;
    appnum app = 20001;
    connection conn;
    char buff[BUFFSIZE];
    int	expect, received, len;
    
    comp = cname_to_comp(argv[1]);
    
    if (comp == -1)
    {
            (void) fprintf(stderr,"comp == -1");
            exit(1);
    }
	
    /* form a connection with the echoserver */

    conn = make_contact(comp, app);
    if (conn < 0)
    {
        (void) fprintf(stderr,"conn < 0");
        exit(1);
    }
    
    return comp;
}

 int verify_input(char input){    
     if (input == 'A' || input == 'B' || input == 'C' || input == 'D'){
         return 0;
     }
     else{
         return 1;
     }
 }
 
 char convert_case(char input){
     switch (input){
         case 'a':
             input = 'A';
             break;
         case 'b':
             input = 'B';
             break;
         case 'c':
             input = 'C';
             break;
         case 'd':
             input = 'D';
             break;
     }
     return input;
}
 
/* The Rest from Echo Client
 
 *      (void) printf(INPUT_PROMPT);
	(void) fflush(stdout);

	// iterate: read input from the user, send to the server,	
	//	    receive reply from the server, and display for user 

	while((len = readln(buff, BUFFSIZE)) > 0) {

		// send the input to the echoserver

		(void) send(conn, buff, len, 0);
		(void) printf(RECEIVED_PROMPT);
		(void) fflush(stdout);

		// read and print same no. of bytes from echo server

		expect = len;
		for (received = 0; received < expect;) {
		   len = recv(conn, buff, (expect - received) < BUFFSIZE ?
				 (expect - received) : BUFFSIZE, 0);
			if (len < 0) {
				send_eof(conn);
				return 1;
			}
			(void) write(STDOUT_FILENO, buff, len);
			received += len;
		}
		(void) printf("\n");
		(void) printf(INPUT_PROMPT);
		(void) fflush(stdout);
	}

	//iteration ends when EOF found on stdin

	(void) send_eof(conn);
	(void) printf("\n");
	return 0;
 * 
 */