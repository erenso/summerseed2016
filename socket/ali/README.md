# ./nc

minimal netcat.

# Yükleme

```sh
cd /path/to/socket/ali
make
```

# Kullanimi

Herhangi bir peer'e mesaj yollamak için:
```sh
echo "merhaba dunya" | ./nc IP port
```
Herhangi bir portu tek bir request için dinlemek:
```sh
./nc -l port
```
Discovery yapmak:
```sh
./discovery
```
Sürekli gelen requestleri dinlemek
```sh
./listen
```
