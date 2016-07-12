while true;do
packet=$(nc -l 10001)
IP=$(echo $packet| cut -d ',' -f1)
NICK=$(echo $packet| cut -d ',' -f2)
if grep -q "$IP" class.txt
then
echo "$IP $NICK listemde var."
else
echo "$IP,$NICK" >> class.txt
fi
done
