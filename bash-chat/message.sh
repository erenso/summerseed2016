echo "mesajlarrrrrrrr"
while true; 
do 	
	PACKET=$(nc -l 10002)
	NICK=$(echo $PACKET | cut -d ',' -f1)
	MESSAGE=$(echo $PACKET | cut -d ',' -f2)
	echo "mesaj nick= $NICK"
	echo "mesaj mesaj= $MESSAGE"

done
