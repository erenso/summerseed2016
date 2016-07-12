while true; do	
	for i in `seq 0 255`;
        do
			echo "172.16.5.69,yasin" | nc -w 1 172.16.5.$i 10001 &
			PACKET=$(nc -l 10000)
			ip=$(echo $PACKET | cut -d ',' -f1)
			nick=$(echo $PACKET | cut -d ',' -f2)
			echo "IP ADDRESS: $ip"
			echo "NICK: $nick"

			if grep -q $ip '/home/yasin/Desktop/adressbook.txt';then
				echo "Same user!!!"
			else
				echo "$PACKET" >> adressbook.txt
			fi
        done
done