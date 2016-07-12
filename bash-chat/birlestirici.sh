
echo "listendan cikiyor"
LIMIT=254
for ((i=1; i <= LIMIT ; i++)) do
 echo "172.16.5.150,onur"| nc 172.16.5.$i 10000
done

send_hello_req.sh
done
