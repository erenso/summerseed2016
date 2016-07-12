sh message_request.sh &

while true; do
	echo -n "your message:  " 
	read msg 
	sh message_send.sh $msg 
done
FOO_PID=$!
kill $FOO_PID