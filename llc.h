#ifndef __LINUX_LLC_H
#define __LINUX_LLC_H
#include <linux/socket.h>
#include <net/if.h>
#define __LLC_SOCK_SIZE__ 16
struct sockaddr {
  __kernel_sa_family_t s_family;
  __kernel_sa_family_t s_arphrd;
  unsigned char s_dst;
  unsigned char s_xid;
  unsigned char s_idx;
  unsigned char s_sap;
  unsigned char s_mac[IFHWADDR];
  unsigned char __pad[__LLC_SOCK_SIZE__ - sizeof(__kernel_sa_family_t) * 2 - sizeof(unsigned char) * 4 - IFHWADDR];
};
enum s_sockopts {
  S_OPT_UNKNOWN = 0,
  S_OPT_RETRY,
  S_OPT_SIZE,
  S_OPT_ACK_TMR_EXP,
  S_OPT_NACK_TMR_EXP,
  S_OPT_REJ_TMR_EXP,
  S_OPT_BUSY_TMR_EXP,
  S_OPT_TX_WIN,
  S_OPT_RX_WIN,
  S_OPT_PKTINFO,
  S_OPT_MAX
};
#define FRAME_OPT_MAX_RETRY
#define FRAME_OPT_MAX_SIZE
#define FRAME_OPT_MAX_WIN
#define FRAME_OPT_MAX_ACK_TMR_EXP
#define FRAME_OPT_MAX_NACK_TMR_EXP
#define FRAME_OPT_MAX_REJ_TMR_EXP
#define FRAME_OPT_MAX_BUSY_TMR_EXP
#define FRAME_SAP_NULL
#define FRAME_SAP_ID
#define FRAME_SAP_SNA
#define FRAME_SAP_PNM
#define FRAME_SAP_IP
#define FRAME_SAP_BSPAN
#define FRAME_SAP_MMS
#define FRAME_SAP_8208
#define FRAME_SAP_3COM
#define FRAME_SAP_PRO
#define FRAME_SAP_NSAP
#define FRAME_SAP_BANYAN
#define FRAME_SAP_IPX
#define FRAME_SAP_NETBEUI
#define FRAME_SAP_LANMGR
#define FRAME_SAP_IMPL
#define FRAME_SAP_DISC
#define FRAME_SAP_OSI
#define FRAME_SAP_LAR
#define FRAME_SAP_RM
#define FRAME_SAP_GLOBAL
struct s_pktinfo {
  int pdev_ifindex;
  unsigned char s_dsp;
  unsigned char s_idi[IFHWADDR];
};
#endif /*! __LLC_H_ */