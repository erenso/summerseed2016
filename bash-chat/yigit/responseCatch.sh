#packet= IP,nickname
#addr book= nickname,IP

while true;do
PACKT=$(nc -l 10001) #wait for packet
IPADD=$(echo "$PACKT" | cut -d ',' -f1) #cut IP from packet
NIC=$(echo "$PACKT" | cut -d ',' -f2) #cut nickname from packet


echo "$NIC ($IPADD) Responded"

cat Addr_Book.txt > log.txt

echo "$NIC,$IPADD" >> log.txt

sort log.txt | uniq  > Addr_Book.txt

done



