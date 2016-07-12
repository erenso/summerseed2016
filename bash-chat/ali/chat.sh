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
	else
		./msg_send.sh "$mesaj"
	fi
done
