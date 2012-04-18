/* echoserver.c */

#include <stdlib.h>
#include <stdio.h>
#include <cnaiapi.h>
#include <pthread.h>


#define BUFFSIZE		256

void *echothread(void *);

/*-----------------------------------------------------------------------
 *
 * Program: echoserver
 * Purpose: wait for a connection from an echoclient and echo data
 * Usage:   echoserver <appnum>
 *
 *-----------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
	connection	*conn;
	int meaningless_handle;

	if (argc != 2)
	{
		(void) fprintf(stderr, "usage: %s <appnum>\n", argv[0]);
		exit(1);
	}




	(void) printf ("waiting for contact");

	while(1)
	{
	/* wait for a connection from an echo client */
		conn=malloc(sizeof(connection));
		*conn=await_contact((appnum)atoi(argv[1]));

		if (conn < 0)
		{
			(void) fprintf(stderr, "conn < 0");
		}
		else
		{
			pthread_t newthread;
			meaningless_handle=pthread_create(&newthread, NULL, echothread, conn);
		}
	}

	return 0;
}

void *echothread(void *value)
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
