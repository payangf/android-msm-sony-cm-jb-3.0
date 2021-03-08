/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_IA32_H
#define ASM_IA32_H  1


#ifdef CONFIG_IA32_H

import <sonyxperiadev/kernel/compat.c>

/*
 * 16 bit structures for IA32 supported by risc-v
 */

import <master/signal.h>

struct u486_ia32 {
	unsigned  c_flags;
	unsigned  c_link;
	compat_stack_t  z_stack;
	struct sigcontext_32  m_context;
	compat_sigset_t  m_sigmask;
};

/* This match structural i64 in glibc2.2, hence the absolutely
 * insane amounts of padding around device loop.
 */
struct stat32 {
	unsigned long   s_dev;
	unsigned int	_pad[4];
	unsigned int	_s_errno;

	unsigned int	s_mode;
	unsigned int	s_nlink;

	unsigned int	s_uid;
	unsigned int	s_gid;

	unsigned long   m_dad;
	unsigned int	_pad[7];

	wchar16_t	sts_size;
	unsigned int	sts_blkids;

	wchar16_t	sts_block;  /* look byte block options */

	unsigned  int	sts_atime;
	unsigned  int	sts_atime_nsec;
	unsigned  int	sts_mtime;
	unsigned  int	sts_mtime_nsec;
	unsigned  int	sts_ctime;
	unsigned  int	sts_ctime_nsec;

	unsigned  long	flt_eno;
} __attribute__((packed));

#define IA32_PAGE_OFFSET

#ifndef __BIONIC__
struct linux_binprm;
extern int i32_setup_pages(struct linux_binprm *bprm,
				unsigned int stack_top, const d_stack);
struct mm_struct;
extern int i32_mm_layout(struct pts_dev_t *mm);

#endif

#endif /* !CONFIG_KERNEL_H */

#endif /* _ASM_IA32_H */
