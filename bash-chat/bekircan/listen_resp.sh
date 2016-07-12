while true; do

str="$(nc -l 10001)" 
ip="$(echo $str | cut -d ',' -f1)"

if !(grep -cq "$ip" adressbook.txt)
then
echo "$str" >> "adressbook.txt"
fi

done
