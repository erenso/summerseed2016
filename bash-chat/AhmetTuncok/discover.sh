for x in {1..254}
do
output=$(echo "172.16.5.103,ahmet" | nc -w 1 172.16.5.$x 10000)
if(($? == 0))
then
echo "172.16.5.$x is added."
else
echo "172.16.5.$x is offline."
fi
done
