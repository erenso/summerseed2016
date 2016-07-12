rm -f adressbook.txt
touch adressbook.txt

sh listen_req.sh &
sh listen_resp.sh &
sh refresh.sh &
sh discover.sh
 
sleep 3 #wait for responds

while true; do

cat adressbook.txt

echo "name"
read name

echo "message"
read message

sh send_msg.sh $name $message

echo "0 for exit, 1 for continue"
read d

# echo $d

if [ $d -eq 0 ]; then
break
fi

done

killall sh listen_req.sh
killall sh listen_resp.sh
killall sh refresh.sh
killall nc
