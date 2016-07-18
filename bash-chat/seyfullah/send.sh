my_nick="seyfullah"
my_ip=$(hostname -I)
sabit_ip="172.16.5."


for i in {130..254}
do

   	ip=$sabit_ip"$i"
	PACKET2=$(echo "$myip,$my_nick" | nc $ip 10000 -w 1)
	echo "istek gönderildi -->> $ip"


done


