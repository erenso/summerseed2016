rm -f adressbook.txt
touch adressbook.txt

sh listen_req.sh &
sh listen_resp.sh &
sh refresh.sh &
sh discover.sh
 
sleep 3 #wait for responds

cat adressbook.txt

echo "name"
read name

echo "message"
read message

sh send_msg.sh $name $message
