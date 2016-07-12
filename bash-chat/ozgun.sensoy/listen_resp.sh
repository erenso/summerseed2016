while true;
do
	PACKET=$(nc -l 10001)
	IP=$(echo $PACKET | cut -d ',' -f1)
	NICK=$(echo $PACKET | cut -d ',' -f2)

	if ! grep -q "$IP" class.txt
	then
		echo "$IP	$NICK" >> class.txt
		echo "$IP,$NICK added successfully."
	fi
done
