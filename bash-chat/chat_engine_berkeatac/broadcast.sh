read MSG
for i in {2..254}
do
   echo "berke,$MSG" | nc -c 172.16.5.$i 10002 &
done
echo "console: message sent to all"