while true;do
packet=$(nc -l 10000)
IP=$(echo $packet|cut -d ',' -f1)
NICK=$(echo $packet|cut -d ',' -f2)
echo "172.16.5.235,anil" | nc $IP 10001

if ! grep -q "$IP" class.txt
then
echo "$IP $NICK" >> class.txt
echo "$IP,$NICK eklendi."
fi
done


