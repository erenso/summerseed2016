#!/bin/bash

#set -x


MYIP=$(ifconfig | grep "inet addr" | tail -n 1 | cut -d ':' -f2 | awk '{print $1}')
PIDFIFO="/tmp/chat-pids-fifo"

DEFAULT="\e[39m"
GREEN="\e[32m"
YELLOW="\e[93m"

function init(){
	if [ ! -f ./known_hosts ]; then
	    touch known_hosts
	fi

	

	trap exit_handler INT
	trap exit_handler EXIT
}



function exit_handler(){
	rm $PIDFIFO
	exit
}


function listen_hello_req(){


	while true; do
		PACKET=$(nc -l 10000)
		if [ "$PACKET" == "" ];then
			continue
		fi

		IPADDR=$(echo $PACKET | cut -d ',' -f1  | sed 's/ //g')
		NICK=$(echo $PACKET | cut -d ',' -f2)

		if [ "$IPADDR" ==  "$MYIP" ]; then
			echo "You can't send request to yourself"
			continue
		fi

		RESPONSE="$MYIP,$USER"

		if  ! grep -q "$IPADDR,$NICK" known_hosts; then
			echo "$IPADDR,$NICK" >> known_hosts
		fi

		RESPONSE_RESULT=$(echo $RESPONSE | netcat $IPADDR 10001; echo $?)
		
		echo "$(clock) $PACKET => $RESPONSE_RESULT" >> log
		
	done
		
}
function listen_hello_resp(){


	while true; do
		PACKET=$(nc -l 10001)
		if [ "$PACKET" == "" ];then
			continue
		fi

		IPADDR=$(echo $PACKET | cut -d ',' -f1  | sed 's/ //g')
		NICK=$(echo $PACKET | cut -d ',' -f2)

		if [ "$IPADDR" ==  "$MYIP" ]; then
			echo "You can't send request to yourself"
			continue
		fi


		RESPONSE="$MYIP,$USER"

		if  ! grep -q "$IPADDR,$NICK" known_hosts; then
			echo "$IPADDR,$NICK" >> known_hosts
		fi

	done
		
}

function discover(){

	while true; do

	   for i in `seq 1 254`;
       do
               ping_it $i &
       done 
       echo "Refreshing known_hosts" >> log
       sleep 10
   done
}



function ping_it(){
	IP="172.16.5.$1"
	if [ "$IP" ==  "$MYIP" ]; then
		return
	fi

	RESULT=$(echo "$MYIP,$USER" | netcat -w 2 "$IP" 10000)


	#result=$(timeout 3 ping -c 2 $IP > /dev/null 2>&1; echo $?)
	# if [ $result -eq 0 ]; then
	# 	RESULT=$(echo "$MYIP,$USER" | netcat -w 2 $IP 10000)
		
	# fi

	#echo "$IP => $result"
}


function message_handler(){
	while true; do
		printf "\n[nick:message] :  "
		read input

		if [ "$input" == "" ]; then 
			continue
		fi

		NICK=$(echo $input | cut -d ',' -f1 | sed 's/ //g')
		MESSAGE=$(echo $input | cut -d ',' -f2 )

		if [ "$NICK" == "/all" ]; then
			send_all "$MESSAGE" &
			continue
		fi


		EXISTS=$(grep "$NICK" known_hosts )
		if [ $EXISTS ]; then
			IP=$(echo $EXISTS | cut -d ',' -f1)
			send_message $IP "$NICK" "$MESSAGE" &
		else
			echo "$NICK does not exist."
		fi
	done
}
#	$1 => IP
#	$2 => NICK
#	$3 => MESSAGE
function send_message(){
	RESULT=$(echo "$USER,$3" | netcat -w 2 $1 10002; echo $?)
	if [ $RESULT -ne 0 ]; then
		echo "$(clock) SEND FAILED $2 : $3" >> log
	else
		echo "$(clock) SEND SUCCESS $2 : $3" >> log
	fi

}

function send_all(){
	   for i in `seq 1 254`; do
            send_message "172.16.5.$i" "/all" "$1" &
       done
   		echo -e "\n$YELLOW $USER $DEFAULT:$1"

}

function listen_messsage(){
	while true; do
		PACKET=$(nc -l 10002)
		if [ "$PACKET" == "" ];then
			continue
		fi

		NICK=$(echo $PACKET | cut -d ',' -f1  | sed 's/ //g')
		MESSAGE=$(echo $PACKET | cut -d ',' -f2)

		echo -e "\n$GREEN $NICK $DEFAULT: $(echo -e $MESSAGE)"

		echo "$(clock) $RECEIVED => $NICK": $MESSAGE >> log
		
	done
		
}

init

discover &

listen_hello_req &

listen_messsage &

message_handler

