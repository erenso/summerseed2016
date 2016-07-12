while true; do 
PACKET=$(nc -l 10000)
IPADDR=$(echo $PACKET | cut -d ',' -f1)
NICK=$(echo $PACKET | cut -d ',' -f2)
echo "IP ADDRESS = $IPADDR"
echo "NICK = $NICK"
echo "172.16.5.103,ahmet" | nc $IPADDR 10001
if grep -cq "$IPADDR" addressBook.txt
then
	echo "$NICK is already added."
else
	echo "$IPADDR,$NICK" >> addressBook.txt
	echo "$NICK is added."
fi
echo ""
done

