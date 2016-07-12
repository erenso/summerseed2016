#!/bin/bash


while true;
	
	do
		
		PACKET_RESP=$(nc -l 10000)
		
		IPADDR=$(echo $PACKET_RESP | cut -d ',' -f1)
		NICK=$(echo $PACKET_RESP | cut -d ',' -f2)
		
		echo "IP ADRRESS: $IPADDR"
		echo "NICK: $NICK "

		if grep -q $PACKET_REQ '/home/caner/Desktop/bookmark.txt' ; then
			
			echo "Duplicate, not written to file"
		
		else
			
			echo "$PACKET_REQ" >> bookmark.txt
		
		fi

		echo "Request is acceptted" | nc $IPADDR 10001
	
	done
