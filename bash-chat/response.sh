dizi=""
while true; 
do 	
	PACKET=$(nc -l 10001)
	IPADDR=$(echo $PACKET | cut -d ',' -f1)
	NICK=$(echo $PACKET | cut -d ',' -f2)
	echo "cevap ip adres= $IPADDR"
	echo "-----------evap nick= $NICK"
	dizi=$dizi""$NICK","$IPADDR"\n"
	printf $dizi > address_book.txt
	

done
