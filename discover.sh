for x in {1..254}
do
	output =$(nc -q 1 -w 1 172.16.5.$x 10000)
	if (($? == 0))
	then
		echo "$output" >> addressBook.txt
	fi
done
