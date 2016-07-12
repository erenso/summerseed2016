# Kapandiginda arkaplanda calisan uygulamalari sonlandiracak sekilde ayarla
trap 'kill $(jobs -p)' SIGHUP SIGINT SIGTERM

# Gelen mesajlari dinle
./listen_hello_req.sh &
./listen_hello_resp.sh &

# Herkese mesaj gonder
./sendall.sh &

# Gelen mesajlari dinle ekrana yaz
./msg_recv.sh &

# kullanicinn yazdiklarini okuyup mesaja donusturme
while true; do
	read mesaj
	if [ "$mesaj" = "/exit" ] # eger mesaj /exit ise cik
	then
		kill $(jobs -p)
		break
	fi
	if [ $(echo "$mesaj" | cut -d ' ' -f1) = "/w" ]
	then
		ip=$(echo $(grep $(echo $mesaj | cut -d ' ' -f2) people.txt | cut -d ',' -f1))
		echo "ip: $ip"
		gnome-terminal -x sh -c "./whisper.sh $ip; bash" &
		continue
	fi
	if [ $(echo "$mesaj" | cut -d ' ' -f1) = "/spam" ]
	then
		gnome-terminal -x sh -c "./whisper.sh $ip; bash" &
	else	
		./msg_send.sh "$mesaj"
	fi
done
