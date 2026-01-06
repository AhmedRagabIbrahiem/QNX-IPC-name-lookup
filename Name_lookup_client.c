////////////////////////////////////////////////////////////////////////////////
// client.c
//
// A QNX msg passing client.  It's purpose is to send a string of text to a
// server.  The server calculates a checksum and replies back with it.  The client
// expects the reply to come back as an int
//
// This program program must be started with commandline args.  
// See  if(argc != 4) below
//
// To complete the exercise, put in the code, as explained in the comments below
// Look up function arguments in the course book or the QNX documentation.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/neutrino.h>
#include "msg_def.h"
#include <sys/dispatch.h>

int main(int argc, char* argv[])
{
	int coid; //Connection ID to server
	cksum_msg_t msg;
	int incoming_checksum; //space for server's reply
	int status; //status return value used for MsgSend

	//PUT CODE HERE to establish a connection to the server's channel, store the
	//connection id in the variable 'coid'
	coid = name_open(SERVER_NAME, 0);

	if (coid == -1)
	{ //was there an error attaching to server?
		perror("ConnectAttach"); //look up error code and print
		exit(EXIT_FAILURE);
	}

	msg.msg_type = CKSUM_MSG_TYPE;
	strlcpy(msg.string_to_cksum, argv[3], sizeof(msg.string_to_cksum));
	printf("Sending string: %s\n", msg.string_to_cksum);

	status = MsgSendPulse(coid, -1, 3, 0xdeadc0de);
	if (status == -1)
	{
		perror("MsgSendPulse");
	}
	
	//PUT CODE HERE to send message to server and get the reply
	status = MsgSend(coid, &msg, sizeof(msg.msg_type) + strlen(msg.string_to_cksum) + 1, &incoming_checksum,
			sizeof(incoming_checksum));
	if (status == -1)
	{ //was there an error sending to server?
		perror("MsgSend");
		exit(EXIT_FAILURE);
	}

	printf("received checksum=%d from server\n", incoming_checksum);
	printf("MsgSend return status: %d\n", status);

	return EXIT_SUCCESS;
}

