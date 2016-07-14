all:
	rm -f nc listen request disc  	
	
	gcc -c client1.c
	gcc client1.o -o nc
	gcc -c client2.c
	gcc client2.o -o request
	gcc -c  discovery.c
	gcc -pthread discovery.o -o disc
