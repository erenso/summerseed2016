# requestleri dinleyen ve request geldiginde response ureten program

while true; do
	PACKET=$(nc -l 10000)
	IP=$(echo $PACKET | cut -d ',' -f1)
	NICK=$(echo $PACKET | cut -d ',' -f2)

	echo "172.16.5.217,ali" | nc $IP 10001 # request geldikten sonra response uret

	if grep -cq "$IP" people.txt
	then
		echo -e "\033[0;33m$IP $NICK zaten kisilerde mevcut."
	else 
		echo -e "\033[0;33m$IP,$NICK" >> people.txt
		echo -e "\033[0;33m$IP $NICK kisilere eklendi."
	fi	
done
