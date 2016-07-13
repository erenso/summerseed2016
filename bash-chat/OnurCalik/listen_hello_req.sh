while true; do

PACKET=$(nc -l 10000)
IPADDR=$(echo $PACKET | cut -d ',' -f1)
NICK=$(echo $PACKET | cut -d ',' -f2)

echo "IP Adresi(REQ):"=$IPADDR
echo "Nickname(REQ):"=$NICK
echo "request alindi"
echo "172.16.5.150,onur"| nc $IPADDR 10001
echo $NICK"e response yollandı"

echo $PACKET >> kisiler.txt

PACKET=$(nc -l 10001)
IPADDR=$(echo $PACKET | cut -d ',' -f1)
NICK=$(echo $PACKET | cut -d ',' -f2)

echo "IP Adresi(RESP):"=$IPADDR
echo "Nickname(RESP):"=$NICK
echo $NICK"ten response alindi"

echo $PACKET >> kisilerresponse.txt

MESSAGE=$(nc -l 10002)


done


