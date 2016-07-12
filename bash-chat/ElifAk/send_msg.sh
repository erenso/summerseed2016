echo "Gondermek istediginiz kullaniciyi giriniz:"
read RECEIVER
while ["$RECEIVER" != "q"] #Eger kullanici islemi sonlandırmak istemiyorsa
do
IP=$(cat usrtable.txt | grep "$RECEIVER" | awk'{print $1}')
if["$IP" == ""]
then echo "Istenen client bulunmamaktadir."
else
read MSG
while["$MSG" != "q"]
do
echo "$MSG" | nc $IP 10002
read MSG
done
fi
echo "Gondermek istediginiz kullaniciyi giriniz:"
read RECEIVER
done
