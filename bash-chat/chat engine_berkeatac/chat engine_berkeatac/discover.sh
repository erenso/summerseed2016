for i in {2..254}
do
   echo "172.16.5.203,berke" | nc -c 172.16.5.$i 10000 &
   echo "$i"
done