while true; do
PACKET=$(nc -l 10001)
IPADDR=$(echo $PACKET | cut -d ',' -f1)
NICK=$(echo $PACKET | cut -d ',' -f2)
echo "RESP:"
echo "IP ADDRESS = $IPADDR / NICK = $NICK"
echo ""
if grep -cq "$IPADDR" addressBook.txt
then
        echo "$NICK is already added."
else
        echo "$IPADDR,$NICK" >> addressBook.txt
        echo "$NICK is added."
fi
done
