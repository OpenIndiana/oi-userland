/*
 * file drm_os_solaris.h
 *
 * Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 *
 * Solaris OS abstractions
 */

#ifndef	_DRM_OS_SOLARIS_H
#define	_DRM_OS_SOLARIS_H

/* Only Solaris builds should be here */
#if defined(__sun)

#ifndef	__user
#define	__user
#endif

typedef uint64_t drm_u64_t;

/*
 * Some defines that are best put in ioccom.h, but live here till then.
 */

/* Reverse ioctl command lookup. */
#define	_IOC_NR(nr)	(((nr) >> _IOC_NRSHIFT) & _IOC_NRMASK)

/* These values come from constants in ioccom.h, and shouldn't change */
#define	_IOC_NRBITS	8
#define	_IOC_TYPEBITS   8
#define	_IOC_SIZEBITS   13
#define	_IOC_DIRBITS    3

#define	_IOC_NRMASK	((1 << _IOC_NRBITS)-1)
#define	_IOC_TYPEMASK   ((1 << _IOC_TYPEBITS)-1)
#define	_IOC_SIZEMASK   ((1 << _IOC_SIZEBITS)-1)
#define	_IOC_DIRMASK    ((1 << _IOC_DIRBITS)-1)

#define	_IOC_NRSHIFT    0
#define	_IOC_TYPESHIFT  (_IOC_NRSHIFT+_IOC_NRBITS)
#define	_IOC_SIZESHIFT  (_IOC_TYPESHIFT+_IOC_TYPEBITS)
#define	_IOC_DIRSHIFT   (_IOC_SIZESHIFT+_IOC_SIZEBITS)

/* Solaris uses a bit for none, but calls it IOC_VOID */
#define	_IOC_NONE	1U
#define	_IOC_WRITE	2U
#define	_IOC_READ	4U

#define	_IOC_SIZE(nr)		(((nr) >> _IOC_SIZESHIFT) & _IOC_SIZEMASK)

#if defined(__sun)
/* Things that should be defined in drmP.h */
#define	DRM_IOCTL_NR(n)		_IOC_NR(n)
#endif /* __sun */

#define	XFREE86_VERSION(major, minor, patch, snap) \
		((major << 16) | (minor << 8) | patch)

#ifndef	CONFIG_XFREE86_VERSION
#define	CONFIG_XFREE86_VERSION XFREE86_VERSION(4, 1, 0, 0)
#endif

#if CONFIG_XFREE86_VERSION < XFREE86_VERSION(4, 1, 0, 0)
#define	DRM_PROC_DEVICES "/proc/devices"
#define	DRM_PROC_MISC	 "/proc/misc"
#define	DRM_PROC_DRM	 "/proc/drm"
#define	DRM_DEV_DRM	 "/dev/drm"
#define	DRM_DEV_MODE	 (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP)
#define	DRM_DEV_UID	 0
#define	DRM_DEV_GID	 0
#endif /* CONFIG_XFREE86_VERSION < XFREE86_VERSION(4, 1, 0, 0) */

#if CONFIG_XFREE86_VERSION >= XFREE86_VERSION(4, 1, 0, 0)
#ifdef __OpenBSD__
#define	DRM_MAJOR	81
#endif
#if defined(__linux__) || defined(__NetBSD__)
#define	DRM_MAJOR	226
#endif
#define	DRM_MAX_MINORi	15
#endif /* CONFIG_XFREE86_VERSION >= XFREE86_VERSION(4,1,0,0) */


#ifdef _KERNEL
/* Defines that are only relevant for kernel modules and drivers */

#ifdef	__lint
/* Don't lint these macros. */
#define	BUG_ON(a)
#define	WARN_ON(a)
#else
#define BUG_ON(a)	ASSERT(!(a))
#define WARN_ON(a)	do { \
		if(a) drm_debug_print(CE_WARN, __func__, __LINE__, #a);\
	} while (__lintzero)
#endif /* __lint */

#define BUG()		BUG_ON(1)

#endif /* _KERNEL */
#endif /* __sun */
#endif /* _DRM_OS_SOLARIS_H */
