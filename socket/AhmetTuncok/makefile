edit : chatter.o nc.o responseModule.o requestModule.o \
	discoverModule.o userModule.o listenModule.o sendModule.o
	cc -o edit chatter.o nc.o responseModule.o requestModule.o \
	discoverModule.o userModule.o listenModule.o sendModule.o -lpthread

chatter.o : chatter.c responseModule.h requestModule.h discoverModule.h listenModule.h sendModule.h userModule.h
	cc -c chatter.c 
nc.o :	nc.c nc.h
	cc -c nc.c 
responseModule.o : responseModule.c responseModule.h
	cc -c responseModule.c 
requestModule.o : requestModule.c requestModule.h
	cc -c requestModule.c 
discoverModule.o : discoverModule.c discoverModule.h userModule.h nc.h
	cc -c discoverModule.c 
userModule.o : userModule.c userModule.h
	cc -c userModule.c 
listenModule.o : listenModule.c listenModule.h userModule.h
	cc -c listenModule.c 
sendModule.o : sendModule.c sendModule.h
	cc -c sendModule.c 

clean : 
	rm chatter.o nc.o responseModule.o requestModule.o \
	discoverModule.o userModule.o listenModule.o sendModule.o
