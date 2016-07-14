all:
	rm -f common.o nc discovery listen
	gcc -c common.c
	gcc nc.c common.o -o nc
	gcc discovery.c common.o -o discovery -lpthread
	gcc listen_requests.c common.o -o listen_req
	gcc listen_responses.c common.o -o listen_resp
	gcc listen_messages.c common.o -o listen_mesg
	rm common.o