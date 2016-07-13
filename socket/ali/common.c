#include "netcat.h"

// nclisten function does what "nc -l #port" does, argument port is the port to listen to
int nclisten(int port){
	int sockfd, newfd, option = 1;	// sockets and socket options
    struct sockaddr_in serverAddr;	// server addresses
    struct sockaddr_in clientAddr;
    char str[MAX_PACKET_LENGTH];	// to hold incoming message
    int structSize;	
    
    // open the socket
    // parameters mean:	   address family: 	AF_INET (IPv4 socket)
    					// socket type: 	SOCK_STREAM (TCP)
    					// protocol number: 0 (IPPROTO_IP IP protocol)
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));	// this prevents port from going to TIME_WAIT state
																			// in TIME_WAIT state, you can't use that port
    if(-1 == sockfd){
    	// if sockfd returns -1, then there's an error, print the error
        perror("socket");	// perror function prints the error in "$argument: error" format
        					// for example: "socket: Some error"
    }
    
	// sockaddr_in is the simplified form of sockaddr
    serverAddr.sin_family = AF_INET;		// sin_family is address family, in this case IPv4
    serverAddr.sin_port = htons((uint16_t)port);		// sin_port means port, duh. htons is a function used in converting
    										// port host to network short, it converts the little endian format to
    										// big endian if needed
    serverAddr.sin_addr.s_addr = INADDR_ANY;// address, INADDR_ANY is address of the working computer
    memset(&(serverAddr.sin_zero), '\0', 8);// this zeroes are needed to convert sockaddr_in to sockaddr

	// binding is the action of binding a port to an address
	// it is necessary for listening side because the program needs to know which port to listen to
	// it is not necessary for the client, operating system will assign a random unused port
	// for connecting
	// bind function accepts three arguments,		1: sockfd - socket
											 	// 	2: sockaddr* - socket address (we convert our sockaddr_in to sockaddr* here)
											 	// 	3: size of the struct sockaddr, which is constant, 
											 	// 		I don't know why we enter it here manually
    if(-1 == bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr))){
        perror("bind");	// if error, p(rint )error
    }
	
	// listen function starts the listening process on a socket
	// it is used after binding
	// parameters are		1: socket number, sockfd
						//	2: int backlog - number of maximum queue pending connections may grow
    if(-1 == listen(sockfd, 20)){
        perror("listen");	// again, print error
    }

    structSize = sizeof(clientAddr);	// size of the new client address struct
    
    // accept function accepts a connection when listening, it returns a new socket
    // it's parameters are:		1: socket number
    						//	2: struct sockaddr* client socket address (it changes the value, cus it's pointer)
    						// 	3: size_t size of the client address struct
    newfd = accept(sockfd, (struct sockaddr *)&clientAddr, (socklen_t*)&structSize);
    if(-1 == newfd){
        perror("accept");	// perror
    }
    
    // here, we start reading from our new socket, one bit per reading
    // this is the place where our program differs from the netcat program, this is kind of a stupid way to do it
    // this method is slow
    int index = 0;	// first, init an index variable, which holds the index of current read char

	while(1){	// while infinitely
		read(newfd, &str[index], 1);	// read a char and write it to str, last parameter means read character 
		if(str[index] == '\t'){			// if the read character is \t, terminate reading, we reached end of file
			index++;					// increment once more here, for, uh, anyway
			break;						// break our loop
		}
		index++;						// increment index after reading
	}
	
	str[index] = '\0';					// after reading, we have char[] in the form of "xxxx\t????", we turn it into
										// "xxxx\t\0???" so we can find it's length and print it, it's a string now
	
    
    printf("Got %d bytes:\t%s\n", (int)strlen(str), str); // print bytes and reading from socket

    close(newfd);	// close connection socket
    close(sockfd);	// close the socket we listened to
    return 0;		// 0 means alles gut
}



// this function does what "nc ip port" does, it sends a spesific message to an ip:port
// it reads the message from stdin so "echo -e "message\t" | ./nc ip port" works :)
int ncsend(char *ip, int port, char *message){
	if(!isValidIpAddress(ip)){	// check if ip address is valid
		printf("Error: %s is not a valid IP address\n", ip);	// if not, print error and return
		return -1;
	}
	if(strlen(message) > MAX_PACKET_LENGTH){	// if the message which is going to be transmitted is longer than maximum length
		return -1;						// kill the execution and return an error
	}
	int sockfd; // our socket
    struct sockaddr_in serverAddr;	// server address
    ssize_t sentByte;		// sentByte is length of our sent message and we check if it's -1 it means message didn't send

    sockfd = socket(AF_INET, SOCK_STREAM, 0);	// create a new IPv4, TCP, IP Protocol socket
    if(-1 == sockfd){
        perror("socket");
    }

	// create server address
    serverAddr.sin_family = AF_INET;	// IPv4
    serverAddr.sin_port = htons((uint16_t)port);	// port number, converted from little endian to big endian
    // The inet_addr() function shall convert the string pointed to by cp, in the standard IPv4 dotted decimal notation, 
    // to an integer value suitable for use as an Internet address.
    serverAddr.sin_addr.s_addr = inet_addr(ip); // we convert the string ip to IPv4 dotted decimal notation
    memset(&(serverAddr.sin_zero), '\0', 8);	// padding zeroes for conversion

	// connect function connects to a listening socket
	// its parameters are 	1: our socket
						//	2: struct sockaddr* server address, we convert our sockaddr_in here
						// 	3: size of the socket address struct we have
						// I just come to thinking that this size may differ from machine to machine so may be it is why we
						// enter it here manually
    if(-1 == connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr))){
        perror("connect");
    }
    
    // first we translate our message from the form "xxxx\0???" to "xxxx\t\0??", so we add the end of line character
    size_t length = strlen(message);	// length of our current string
    if(message[length-1] == '\n'){
    	message[length-1] = '\t';
    }else{
    	message[length] = '\t';
    	message[length+1] = '\0';
    }	
    // now we converted our message to the desired form

	// so, we already know our messages size, we don't have to send it char by char, we can simply send it via send method
	// send accepts three arguments and sends a message to connected socket, these are: 	1: socket number
																						//	2: message
																						//	3: message length
																						// 	4: some flags, I don't know what 0 means
    sentByte = send(sockfd, message, strlen(message), 0);
    if(-1 == sentByte){  
        perror("send");
    }
    else if(strlen(message) != sentByte){ // if the message length and transmitted message length didn't match
    	// then there's something terrible happened
    	// just print the numbers, we're not going to do anything here other than hoping something terrible didn't happen
    	// on the transmitted side
        printf("Something happended while transmitting!\nMessage length: %d\tTransmitted Length: %d\n", (int)strlen(message), (int)sentByte);
    }
    printf("Sent %d bytes:\t%s to %s\n", (int)sentByte, message, ip);

    close(sockfd);	// close our socket
    return 0;		// 0 means everythings ok
}

// checks if a given IP address valid or not
// source: http://stackoverflow.com/a/792016
int isValidIpAddress(char *ipAddress){
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
    return result != 0;
}
