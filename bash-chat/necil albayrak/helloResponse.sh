MYIP=$(ifconfig | grep "inet addr:" | head -n1 | cut -d ':' -f2 | cut -d ' ' -f1)
MYNUMBER=$(echo $MYIP | cut -d '.' -f4)
for((K=1; K<256; K++))
do
  if [[ $K == $MYNUMBER ]];
  then 
    continue
  fi
  echo "$MYIP,TomatoSlicer" | nc -w 1 "172.16.5.$K" 10001 &
done
