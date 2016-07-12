while true;do
packet=$(nc -l 10002)
NICK=$(echo $packet | cut -d ',' -f1)
Mesge=$(echo $packet |cut -d ',' -f2)
echo "$NICK: $Mesge"
done
