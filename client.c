/****************************************************************************
                                client.c
 * usage: client.c <host>
 
 * duties: * allows for joining or registering		[ ]
		   * responds to servers questions			[ ]
 
 TODO: Documentation
 TODO: timeout?
 TODO: TEST!
 TODO: Add Team Names?
 ****************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <cnaiapi.h>

#define BUFFSIZE			256
// define value of user input prompt
#define INPUT_PROMPT		"Answer      > "
// define comical reveived prompt
#define RECEIVED_PROMPT		"Alex Trebek > "

//////////////////////////////////////////////////////////////////////
//------------A NOTE ON FUNCTIONS PREFIXED WITH (void)--------------//
//                                                                  //
//   Placing '(void)' before a function call works like any other   //
//   typecast. It is used to cast functions that normally return a  //
//   value as void. Put plainly, it says, this function returns     //
//   some value, but I am not storing or using that value in any    //
//   way, so don't worry about returning a value at all.            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

// readln reads from stdin stream until
// EOF or buffer is full
// location: ../anaiapi/apps/readln.c
int readln(char *, int); 


// ------- FUNCTIONS WHICH ARE DEFINED BELOW ------- //

// timeout(): times-out cliets who fail to 
//   repond within predetermined time limit
int timeout();

// verify_input(): 
//   TAKES: a charater
//
//   RETURNS: boolean value indicating validity 
//            either 0 (valid) or 1 (invalid)
int verify_input(char);

// convert_case(): 
//   TAKES: a single character
//
//   RETURNS: if that character is either 'a', 'b', 'c', 
//            or'd', funciton will return the uppercase 
//            analog of supplied character; else the input
//            value is returned unchaged
char convert_case(char);

// NOTE: computer is typedef of long
//
// make_connection(): 
//   TAKES: an integer and a pointer to arguments supplied to 
//          main() during command line call
//
//   RETURNS: value of datatype coputer (typedef of long)
computer make_connection(int, char*[]);

int main(int argc, char *argv[]){
	// create variable of type long to identify a host computer
    computer comp;

	// create variable of type short to represent an application
    appnum app = 20001;

	// create a variable of type int to represent the client/host
	// connection
    connection conn;

	// create a buffer array of size 256 to store characters
    char buff[BUFFSIZE];

	// declare three integers dealing with packages
    int	expect, 
		received, 
		len;		// used to store buffer size
    
    int answer_index = 0;             // does this return index of the beginning of an answer?
    char answers[21];
    int bad_input;
    
    // ***************** Check Args ************************//
	// this program must have at least 1 & no more than 2
	// arguments
    if (argc < 1 || argc > 2) {
		// print a helpful usage  message
        (void) fprintf(stderr, "usage: %s <compname>\n", argv[0]);
        exit(1);
    }
    
    // *************** Make Connection ********************//
    (void) printf("Connecting");

	// determine whether arguments supplied when program
	// was called are valid; store returned IP address of
	// host system
    comp = make_connection(argc, argv);

    // **************** Start Game ***************************** //

	//////////////////////////////////////////////////////////////
	// recvln(): 
	//   TAKES: an conn (integer), character buffer of 256, & the
	//          BUFFSIZE (256)
	//
	//   SIDE EFFECTS: makes call to winsocket api's recv() 
	//                 which returns number of bytes received
	//                 & and stores data recieved in the buffer
	//                 that has been pointed to; recvln, does
	//                 the same for the buffer it is given
	//
	//   RETURNS: number of bytes recieved
	//////////////////////////////////////////////////////////////
    while((len = recvln(conn, buff, BUFFSIZE)) > 0) {   //      Game is playing
		//  Read Question
        (void) printf(RECEIVED_PROMPT);
		// flush stdio stream
        (void) fflush(stdout);
		// NOTE: STDOUT_FILENO is just a typedef set to one
		// write() writes prints len number of bytes from
		// buff into the command line
        (void) write(STDOUT_FILENO, buff, len);
        
		//  Get Answer
        do {
            (void) printf(INPUT_PROMPT);
            (void) fflush(stdout);
			// read BUFFSIZE bytes from buff
			// stores number of bytes in len
            len = readln(buff, BUFFSIZE);
            bad_input = 0;

            //  make character uppercase if 'a', 'b', 'c', or 'd'
            buff[0] = convert_case(buff[0]);

			// validate that buff[0] contains either 'A', 'B', 
			// 'C', or 'D'
            if(verify_input(buff[0]) != 0){
                (void) printf("Bad Input\n");
                bad_input = 1;
            }
        } while(bad_input != 0);
		

		//  Store Answer
        answers[answer_index] = buff[0];
    
		//  TODO: Timeout: must time-out cliets 
		//	who fail to repond within predetermined time limit
    
    }
    // ***************** Finish Game  ***************************//
    // Get Winner/Loser
    
    (void) send_eof(conn);
    (void) printf("\n");
    
    return 0;
}

//////////////////////////////////////////////////////////////
// make_connection(): 
//   TAKES: an integer and a pointer to arguments supplied to 
//          main() during command line call
//
//   RETURNS: value of datatype coputer (typedef of long)
//////////////////////////////////////////////////////////////
computer 
make_connection(int argc, char *argv[]) {
	// create variable of type long to hold a value that
	// represents the host computer to be connected to
    computer comp;

	// create variable of type appnum (typedef of short)
	// to represet app to run
    appnum app = 20001;

	// create variable of type connection (typedef of int)
	// to represent connection
    connection conn;

    // create a buffer array of size 256 to store characters
    char buff[BUFFSIZE];

	// declare three integers dealing with packages
    int	expect, 
		received, 
		len;		// used to store buffer size
   
	// look up host by name and return its IP address
	// store returned value as type computer
    comp = cname_to_comp(argv[1]);
   
	// if cname_to_comp() returns -1, exit with error
    if (comp == -1) {
 		(void) fprintf(stderr,"comp == -1");
		exit(1);
	}

	// open a new TCP connection to the specified IP address
	// store returned connection type value
    conn = make_contact(comp, app);

	// if make_contact returns a negative value, exit with
	// error
    if (conn < 0) {
        (void) fprintf(stderr,"conn < 0");
        exit(1);
    }
    
	// if all has gone as planned, tell user they are 
	// connected
    (void) printf("Connected");    
    
	// return host's IP address
    return comp;
}

////////////////////////////////////////////////////////////////
// verify_input(): 
//   TAKES: a charater
//
//   RETURNS: boolean value indicating validity 
//            either 0 (valid) or 1 (invalid)
////////////////////////////////////////////////////////////////
int 
verify_input(char input) {    
    if (input == 'A' || input == 'B' || input == 'C' || input == 'D'){
        return 0;
    }
    else { return 1; }
}
 
/////////////////////////////////////////////////////////////////
// convert_case(): 
//   TAKES: a single character
//
//   RETURNS: if that character is either 'a', 'b', 'c', 
//            or'd', funciton will return the uppercase 
//            analog of supplied character; else the input
//            value is returned unchaged
////////////////////////////////////////////////////////////////
char 
convert_case(char input) {
    switch (input ){
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
