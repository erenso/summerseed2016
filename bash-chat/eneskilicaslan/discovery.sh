#!/bin/bash
#my_ip=$(ip -4 addr show wlan1 | grep -oP "(?<=inet).*(?=/)")
#my_ip=$(ifconfig eth0 | grep 'inet addr:' | cut -d: -f2 | awk '{print $1}')
#my_ip_last_part=ifconfig | sed -En 's/127.0.0.1//;s/.*inet (addr:172.)?(([0-9]*\.){3}[0-9]*).*/\2/p'
my_ip=$(ifconfig | awk '/inet addr/{print substr($2,6)}' | grep 172)
nick="enes"
virgul=","

ip_nick=$my_ip$virgul$nick

for i in `seq 1 254`;
  	do
        packet=$(echo "$ip_nick" | nc 172.16.5.$i 10000 -w 1 & )              
    done    
