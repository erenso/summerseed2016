while true; do
  PACKAGE=$(nc -l 10001)
  IP=$(echo $PACKAGE | cut -d ',' -f1)
  NICKNAME=$(echo $PACKAGE | cut -d ',' -f2)
  
  grep -q -F $NICKNAME adresses.txt || printf "$NICKNAME,$IP\n" >> adresses.txt
done


