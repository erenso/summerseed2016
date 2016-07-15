edit : soc.o send_msg.o responseModule.o requestModule.o \
	broadcastModule.o usrModule.o listenModule.o senderModule.o
	cc -o edit soc.o send_msg.o responseModule.o requestModule.o \
	 broadcastModule.o usrModule.o listenModule.o senderModule.o -lpthread

soc.o : soc.c soc.h
	cc -c soc.c
send_msg.o : send_msg.c responseModule.h requestModule.h  broadcastModule.h listenModule.h senderModule.h usrModule.h
	cc -c send_msg.c -lpthread
responseModule.o : responseModule.c responseModule.h soc.h
	cc -c responseModule.c -lpthread
requestModule.o : requestModule.c requestModule.h
	cc -c requestModule.c -lptread
broadcastModule.o : broadcastModule.c broadcastModule.h usrModule.h soc.h
	cc -c broadcastModule.c -lpthread
usrModule.o : usrModule.c usrModule.h
	cc -c usrModule.c -lpthread
listenModule.o : listenModule.c listenModule.h usrModule.h
	cc -c listenModule.c -lpthread
senderModule.o : senderModule.c senderModule.h
	cc -c senderModule.c -lpthread
clean : 
	rm send_msg.o soc.o responseModule.o requestModule.o \
	usrModule.o broadcastModule.o listenModule.o senderModule.o
