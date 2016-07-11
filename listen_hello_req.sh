#!/bin/bash

while  true ; do
	MY_IP=$(echo "172.16.5.187")
	MY_NICK_NAME=$(echo "OSMAN")
	for i in `seq 1 255` ;
		do
			echo "$MY_IP,$MY_NICK_NAME" | nc -w 3 172.16.5.$i 10001 > file.txt &
			echo "Osman Request"
			PACKET=$(nc -l 10000)
			ADDRESS=$(echo $PACKET | cut -d ',' -f1)
			NICK=$(echo $PACKET |cut -d ',' -f2)
			echo "ADDRESS = $ADDRESS"
			echo "NICK = $PACKET"
			echo "Finish Request"
		done
	
done
