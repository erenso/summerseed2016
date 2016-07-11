# kullanimi: ./msg_send mesaj
# mesaji herkese gonderir

for i in `seq 0 255`;
do
	echo "ali,$@" | nc -w 1 172.16.5.$i 10002 &
done 
