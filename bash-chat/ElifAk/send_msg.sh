echo "Gondermek istediginiz kullaniciyi giriniz:"
read RECEIVER
while [ "$RECEIVER" != "q" ] #Eger kullanici islemi sonlandırmak istemiyorsa
do
IP=$(cat usrtable.txt | grep "$RECEIVER" |  cut -d ',' -f1)
if [ "$IP" == "" ]
then
echo "Istenen client bulunmamaktadir."
else
echo "Iletisime gecmek istediginiz kullanicinin IP'si: $IP"
echo "Lutfen mesajinizi yaziniz: "
read MSG
while [ "$MSG" != "q" ]
do
echo "elif,$MSG" | nc $IP 10002
read MSG
done
fi
echo "Gondermek istediginiz kullaniciyi giriniz:"
read RECEIVER
done
