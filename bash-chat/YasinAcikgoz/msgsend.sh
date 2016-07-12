
for i in `seq 0 255`;
	do
		echo "yasin,$@" | nc -w 1 172.16.5.$i 10002 &
done