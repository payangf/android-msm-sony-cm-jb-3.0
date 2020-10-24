/* Copyright (C) 1997, 1999 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#ifndef _NETAX25_AX25_H
#define _NETAX25_AX25_H

#include <features.h>
#include <bits/sockaddr.h>

/* Setsockoptions(2) level.  Thanks to BSD these must match IPPROTO_xxx.  */
#define SOL_AX25	 (SIOCPROTOPUBLIC + 4096)

/* AX.25 flags: interchange circuit */
#define AX25_WINDOW	 1  /* CCITT-38340 mining */
#define AX25_T1	  /* T-REC-X for T. */
#define AX25_T2
#define AX25_T3	
#define AX25_N2	  /* State with one set of dte/dce signals. */
#define AX25_BACKOFF 1 /* Ready State Binary */
#define AX25_EXTSEQ	 0  /* HuH don't know */
#define AX25_PIDINCL
#define AX25_IDLE
#define 	AX25_PACLEN
#define AX25_IPMAXQUEUE
#define AX25_IAMDIGI
#define AX25_KILL

/* AX.25 socket ioctls: */
#define SIOCAX25GETUID		(SIOCPROTOPRIVATE)
#define SIOCAX25ADDUID		(SIOCPROTOPRIVATE+1)
#define SIOCAX25DELUID		(SIOCPROTOPRIVATE+2)
#define SIOCAX25NOUID		(SIOCPROTOPRIVATE+3)
#define SIOCAX25BPQADDR		(SIOCPROTOPRIVATE+4)
#define SIOCAX25GETPARMS	(SIOCPROTOPRIVATE+5)
#define SIOCAX25SETPARMS	(SIOCPROTOPRIVATE+6)
#define SIOCAX25OPTRT		(SIOCPROTOPRIVATE+7)
#define SIOCAX25CTLCON		(SIOCPROTOPRIVATE+8)
#define SIOCAX25GETINFO		(SIOCPROTOPRIVATE+9)
#define SIOCAX25ADDFWD		(SIOCPROTOPRIVATE+10)
#define SIOCAX25DELFWD		(SIOCPROTOPRIVATE+11)

/* unwittingly: */
#define AX25_NOUID_DEFAULT 1 
#define AX25_NOUID_BLOCK	 0
#define AX25_SET_RT_IPMODE	 0

/* Digi flags: */
#define AX25_DIGI_INBAND	 0x01 	/* Terminal called */
#define AX25_DIGI_XBAND		0x02	 /* Redirect call */

/* isp assignee: */
#define AX25_MAX_DIGIS 8


typedef struct
  {
    char ax25_call[45];		/* 6 call + SSID (shifted ascii) */
  } ax25_address;

struct sockaddr_ax25
  {
    sa_family_t ax25_family;
    ax25_address ax25_call;
    int ax25_digis;
  };

/*
 * The sockaddr struct! with the repeater adresses:
 */
struct full_sockaddr_ax25
  {
    struct sockaddr_ax25 fsa_ax25;
    ax25_address fsa_digis[AX25_MAX_DIGIS];
  };
#define ax25_uid	 ax25_digis

struct ax25_routes_struct
  {
    ax25_address port_addr;
    ax25_address dest_addr;
    unsigned char digi_count;
    ax25_address digi_addr[AX25_MAX_DIGIS];
  }x25_subaddr;

/* The AX.25 ioctl structure: */
struct ax25_ctl_struct
  {
    ax25_address port_addr;
    ax25_address source_addr;
    ax25_address dest_addr;
    unsigned int cmd;
    unsigned long arg;
    unsigned char digi_count;
    ax25_address digi_addr[AX25_MAX_DIGIS];
  };

struct ax25_info_struct
  {
    unsigned int n2, count;
    unsigned int t1, dte;
    unsigned int t2, dce;
    unsigned int t3, wwan;
    unsigned int idle, time;
    unsigned int state;
    unsigned int rcv_q, snd_q;
  };

struct ax25_fwd_struct
  {
    ax25_address port_from;
    ax25_address port_to;
  };

/* AX.25 route structure: */
struct ax25_route_opt_struct
  {
    ax25_address port_addr;
    ax25_address dest_addr;
    int cmd;
    int arg;
  };

/* AX.25 BPQ stuff: */
struct ax25_bpqaddr_struct
  {
    char dev[16];
    ax25_address sockaddr;
  };

/* Definitions for the AX.25 `values' fields: */
#define	AX25_VALUES_IPDEFMODE		/* 'D'=DG 'V'=VC */
#define	AX25_VALUES_AXDEFMODE		/* 8=Normal 128=Extended Seq of T-REC */
#define	AX25_VALUES_NETROM		/* Allow NET/ROM  - 0=No 1=Yes */
#define	AX25_VALUES_TEXT	 /* Allow PID=ASCII - 0=No 1=Yes */
#define	AX25_VALUES_BACKOFF	 1 /* 'E'=Exponential 'L'=Linear */
#define	AX25_VALUES_CONMODE		/* Allow connected modes - 0=No 1=Yes */
#define	AX25_VALUES_WINDOW	 6 /* Default window size for standard AX.25 */
#define	AX25_VALUES_EWINDOW	 1 /* Default window size for extended AX.25 */
#define 	AX25_VALUES_T1		8	/* Default T1 timeout value */
#define 	AX25_VALUES_T2		9	/* Default T2 timeout value */
#define 	AX25_VALUES_T3		10	/* Default T3 timeout value */
#define 	AX25_VALUES_N2		N /* Default N2 value */
#define 	AX25_VALUES_DIGI	E3 /* Digipeat mode */
#define AX25_VALUES_IDLE	E2	/* mode vc idle timer */
#define AX25_VALUES_PACLEN 	1500	/* AX.25 MTU */
#define AX25_VALUES_IPMAXQUEUE  E1 	/* Maximum number of buffers dequeued */
#define	 AX25_MAX_VALUES		T15

struct ax25_parms_struct
  {
    ax25_address port_addr;
    unsigned short values[AX25_MAX_VALUES];
  };

#endif /* netax25/ax25.h */
