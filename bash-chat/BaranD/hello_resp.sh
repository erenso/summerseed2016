while true; do
	PACKET=$(nc -l 10001)
	IP=$(echo $PACKET | cut -d ',' -f1)
	NICK=$(echo $PACKET | cut -d ',' -f2)
	
	
	
	if ! grep -q "$IP" addressbook.txt
		then
		echo "$IP $NICK" >> addressbook.txt
		echo "$NICK, $IP IP numarasıyla arkadaşın oldu."
	fi
done
