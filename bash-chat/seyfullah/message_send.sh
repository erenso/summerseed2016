my_nick="seyfullah"
while true;
do


echo "mesaj = "
read mesaj
echo "nick = "
read nick

IP=$(cat address_book.txt | grep "$nick" |  cut -d ',' -f2)
PACKET2=$(echo "$my_nick,$mesaj" | nc $IP 10002 -w 3)
echo "mesaj gönderildi"


done



