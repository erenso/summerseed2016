// Copyright Mustafa Karaca, June 25 2015. Do not distribute. 


#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "osdep.h"

#define DEAUTH_REQ      \
    "\xC0\x00\x3A\x01\xCC\xCC\xCC\xCC\xCC\xCC\xBB\xBB\xBB\xBB\xBB\xBB" \
    "\xBB\xBB\xBB\xBB\xBB\xBB\x00\x00\x07\x00"

#define AUTH_REQ        \
    "\xB0\x00\x3A\x01\xBB\xBB\xBB\xBB\xBB\xBB\xCC\xCC\xCC\xCC\xCC\xCC" \
    "\xBB\xBB\xBB\xBB\xBB\xBB\xB0\x00\x00\x00\x01\x00\x00\x00"

#define ASSOC_REQ       \
    "\x00\x00\x3A\x01\xBB\xBB\xBB\xBB\xBB\xBB\xCC\xCC\xCC\xCC\xCC\xCC"  \
    "\xBB\xBB\xBB\xBB\xBB\xBB\xC0\x00\x31\x04\x64\x00"

#define REASSOC_REQ       \
    "\x20\x00\x3A\x01\xBB\xBB\xBB\xBB\xBB\xBB\xCC\xCC\xCC\xCC\xCC\xCC"  \
    "\xBB\xBB\xBB\xBB\xBB\xBB\xC0\x00\x31\x04\x64\x00\x00\x00\x00\x00\x00\x00"

#define NULL_DATA       \
    "\x48\x01\x3A\x01\xBB\xBB\xBB\xBB\xBB\xBB\xCC\xCC\xCC\xCC\xCC\xCC"  \
    "\xBB\xBB\xBB\xBB\xBB\xBB\xE0\x1B"

#define RTS             \
    "\xB4\x00\x4E\x04\xBB\xBB\xBB\xBB\xBB\xBB\xCC\xCC\xCC\xCC\xCC\xCC"

#define RATES           \
    "\x01\x04\x02\x04\x0B\x16\x32\x08\x0C\x12\x18\x24\x30\x48\x60\x6C"

#define PROBE_REQ       \
    "\x40\x00\x00\x00\xFF\xFF\xFF\xFF\xFF\xFF\xCC\xCC\xCC\xCC\xCC\xCC"  \
    "\xFF\xFF\xFF\xFF\xFF\xFF\x00\x00"

//wi-fi addresses
static const char *bssid_announcment = "\x00" "chat0";
static const char *bssid = "\x00" "chat1" "\x55";
static const char *smac = "\x94\x39\xe5\xa1\xda\xf5";//"\x94\x39\xe5\xa1\xda\xf5";
static const char *dmac = "\x60\x36\xdd\x50\xa0\xdc";//"\x60\x36\xdd\x50\xa0\xdc";

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
	memcpy(&pkt[4], bssid, 6);
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
