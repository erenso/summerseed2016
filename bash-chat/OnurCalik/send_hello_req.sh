
IFS=""

for i in `cat kisiler.txt`;


do echo "172.16.5.150,onur"|nc $(echo $i | cut -d ',' -f1) 10001;
done


