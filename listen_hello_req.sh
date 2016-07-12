IFS=$(echo -en "\n\b")

for i in `cat addressbook2.txt | cut -d ',' -f1`; do

MY_NICK='alp'
MY_ADDRESS='172.16.5.50'

echo $MY_ADDRESS,$MY_NICK | nc $i 10001

done





