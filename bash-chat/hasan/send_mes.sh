cat ip_nick.txt
while true; do
read opt
if [ "$opt" = "renew" ]
then
     cat ip_nick.txt
else
     read mes
     echo "hasan,$mes" | nc $opt 10002
fi
done
