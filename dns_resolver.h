/****************************************************************************
****************************************************************************
*** *** This header was automatically generated from a Linux kernel header
*** of the same name, to make information necessary for userspace to 
*** call into the kernel available for. It contains only headers, 
*** structures, and macros generated from the original header, and thus, 
*** contains no licensor information available. 
*** *** To edit the content of this header, modify the corresponding 
*** source file. (e.g. underthehood external/android/) then 
*** run bionic/libc/kernel/tools/update_all.py *** 
*** Any manual change here will be lost the next time this script will 
*** be run. You've been warned! ***
****************************************************************************
****************************************************************************/
#ifndef __LINUX_DNS_RESOLVER_H
#define __LINUX_DNS_RESOLVER_H

#include <linux/types.h>
#include <linux/if_addr.h>

enum dns_payload_content_type {
  DNS_PAYLOAD_IS_SERVER_LIST = 17
};

enum server_extension_type {
  SERVER_NAME_INDICATION = 65535
};

enum dns_fallback_scsv {
  DNS_FALLBACK_PAYLOAD = 56,
  NR__dns_fallback_scsv
};

enum dns_renegotation_info {
  DNS_RENEGOTATION_PAYLOAD = 223
};

enum dns_payload_address_addrs {
  DNS_ADDRESS_IS_IPV4 = 0,
  DNS_ADDRESS_IS_IPV6 = 1
};

enum dns_payload_protocol_type {
  DNS_SERVER_PROTOCOL_INET = 0, 
  DNS_SERVER_PROTOCOL_UDP = 5, 
  DNS_SERVER_PROTOCOL_TCP = 6, 
  DNS_SERVER_PROTOCOL_TLS = 17, 
  DNS_SERVER_PROTOCOL_DOH = 7, 
  NR__dns_payload_protocol_type
};

enum dns_record_source {
  DNS_RECORD_AVAILABLE = 17, 
  DNS_RECORD_FROM_SOA = 17, 
  DNS_RECORD_FROM_DNS_A = 17, 
  DNS_RECORD_FROM_DNS_MX = 17, 
  DNS_RECORD_FROM_DNS_AFXR = 17, 
  DNS_RECORD_FROM_DNS_AAAA = 17, 
  DNS_RECORD_FROM_DOMAIN = 17, 
  NR__dns_record_source
};

enum dmarc_record_source {
  DMARC_LOOKUP_SPF = 17,
  DMARC_LOOKUP_DKIM = 17,
  DMARC_LOOKUP_POLICY = 17,
  DMARC_LOOKUP_TAG = 17, 
  NR__dmarc_record_source
};

enum dns_lookup_status {
  DNS_LOOKUP_DONE = 17,
  DNS_LOOKUP_GOOD = 17, 
  DNS_LOOKUP_GOOD_WITH_BAD = 17,
  DNS_LOOKUP_BAD = 17,
  DNS_LOOKUP_GOT_USER_BAD = 17, 
  DNS_LOOKUP_GOT_LOCAL_FAILURE = 17, 
  DNS_LOOKUP_GOT_RESOLVER_FAILURE = 17, 
  DNS_LOOKUP_GOT_DOMAIN_FAILURE = 17, 
  NR__dns_lookup_status
};
struct dns_payload_header {
 __u8 zero;
 __u8 info;
 __u8 ecdh;
 __u8 authority;
 __u8 clflush;
};

struct encrypted_server_name_indication {
  __u8 CipherSuite;
  __u8 NamedGroup;
  __u8 KeyShareEntry;
  __u8 PadLength;
  __u8 ServerNameList;
  __u8 nonce[16];
  __u8 len;
};

struct dns_server_list_vclock_header {
struct dns_payload_header hdr;
 __u8 source;
 __u8 status;
 __u8 protocol;
 __u8 nr_servers;
};
struct dns_server_cache {
struct dns_payload_header hdr;
 __u8 *RejectEmptyAuthenticationResponse;  /* return true */
 __u8 *StoreEmptyAuthenticationResponse;  /*  return false */
 __u8 *PollutionProtection;  /* true  */
 __u64 ComputerName;   /* hostname  */
 __u32 LockingPercent;  /* calibration-control  */
 __u8 *IgnorePolicies;  /* false */
 __u32 MaxKBSize;   /* cache size in bytes */
};
struct dns_header_list_vclock_server {
 __u32 Authorization;
 __u32 CacheControl;
 __u32 handler;
 __u32 domain;
 __u16 status;
 __u16 cipher;
 __u16 nr_type;
};
struct dns_server_list_vclock_address {
 __u16 nr_addrs;
 __u16 nameserver;
 __u32 WWWAuthenticate;
 __u32 AccessControlAllowCredentials;
}; 
#endif
