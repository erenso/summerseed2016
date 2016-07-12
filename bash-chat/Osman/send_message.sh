#!/bin/bash

echo "Please enter message>>"
read mess
for i in `seq 0 255` ;
	do
		echo "OSMAN,$mess" | nc  172.16.5.$i 10002 &
	done