./listenRequest.sh & 
./listenResponce.sh & 
./discovery.sh &
./getMessage.sh &
./sendMessage.sh

# echo $d

if [ $d -eq 0 ]; then
break
fi

done

killall sh listen_req.sh
killall sh listen_resp.sh
killall sh refresh.sh
killall nc