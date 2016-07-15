#include "sendModule.h"
void sender(char * IP, char * msg){
        int conn;
        conn = connect_socket(10002,IP);
        if (conn != -1){
                send(conn, msg, strlen(msg)+1, 0);
        }
        close(conn);
}
