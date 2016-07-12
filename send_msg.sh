echo "Write broadcast if you want to speak to all or write the name of the person you want to speak or write quit to quit this bash."
echo "Enter the name of the person you want to send message: "
read PERSON
while [ "$PERSON" != "quit" ]
do
	if [ "$PERSON" != "broadcast" ]
	then
		IP=$(cat class.txt | grep $PERSON | awk '{print $1}')
		if [ $IP != "" ]
		then
			echo "Write quit to the quit from message option."			
			echo "Enter the message you want to send: "
			read MSG
			while [ "$MSG" != "quit" ]
			do
				echo "özgün,$MSG" | nc $IP 10002			
				echo "Enter the message you want to send: "
				read MSG
			done
		else
			echo "There is no such client."
		fi
		echo "Enter the name of the person you want to send message: "
		read PERSON
	else
		echo "Send message to all: "
		read MESSAGE
		while [ "$MESSAGE" != "quit" ]
		do
			for i in {1..254}
			do
				echo "özgün,$MESSAGE" | nc -w 1 172.16.5.$i 10002 &
			done
			echo "Send message to all: "
			read MESSAGE
		done
		echo "Enter the name of the person you want to send message: "
		read PERSON
	fi
done
