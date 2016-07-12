# Gelen mesajlari dinle
./listen_hello_req.sh &
./listen_hello_resp.sh &

# Herkese mesaj gonder
./sendall.sh &

# Gelen mesajlari dinle ekrana yaz
./msg_recv.sh
