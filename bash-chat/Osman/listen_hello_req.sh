#!/bin/bash

while  true ; do
	echo "Osman Request"
	MY_IP=$(echo "172.16.5.187")
	MY_NICK_NAME=$(echo "OSMAN")
	PACKET=$(nc -l 10000)
	ADDRESS=$(echo $PACKET | cut -d ',' -f1)
	NICK=$(echo $PACKET |cut -d ',' -f2)
	echo "ADDRESS = $ADDRESS"
	echo "NICK = $PACKET"
	
	echo "$MY_IP,$MY_NICK_NAME" | nc $ADDRESS 10001
	if grep --quiet "$ADDRESS"  requestID.txt; then
	  echo "exists"
	else
	 	echo "$ADDRESS,$NICK" >> requestID.txt
	fi
	echo "Finish Request"
	
done
