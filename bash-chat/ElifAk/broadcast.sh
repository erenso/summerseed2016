
for x in {1..254}
do
OUTPUT=$(nc -q 1 -w 1 172.16.5.$x 10000)
if(($? == 0))
then
echo "$OUTPUT" >> usrtable.txt
fi
done
