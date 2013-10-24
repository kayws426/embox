/**
 * @file
 * @brief implementation of the RARP protocol
 * @details RFC 903
 *
 * @date 29.09.12
 * @author Ilia Vaprol
 */

#include <arpa/inet.h>
#include <assert.h>
#include <embox/net/pack.h>
#include <errno.h>
#include <net/if_arp.h>
#include <net/if_packet.h>
#include <net/inetdevice.h>
#include <net/neighbour.h>
#include <net/l0/net_tx.h>
#include <net/l3/rarp.h>
#include <net/skbuff.h>
#include <string.h>

EMBOX_NET_PACK(ETH_P_RARP, rarp_rcv);

static int rarp_build(struct sk_buff *skb, unsigned short oper,
		unsigned short paddr_space, unsigned char haddr_len,
		unsigned char paddr_len, const void *source_haddr,
		const void *source_paddr, const void *dest_haddr,
		const void *dest_paddr, const void *target_haddr,
		struct net_device *dev) {
	int ret;
	struct arpghdr *rarph;
	struct arpg_stuff rarph_stuff;
	struct net_header_info hdr_info;

	assert(skb != NULL);
	assert((haddr_len != 0) && (paddr_len != 0));
	assert(dest_haddr != NULL);
	assert((dev != NULL) && (haddr_len == dev->addr_len));

	/* Get default arguments */
	source_haddr = source_haddr != NULL ? source_haddr : &dev->dev_addr[0];
	target_haddr = target_haddr != NULL ? target_haddr : &dev->broadcast[0];

	/* Setup some fields */
	skb->dev = dev;
	skb->nh.raw = skb->mac.raw + dev->hdr_len;

	/* Make device specific header */
	hdr_info.type = ETH_P_RARP;
	hdr_info.src_hw = source_haddr;
	hdr_info.dst_hw = target_haddr;
	assert(dev->ops != NULL);
	assert(dev->ops->build_hdr != NULL);
	ret = dev->ops->build_hdr(skb, &hdr_info);
	if (ret != 0) {
		return ret;
	}

	/* Setup fixed-length fields */
	rarph = skb->nh.arpgh;
	assert(rarph != NULL);
	rarph->ha_space = htons(dev->type);
	rarph->pa_space = htons(paddr_space);
	rarph->ha_len = haddr_len;
	rarph->pa_len = paddr_len;
	rarph->oper = htons(oper);

	/* Setup variable-length fields */
	arpg_make_stuff(rarph, &rarph_stuff);
	memcpy(rarph_stuff.sha, source_haddr, haddr_len);
	if (source_paddr != NULL) {
		memcpy(rarph_stuff.spa, source_paddr, paddr_len);
	}
	else {
		memset(rarph_stuff.spa, 0, paddr_len);
	}
	memcpy(rarph_stuff.tha, dest_haddr, haddr_len);
	if (dest_paddr != NULL) {
		memcpy(rarph_stuff.tpa, dest_paddr, paddr_len);
	}
	else {
		memset(rarph_stuff.tpa, 0, paddr_len);
	}

	return 0;
}

static int rarp_xmit(struct sk_buff *skb) {
	/* fall through to dev layer */
	return net_tx(skb, NULL);
}

int rarp_send(unsigned short oper, unsigned short paddr_space,
		unsigned char haddr_len, unsigned char paddr_len,
		const void *source_haddr, const void *source_paddr,
		const void *dest_haddr, const void *dest_paddr,
		const void *target_haddr, struct net_device *dev) {
	int ret;
	struct sk_buff *skb;

	if ((haddr_len == 0) || (paddr_len == 0)
			|| (dest_haddr == NULL)
			|| (dev == NULL) || (haddr_len != dev->addr_len)) {
		return -EINVAL;
	}

	/* check device flags */
	if (dev->flags & IFF_NOARP) {
		return -EINVAL;
	}

	/* allocate net package */
	skb = skb_alloc(dev->hdr_len + ARPG_CALC_HDR_SZ(haddr_len, paddr_len));
	if (skb == NULL) {
		return -ENOMEM;
	}

	/* build package */
	ret = rarp_build(skb, oper, paddr_space, haddr_len, paddr_len,
			source_haddr, source_paddr, dest_haddr, dest_paddr, target_haddr,
			dev);
	if (ret != 0) {
		skb_free(skb);
		return ret;
	}

	/* and send */
	return rarp_xmit(skb);
}

static int rarp_hnd_request(struct arpghdr *rarph, struct arpg_stuff *rarps,
		struct sk_buff *skb, struct net_device *dev) {
	int ret;
	unsigned char haddr_len, paddr_len;
	unsigned char src_paddr[MAX_ADDR_LEN];
	unsigned char dst_haddr[MAX_ADDR_LEN], dst_paddr[MAX_ADDR_LEN];
	unsigned char tar_haddr[MAX_ADDR_LEN];
	struct in_device *in_dev;

	in_dev = inetdev_get_by_dev(dev);
	assert(in_dev != NULL);

	haddr_len = rarph->ha_len;
	paddr_len = rarph->pa_len;

	/* check protocol capabilities */
	if ((rarph->pa_space != htons(ETH_P_IP))
			|| (paddr_len != sizeof in_dev->ifa_address)) {
		skb_free(skb);
		return 0; /* FIXME error: only IPv4 is supported */
	}

	/* get source protocol address */
	memcpy(&src_paddr[0], &in_dev->ifa_address, paddr_len);

	/* get dest addresses */
	memcpy(&dst_haddr[0], rarps->tha, haddr_len);
	ret = neighbour_get_paddr(ntohs(rarph->ha_space), &dst_haddr[0],
			dev, ntohs(rarph->pa_space), paddr_len, &dst_paddr[0]);
	if (ret != 0) {
		skb_free(skb);
		return ret;
	}

	/* get target hardware address */
	memcpy(&tar_haddr[0], rarps->sha, haddr_len);

	/* build reply */
	ret = rarp_build(skb, RARP_OPER_REPLY, ntohs(rarph->pa_space),
			haddr_len, paddr_len, NULL, &src_paddr[0],
			&dst_haddr[0], &dst_paddr[0], &tar_haddr[0], dev);
	if (ret != 0) {
		skb_free(skb);
		return ret;
	}

	/* and send */
	return rarp_xmit(skb);
}

static int rarp_hnd_reply(struct arpghdr *rarph, struct arpg_stuff *rarps,
		struct sk_buff *skb, struct net_device *dev) {
	int ret;

	assert(rarph != NULL);
	assert(rarps != NULL);

	/* save destination hardware and protocol addresses */
	ret = neighbour_add(ntohs(rarph->pa_space), rarps->tpa,
			rarph->pa_len, dev, ntohs(rarph->ha_space),
			rarps->tha, rarph->ha_len, 0);
	skb_free(skb);
	return ret;
}

static int rarp_rcv(struct sk_buff *skb, struct net_device *dev) {
	struct arpghdr *rarph;
	struct arpg_stuff rarph_stuff;

	if ((skb == NULL) || (dev == NULL)) {
		return -EINVAL;
	}

	/* check device flags */
	if (dev->flags & IFF_NOARP) {
		return 0; /* error: rarp doesn't supported by device */
	}

	rarph = skb->nh.arpgh;
	assert(rarph != NULL);

	/* check hardware and protocol address lengths */
	if (dev->hdr_len + ARPG_HEADER_SIZE(rarph) > skb->len) {
		skb_free(skb);
		return 0; /* error: bad packet */
	}

	/* check device capabilities */
	if ((rarph->ha_space != htons(dev->type))
			|| (rarph->ha_len != dev->addr_len)) {
		skb_free(skb);
		return 0; /* error: invalid hardware address info */
	}

	arpg_make_stuff(rarph, &rarph_stuff);

	/* process the packet by the operation code */
	switch (ntohs(rarph->oper)) {
	default:
		skb_free(skb);
		return 0; /* error: bad operation type */
	case RARP_OPER_REQUEST:
		/* handling request */
		return rarp_hnd_request(rarph, &rarph_stuff, skb, dev);
	case RARP_OPER_REPLY:
		/* handling reply */
		return rarp_hnd_reply(rarph, &rarph_stuff, skb, dev);
	}
}
