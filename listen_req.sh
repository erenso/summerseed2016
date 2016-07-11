while true; do
PACKET=$(nc -l 10000)
IPADDR=$(echo $PACKET | cut -d ',' -f1)
USR=$(echo $PACKET | cut -d ',' -f2)
echo "IP ADDRESS = $IPADDR"
echo "USER NAME = $USR"
echo "172.16.5.83,elif" | nc $IPADDR 10001
echo ""
if grep -cq "$IPADDR" usrtable.txt
then
echo "$IPADDR - $USR zaten var"
else
echo "$PACKET" >> usrtable.txt
echo "$IPADDR - $USR eklendi."
fi
done
