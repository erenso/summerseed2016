while true; do

PACKET=$(nc -l 10000)
NICK=$(echo $PACKET | cut -d ',' -f2)
IPADDRESS=$(echo $PACKET | cut -d ',' -f1)

echo $IPADDRESS,$NICK >> addresbook.txt

done

