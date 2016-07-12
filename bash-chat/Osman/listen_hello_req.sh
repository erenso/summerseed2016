#!/bin/bash

while  true ; do
	echo "Osman Request"
	PACKET=$(nc -l 10000)
	ADDRESS=$(echo $PACKET | cut -d ',' -f1)
	NICK=$(echo $PACKET |cut -d ',' -f2)
	echo "ADDRESS = $ADDRESS"
	echo "NICK = $PACKET"
	
	#http://stackoverflow.com/questions/2480584/how-do-i-use-a-file-grep-comparison-inside-a-bash-if-else-statement
	if grep --quiet "$ADDRESS"  requestID.txt; then
	  echo "exists"
	else
	 	echo "$ADDRESS,$NICK" >> requestID.txt
	fi
	echo "Finish Request"
	
done
