/*************************************************************************
                                server.c
 usage: server.c
 
 * TODO: Send Questions
 * TODO: Get ANswers
 * TODO: Calc Winner
 * TODO: TEst
 * TODO: Makefile?
 * TODO: Read QUestions & Answers
 * TODO: Parse QUestions
 *************************************************************************/


#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <cnaiapi.h>

#define BUFFSIZE		256
#define CONNECTIONS             21

char get_answer(int);
char* get_all_answers();
int ask_question(char[]);
void *client_thread(void *);

int main(int argc, char *argv[])
{
    connection	conn[CONNECTIONS];
    int         connection_index = 0;
    int		len;
    char        buff[BUFFSIZE];
    int         loop;
    int         points[CONNECTIONS];

    // Check usage
    if (argc != 1) {
            (void) fprintf(stderr, "usage: %s\n", argv[0]);
            exit(1);
    }
    
    //  Create Clients
    while(connection_index < 20){
        conn=malloc(sizeof(connection));
        *conn=await_contact((appnum)atoi(argv[1]));

        if (conn < 0){
            (void) fprintf(stderr, "conn < 0");
        }
        else{
            pthread_t newthread;
            conn[connection_index] = pthread_create(&newthread, NULL, client_thread, conn);
        }

        connection_index++;
    }
    
    // OPEN FILES FOR READING!
    
    for(loop = 0; loop < CONNECTIONS; loop++){
        //  Send Questions to Clients
        //  Get Answers   
    }
   
    
    //  Calc Winner
    //  Cake?
    

    return 0;
}


struct client{
    int link;
    int client_num;
    char answers[21];
};

void *client_thread(void *value)
{
	int		len;
	char	buff[BUFFSIZE];
	
	connection conn= *(connection *)value;

	while((len = recv(conn, buff, BUFFSIZE, 0)) > 0)
	{
		(void) send(conn, buff, len, 0);
	}		/* iterate, echoing all data received until end of file */
	send_eof(conn);
	free(value);
	pthread_exit(NULL);
}