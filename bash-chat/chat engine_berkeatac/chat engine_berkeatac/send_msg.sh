while true 
do

echo "people known are:"

while read line
do
    echo $line | cut -d ',' -f2
done < tablo.txt

echo "enter recipient: "
read name
echo "enter message: "
read message

line=$(grep $name tablo.txt)
IPADDR=$(echo $line | cut -d ',' -f1)

echo "berke,$message" | nc -c $IPADDR 10002

done