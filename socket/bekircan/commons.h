#ifndef NICK_MAX
#define NICK_MAX 256
#endif
#ifndef IP_MAX
#define IP_MAX 15
#endif

#define REQ_PORT 10000
#define RESP_PORT 10001
#define MSG_PORT 10002

#define NICK "bekircan"


typedef struct{
	
	char nick[NICK_MAX];
	char ip[IP_MAX];
	int numReq;
}address_t;

/* linked list structure */
typedef struct address_ll_s{
	
	address_t address;
	struct address_ll_s *next;
}address_ll;
