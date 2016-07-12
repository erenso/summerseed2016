my_nick="seyfullah"
while true;
do


echo "mesaj = "
read mesaj
echo "ip = "
read ip

PACKET2=$(echo "$my_nick,$mesaj" | nc $ip 10002 -w 3)
echo "mesaj gönderildi"


done



