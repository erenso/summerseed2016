cat ip_nick.txt
while true; do
echo "enter an IP or 'renew':"
read opt
if [ "$opt" = "renew" ]
then
     cat ip_nick.txt
else
     echo "enter your message"
     read mes
     echo "hasan,$mes" | nc $opt 10002
fi
done
