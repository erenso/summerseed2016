#!/bin/bash


while true;
	
	do
		
		PACKET_REQ=$(nc -l 10001)
		
		IPADDR=$(echo $PACKET_REQ | cut -d ',' -f1)
		NICK=$(echo $PACKET_REQ | cut -d ',' -f2)
		
		echo "IP ADRRESS: $IPADDR"
		echo "NICK: $NICK "
		
		if grep -q $PACKET_REQ '/home/caner/Desktop/bookmark.txt' ; then
			
			echo "Same nick, not written to file"
		
		else
			
			echo "$PACKET_REQ" >> bookmark1.txt
		
		fi
	
	done
