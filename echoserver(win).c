/* echoserver.c */

#include <stdlib.h>
#include <stdio.h>
#include <cnaiapi.h>
#include <process.h>

#define BUFFSIZE		256

void echothread(void *);

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
	int			len;
	char		buff[BUFFSIZE];

	if (argc != 2)
	{
		(void) fprintf(stderr, "usage: %s <appnum>\n", argv[0]);
		exit(1);
	}

	/* wait for a connection from an echo client */

	conn = await_contact((appnum) atoi(argv[1]));
	if (conn < 0)
	{
		(void) fprintf(stderr, "conn < 0");
		exit(1);
	}

	(void) printf ("waiting for contact");
	/* iterate, echoing all data received until end of file */
	


	while(1)
	{
		conn=malloc(sizeof(connection));
		*conn=await_contact((appnum)atoi(argv[1]));
		_beginthread(echothread,0,conn);
	}

	return 0;
}

void echothread(void *value)
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
