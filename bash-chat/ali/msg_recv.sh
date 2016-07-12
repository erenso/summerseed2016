# gelen mesajlari dinleyen program, mesaj geldiginde terminale yaziyor
while true; do
	PACKET=$(nc -l 10002)
	NICK=$(echo $PACKET | cut -d ',' -f1)
	MSG=$(echo $PACKET | cut -d ',' -f2)
	
	RED='\033[0;31m'
	NC='\033[0m' # No Color
	echo -e "$RED$NICK:$NC $MSG"
done
