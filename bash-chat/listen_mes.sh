while true; do
NEWMES=$(nc -l 10002)
nick=$(echo $NEWMES | cut -d ',' -f1)
mes=$(echo $NEWMES | cut -d ',' -f2)
echo "$nick: $mes"
done

