echo "Enter your peer's nick: "
read PEER

while [ "$PEER" != "quit" ]
do
	IPADDR=$(cat addressBook.txt | grep "$PEER" | cut -d ',' -f1)
	echo "IP Address: $IPADDR"
	if [ "$IPADDR" == "" ]
	then
		echo "There is no peer."
	else
		echo "Your message: "
		read msg
		while [ "$msg" != "quit" ]
		do
			echo "ahmet,$msg" | nc $IPADDR 10002
			read msg
		done
	fi
	echo "Peer: "
	read PEER
done
