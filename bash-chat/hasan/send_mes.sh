cat ip_nick.txt
while true; do
echo "enter a nick or 'renew':"
read opt
if [ "$opt" = "renew" ]
then
     cat ip_nick.txt
else
     ip=$(cat ip_nick.txt | grep "$opt" | cut -d ',' -f1)
     echo "enter your message"
     read mes
     echo "hasan,$mes" | nc $ip 10002
fi
done
