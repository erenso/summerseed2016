#!/bin/bash


while true;
	
	do
		
		PACKET_RESP=$(nc -l 10001)
		
		IPADDR=$(echo $PACKET_RESP | cut -d ',' -f1)
		NICK=$(echo $PACKET_RESP | cut -d ',' -f2)
		
		echo "IP ADRRESS: $IPADDR"
		echo "NICK: $NICK "

		CURRENT=`pwd`
		CURRENT="$PWD/bookmark.txt"

		if grep -q $PACKET_REQ $CURRENT ; then
			
			echo "Duplicate, not written to file"
		
		else
			
			echo "$PACKET_REQ" >> bookmark.txt
		
		fi

	
	done
