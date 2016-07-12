while true 
do
echo "enter recipient: "
read name
echo "enter message: "
read message

line=$(grep $name tablo.txt)
IPADDR=$(echo $line | cut -d ',' -f1)

echo "berke,$message" | nc -c $IPADDR 10002

done