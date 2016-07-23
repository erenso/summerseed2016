// Copyright Mustafa Karaca, June 25 2015. Do not distribute. 


#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "osdep.h"



//wi-fi addresses
static const char *bssid_announcment = "\x00" "chat0";
static const char *bssid = "\x00" "chat1" "\x55";
static const char *smac = "\x00" "smac" "\x55";//"\x94\x39\xe5\xa1\xda\xf5";
static const char *dmac = "\x00" "dmac" "\x55";//"\x60\x36\xdd\x50\xa0\xdc";

int main(int argc, char *argv[])
{
	struct wif *wif;
	int ret;
	unsigned char pkt[4096];
	struct mgmt_header_t *d11h = (struct mgmt_header_t *)pkt;
	unsigned int len;
	char *payload;
	int payload_len;

	wif = wi_open(argv[1]);
	if (!wif) {
		printf("wi_open failed\n");
		return -1;
	}
	payload = argv[2];
	payload_len = strlen(payload);

	ret = wi_set_channel(wif, 11);
	if (ret) {
		printf("wi_set_channel failed with code: %d\n", ret);
		goto out;
	}

	ret = wi_set_rate(wif, 2000000);
	if (ret) {
		printf("wi_set_rate failed with code: %d\n", ret);
		goto out;
	}


	memcpy(pkt, NULL_DATA, 24);
	len = 24;
	memcpy(&pkt[4], bssid_announcment, 6);
	memcpy(&pkt[10], smac, 6);
	memcpy(&pkt[16], dmac, 6);

	memcpy(&pkt[len], payload, payload_len);
	len += payload_len;

	ret = wi_write(wif, pkt, len, NULL);
	printf("wi_write returned: %d\n", ret);

out:
	wi_close(wif);
	return ret;
}
