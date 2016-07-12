for i in {2..254} #search all addresses
do
#nc -w 1sec #set time out to 1 sec

#MYIP=$((ifconfig | grep 172) | cut -d ' ' -f2) #get this machines IP chance num if needed 

#ADDRS=$(echo "172.16.5.$i") #generate send address

MYIP=$(ipconfig getifaddr en0)
hAD=$(echo "$MYIP" |  cut -d '.' -f1-3) #get x.x.x part of IP
ADDRS=$(echo "$hAD.$i") #get .x part of IP 
echo "$MYIP,ys" | nc $ADDRS 10000 &
PID=$!
sleep 0.01
kill $PID &
done
clear

echo "All requests send"