all:
	rm -f common.o nc discovery listen
	gcc -c common.c
	gcc nc.c common.o -o nc
	gcc discovery.c common.o -o discovery -lpthread
	gcc listen_requests.c common.o -o listen
	rm common.o
