all:
	rm -f nc listen request disc  	
	
	gcc -c listen_request.c
	gcc listen_request.o -o listen_request
	gcc -c listen_response.c
	gcc listen_response.o -o listen_response
	gcc -c  discovery.c
	gcc -pthread discovery.o -o disc
	gcc -c  send_message.c
	gcc -c receive_message.c
	gcc send_message.o -o sendM
	gcc receive_message.o -o recM
	
