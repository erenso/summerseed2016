while  true ; do
	MY_IP=$(echo "172.16.5.187")
	MY_NICK_NAME=$(echo "OSMAN")
	echo $MY_NICK_NAME

	for i in `seq 1 255` ;
		do
			echo "$MY_IP,$MY_NICK_NAME" | nc -w 3 172.16.5.$i 10000 &
		done
done