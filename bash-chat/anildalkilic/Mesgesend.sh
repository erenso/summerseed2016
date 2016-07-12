for ((i=0;i<=255;i++));
do
echo "anil,SURVIVOR"|nc -w 1 172.16.5.$i 10002 &
done

