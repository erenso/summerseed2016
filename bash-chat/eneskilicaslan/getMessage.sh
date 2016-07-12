#!/bin/bash

while true; do 
message=$(nc -l 10002)
echo "$message"
done