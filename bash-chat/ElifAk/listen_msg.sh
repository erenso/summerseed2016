while true; do
PACKET=$(nc -l 10002)
USR=$(echo $PACKET | cut -d ',' -f1)
MSG=$(echo $PACKET | cut -d ',' -f2)
echo "$USR adli kullanicinin mesaji:"
echo "$MSG"
done
