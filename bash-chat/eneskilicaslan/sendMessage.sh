#!/bin/bash

nick=$1
message=$2

while IFS='' read -r line || [[ -n $line ]]; do

    IFS=',' read -r ipAddr nickRead <<< "$line"

    if [[ $nick == $nickRead ]]; then
    		
			echo "$nick: $message" | nc -w3 $ipAddr 10002
    	
    fi

done < "requests.txt"