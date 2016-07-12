for (( i=0; i <= 255; i++ ));
do
	echo "172.16.5.194,Hasan" | nc -w 1 192.168.2.$i 10000 &
done
