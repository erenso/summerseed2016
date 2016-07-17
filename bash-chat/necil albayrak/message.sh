while true; do
  PACKAGE=$(nc -l 10002)
  NICKNAME=$(echo $PACKAGE | cut -d ',' -f1)
  MESSAGE=$(echo $PACKAGE | cut -d ',' -f2)
  
  printf "$NICKNAME: $MESSAGE"
  DATE=$(echo date)
  printf "$MESSAGE | $DATE\n" >> "$NICKNAME.txt"
done


