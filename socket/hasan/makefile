all:
	gcc -c get_send_mes.c
	gcc get_send_mes.o discover.c -o discover -lpthread
	gcc get_send_mes.o listen_mes.c -o listen_mes
	gcc get_send_mes.o recv_req.c -o recv
	gcc get_send_mes.o send_msg.c -o sendmes -lpthread
	gcc get_send_mes.o recv_res.c -o recv_res
	rm get_send_mes.o