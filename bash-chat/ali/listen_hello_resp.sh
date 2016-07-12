# responselari dinleyen program

while true; do
	PACKET=$(nc -l 10001)
	IP=$(echo $PACKET | cut -d ',' -f1)
	NICK=$(echo $PACKET | cut -d ',' -f2)
	
	if grep -q "$IP" people.txt
	then 
		echo -e "\033[0;33m$IP $NICK zaten kisilerde mevcut."
	else
		echo -e "\033[0;33m$IP,$NICK" >> people.txt
		echo -e "\033[0;33m$IP $NICK kisilere eklendi."
	fi
done
