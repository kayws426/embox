/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    11.11.2013
 */

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <drivers/usb_dev_desc.h>
#include <drivers/usb_desc.h>

#include <embox/cmd.h>

EMBOX_CMD(input_test_main);

#define TEST_BUF_LEN 16
static char test_buf[TEST_BUF_LEN];

static struct usb_desc_device usb_test_dev_desc;
static struct usb_desc_interface usb_test_iface_desc;

static void usage(char *argv0) {
	printf("Usage: %s -v VID -p PID -e ENDP [-a] { -r LENGTH | -w [ DATA ] }\n", argv0);
}

static int usb_test_read(struct usb_endp_desc *edesc, int len, usb_token_t tok) {
	int res;

	if (len > TEST_BUF_LEN) {
		return -ERANGE;
	}

	if ((res = usb_request(edesc, test_buf, len, USB_TOKEN_IN | tok)) != 0) {
		return res;
	}

	printf("read:");
	for (int i = 0; i < len; i++) {
		printf(" %02X", test_buf[i]);
	}
	printf("\n");	

	return 0;
}

static int usb_test_write(struct usb_endp_desc *edesc, char **data, 
		int len, usb_token_t tok) {

	if (len > TEST_BUF_LEN) {
		return -ERANGE;
	}

	for (int i = 0; i < len; i++) {
		test_buf[i] = strtoul(data[i], NULL, 0);
	}

	return usb_request(edesc, test_buf, len, USB_TOKEN_OUT | tok);
}

static int input_test_main(int argc, char **argv) {
	int vid = -1, pid = -1, endp = -1, len = -1;
	signed char write = -1, setup_tok = 0, ack_tok = 0;
	struct usb_dev_desc *ddesc;
	struct usb_endp_desc *edesc;
	int opt, res;

	getopt_init();
	while (-1 != (opt = getopt(argc, argv, "v:p:e:r:asw"))) {
		switch(opt) {
		case 'v':
			vid = strtoul(optarg, NULL, 0);
			break;
		case 'p':
			pid = strtoul(optarg, NULL, 0);
			break;
		case 'e':
			endp = atoi(optarg);
			break;
		case 'r':
			len = atoi(optarg);
			break;
		case 'w':
			write = 1;
			break;
		case 's':
			setup_tok = 1;
			break;
		case 'a':
			ack_tok = 1;
			break;
		default:
			fprintf(stderr, "unknown argument: %c\n", opt);
			usage(argv[0]);
			return 1;
		}
	}

	if (vid == -1 || pid == -1 || endp == -1 
			|| (write != -1 && len != -1)) {
		printf("vid=%d pid=%d endp=%d write=%d len=%d\n",
				vid, pid, endp, write, len);
		fprintf(stderr, "one of necessary argument isn't specified\n");
		usage(argv[0]);
		return 1;
	}

	if (vid > 0xffff || pid > 0xffff || endp > 16) {
		fprintf(stderr, "pid/vid or endpoint number is too big\n");
		return 1;
	}

	if (NULL == (ddesc = usb_dev_open(vid, pid))) {
		fprintf(stderr, "no such device found\n");
		return 1;
	}

	if (0 != usb_dev_desc_get_desc(ddesc, &usb_test_dev_desc, 
				&usb_test_iface_desc)) {
		fprintf(stderr, "can't get device descriptor\n");
		return 1;
	}

	if (endp > usb_test_iface_desc.b_num_endpoints) {
		fprintf(stderr, "endppoint number is too big for this device\n");
		return 1;
	}

	if (NULL == (edesc = usb_endp_open(ddesc, endp))) {
		fprintf(stderr, "can't open endpoint\n");
		return 1;
	}

	if (len != -1) {

		res = usb_test_read(edesc, len, ack_tok ? USB_TOKEN_STATUS : 0 );
		goto exit;
	} 

	res = usb_test_write(edesc, argv + optind, argc - optind, 
			(setup_tok ? USB_TOKEN_SETUP : 0) 
			| (ack_tok ? USB_TOKEN_STATUS : 0));
exit:
	usb_endp_desc_close(edesc);
	usb_dev_desc_close(ddesc);

	return res;
}

