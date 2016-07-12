my_nick="bekircan"

target_ip="$(cat adressbook.txt | grep $1 | cut -d ',' -f1)"

echo "$my_nick, $2" | nc $target_ip 10002 -w3
