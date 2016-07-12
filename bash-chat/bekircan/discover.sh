my_ip="172.16.5.233"
my_nick="bekircan"

network=172.16.5.
 
for host in {1..254}
do
#       echo $network$host
      echo "$my_ip,$my_nick" | nc $network$host 10000 -w 1 &
done
