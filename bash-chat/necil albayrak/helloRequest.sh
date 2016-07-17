while true; do
  PACKAGE=$(nc -l 10000)
  IP=$(echo $PACKAGE | cut -d ',' -f1)
  NICKNAME=$(echo $PACKAGE | cut -d ',' -f2)
  
  MYIP=$(ifconfig | grep "inet addr:" | head -n1 | cut -d ':' -f2 | cut -d ' ' -f1)
  
  printf "$MYIP,TomatoSlicer" | nc $IP 10001
  
  grep -q -F $NICKNAME adresses.txt || printf "$NICKNAME,$IP\n" >> adresses.txt
done


