while true; do
	for i in {1..254}
	do
		echo "172.16.5.142,özgün" | nc -w 1 172.16.5.$i 10000 &
	done
done
