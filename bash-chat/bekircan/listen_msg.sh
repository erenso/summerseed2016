while true; do

str="$(nc -l 10002)"

nick="$(echo $str | cut -d ',' -f1)"
msg="$(echo $str | cut -d ',' -f2)"

echo "$nick : $msg"

done
