#!/bin/bash

MYIP=$(ifconfig | grep "inet addr" | tail -n 1 | cut -d ':' -f2 | awk '{print $1}')

function init(){
	if [ ! -f ./known_hosts ]; then
	    touch known_hosts
	fi
}


function listen(){


	while true; do
		PACKET=$(nc -l 10000)
		IPADDR=$(echo $PACKET | cut -d ',' -f1  | sed 's/ //g')
		NICK=$(echo $PACKET | cut -d ',' -f2)

		if [ "$IPADDR" ==  "$MYIP" ]; then
			echo "You can't send request to yourself"
			continue
		fi

		RESPONSE="$MYIP,$USER"



		RESPONSE_RESULT=$(echo $RESPONSE | netcat -w 2 $IPADDR 10001; echo $?)
		echo $RESPONSE_RESULT

		if [ $RESPONSE_RESULT -eq 1 ] ; then
			echo "Can not send response $RESPONSE to $IPADDR, user $NICK"
				
		else
			echo "$IPADDR => $NICK"
			if  ! grep -q "$IPADDR,$NICK" known_hosts; then
				echo "$IPADDR,$NICK" >> known_hosts
			fi

		fi

		echo "$(clock) $PACKET => $RESPONSE_RESULT" >> log &
		
	done
		
}


function discover(){

	   for i in `seq 1 254`;
       do
               ping_it $i &
       done 
}



function ping_it(){
	IP="172.16.5.$1"
	if [ "$IP" ==  "$MYIP" ]; then
		return
	fi
	result=$(timeout 3 ping -c 2 $IP > /dev/null 2>&1; echo $?)
	if [ $result -eq 0 ]; then
		echo "$MYIP:$USER" | netcat -w 2 $IP 10000
		#echo "yep $IP"
	fi
}


# function message_handler(){
# 	while true; then
# 		read input
# 		parsed_input=$(echo $input | cut -d ',' -f1 )
# }

init

discover &

listen


