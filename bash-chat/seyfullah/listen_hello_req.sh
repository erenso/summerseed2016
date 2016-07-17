gnome-terminal -e ./send.sh
while true; 
do 

	PACKET=$(nc -l 10000)	
	IPADDR=$(echo $PACKET | cut -d ',' -f1)
	NICK=$(echo $PACKET | cut -d ',' -f2)
	echo "istek gelen ip adres= $IPADDR"
	echo "istek gelen nick= $NICK"

	my_nick="seyfullah"
	my_ip=$(hostname -I)
	PACKET2=$(echo "$my_ip,$my_nick" | nc $IPADDR 10001)
	echo "cevap gönderildi"
	echo "-------------------------------------------------------"

done
