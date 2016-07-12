while true;
do
	PACKET=$(nc -l 10000)
	IP=$(echo $PACKET | cut -d ',' -f1)
	NICK=$(echo $PACKET | cut -d ',' -f2)

	echo "172.16.5.142,özgün" | nc $IP 10001

	if ! grep -q "$IP" class.txt
	then
		echo "$IP	$NICK" >> class.txt
		echo "$IP,$NICK added successfully."
	fi
done
