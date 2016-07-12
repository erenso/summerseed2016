while true; do

	PACKET=$(nc -l 10001)
	ip=$(echo $PACKET | cut -d ',' -f1)
	nick=$(echo $PACKET | cut -d ',' -f2)
	echo "IP ADDRESS: $ip"
	echo "NICK: $nick"

done
