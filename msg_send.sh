peer=""
	echo "Enter your peer's nick: "
	read peer

while [$peer!="quit"]
do
	IPADDR=$(cat addressBook.txt | grep "$peer$ | awk '{print $1}')
	if ["$IPADDR"==""]
	then
		echo "There is no peer."
	else
		read msg
		while ["$msg"!="quit"]
		do
			echo "ahmet: " $msg | nc $IPADDR 10002
			read msg
		done
	fi
	echo "peer: "
	read peer
done
