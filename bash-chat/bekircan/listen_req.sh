host="172.16.5.233"
my_nick="bekircan"

while true; do

str="$(nc -l 10000)"
ip="$(echo $str | cut -d ',' -f1)"


if !(grep -cq "$ip" adressbook.txt)
then
# echo $str
echo "$str" >> "adressbook.txt"
fi

echo "$host,$my_nick" | nc $ip 10001 -w 3&

done
