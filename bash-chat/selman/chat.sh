#!/bin/bash

#set -x


MYIP=$(ifconfig | grep "inet addr" | tail -n 1 | cut -d ':' -f2 | awk '{print $1}')
ME=$(echo $MYIP | awk -F '[.]' '{print $4}')
LOGFILE="log"

DEFAULT="\e[39m"
GREEN="\e[32m"
YELLOW="\e[93m"
ERRORBG="\e[41m"
DEFAULTBG="\e[49m"


#
#	TODO: Active users pipe
#

function init(){
	if [ ! -f ./known_hosts ]; then
	    touch known_hosts
	fi

	

	trap exit_handler INT
	trap exit_handler EXIT
}



function exit_handler(){
	# OTHER STUFF
	echo "C ya!"
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
			echo "Added $NICK to known_hosts" >> log
		fi

		RESPONSE_RESULT=$(echo $RESPONSE | netcat $IPADDR 10001; echo $?)
		
		log "$PACKET => $RESPONSE_RESULT"
		
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
       sleep 120
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


		EXISTS=$(grep "$NICK" known_hosts | cut -d ',' -f1 | head -n 1 )
		if [ $EXISTS ]; then
			IP=$(echo $EXISTS )
			send_message $IP "$NICK" "$MESSAGE" true &
		else
			echo -e "$ERRORBG$NICK does not exist.$DEFAULTBG"
		fi
	done
}
#	$1 => IP
#	$2 => NICK
#	$3 => MESSAGE
#	$4 => echo?
function send_message(){
	RESULT=$(echo "$USER,$3" | netcat -w 2 $1 10002; echo $?)
	if [ $RESULT -ne 0 ]; then

		if [ "$4" = true ]; then
			echo -e "\n$YELLOW $USER $DEFAULT:$3"
		fi

		log "SEND FAILED $2 : $3"
	else

		if [ "$4" = true ]; then
			echo -e "\n$ERRORBG $USER :$3$DEFAULTBG"
		fi

		log "SEND SUCCESS $2 : $3"
	fi

}

function send_all(){

	for i in `seq 1 254`; do

		if [ $i -eq $ME ];then
			continue
		fi

	    send_message "172.16.5.$i" "/all" "$1" false &
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

		log "$RECEIVED => $NICK: $MESSAGE"
		
	done
		
}

function log(){
	echo "$(clock) $1" >> $LOGFILE 
}

init

discover &

listen_hello_req &

listen_messsage &

message_handler

