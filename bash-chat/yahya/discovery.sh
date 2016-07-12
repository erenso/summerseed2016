# tüm kullanıcıları bul
for num in {1..254};
do
	echo "172.16.5.80,yahya" | nc 172.16.5.$num 10000 -w 1 &

done
