while true 
do
PACKET=$(nc -l -p 10001)
IPADDR=$(echo $PACKET | cut -d ',' -f1)
NICK=$(echo $PACKET | cut -d ',' -f2)
echo "IP ADDR = $IPADDR"
echo "NICK = $NICK"

PATTERN="$IPADDR,$NICK"
FILE="tablo.txt"
if grep -q $PATTERN $FILE;
 then
    echo "existing person not added"
 else
    echo "non-existent adding to table"
	echo "$IPADDR,$NICK" >> tablo.txt
fi

done