#!/bin/bash

while true;
	
	do
		echo -n "Enter some text > "
		read text
		
		for i in `seq 1 255`
			
			do
				echo "caner, $text" | nc -w 1 172.16.5.$i 10002 & 
				
		done
	
	done
