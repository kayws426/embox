/**
 * @file
 * @brief Implementation of the ICMP protocol layer.
 * @details RFC 792
 *
 * @date 14.03.09
 * @author Alexander Batyukov
 * @author Nikolay Korotky
 * 		- remove callback interface
 * 		- major refactoring
 */

#include <string.h>
#include <net/inetdevice.h>
#include <net/icmp.h>
#include <net/ip.h>
#include <net/checksum.h>
#include <net/protocol.h>
#include <net/kernel_socket.h>
#include <linux/init.h>
#include <embox/net/proto.h>

EMBOX_NET_PROTO(IPPROTO_ICMP, icmp_rcv, NULL, icmp_init);

/**
 * Build xmit assembly blocks
 */
struct icmp_bxm {
	/**
	 * For ICMP messages sent with icmp_send, represents the ingress IP packet
	 * that triggered the transmission. For ICMP messages sent with icmp_reply,
	 * represents an ingress ICMP messages request.
	 */
	sk_buff_t *skb;
	/**
	 * Offset between skb->data and skb->nh. This offset is useful
	 * when evaluating how much data can be put into the ICMP payload
	 * for those ICMP messages that require it.
	 */
	int offset;
	/** Size of the ICMP payload. */
	int data_len;
	struct {
		/** Header of the ICMP message to transmit. */
		icmphdr_t icmph;
		/* Used by the ICMP_TIMESTAMPREPLY message type. */
		uint32_t  times[3];
	} data;
	/** Size of the ICMP header */
	int head_len;
#if 0
	struct ip_options replyopts;
#endif
	unsigned char  optbuf[40];
};

/**
 * ICMP control array. This specifies what to do with each ICMP.
 */
struct icmp_control {
	void (*handler)(sk_buff_t *skb);
	short error; /* This ICMP is classed as an error message */
};

static const struct icmp_control icmp_pointers[NR_ICMP_TYPES + 1];

/** socket for transmitting ICMP messages generated by the kernel */
static socket_t *__icmp_socket;

/**
 * Driving logic for building and sending ICMP messages.
 * Used by the ICMP protocol to reply to ingress ICMP request messages
 * that require a response (ECHO and TIMESTAMP).
 *
 * @param icmp_param
 * @param skb_in
 */
static void icmp_reply(struct icmp_bxm *icmp_param, sk_buff_t *skb_in) {
	sk_buff_t *skb = skb_copy(icmp_param->skb, 0);
	skb->dev = icmp_param->skb->dev;
	skb->h.icmph->type = icmp_param->data.icmph.type;
	skb->h.icmph->code = icmp_param->data.icmph.code;
	skb->h.icmph->checksum = 0;
	skb->h.icmph->checksum = ptclbsum(skb->h.raw,
				skb->nh.iph->tot_len - IP_HEADER_SIZE(skb->nh.iph));
	//TODO: kernel_sendmsg(NULL, __icmp_socket, ...);
	ip_send_reply(NULL, icmp_param->skb->nh.iph->daddr,
				icmp_param->skb->nh.iph->saddr, skb, 0);
	kfree_skb(skb);
}

/**
 * Handle ICMP_DEST_UNREACH, ICMP_TIME_EXCEED, and ICMP_QUENCH.
 */
static void icmp_unreach(sk_buff_t *skb) {
	iphdr_t *iph = ip_hdr(skb);
	icmphdr_t *icmph = icmp_hdr(skb);
	int hash, protocol;
	uint32_t info = 0;
	const net_protocol_t *ipprot;
	protocol = iph->proto;
	hash = protocol & (MAX_INET_PROTOS - 1);
	ipprot = inet_protos[hash];

	if (icmph->code > NR_ICMP_UNREACH) {
		return;
	}
	if (icmph->type == ICMP_PARAMETERPROB) {
		info = ntohl(icmph->un.gateway) >> 24;
	}

	if (ipprot && ipprot->err_handler) {
		ipprot->err_handler(skb, info);
	}
}

static void icmp_discard(sk_buff_t *skb) {
	/* nothing to do here */
}

/*
 * Handle ICMP_REDIRECT.
 */
static void icmp_redirect(sk_buff_t *skb) {
	//TODO: fix ip route before.
	return;
}

/**
 * Handle ICMP_ADDRESS_MASK requests. (RFC950)
 *
 * RFC1122 (3.2.2.9). A host MUST only send replies to
 * ADDRESS_MASK requests if it's been configured as an address mask
 * agent.  Receiving a request doesn't constitute implicit permission to
 * act as one. Of course, implementing this correctly requires (SHOULD)
 * a way to turn the functionality on and off.
 *
 * RFC1812 (4.3.3.9). A router MUST implement it.
 *                    A router SHOULD have switch turning it on/off.
 *                    This switch MUST be ON by default.
 */
static void icmp_address(struct sk_buff *skb) {
	//TODO:
}

/**
 * RFC1812 (4.3.3.9). A router SHOULD listen all replies, and complain
 *                    loudly if an inconsistency is found.
 */
static void icmp_address_reply(struct sk_buff *skb) {
	//TODO:
}

/**
 * Handle ICMP_ECHO ("ping") requests.
 * RFC 1122: 3.2.2.6 MUST have an echo server that answers ICMP echo
 *                requests.
 * RFC 1122: 3.2.2.6 Data received in the ICMP_ECHO request MUST be
 *                included in the reply.
 * RFC 1812: 4.3.3.6 SHOULD have a config option for silently ignoring
 *                echo requests, MUST have default=NOT.
 */
static void icmp_echo(sk_buff_t *skb) {
	struct icmp_bxm icmp_param;
	icmp_param.data.icmph      = *icmp_hdr(skb);
	icmp_param.data.icmph.type = ICMP_ECHOREPLY;
	icmp_param.skb             = skb;
	icmp_param.offset          = 0;
	icmp_param.data_len        = skb->len;
	icmp_param.head_len        = sizeof(icmphdr_t);
	icmp_reply(&icmp_param, skb);
}

/**
 * Handle ICMP Timestamp requests.
 * RFC 1122: 3.2.2.8 MAY implement ICMP timestamp requests.
 *         SHOULD be in the kernel for minimum random latency.
 *         MUST be accurate to a few minutes.
 *         MUST be updated at least at 15Hz.
 */
static void icmp_timestamp(sk_buff_t *skb) {
	//TODO: we can't work with timestamp now.
	struct icmp_bxm icmp_param;
	icmp_param.data.icmph      = *icmp_hdr(skb);
	icmp_param.data.icmph.type = ICMP_TIMESTAMPREPLY;
	icmp_param.data.icmph.code = 0;
	icmp_param.skb             = skb;
	icmp_param.offset          = 0;
	icmp_param.data_len        = 0;
	icmp_param.head_len        = sizeof(icmphdr_t) + 12;
	icmp_reply(&icmp_param, skb);
}

#define DATA_SIZE(iph) (IP_HEADER_SIZE(iph) + 8)

void icmp_send(sk_buff_t *skb_in, int type, int code, uint32_t info) {
	iphdr_t *iph_in = ip_hdr(skb_in);
	iphdr_t *iph;
	icmphdr_t *icmph;
	struct iovec iov;
	struct msghdr m;
	char packet[IP_HEADER_SIZE(iph_in) + ICMP_HEADER_SIZE + DATA_SIZE(iph_in)];
	/*
	 * RFC 1122: 3.2.2 MUST send at least the IP header and 8 bytes of header.
	 *   MAY send more (we do).
	 *   MUST NOT change this header information.
	 *   MUST NOT reply to a multicast/broadcast IP address.
	 *   MUST NOT reply to a multicast/broadcast MAC address.
	 *   MUST reply to only the first fragment.
	 */
	if ((skb_in->pkt_type != PACKET_HOST) ||
		(iph_in->frag_off & htons(IP_OFFSET))) {
		return;
	}
	iph = (iphdr_t *) packet;
	icmph = (icmphdr_t *) (packet + IP_HEADER_SIZE(iph_in));
	/* build IP header */
	memcpy(iph, iph_in, IP_HEADER_SIZE(iph_in));
	iph->proto = IPPROTO_ICMP;
	iph->tot_len = IP_HEADER_SIZE(iph_in) + ICMP_HEADER_SIZE + DATA_SIZE(iph_in);
	iph->daddr = skb_in->nh.iph->saddr;
	iph->saddr = skb_in->nh.iph->daddr;
	iph->id++;
	iph->frag_off = IP_DF;
	/* build ICMP header */
	memcpy(icmph + ICMP_HEADER_SIZE, iph_in, DATA_SIZE(iph_in));
	icmph->type = type;
	icmph->code = code;
	icmph->un.gateway = info;
	icmph->checksum = 0;
	icmph->checksum = ptclbsum(icmph, iph->tot_len - IP_HEADER_SIZE(iph));

	iov.iov_base = (void *) packet;
	iov.iov_len = IP_HEADER_SIZE(iph) + ICMP_HEADER_SIZE + DATA_SIZE(iph);
	m.msg_iov = &iov;
	kernel_sendmsg(NULL, __icmp_socket, &m, iov.iov_len);

	kfree_skb(skb_in);
}

/*
 * This table is the definition of how we handle ICMP.
 */
static const struct icmp_control icmp_pointers[NR_ICMP_TYPES + 1] = {
	[ICMP_ECHOREPLY] = {
		.handler = icmp_discard,
	},
	[1] = {
		.handler = icmp_discard,
		.error = 1,
	},
	[2] = {
		.handler = icmp_discard,
		.error = 1,
	},
	[ICMP_DEST_UNREACH] = {
		.handler = icmp_unreach,
		.error = 1,
	},
	[ICMP_SOURCE_QUENCH] = {
		.handler = icmp_unreach,
		.error = 1,
	},
	[ICMP_REDIRECT] = {
		.handler = icmp_redirect,
		.error = 1,
	},
	[6] = {
		.handler = icmp_discard,
		.error = 1,
	},
	[7] = {
		.handler = icmp_discard,
		.error = 1,
	},
	[ICMP_ECHO] = {
		.handler = icmp_echo,
	},
	[9] = {
		.handler = icmp_discard,
		.error = 1,
	},
	[10] = {
		.handler = icmp_discard,
		.error = 1,
	},
	[ICMP_TIME_EXCEEDED] = {
		.handler = icmp_unreach,
		.error = 1,
	},
	[ICMP_PARAMETERPROB] = {
		.handler = icmp_unreach,
		.error = 1,
	},
	[ICMP_TIMESTAMP] = {
		.handler = icmp_timestamp,
	},
	[ICMP_TIMESTAMPREPLY] = {
		.handler = icmp_discard,
	},
	[ICMP_INFO_REQUEST] = {
		.handler = icmp_discard,
	},
	[ICMP_INFO_REPLY] = {
		.handler = icmp_discard,
	},
	[ICMP_ADDRESS] = {
		.handler = icmp_address,
	},
	[ICMP_ADDRESSREPLY] = {
		.handler = icmp_address_reply,
	},
};

void __init icmp_init(void) {
	sock_create_kern(PF_INET, SOCK_RAW, IPPROTO_ICMP, &__icmp_socket);
}

/**
 * Receive packet.
 *
 * @param skb received packet
 */
static int icmp_rcv(sk_buff_t *pack) {
	icmphdr_t *icmph = pack->h.icmph;
	net_device_stats_t *stats = pack->dev->netdev_ops->ndo_get_stats(pack->dev);
	uint16_t tmp;
	/**
	 * 18 is the highest 'known' ICMP type. Anything else is a mystery
	 * RFC 1122: 3.2.2  Unknown ICMP messages types MUST be silently
	 *                discarded.
	 */
	if (icmph->type > NR_ICMP_TYPES) {
		LOG_ERROR("unknown type of ICMP packet\n");
		stats->rx_err++;
		return -1;
	}
	/*
	 * RFC 1122: 3.2.2.6 An ICMP_ECHO to broadcast MAY be
	 *        silently ignored.
	 * RFC 1122: 3.2.2.8 An ICMP_TIMESTAMP MAY be silently
	 *        discarded if to broadcast/multicast.
	 */
	if (0 /* (IFF_BROADCAST | IFF_MULTICAST) */) {
		if (icmph->type == ICMP_ECHO ||
			icmph->type == ICMP_TIMESTAMP) {
			return -1;
		}
		if (icmph->type != ICMP_ECHO &&
			icmph->type != ICMP_TIMESTAMP &&
			icmph->type != ICMP_ADDRESS &&
			icmph->type != ICMP_ADDRESSREPLY) {
			return -1;
		}
	}

	//TODO: check summ icmp? not need, if ip checksum is ok.
	tmp = icmph->checksum;
	icmph->checksum = 0;
	if (tmp != ptclbsum(pack->h.raw, pack->nh.iph->tot_len - IP_HEADER_SIZE(pack->nh.iph))) {
		LOG_ERROR("bad icmp checksum\n");
		return -1;
	}
	if (NULL != icmp_pointers[icmph->type].handler) {
		icmp_pointers[icmph->type].handler(pack);
		kfree_skb(pack);
		return 0;
	}
	return -1;
}
