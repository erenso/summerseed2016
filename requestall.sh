while true; do
for ((i=0;i<=255;i++));
do
echo "172.16.5.235,anil" | nc -w 1 172.16.5.$i 10000 &
done
done
