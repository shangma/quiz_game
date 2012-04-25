/****************************************************************************
                                client.c
 * usage: client.c <host>
 
 * Connects to Host to Get Questions, and Answers
 * Then sends answers to Host and finds out if winner
 
 TODO: Documentation
 TODO: timeout?
 TODO: TEST!
 TODO: Add Team Names?
 ****************************************************************************/


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


int main(int argc, char *argv[]){
    computer comp;
    appnum app = 20001;
    connection conn;
    char buff[BUFFSIZE];
    int	expect, received, len;
    
    int answer_index = 0;
    char answers[21];
    int bad_input;
    
    // ***************** Check Args ************************//
    if (argc < 1 || argc > 2) {
        (void) fprintf(stderr, "usage: %s <compname>\n", argv[0]);
        exit(1);
    }
    
    // *************** Make Connection ********************//
    (void) printf("Connecting");
    comp = make_connection(argc, argv);

    // **************** Start Game ***************************** //
    while((len = recvln(conn, buff, BUFFSIZE)) > 0){   //      Game is playing
    //  Read Question
        (void) printf(RECEIVED_PROMPT);
        (void) fflush(stdout);
        (void) write(STDOUT_FILENO, buff, len);
        
    //  Get Answer
        do{
            (void) printf(INPUT_PROMPT);
            (void) fflush(stdout);
            len = readln(buff, BUFFSIZE);
            bad_input = 0;

            //  Verify
            buff[0] = convert_case(buff[0]);

            if(verify_input(buff[0]) != 0){
                (void) printf("Bad Input\n");
                bad_input = 1;
            }
        }
        while(bad_input != 0);
    
    //  Store Answer
        answers[answer_index] = buff[0];
    
    //  TODO: Timeout
    
    }
    // ***************** Finish Game  ***************************//
    // Get Winner/Loser
    
    (void) send_eof(conn);
    (void) printf("\n");
    
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

    conn = make_contact(comp, app);
    if (conn < 0)
    {
        (void) fprintf(stderr,"conn < 0");
        exit(1);
    }
    
    (void) printf("Connected");    
    
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