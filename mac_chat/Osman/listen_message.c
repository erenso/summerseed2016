// Copyright Mustafa Karaca, June 25 2015. Do not distribute.

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "osdep.h"


//wi-fi addresses
static const char *bssid_announcment = "\x00" "chat0";
static const char *bssid = "\x00" "chat1" "\x55";
static const char *smac = "\x94\x39\xe5\xa1\xda\xf5";//"\x94\x39\xe5\xa1\xda\xf5";
static const char *dmac = "\x00" "dmac" "\x55";//"\x60\x36\xdd\x50\xa0\xdc";

int main(int argc, char *argv[])
{
	struct wif *wif;
	int ret;
	struct rx_info ri;
	unsigned char pkt[4096];
	unsigned int len;
	const char *type;
	char payload[4096];
	unsigned int payload_len;
	char smac[20];
	unsigned int destLen=0;

	wif = wi_open(argv[1]);
	if (!wif) {
		printf("wi_open failed\n");
		return -1;
	}

	ret = wi_set_channel(wif, 11);
	if (ret) {
		printf("wi_set_channel failed with code: %d\n", ret);
		goto out;
	}

	for (;;) {
		ret = wi_read(wif, pkt, sizeof(pkt), &ri);
		if (ret < 0) {
			if (errno == EAGAIN)
				continue;
			printf("error on reading!!!\n");
			break;
		}


		if (ret < 24)
			continue;

		/* only QoS null function data */
		if ((pkt[0] & 0xfc) != 0x48)
			continue;

		/* source address mac */
		if (memcmp(pkt + 16, smac, 6))
			continue;

		payload_len = ret - 24;
		memcpy(payload, pkt + 24, payload_len);
		payload[payload_len] = '\0';


		
		printf("msg with rate: %d captured in air data: %s\n", ri.ri_rate, payload);


	}

out:
	wi_close(wif);
	return ret;
}
