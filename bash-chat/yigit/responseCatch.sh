#packet= IP,nickname
#addr book= nickname,IP

while true;do
PACKT=$(nc -l 10001) #wait for packet
IPADD=$(echo "$PACKT" | cut -d ',' -f1) #cut IP from packet
NIC=$(echo "$PACKT" | cut -d ',' -f2) #cut nickname from packet

touch Addr_Book.txt   #address book

echo "$NIC ($IPADD) Added"


echo "$NICK,$IPADDR" >> Addr_Book

sort Addr_Book | uniq  > Addr_Book

done



