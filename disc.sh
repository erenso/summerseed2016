for ((i=5;i<=254;i++))
do

MY_ADDRESS="172.16.5.50"
NICK="alp"

echo $NICK,$MY_ADDRESS | nc 172.16.5.$i 10000

done
