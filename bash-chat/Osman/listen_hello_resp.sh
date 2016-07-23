#!/bin/bash

while true ; do
	echo "MY_IP : $MY_IP"
	echo "MY_NICK_NAME : $MY_NICK_NAME"
	echo "I am waiting a host request"
	
	PACKET=$(nc -l 10001)
	ADDRESS=$(echo $PACKET | cut -d ',' -f1)
	NICK=$(echo $PACKET | cut -d ',' -f2)
	
	echo "Get a request"	
	echo "ADDRESS=$ADDRESS"
	echo "NICK=$NICK"

	if grep --quiet "$ADDRESS"  resPonseId.txt; then
	  echo "exists"
	else
	 	echo "$ADDRESS,$NICK" >> resPonseId.txt
	fi
	
	echo "Accept request"
	echo "----------------------------"
	echo ""
done
