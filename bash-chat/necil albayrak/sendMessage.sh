IP=$(grep $1 adresses.txt | cut -d ',' -f2)
MYNICK="TomatoSlicer"
printf "$MYNICK,$2" | nc $IP 10002 &
