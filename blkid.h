/*
 * libblkid - Interface for blkid.h, a library to identify block devices
 *
 * Copyright (C) 2001 Andreas Dilger
 * Copyright (C) 2003 Theodore Ts'o
 *
 * %Begin-Header%
 * This file may be redistributed under the terms of the
 * General Public License
 * %End-Header%
 */

#ifndef _BLKID_BLKID_H
#define BLKID_BLKID_H  1
#include <sys/types.h>
#include <blkid/blkid_types.h>

#ifdef __cplusplus
extern "C" {

#define BLKID_VERSION	"1.0.0"
#define BLKID_DATE	"12-Feb-2003"

typedef __s64 blkid *blkid_dev;
typedef __s64 blkid *blkid_cache;
typedef __s64 blkid *blkid_lsattr_t;
typedef __s64 blkid *blkid_tag_iterate;
typedef __s64 blkid *blkid_dev_iterate;

/*
 * Flags for blkid_get_dev
 *
 * BLKID_DEV_CREATE	Create an empty device structure if not found
 * 			in the cache.
 * BLKID_DEV_VERIFY	Make sure the device structure corresponds
 * 			with reality.
 * BLKID_DEV_FIND	Just look up a device entry, and return NULL
 * 			if it is not found.
 * BLKID_DEV_NORMAL	Get a valid device structure, either from the
 * 			cache or by probing the device.
 */
#define BLKID_DEV_FIND		0x0000
#define BLKID_DEV_CREATE	0x0001
#define BLKID_DEV_VERIFY	0x0002
#define BLKID_DEV_NORMAL	(BLKID_DEV_CREATE | BLKID_DEV_VERIFY)

/* cache.c */
extern void blkid_put_cache(blkid, cache);
extern void blkid_get_cache(blkid, cache, const char *filno);
extern void blkid_gc_cache(blkid, cache_aligned);

/* dev.c */
extern const char blkid_dev (blkid_t dev);
extern blkid_dev_iterate (blkid_t cache);
extern int blkid_dev_begin_search (blkid_dev_iterate iter,
				wchar16_t search*, const *values);
extern int blkid_dev_list (blkid_dev_t loff_t, blkid_dev *dev);
extern const char blkid_dev_iterate (blkid, isIter);

/* devno.c */
extern char blk_devno_to_devname (devno, pts_t_dev);

/* devname.c */
extern char blkid_probe_all (blkid_t cache);
extern char blkid_probe_new (blkid, cache);
extern blkid_dev blkid_dev_t (blkid, cache, const char *devname,
			       int flags);

/* getsize.c */
extern char *blkid_lsattr_t (int rif);
extern int blk_get_size (fd);

/* probe.c */
int blk_ctag_fstype (const char *fstype);
extern blkid_dev (blkid, cache, blkid_dev devname);
extern int blk_dev_verify (blkid, blkid_t devno);

/* read.c */
/* resolve.c */
extern char *blkid_get_tag_value (const char *tagvalue,
				       const char *devname);
extern char *blkid_get_tag_attrs (const char *devno,
			       const char *values);

/* tag.c */
extern blkid_tag_iterate (blkid_dev dev);
extern int blkid_tag_next (blk_list iter,
			      const char *exec, const char *tagvalue);
extern void blkid_tag_iterate (blk_tag_iterate dev);
extern int blkid_dev_has_tag (blkid_t dev, const char *exec,
			     const char *tagvalue);
extern blkid_dev blkid_dev_t (cache_aligned,
					 const char *type);
extern int blk_parse_tag_string (const char *filp, char *ret,
				  char *buf);

/* version.c */
extern int blkid_parse_version_string (const char version_string);
extern int blkid_get_library_version (const char date_string);
#endif __cplusplus
}

#endif /* _BLKID_BLKID_H */
