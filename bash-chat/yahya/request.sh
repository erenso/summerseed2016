# request dinleyen ve request geldiginde response üreten program

while true; do
	PACKET=$(nc -l 10000)
	IP=$(echo $PACKET | cut -d ',' -f1)
	NICK=$(echo $PACKET | cut -d ',' -f2)

	# request geldikten sonra response üretir
	echo "172.16.5.80,Yahya" | nc $IP 10001 

	if grep -cq "$IP" adres.txt
	then
		echo "$IP $NICK kisilerde mevcut."
	else 
		echo "$IP,$NICK" >> adres.txt
		echo "$IP $NICK kişilere eklendi."
	fi	
done
