while true; do

List=$(cat adressbook2.txt | cut -d ',' -f1 |sort -u)
echo $List

echo "NICK?"
read -r  NICK

IP=$(cat addressbook2.txt | grep $NICK | cut -d ',' -f1 | sort -u)

MY_NICK="ae"

echo "Message?"
read -r Mes
MY_MES=$Mes

echo $MY_NICK,$MY_MES | nc $IP 10002

done
