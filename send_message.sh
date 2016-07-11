#!/bin/bash
while true;
do
	for i in `seq 0 255` ;do
		echo "OSMAN,hi" | nc -w 2 172.16.5.$i 10003 &
	done
done