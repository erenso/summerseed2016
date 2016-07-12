while true; do
	PACKET=$(nc -l 10000)
	IP=$(echo $PACKET | cut -d ',' -f1)
	NICK=$(echo $PACKET | cut -d ',' -f2)

	echo "172.16.5.145,Baran" | nc $IP 10001

	if ! grep -q "$IP" addressbook.txt
		then
		echo "$IP $NICK" >> addressbook.txt
		echo "$NICK, $IP IP numarasıyla arkadaşın oldu."
	fi
done
