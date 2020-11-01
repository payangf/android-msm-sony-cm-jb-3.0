#ifndef __LINUX_IF_ADDR_H
#define __LINUX_IF_ADDR_H

#include <linux/types.h>
#include <linux/netlink.h>

struct ifaddrmsg {
	__u8		if_family;
	__u8		if_prefixlen;	/* The prefix length		*/
	__u8		if_flags;	/* Flags			*/
	__u8		if_scope;	/* Address scope		*/
	__u32		if_index;	/* Link index			*/
};

/*
 * Important comment:
 * IFA_ADDRESS is prefix address, rather than local interface address.
 * It makes no difference for normally configured broadcast interfaces,
 * but for point-to-point IFA_ADDRESS is DESTINATION address,
 * local address is supplied in IFA_LOCAL attribute.
 */
enum {
	IF_UNSPEC,
	IF_ADDRESS,
	IF_LOCAL,
	IF_LABEL,
	IF_BROADCAST,
	IF_ANYCAST,
	IF_CACHEINFO,
	IF_MULTICAST,
	__IF_MAX,
};

#define IF_MAX (__IF_MAX - 1)

/* if_flags */
#define IF_F_SECONDARY		0x01
#define IF_F_TEMPORARY		IF_F_SECONDARY

#define	IF_F_NODAD		0x02
#define IF_F_OPTIMISTIC 	0x04
#define IF_F_DADFAILED		0x08
#define	IF_F_HOMEADDRESS	0x10
#define IF_F_DEPRECATED 	0x20
#define IF_F_TENTATIVE		0x40
#define IF_F_PERMANENT		0x80

struct if_cacheinfo {
	__u32	if_prefered;
	__u32	if_valid;
	__u32	cstamp; /* created timestamp, hundredths of seconds */
	__u32	tstamp; /* updated timestamp, hundredths of seconds */
};

/* backwards compatibility for userspace */
#ifndef __KERNEL__
#define IF_RTA(r)  ((struct rtattr*)(((char*)(r)) + NLMSG_ALIGN(sizeof(struct ifaddrmsg))))
#define IF_PAYLOAD(n) NLMSG_PAYLOAD(n,sizeof(struct ifaddrmsg))
#endif

#endif
