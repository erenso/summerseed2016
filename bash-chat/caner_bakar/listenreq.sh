#!/bin/bash


while true;
	
	do
		
		PACKET_REQ=$(nc -l 10000)
		
		IPADDR=$(echo $PACKET_REQ | cut -d ',' -f1)
		NICK=$(echo $PACKET_REQ | cut -d ',' -f2)
		
		echo "IP ADRRESS: $IPADDR"
		echo "NICK: $NICK "

		CURRENT=`pwd`
		CURRENT="$PWD/bookmark.txt"
		echo CURRENT
		
		if grep -q $PACKET_REQ $CURRENT ; then
			
			echo "Same nick, not written to file"
		
		else
			
			echo "$PACKET_REQ" >> bookmark1.txt
		
		fi
	
	done
