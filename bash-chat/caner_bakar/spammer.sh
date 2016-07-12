#!/bin/bash

while true;
	
	do

		for i in `seq 1 255`
			
			do
				echo "caner, Hello My Friend" | nc 172.16.5.$i 10002 & 
				
		
		done
	
	done
