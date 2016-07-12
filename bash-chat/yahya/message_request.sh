# gelen mesajlari dinleyen betik
while true; do
	
	PACKET=$(nc -l 10002)
	NICK=$(echo $PACKET | cut -d ',' -f1)
	MESSAGE=$(echo $PACKET | cut -d ',' -f2)
	echo "$NICK: $MESSAGE"
	
done
