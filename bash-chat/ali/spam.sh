while true; do
	./msg_send.sh $(cat /dev/urandom | base64 | head -c 100)
done
