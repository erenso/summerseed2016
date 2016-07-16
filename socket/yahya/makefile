all: 

	rm -f func.o net discovery listen
	gcc -c func.c
	gcc net.c func.o -o net
	gcc discovery.c func.o -o discovery -lpthread
	gcc listen_requests.c func.o -o listen_req
	gcc listen_responses.c func.o -o listen_resp
	gcc listen_messages.c func.o -o listen_mesg
	gcc send_msg.c func.o -o send -lpthread
	rm func.o