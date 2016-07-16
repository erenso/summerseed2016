all:
	gcc -o discover discovery.c sender.c -lpthread
	gcc -o listenreq listenreq.c listener.c sender.c
	gcc -o listenresp listenresp.c listener.c sender.c
	gcc -o listenmsg listenmsg.c listener.c sender.c
	gcc -o sendmsg sendmsg.c sender.c
