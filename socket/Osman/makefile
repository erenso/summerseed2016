all:
	rm -f nc listen request disc  	
	
	gcc -c listen_request.c
	gcc listen_request.o -o nc
	gcc -c client2.c
	gcc client2.o -o request
	gcc -c  discovery.c
	gcc -pthread discovery.o -o disc
	gcc -c  send_message.c
	gcc -c receive_message.c
	gcc send_message.o -o sendM
	gcc receive_message.o -o recM
	
