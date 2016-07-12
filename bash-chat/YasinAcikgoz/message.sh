while true; do 
	PACKET=$(nc -l 10002)
	nick=$(echo $PACKET | cut -d ',' -f1)
	if grep -q $nick '/home/yasin/Desktop/adressbook.txt';then
		msg=$(echo $PACKET | cut -d ',' -f2)
		now=$(date +"%T")
		echo "[$now] <$nick>: $msg"
	fi
done
