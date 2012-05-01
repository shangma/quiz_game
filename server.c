/*************************************************************************
                                server.c
 * usage: server.c
 
 * duties: * sends questions to all clients				[ ]
	       * records answers recieved by clients                    [ ]
		   * times-out clients who fail to respond		[ ]
                    within set time limit				[ ]
		   * announce winner of 100 question game		[ ]

 * TODO: Send Questions
 * TODO: Get ANswers
 * TODO: Calc Winner
 * TODO: TEst
 * TODO: Makefile?
 * TODO: Read QUestions & Answers
 * TODO: Parse QUestions
 *************************************************************************/

// include standard libraries
#include <stdlib.h>
#include <stdio.h>
#include <cnaiapi.h>
#include <ctime.h>
#include <time.h>

// include POSIX system headers
#ifdef __GNU__
	#include <pthread.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <sys/stat.h>
#endif

// include windows-specific headers
#ifdef _WIN32
	#include <process.h>
#endif

#define BUFFSIZE			256
#define CONNECTIONS         21

const int TIME_LIMIT	  = 45; // in seconds
const int NO_OF_QUESTIONS = 10;

char get_answer(int);
char* get_all_answers();
int ask_question(char[]);
void* client_thread(void *);

// declare POXIS functions
#ifdef __GNU__
	// Declare a global variable with array [2] of data type int.
	int pipefd[2];
	unsigned int thread_id;
#endif

// declare Windows-specific functions
#ifdef _WIN32
	void echothread(void *);
#endif

// count_down:
//   TAKES: int representing the number of seconds to
//          count down from
// 
//   RETURNS: int returning 0 if succesfully executed
int count_down(int);

int main(int argc, char *argv[]) {
	// NOTE: connection is typedef of int
	// declare array of 21 ints
    connection	conn[CONNECTIONS];
    int         connection_index = 0;
    int			len;
	// declare character buffer of size 256
    char        buff[BUFFSIZE];
    int         loop;
    int         points[CONNECTIONS];

    // Check usage
    if (argc != 1) {
            (void) fprintf(stderr, "usage: %s\n", argv[0]);
            exit(1);
    }
    
    //  Create Clients
    while(connection_index < 20) {
		// connection is a typedef of int, so its size is 
		// 4 bytes (on most current intel CPUs); thus, malloc 
		// will allocate a memory block of 4 bytes & return 
		// a pointer to the adress of that block; this works 
		// because conn is an array and so after declaration 
		// it is simply a pointer to the memory address of 
		// the first element of its array; this is called
		// decaying; the array decays to a pointer; after 
		// this line, the variable 'conn' will hold a pointer
		// to a block of size 4 bytes
        conn = malloc(sizeof(connection));

		
		/////////////////////////////////////////////////////////////
		// await_contact():
		//   TAKES: accepts a connection on port a
		// 
		//   RETURNS: if no master sock is already open for the 
		//            port, create one and record it in the port-to-
        //            socket table
		/////////////////////////////////////////////////////////////

		// here conn (which is a pointer variable) is being 
		// dereferenced, so here we are actually story
		// a value beginning at the memory address
		// referenced by the variable conn; also note that
		// the return value of function atoi() is being 
		// cast as tyoe appnum (short)
        *conn = await_contact((appnum)atoi(argv[1]));

		// if no connection, print error
        if (conn < 0) {
            (void) fprintf(stderr, "conn < 0");
        }
        else {
			// Windows-specific
			#ifdef _WIN32
			#endif

			// POSIX-specific
			#ifdef __GNU__
				// declare new thread identifier
				pthread_t newthread;
				// pthread_create() routine creates a new thread within a process;
				// the new thread starts in client_thread; conn is the start
				// argument to client_thread; the resulting thread is stored in
				// index connection_index of conn array
				conn[connection_index] = pthread_create(&newthread, NULL, client_thread, conn);
			#endif
        }

        connection_index++;
    }
    
    // --------------------- FILE IO -----------------------------//

	// questions.dat should be written in the following format
	//////////////////////////////////////////////////////////
	//question #
	//question
	//option a
	//option b
	//option c
	//option d
	//correct answer
	//blank line
	//repeat until no more questions
	//////////////////////////////////////////////////////////
	//  Example:
	//////////////////////////////////////////////////////////
	//1
	//How much wood could a wookchuck chuck?
	//a) 20 pounds
	//b) 39 pounds
	//c) 3 pounds
	//d) none of the above
	//d
	//
	//2
	//How much money is in my pocket?
	//a) 3 bucks
	//b) 100 bucks
	//c) 0 bucks
	//d) 20 bucks
	//c
	//
	//3
	//////////////////////////////////////////////////////////
	// . . . and so on
	/////////////////////////////////////////////////////////

	// declare an input file pointer
	FILE * input_file_ptr;

	// set fopen() mode to read
	char * mode = "r";

	// store address of file stream in pointer variable
	input_file_ptr = fopen("questions.dat", mode);

	// error check
	if (input_file_ptr == NULL) {
		fprintf(stderr, "Can't open input file questions.dat!\n");
		exit(1);
	}
    
	int question_no = 1;
	// read through file by line
	while (len = readln(buff, BUFFSIZE) != EOF) {
		// send question and potential answers to everyone

	}

    for(loop = 0; loop < CONNECTIONS; loop++){
        //  Send Questions to Clients
        //  Get Answers   
    }
   
    
    //  Calc Winner
    //  Cake?
    

    return 0;
}

// structure holding information about client
struct client {
    int link;
    int client_num;
    char answers[21];
};

// POXIS-specific functions
#ifdef __GNU__
	void* 
	client_thread(void *value) {
		int		len;
		char	buff[BUFFSIZE];
	
		connection conn= *(connection *)value;

		while((len = recv(conn, buff, BUFFSIZE, 0)) > 0)
		{
			(void) send(conn, buff, len, 0);
		}
		send_eof(conn);
		free(value);
		pthread_exit(NULL);
	}

	// thread entry point
	void* 
	pipe_writer_thread(void* arg) {

	}

	void 
	create_thread() {
	   pthread_create(&thread_id, (pthread_attr_t *)NULL, pipe_writer_thread, NULL);
	}
#endif

// Windows-specific functions
#ifdef _WIN32
	void 
	echothread(void *value)
	{
		connection conn= *(connection *)value;

		while((len = recv(conn, buff, BUFFSIZE, 0)) > 0)
		{
			(void) send(conn, buff, len, 0);
		}
		send_eof(conn);

		free(&conn);
		_endthread();
	}
#endif

/////////////////////////////////////////////////////////////////
// count_down:
//   TAKES: int representing the number of seconds to
//          count down from
// 
//   RETURNS: int returning 0 if succesfully executed
/////////////////////////////////////////////////////////////////
int 
count_down(int num_of_seconds) {
	// store start value for count down; this value is the
	// number of seconds that have lapsed since the Epoch
	time_t start_time = time (NULL);

	// calculate end time
	time_t end_time = start_time + num_of_seconds;

	int time_elapsed;

	// lcountdown
	while(difftime(end_time, start_time) > 0) {
		// store number of seconds left in countdown
		time_elapsed = difftime(end_time, start_time);  // if timer is a thread this could be a pointer to some external variable
	}

	return 0;
}

char question(char question[]){
    char answer;
    
    (void) send(conn, buff, len, 0);
    
    return answer;
}