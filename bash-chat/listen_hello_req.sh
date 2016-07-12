while true; do
PACKET=$(nc -l 10000)
IPADDR=$(echo $PACKET | cut -d ',' -f1)
NICK=$(echo $PACKET | cut -d ',' -f2)
echo "172.16.5.194,hasan" | nc -w 1 $IPADDR 10001 &
if grep -cq "$IPADDR" ip_nick.txt; 
then
     :
else
     echo "$IPADDR,$NICK" >> ip_nick.txt
fi
done
