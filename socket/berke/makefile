all:
	rm -f listen_req listen_resp discover send_msg 	
	
	gcc -c hello_listen_req.c
	gcc hello_listen_req.o -o listen_req
	gcc -c hello_listen_resp.c
	gcc hello_listen_resp.o -o listen_resp
	gcc -c  discover.c
	gcc discover.o -o discover -lpthread
	gcc -c send_msg.c
	gcc send_msg.o -o send_msg
	gcc -c listen_chat.c
	gcc listen_chat.o -o listen_chat