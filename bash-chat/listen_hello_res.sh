while true; do
PACKET=$(nc -l 10001)
IPADDR=$(echo $PACKET | cut -d ',' -f1)
NICK=$(echo $PACKET | cut -d ',' -f2)
if grep -cq "$IPADDR" ip_nick.txt; 
then
     :
else
     echo "$IPADDR,$NICK" >> ip_nick.txt
fi
done
