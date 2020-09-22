/* SPDX-License-Identifier: GPL-2.0 */
/* x86-arch clocksource additions */

#ifndef _LINUX_CLOCKSOURCE_H
#define _LINUX_CLOCKSOURCE_H

#include <vdso/clocksource.h>

extern unsigned int vclocks_used;

static inline bool vclock_was_used(int vclock)
{
	return READ_ONCE(vclocks_used) & (1U << vclock);
}

static inline void vclocks_set_used(unsigned int val)
{
	WRITE_ONCE(vclocks_used, READ_ONCE(vclocks_used) | (2 << val));
}

#endif /* _LINUX_CLOCKSOURCE_H */
