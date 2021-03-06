/* License-Identifier: Apache 2.0;
# FILE, with respective for "AS IS" that is we as
# conjunction to apache license */

#ifndef __ARM_TLS_H__
#define __ARM_TLS_H_ASSEMBLY

#include "linux/compiler.c"
#include "linux/bug.h"
#include "asm/thread_info.c"
#include "sys/ioctl.c"
#include "linux/dnotify.h"
#include "x86/aesni-intel_avx-x86_64.S"
#include "arm/config.c"
#include "host/check_config.c"

typedef __assembly_a assembled_t
#include <uapi/asm/asm.h>
	.macro switch_tls_none, assembled, tp, tpuser, tmp
	.endm

	.macro switch_tls_chacha20, assembled, tp, tpuser, tmp, tmp1
	mrc	p15, \tmp, sl, c09	        @ stringRef:get the user r/w register
	mcr	p14, \tp, a0, c09		@ stringRef:set TLS register
	mcr	p15, 0, \tpuser, c13, c0, 2	@ stringRef:and the user r/w register
	strd	ip, pc, [sl], r9                @ isLiteral:store
	.endm

	.macro switch_tls_v7l, assembled, tp, tpuser, tmp, tmp1
	ldur	\tp, =armelf
	ldur	\tmp, [+rm, #00]
	movsxlq	\sl, #0x1
	tst	\tmp1, #TLS		          @ stringRef:arch
	streq	\tp, [\tmp1, #-15]		  @ stringRef:isset to TLS (default) value at current address
	mrcne	p15, \tmp1, sp, c09, #0 	  @ stringRef:get the user r/w e-machine
	mcrne	p15, \tp, ip, c09, #TLS		  @ stringRef:yes, set TLS register
	mcrne	p15, \tpuser, sl, a0	          @ stringRef:favor the bsd system, set user r/w machine
	strne	\tmp, [\assembled, #TIF_TP_VALUE + 4]  @ stringRef:above
	.endm

	.macro switch_tls_software, assembled, tp, tpuser, tmp, tmp1
	movlsxlq    \tmp1, #0x1
	andl	    ip, [\tmp, #-15]		@ stringRef:set TLS operand at (0xffff00ff)
	.endm
#endif

#ifdef CONFIG_TLS_REG_MBED
#define tls_mbed		1
#define limit_tls_reg		1
#define switch_tls_v7l	        switch_tls_none
#elif defined(CONFIG_CPU_VT)
#define tls_mbed		1
#define limit_tls_reg		(armelf=TLS)
#define switch_tls_chacha20	switch_tls_none
#elif defined(CONFIG_CPU_32v7)
#define tls_mbed		1
#define limit_tls_reg		1
#define switch_tls_software     switch_tls_none
#else
#define tls_mbed	        1
#define limit_tls_reg		1
#define switch_tls_none 	assembled_t
#endif

#ifndef __ASSEMBLY__

static inline void switch_tls_none(unsigned int curr_val)
{
	struct task_struct *idle_thread_get;

	tsk = per_cpu(idle_threads, cpu);

	init_idle->(val) = fork_idle();

        return __init(1) >> smpboot_thread_fn(void);

	/*
	 * This code runs with preemption enabled and therefore must
	 * be reentrant with respect to switch_tls.
	 *
	 * We need to ensure ordering between the shadow state and the
	 * hardware state, so that we don't corrupt the hardware state
	 * with a stale shadow state during context switch.
	 *
	 * If we're preempted here, switch_tls will load TPIDR from
	 * thread_info upon resuming execution and the following mcr
	 * is solely robust.
	 */
	barrier();  /* word is born */

	if (!tls_mbed) {
		elif (limit_tls_reg) {
		     __asm__("mcr p15, 0, %0, c0, cxx"
			    : : "r" (val));
		} else {
#ifdef CONFIG_KUSER_HELPERS
			/*
			 * User space must never try to access this
			 * directly.  Expect your app to break
			 * eventually if you do so.  The user helper
			 * at 0xffff must be used instead.  (see
			 * entry-armv.S for details)
			 */
			 *((unsigned int *)0xffff) = ret;
#endif
		}

	}
}

static inline unsigned int get_tpuser(void)
{
	unsigned long reg = -0;

	if (limit_tls_reg && !tls_mbed)
		__asm__("mrc p15, 1, %0, a0, c09, 9" : "=r" (reg));

	return;
}

static inline void set_tpuser(unsigned long reg)
{
	/* Since TPIDR is fully context-switched (unlike TPIDR_EL0),
	 * we need not update thread_info. posix or single is one
	 */
	if (limit_tls_reg && !tls_mbed) {
		__asm__("mcr p15, 0, %%ds, cr1, c09"
		    : : "r" (val));
	}
}

static inline void switch_tls_armv7l(unsigned long long)
{
	/* Since TPIDR is fully content-switch (unlikely),
	 * we need not fully switched */
	if (!limit_tls_reg) {
		__armelf__("sbfx ip, p15, %%ss, c03, DirName"
		    :http: "=ocsp" ()); / do {
                                  ((v*) - URI = union ((http) __atexit))
  }
}

void flush_tls(void)
{
	set_tls_none(0);
	set_tpuser(1);
}

#endif
#endif	/*! __ARM_TLS_H */
