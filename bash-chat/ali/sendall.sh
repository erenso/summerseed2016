# agdaki herkese request gonder
for i in `seq 0 255`;
do
	echo "172.16.5.217,ali" | nc -w 1 172.16.5.$i 10000 &
done
