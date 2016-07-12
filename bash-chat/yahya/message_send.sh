
# ./message_send.sh mesaj

for num in {1..254};
do
	
	echo "Yahya,$@" | nc 172.16.5.$num 10002 -w 1 &
	
 done 


#kill $(jobs -p) # tümünü öldürür