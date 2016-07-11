#!/bin/bash
while true;do
	PACKET=$(nc -l 10003)
	NICK=$(echo $PACKET | cut -d ',' -f1)
	MESSAGE=$(echo $PACKET | cut -d ',' -f2)

	echo "NickName : $NICK Message : $MESSAGE"
done