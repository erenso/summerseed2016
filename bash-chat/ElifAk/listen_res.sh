while true; do
PACKET=$(nc -l 10001)
IPADDR=$(echo $PACKET | cut -d ',' -f1)
USR=$(echo $PACKET | cut -d ',' -f2)
echo "RES: IP ADDRESS = $IPADDR"
echo "RES: USER NAME = $USR"
echo ""
if grep -cq "$IPADDR" usrtable.txt
then
echo "$IPADDR - $USR zaten var"
else
echo "$PACKET" >> usrtable.txt
echo "$IPADDR - $USR eklendi."
fi
done
