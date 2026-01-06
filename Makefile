
#
#	Makefile for hello project
#

DEBUG = -g
CC = qcc
LD = qcc


TARGET = -Vgcc_ntox86_64
#TARGET = -Vgcc_ntoaarch64le


CFLAGS += $(DEBUG) $(TARGET) -Wall
LDFLAGS+= $(DEBUG) $(TARGET)

all:	name_lookup_client name_lookup_server

name_lookup: name_lookup_client name_lookup_server

Client_Server:
	$(CC) $(CFLAGS) -o Client_Server Client_Server.c $(LDFLAGS)

affinity_test:
	$(CC) $(CFLAGS) -o affinity_test Affinity_test.c $(LDFLAGS)

name_lookup_client:
	$(CC) $(CFLAGS) -o name_lookup_client Name_lookup_client.c $(LDFLAGS)

name_lookup_server:
	$(CC) $(CFLAGS) -o name_lookup_server Name_lookup_server.c $(LDFLAGS)

clean_soln:
	rm -f *.o Client_Server affinity_test
