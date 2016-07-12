while true;do
MSGG=$(nc -l 10002) #waits untill gets a massge then waits again

OTHER=$(echo "$MSGG" | cut -d ',' -f1)

MG=$(echo "$MSGG" | cut -d ',' -f2-)

echo "$OTHER: $MG"
done
