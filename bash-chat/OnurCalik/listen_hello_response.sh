while true: do

PACKET=$(nc -l 10001)
IPADDR=$(echo $PACKET | cut -d ',' -f1)
NICK=$(echo $PACKET | cut -d ',' -f2)

echo "IP Adresi:"=$IPADDR
echo "Nickname:"=$NICK

echo $PACKET >> kisilerresponse.txt

done
