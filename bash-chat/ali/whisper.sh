echo "[$@] ile konusuyorsun."
while true; do
	read mesaj
	echo "ali,$mesaj" | nc $@ 10002
done
