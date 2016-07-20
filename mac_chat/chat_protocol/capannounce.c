// Copyright Mustafa Karaca, June 25 2015. Do not distribute.

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "osdep.h"

static const char *bssid_announce = "\x00" "chat0";
static const char *bssid_data = "\x00" "chat1";
static const char *smac = "\x60\x36\xdd\x50\xa0\xdc";
static const char *dmac = "\x00" "dmac" "\x55";

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

		/* filter mac */
		if (memcmp(pkt + 4, bssid_announce, 6))
			continue;

		payload_len = ret - 24;
		memcpy(payload, pkt + 24, payload_len);
		payload[payload_len] = '\0';	
		printf("announce: %s, MAC: %02X:%02X:%02X:%02X:%02X:%02X\n", payload, pkt[10], pkt[11], pkt[12], pkt[13], pkt[14], pkt[15]);
	}

out:
	wi_close(wif);
	return ret;
}
