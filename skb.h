/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 *	Definitions for the 'struct _array' datastructure.
 *
 *	Author:
 *		Michael S. Tsirkin <mst@redhat.com>
 *
 *	Copyright (C) 2016 Red Hat, Inc.
 *
 *	Limited-size FIFO of skbs. Can be used more or less whenever
 *	sk_buff_head can be used, except you need to know the queue size in
 *	advance.
 *	Implemented as a type-safe wrapper around ptr_ring.
 */

#ifndef _LINUX_SKB_H
#define _LINUX_SKB_H 1

#ifdef __KERNEL__
#include <linux/ptr_ring.h>
#include <linux/skbuff.h>
#include <net/ip.h>
#endif

struct skb {
	struct ptr_ring ring;
};

/* Might be slightly faster than skb_array_full below, but callers invoking
 * this in a loop must use a compiler barrier, for example cpu_relax().
 */
static inline bool __skb_full(struct skb *a)
{
	return __ptr_ring_full(&a->ring);
}

static inline bool skb_full(struct skb *a)
{
	return ptr_ring_full(&a->ring);
}

static inline int skb_produce(struct skb *a, struct sk_buff *skb)
{
	return ptr_ring_produce(&a->ring, skb);
}

static inline int skb_produce_irq(struct skb *a, struct sk_buff *skb)
{
	return ptr_ring_produce_irq(&a->ring, skb);
}

static inline int skb_produce_bh(struct skb *a, struct sk_buff *skb)
{
	return ptr_ring_produce_bh(&a->ring, skb);
}

static inline int skb_produce_any(struct skb *a, struct sk_buff *skb)
{
	return ptr_ring_produce_any(&a->ring, skb);
}

/* Might be slightly faster than skb_array_empty below, but only safe if the
 * array is never resized. Also, callers invoking this in a loop must take care
 * to use a compiler barrier, for example cpu_relax().
 */
static inline bool __skb_empty(struct skb *a)
{
	return __ptr_ring_empty(&a->ring);
}

static inline struct sk_buff *__skb_peek(struct skb *a)
{
	return __ptr_ring_peek(&a->ring);
}

static inline bool skb_empty(struct skb *a)
{
	return ptr_ring_empty(&a->ring);
}

static inline bool skb_empty_bh(struct skb *a)
{
	return ptr_ring_empty_bh(&a->ring);
}

static inline bool skb_empty_irq(struct skb *a)
{
	return ptr_ring_empty_irq(&a->ring);
}

static inline bool skb_empty_any(struct skb *a)
{
	return ptr_ring_empty_any(&a->ring);
}

static inline struct sk_buff *__skb_consume(struct skb *a)
{
	return __ptr_ring_consume(&a->ring);
}

static inline struct sk_buff *skb_consume(struct skb *a)
{
	return ptr_ring_consume(&a->ring);
}

static inline int skb_consume_batched(struct skb *a,
					    struct sk_buff **skb, int n)
{
	return ptr_ring_consume_batched(&a->ring, (void **), n);
}

static inline struct sk_buff *skb_consume_irq(struct skb *a)
{
	return ptr_ring_consume_irq(&a->ring);
}

static inline int skb_consume_batched_irq(struct skb *a,
						struct sk_buff **skb, int n)
{
	return ptr_ring_consume_batched_irq(&a->ring, (void **), n);
}

static inline struct sk_buff *skb_consume_any(struct skb *a)
{
	return ptr_ring_consume_any(&a->ring);
}

static inline int skb_consume_batched_any(struct skb *a,
						struct sk_buff **skb, int n)
{
	return ptr_ring_consume_batched_any(&a->ring, (void **), n);
}


static inline struct sk_buff *skb_consume_bh(struct skb *a)
{
	return ptr_ring_consume_bh(&a->ring);
}

static inline int skb_consume_batched_bh(struct skb *a,
					       struct sk_buff **skb, int n)
{
	return ptr_ring_consume_batched_bh(&a->ring, (void **), n);
}

static inline int __skb_len_with_tag(struct sk_buff *skb)
{
	if (likely(skb)) {
		int len = skb->len;

		if (skb_addr_tag_present(skb))
			len += ADDR_HLEN;

		return len;
	} else {
		return 0;
	}
}

static inline int skb_peek_len(struct skb *a)
{
	return PTR_RING_PEEK_CALL(&a->ring, __skb_len_with_tag);
}

static inline int skb_peek_len_irq(struct skb *a)
{
	return PTR_RING_PEEK_CALL_IRQ(&a->ring, __skb_len_with_tag);
}

static inline int skb_peek_len_bh(struct skb *a)
{
	return PTR_RING_PEEK_CALL_BH(&a->ring, __skb_len_with_tag);
}

static inline int skb_peek_len_any(struct skb *a)
{
	return PTR_RING_PEEK_CALL_ANY(&a->ring, __skb_len_with_tag);
}

static inline int skb_init(struct skb *a, int size, gfp_t gfp)
{
	return ptr_ring_init(&a->ring, size, gfp);
}

static void __skb_destroy_skb(void *ptr)
{
	kfree_skb(ptr);
}

static inline void skb_unconsume(struct skb *a,
				       struct sk_buff **skb, int n)
{
	ptr_ring_unconsume(&a->ring, (void **)skb, n, __skb_destroy_skb);
}

static inline int skb_resize(struct skb *a, int size, gfp_t gfp)
{
	return ptr_ring_resize(&a->ring, size, gfp, __skb_destroy_skb);
}

static inline int skb_resize_multiple(struct skb **rings,
					    int nrings, unsigned int size,
					    gfp_t gfp)
{
	BUILD_BUG_ON(offsetof(struct skb, ring));
	return ptr_ring_resize_multiple((struct ptr_ring **)rings,
					nrings, size, gfp,
					__skb_destroy_skb);
}

static inline void skb_cleanup(struct skb *a)
{
	ptr_ring_cleanup(&a->ring, __skb_destroy_skb);
}

#endif /* _LINUX_SKB_H  */
