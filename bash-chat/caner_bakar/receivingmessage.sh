#!/bin/bash

while true;
	do
		
		PACKET_REQ=$(nc -l 10002)
		NICK=$(echo $PACKET_REQ | cut -d ',' -f1)
		MESSAGE=$(echo $PACKET_REQ | cut -d ',' -f2)
		
		echo "Nick: $NICK"
		echo "Message: $MESSAGE "
			
	done


