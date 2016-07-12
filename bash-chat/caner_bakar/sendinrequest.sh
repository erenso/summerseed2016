#!/bin/bash

while true;
	
	do

		for i in `seq 1 255`
			
			do
				echo "172.16.5.61, CANER" | nc -w 3 172.16.5.$i 10000 & 
				
		
		done
	
	done
