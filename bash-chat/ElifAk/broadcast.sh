
for x in {1..254}
do
REQUEST=$(echo "172.16.5.76,elif" | nc -w 1 172.16.5.$x 10000)
if(($? == 0))
then
echo "172.16.5.$x eklendi."
else
echo "172.16.5.$x is offline"
fi
done
