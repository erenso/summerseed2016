#ifndef SOC_H
#define SOC_H
int connect_socket(int connect_port, char *address);
int listen_socket(int listen_port);
int receive_message(int socket, char *message);
#endif
