while true; do
PACKET=$(nc -l 10002)
NICK=$(echo $PACKET | cut -d ',' -f1)
MSG=$(echo $PACKET | cut -d ',' -f2)
echo "NICK = $NICK"
echo "MESSAGE = $MSG"
echo ""
done
