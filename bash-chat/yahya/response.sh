# response dinleyen program

while true; do
	PACKET=$(nc -l 10001)
	IP=$(echo $PACKET | cut -d ',' -f1)
	NICK=$(echo $PACKET | cut -d ',' -f2)
	
	if grep -q "$IP" adres.txt
	then 
		echo "$IP $NICK kisilerde mevcut."
	else 
		echo "$IP,$NICK" >> adres.txt
		echo "$IP $NICK kisilere eklendi."
	fi
done
