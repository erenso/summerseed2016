echo "BaranMSG'ye hoşgeldin. Kimle konuşmak istiyorsun? (Broadcast için Broadcast yaz)"
read FRIEND
if [ "$FRIEND" != "Broadcast" ]
then
	IP=$(cat addressbook.txt | grep "$FRIEND" | awk '{print $1}')
	if [ "$IP" == "" ]
		then
			echo "Böyle bir arkadaşın yok!"
		else
			echo "$FRIEND ile konuşmaktasın. Konuşmayı bitirmek için QuitBaranMSG yazman yeterli."
			read MSG
			while [ "$MSG" != "QuitBaranMSG" ]
				do
					echo "Baran,$MSG" | nc $IP 10002
					read MSG
			done	
	fi
else
	
	
	echo "Broadcast'tesin. Konuşmayı bitirmek için QuitBaranMSG yazman yeterli."
	read MSG
	while [ "$MSG" != "QuitBaranMSG" ]
		do
		for i in {1..254}
			do
			echo "Baran,$MSG" | nc 172.16.5.$i 10002 &
			done
		read MSG
	done	
	
	
	
	
fi
done
