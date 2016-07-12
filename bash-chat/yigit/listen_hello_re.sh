#packet= IP,nickname
#addr book= nickname,IP

while true;do
PACKET=$(nc -l 10000) #wait for packet
IPADDR=$(echo "$PACKET" | cut -d ',' -f1) #cut IP from packet
NICK=$(echo "$PACKET" | cut -d ',' -f2) #cut nickname from packet
#MYIP=$((ifconfig | grep 172) | cut -d ' ' -f2) #get this machines IP chance num if needed  
MYIP=$(ipconfig getifaddr en0) #get this machines IP (works only on MacOS)
echo "$MYIP,ys" | nc $IPADDR 10001  #send response


echo "$NICK,$IPADDR" >> Addr_Book

sort Addr_Book | uniq  > Addr_Book

done

