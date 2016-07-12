RED='\033[0;31m'
NC='\033[0m' # No Color
while true 
do
PACKET=$(nc -l -p 10002)
NICK=$(echo $PACKET | cut -d ',' -f1)
MSG=$(echo $PACKET | cut -d ',' -f2)
echo -e "${RED}$NICK:${NC} $MSG"
done