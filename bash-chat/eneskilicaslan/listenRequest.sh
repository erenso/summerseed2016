
echo -e "\c" > /home/parallels/Desktop/addressBook.txt
cat /home/parallels/Desktop/addressBook.txt
my_ip=$(ifconfig | awk '/inet addr/{print substr($2,6)}' | grep 172)

while true; do 

request=$(nc -l 10000)

ipaddr=$(echo $request | cut -d ',' -f1)
echo "$ipaddr"
printf "%s\n" "${request[@]}" >> /home/parallels/Desktop/addressBook.txt

packet2=$(echo "$my_ip,enes" | nc $ipaddr 10001)

done

