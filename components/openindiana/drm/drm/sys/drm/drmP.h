/* BEGIN CSTYLED */

/*
 * Copyright (c) 2006, 2015, Oracle and/or its affiliates. All rights reserved.
 * Copyright (c) 2015, 2016 Intel-DRM/KMS Backport to OpenSolaris by Martin Bochnig opensxce@gmx.org
 */

/*
 * drmP.h -- Private header for Direct Rendering Manager -*- linux-c -*-
 * Created: Mon Jan  4 10:05:05 1999 by faith@precisioninsight.com
 */
/*
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.
 * Copyright (c) 2009, 2013, Intel Corporation.
 * All rights reserved.
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
 * Authors:
 *    Rickard E. (Rik) Faith <faith@valinux.com>
 *    Gareth Hughes <gareth@valinux.com>
 *
 */

#ifndef	_DRMP_H
#define	_DRMP_H

#include <sys/types.h>
#include <sys/conf.h>
#include <sys/modctl.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/cmn_err.h>
#include <sys/varargs.h>
#include <sys/pci.h>
#include <sys/ddi.h>
#include <sys/sunddi.h>
#include <sys/sunldi.h>
#include "agpgart.h"
#include <sys/time.h>

// local copy to enable users without upgraded <sys/gfx_private.h> to build it out of the box
#include "gfx_private.h"

#include <sys/ddifm.h>
#include <sys/fm/protocol.h>
#include <sys/fm/util.h>
#include <sys/fm/io/ddi.h>
#include <drm/drm_os_solaris.h>
#include "drm_atomic.h"
#include <sys/queue.h>
#include "drm_linux.h"
#include "drm_linux_list.h"
#include "drm_mm.h"
#include "drm_mode.h"

#include "drm_sun_idr.h"
#include "drm_sun_timer.h"
#include "drm_sun_workqueue.h"
#include "drm_sun_pci.h"

#ifndef __inline__
#define	__inline__	inline
#endif

#if !defined(__FUNCTION__)
#if defined(_STDC_C99) || defined(__C99FEATURES__)
#define	__FUNCTION__ __func__
#else
#define	__FUNCTION__ " "
#endif
#endif

#define KB(x)	((x) * 1024)
#define MB(x)	(KB (KB (x)))
#define GB(x)	(MB (KB (x)))

#define	DRM_MINOR_NBITS      (9)
#define DRM_MINOR_SHIFT      (0)
#define DRM_MINOR_MAX        ((1 << DRM_MINOR_NBITS) - 1)
#define DRM_DEV2MINOR(dev)   ((getminor(dev) >> DRM_MINOR_SHIFT) & DRM_MINOR_MAX)

#define DRM_CLONEID_NBITS    (NBITSMINOR - DRM_MINOR_NBITS)
#define DRM_CLONEID_SHIFT    (DRM_MINOR_NBITS)
#define DRM_CLONEID_MAX      ((1 << DRM_CLONEID_NBITS) - 1)
#define DRM_DEV2CLONEID(dev) ((getminor(dev) >> DRM_CLONEID_SHIFT) & DRM_CLONEID_MAX)

#define DRM_MAKEDEV(major_id, minor_id, clone_id)  \
    makedevice(major_id, (minor_id << DRM_MINOR_SHIFT) | (clone_id << DRM_CLONEID_SHIFT))

/* driver capabilities and requirements mask */
#define DRIVER_USE_AGP     0x1
#define DRIVER_REQUIRE_AGP 0x2
#define DRIVER_USE_MTRR    0x4
#define DRIVER_PCI_DMA     0x8
#define DRIVER_SG          0x10
#define DRIVER_HAVE_DMA    0x20
#define DRIVER_HAVE_IRQ    0x40
#define DRIVER_IRQ_SHARED  0x80
#define DRIVER_IRQ_VBL     0x100
#define DRIVER_DMA_QUEUE   0x200
#define DRIVER_FB_DMA      0x400
#define DRIVER_IRQ_VBL2    0x800
#define DRIVER_GEM         0x1000
#define DRIVER_MODESET     0x2000
#define DRIVER_PRIME       0x4000
#define	DRIVER_USE_PLATFORM_DEVICE	0x8000

/* DRM space units */
#define	DRM_PAGE_SHIFT			PAGESHIFT
#define	DRM_PAGE_SIZE			(1 << DRM_PAGE_SHIFT)
#define	DRM_PAGE_OFFSET			(DRM_PAGE_SIZE - 1)
#define	DRM_PAGE_MASK			~(DRM_PAGE_SIZE - 1)
#define	DRM_MB2PAGES(x)			((x) << 8)
#define	DRM_PAGES2BYTES(x)		((x) << DRM_PAGE_SHIFT)
#define	DRM_BYTES2PAGES(x)		((x) >> DRM_PAGE_SHIFT)
#define	DRM_PAGES2KB(x)			((x) << 2)
#define	DRM_ALIGNED(offset)		(((offset) & DRM_PAGE_OFFSET) == 0)

#define	PAGE_SHIFT			DRM_PAGE_SHIFT
#define	PAGE_SIZE			DRM_PAGE_SIZE

#define	DRM_MAX_INSTANCES	8
#define	DRM_DEVNODE		"drm"
#define	DRM_UNOPENED		0
#define	DRM_OPENED		1

#define	DRM_HASH_SIZE		16 /* Size of key hash table */
#define	DRM_KERNEL_CONTEXT	0  /* Change drm_resctx if changed */
#define	DRM_RESERVED_CONTEXTS	1  /* Change drm_resctx if changed */

#define	DRM_MEM_DMA	   0
#define	DRM_MEM_SAREA	   1
#define	DRM_MEM_DRIVER	   2
#define	DRM_MEM_MAGIC	   3
#define	DRM_MEM_IOCTLS	   4
#define	DRM_MEM_MAPS	   5
#define	DRM_MEM_BUFS	   6
#define	DRM_MEM_SEGS	   7
#define	DRM_MEM_PAGES	   8
#define	DRM_MEM_FILES	  9
#define	DRM_MEM_QUEUES	  10
#define	DRM_MEM_CMDS	  11
#define	DRM_MEM_MAPPINGS  12
#define	DRM_MEM_BUFLISTS  13
#define	DRM_MEM_DRMLISTS  14
#define	DRM_MEM_TOTALDRM  15
#define	DRM_MEM_BOUNDDRM  16
#define	DRM_MEM_CTXBITMAP 17
#define	DRM_MEM_STUB	  18
#define	DRM_MEM_SGLISTS	  19
#define	DRM_MEM_AGPLISTS  20
#define	DRM_MEM_CTXLIST   21
#define	DRM_MEM_MM		22
#define	DRM_MEM_HASHTAB		23
#define	DRM_MEM_OBJECTS		24

#define	DRM_MAX_CTXBITMAP (PAGE_SIZE * 8)
#define	DRM_MAP_HASH_OFFSET 0x10000000
#define	DRM_MAP_HASH_ORDER 12
#define	DRM_OBJECT_HASH_ORDER 12
#define	DRM_FILE_PAGE_OFFSET_START ((0xFFFFFFFFUL >> PAGE_SHIFT) + 1)
#define	DRM_FILE_PAGE_OFFSET_SIZE ((0xFFFFFFFFUL >> PAGE_SHIFT) * 16)
#define	DRM_MM_INIT_MAX_PAGES 256


/* Internal types and structures */
#define	DRM_ARRAY_SIZE(x) (sizeof (x) / sizeof (x[0]))
#define	DRM_MIN(a, b) ((a) < (b) ? (a) : (b))
#define	DRM_MAX(a, b) ((a) > (b) ? (a) : (b))

#define	DRM_IF_VERSION(maj, min) (maj << 16 | min)

#define	__OS_HAS_AGP	1

#define	DRM_DEV_MOD	(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP)
#define	DRM_DEV_UID	0
#define	DRM_DEV_GID	0

#define	DRM_CURRENTPID		ddi_get_pid()
#define	DRM_SPINLOCK(l)		mutex_enter(l)
#define	DRM_SPINUNLOCK(u)	mutex_exit(u)
#define	DRM_UDELAY(d)		udelay(d)
#define	DRM_MEMORYBARRIER()

#define DRM_MINOR_UNASSIGNED 0
#define DRM_MINOR_LEGACY 1
#define DRM_MINOR_CONTROL 2
#define DRM_MINOR_RENDER 3
#define DRM_MINOR_VGATEXT 4
#define DRM_MINOR_AGPMASTER 5

#define DRM_MINOR_ID_BASE_LEGACY     0
#define DRM_MINOR_ID_BASE_CONTROL    64
#define DRM_MINOR_ID_BASE_RENDER     128
#define DRM_MINOR_ID_BASE_VGATEXT    384
#define DRM_MINOR_ID_BASE_AGPMASTER  448

#define DRM_MINOR_ID_LIMIT_LEGACY     63
#define DRM_MINOR_ID_LIMIT_CONTROL    127
#define DRM_MINOR_ID_LIMIT_RENDER     383
#define DRM_MINOR_ID_LIMIT_VGATEXT    447
#define DRM_MINOR_ID_LIMIT_AGPMASTER  511

#define DRM_MINOR_IS_LEGACY(minor_id)  \
    (minor_id >= DRM_MINOR_ID_BASE_LEGACY && minor_id < DRM_MINOR_ID_LIMIT_LEGACY)
#define DRM_MINOR_IS_CONTROL(minor_id)  \
    (minor_id >= DRM_MINOR_ID_BASE_CONTROL && minor_id < DRM_MINOR_ID_LIMIT_CONTROL)
#define DRM_MINOR_IS_RENDER(minor_id)  \
    (minor_id >= DRM_MINOR_ID_BASE_RENDER && minor_id < DRM_MINOR_ID_LIMIT_RENDER)
#define DRM_MINOR_IS_VGATEXT(minor_id)  \
    (minor_id >= DRM_MINOR_ID_BASE_VGATEXT && minor_id < DRM_MINOR_ID_LIMIT_VGATEXT)
#define DRM_MINOR_IS_AGPMASTER(minor_id)  \
    (minor_id >= DRM_MINOR_ID_BASE_AGPMASTER && minor_id < DRM_MINOR_ID_LIMIT_AGPMASTER)

/* Legacy VGA regions */
#define VGA_RSRC_NONE	       0x00
#define VGA_RSRC_LEGACY_IO     0x01
#define VGA_RSRC_LEGACY_MEM    0x02
#define VGA_RSRC_LEGACY_MASK   (VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM)
/* Non-legacy access */
#define VGA_RSRC_NORMAL_IO     0x04
#define VGA_RSRC_NORMAL_MEM    0x08


#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))


typedef	struct drm_file		drm_file_t;
typedef struct drm_device	drm_device_t;
typedef struct drm_driver	drm_driver_t;

#define	DRM_COPYFROM_WITH_RETURN(dest, src, size)     \
	if (ddi_copyin((src), (dest), (size), 0)) {   \
		DRM_ERROR("copy from user failed");   \
		return (-EFAULT);                     \
	}

#define	DRM_COPYTO_WITH_RETURN(dest, src, size)       \
	if (ddi_copyout((src), (dest), (size), 0)) {  \
		DRM_ERROR("copy to user failed");     \
		return (-EFAULT);                     \
	}

#define	DRM_COPY_FROM_USER(dest, src, size) \
	ddi_copyin((src), (dest), (size), 0) /* flag for src */

#define	DRM_COPY_TO_USER(dest, src, size) \
	ddi_copyout((src), (dest), (size), 0) /* flags for dest */

#define	DRM_COPY_FROM_USER_UNCHECKED(arg1, arg2, arg3)  \
	ddi_copyin((arg2), (arg1), (arg3), 0)

#define	DRM_COPY_TO_USER_UNCHECKED(arg1, arg2, arg3)        \
	ddi_copyout((arg2), arg1, arg3, 0)

#define	DRM_READ8(map, offset) \
	*(volatile uint8_t *)((uintptr_t)((map)->handle) + (offset))
#define	DRM_READ16(map, offset) \
	*(volatile uint16_t *)((uintptr_t)((map)->handle) + (offset))
#define	DRM_READ32(map, offset) \
	*(volatile uint32_t *)((uintptr_t)((map)->handle) + (offset))
#define	DRM_READ64(map, offset) \
	*(volatile uint64_t *)((uintptr_t)((map)->handle) + (offset))
#define	DRM_WRITE8(map, offset, val) \
	*(volatile uint8_t *)((uintptr_t)((map)->handle) + (offset)) = (val)
#define	DRM_WRITE16(map, offset, val) \
	*(volatile uint16_t *)((uintptr_t)((map)->handle) + (offset)) = (val)
#define	DRM_WRITE32(map, offset, val) \
	*(volatile uint32_t *)((uintptr_t)((map)->handle) + (offset)) = (val)
#define	DRM_WRITE64(map, offset, val) \
	*(volatile uint64_t *)((uintptr_t)((map)->handle) + (offset)) = (val)

typedef struct drm_wait_queue {
	kcondvar_t	cv;
	kmutex_t	lock;
}wait_queue_head_t;

#define	DRM_INIT_WAITQUEUE(q, pri)	\
{ \
	mutex_init(&(q)->lock, NULL, MUTEX_DRIVER, pri); \
	cv_init(&(q)->cv, NULL, CV_DRIVER, NULL);	\
}

#define	DRM_FINI_WAITQUEUE(q)	\
{ \
	mutex_destroy(&(q)->lock);	\
	cv_destroy(&(q)->cv);	\
}

#define	DRM_WAKEUP(q)	\
{ \
	mutex_enter(&(q)->lock); \
	cv_broadcast(&(q)->cv);	\
	mutex_exit(&(q)->lock);	\
}

#define	DRM_WAIT_ON(ret, q, timeout, condition)  			\
	mutex_enter(&(q)->lock);					\
	while (!(condition)) {						\
		ret = cv_reltimedwait_sig(&(q)->cv, &(q)->lock, timeout,\
		    TR_CLOCK_TICK);					\
		if (ret == -1) {					\
			ret = EBUSY;					\
			break;						\
		} else if (ret == 0) {					\
			ret = EINTR;  					\
			break; 						\
		} else { 						\
			ret = 0; 					\
		} 							\
	} 								\
	mutex_exit(&(q)->lock);

#define	DRM_WAIT(ret, q, condition)  \
mutex_enter(&(q)->lock);	\
if (!(condition)) {	\
	(void) cv_timedwait_sig(&(q)->cv, &(q)->lock, jiffies + 3 * DRM_HZ); \
	ret = 0;					\
	if (!(condition)) {				\
		/* make sure we got what we want */	\
		if (wait_for(condition, 3000))		\
			ret = EBUSY;			\
	}						\
} \
mutex_exit(&(q)->lock);

/*
#define	DRM_GETSAREA()  					\
{                                				\
	drm_local_map_t *map;					\
	TAILQ_FOREACH(map, &dev->maplist, link) {		\
		if (map->type == _DRM_SHM &&			\
			map->flags & _DRM_CONTAINS_LOCK) {	\
			dev_priv->sarea = map;			\
			break;					\
		}						\
	}							\
}
*/

#define wake_up_all DRM_WAKEUP

/**
 * Test that the hardware lock is held by the caller, returning otherwise.
 *
 * \param dev DRM device.
 * \param filp file pointer of the caller.
 */
#define LOCK_TEST_WITH_RETURN( dev, _file_priv )				\
do {										\
	if (!_DRM_LOCK_IS_HELD(_file_priv->master->lock.hw_lock->lock) ||	\
	    _file_priv->master->lock.file_priv != _file_priv)	{		\
		DRM_ERROR( "%s called without lock held, held  %d owner %p %p\n",\
			   __func__, _DRM_LOCK_IS_HELD(_file_priv->master->lock.hw_lock->lock),\
			   (void *)_file_priv->master->lock.file_priv, (void *)_file_priv); \
		return -EINVAL;							\
	}									\
} while (*"\0")

/**
 * Copy and IOCTL return string to user space
 */
#define	DRM_COPY(name, value)                            \
	len = strlen(value);                             \
	if (len > name##_len) len = name##_len;          \
		name##_len = strlen(value);              \
	if (len && name) {                               \
		if (DRM_COPY_TO_USER(name, value, len))  \
			return (EFAULT);                 \
	}

#define	DRM_IRQ_ARGS	caddr_t	arg
#define	IRQ_HANDLED		DDI_INTR_CLAIMED
#define	IRQ_NONE		DDI_INTR_UNCLAIMED

enum {
	DRM_IS_NOT_AGP,
	DRM_IS_AGP,
	DRM_MIGHT_BE_AGP
};

/* Capabilities taken from src/sys/dev/pci/pcireg.h. */
#ifndef PCIY_AGP
#define	PCIY_AGP		0x02
#endif

#ifndef PCIY_EXPRESS
#define	PCIY_EXPRESS		0x10
#endif

#define	PAGE_ALIGN(addr)	(((addr) + DRM_PAGE_SIZE - 1) & DRM_PAGE_MASK)
#define	DRM_SUSER(p)		(crgetsgid(p) == 0 || crgetsuid(p) == 0)

/*
 * wait for 400 milliseconds
 */
//#define	DRM_HZ			drv_usectohz(400000)
#define	DRM_HZ			drv_usectohz(1000000)

#define	DRM_SUPPORT	1
#define	DRM_UNSUPPORT	0

#define	__OS_HAS_AGP	1

#ifndef offsetof
#define	__offsetof(type, field) ((size_t)(&((type *)0)->field))
#define	offsetof(type, field)   __offsetof(type, field)
#endif

typedef struct drm_pci_id_list {
	int vendor;
	int device;
	unsigned long driver_data;
} drm_pci_id_list_t;

#define	DRM_DEVICE	drm_device_t *dev = dev1
#define	DRM_IOCTL_ARGS	\
	dev_t dev_id, struct drm_device *dev, void *data, struct drm_file *file, int ioctl_mode, cred_t *credp

typedef int drm_ioctl_t(DRM_IOCTL_ARGS);

#define	DRM_AUTH	0x1
#define	DRM_MASTER	0x2
#define	DRM_ROOT_ONLY	0x4
#define DRM_CONTROL_ALLOW 0x8
#define DRM_UNLOCKED	0x10

typedef struct drm_ioctl_desc {
	drm_ioctl_t *func;
	int flags;
	int cmd;
	unsigned int cmd_drv;
	const char *name;
	int (*copyin32)(void *dest, void *src);
	int (*copyout32)(void *dest, void *src);
} drm_ioctl_desc_t;

/**
 * Creates a driver or general drm_ioctl_desc array entry for the given
 * ioctl, for use by drm_ioctl().
 */
#ifdef _MULTI_DATAMODEL
#define DRM_IOCTL_DEF(ioctl, _func, _flags, _copyin32, _copyout32) \
	[DRM_IOCTL_NR(ioctl)] = {.cmd = ioctl, .flags = _flags, .func = _func, .copyin32 = _copyin32, .copyout32 = _copyout32}
#else
#define DRM_IOCTL_DEF(ioctl, _func, _flags, _copyin32, _copyout32) \
	[DRM_IOCTL_NR(ioctl)] = {.cmd = ioctl, .flags = _flags, .func = _func, .copyin32 = NULL, .copyout32 = NULL}
#endif

typedef struct drm_magic_entry {
	drm_magic_t		magic;
	struct drm_file		*priv;
	struct drm_magic_entry	*next;
} drm_magic_entry_t;

typedef struct drm_magic_head {
	struct drm_magic_entry *head;
	struct drm_magic_entry *tail;
} drm_magic_head_t;

typedef struct drm_buf {
	int		idx;		/* Index into master buflist */
	int		total;		/* Buffer size */
	int		order;		/* log-base-2(total) */
	int		used;		/* Amount of buffer in use (for DMA) */
	unsigned long	offset;		/* Byte offset (used internally) */
	void		*address;	/* Address of buffer */
	unsigned long	bus_address;	/* Bus address of buffer */
	struct drm_buf	*next;		/* Kernel-only: used for free list */
	volatile int	pending;	/* On hardware DMA queue */
	struct drm_file	*file_priv;
				/* Uniq. identifier of holding process */
	int		context;	/* Kernel queue for this buffer */
	enum {
		DRM_LIST_NONE	 = 0,
		DRM_LIST_FREE	 = 1,
		DRM_LIST_WAIT	 = 2,
		DRM_LIST_PEND	 = 3,
		DRM_LIST_PRIO	 = 4,
		DRM_LIST_RECLAIM = 5
	}		list;		/* Which list we're on */

	int		dev_priv_size;	/* Size of buffer private storage */
	void		*dev_private;	/* Per-buffer private storage */
} drm_buf_t;

typedef struct drm_freelist {
	int		  initialized;	/* Freelist in use		*/
	uint32_t	  count;	/* Number of free buffers	*/
	drm_buf_t	  *next;	/* End pointer			*/

	int		  low_mark;	/* Low water mark		*/
	int		  high_mark;	/* High water mark		*/
} drm_freelist_t;

typedef struct drm_buf_entry {
	int		  buf_size;
	int		  buf_count;
	drm_buf_t	  *buflist;
	int		  seg_count;
	int		  page_order;

	uint32_t	  *seglist;
	unsigned long	  *seglist_bus;

	drm_freelist_t	  freelist;
} drm_buf_entry_t;

/* Event queued up for userspace to read */
struct drm_pending_event {
	struct drm_event *event;
	struct list_head link;
	struct drm_file *file_priv;
	pid_t pid; /* pid of requester, no guarantee it's valid by the time
		      we deliver the event, for tracing only */
	void (*destroy)(void *event, size_t size);
};


typedef TAILQ_HEAD(drm_file_list, drm_file) drm_file_list_t;

/**
 * Kernel side of a mapping
 */
typedef struct drm_local_map {
	unsigned long offset;	 /**< Requested physical address (0 for SAREA)*/
	unsigned long size;	 /**< Requested physical size (bytes) */
	enum drm_map_type type;	 /**< Type of memory to map */
	enum drm_map_flags flags;	 /**< Flags */
	void *handle;		 /**< User-space: "Handle" to pass to mmap() */
				 /**< Kernel-space: kernel-virtual address */
	int mtrr;		 /**< MTRR slot used */

	/* OSOL_drm Begin */
	ddi_acc_handle_t acc_handle;	 /**< The data access handle */
	ddi_umem_cookie_t umem_cookie;	 /**< For SAREA alloc and free */
	int callback;			/** need callback ops to handle GTT mmap */
	int gtt_mmap;			/** gtt mmap has been setuped */
	/* OSOL_drm End */
} drm_local_map_t;

/**
 * Mappings list
 */
struct drm_map_list {
	struct list_head head;		/**< list head */
	/* OSOL_drm: struct drm_hash_item hash; */
	struct drm_local_map *map;	/**< mapping */
	uint64_t user_token;
	struct drm_master *master;
	struct drm_mm_node *file_offset_node;	/**< fake offset */
};

struct drm_ctx_list {
	struct list_head head;		/**< list head */
	drm_context_t handle;		/**< context handle */
	struct drm_file *tag;		/**< associated fd private data */
};

struct drm_history_list {
	struct list_head head;
	char info[20];			/**< history info */
	uint32_t cur_seq;		/**< current system seqno */
	uint32_t last_seq;		/**< last seqno */
	void *ring_ptr;			/**< current ring ptr */
};

struct gem_map_list {
	struct list_head head;		/**< list head */
	devmap_cookie_t dhp;
	offset_t mapoffset;
	size_t maplen;
};

/*
 * This structure defines the drm_mm memory object, which will be used by the
 * DRM for its buffer objects.
 */
struct drm_gem_object {
	/* Reference count of this object */
	struct kref refcount;

	/* Handle count of this object. Each handle also holds a reference */
	atomic_t handle_count;

	/* Related drm device */
	struct drm_device *dev;

	/* Mapping info for this object */
	struct drm_map_list map_list;

	/*
	 * Size of the object, in bytes.  Immutable over the object's
	 * lifetime.
	 */
	size_t size;

	/*
	 * Global name for this object, starts at 1. 0 means unnamed.
	 * Access is covered by the object_name_lock in the related drm_device
	 */
	int name;

	/*
	 * Memory domains. These monitor which caches contain read/write data
	 * related to the object. When transitioning from one set of domains
	 * to another, the driver is called to ensure that caches are suitably
	 * flushed and invalidated
	 */
	uint32_t read_domains;
	uint32_t write_domain;

	/*
	 * While validating an exec operation, the
	 * new read/write domain values are computed here.
	 * They will be transferred to the above values
	 * at the point that any cache flushing occurs
	 */
	uint32_t pending_read_domains;
	uint32_t pending_write_domain;

	void *driver_private;

	struct drm_map_list maplist;
	ddi_dma_handle_t dma_hdl;
	ddi_acc_handle_t acc_hdl;
	caddr_t kaddr;
	size_t real_size;	/* real size of memory */
	pfn_t *pfnarray;
	caddr_t gtt_map_kaddr;

	ddi_dma_cookie_t cookie; /* placeholder maybe for later use, as filler replacement for struct gfxp_pmem_cookie  mempool_cookie; */

	struct list_head seg_list;

	struct list_head track_list;	/* for i915 mdb */
	struct list_head his_list;
};

typedef struct drm_lock_data {
	struct drm_hw_lock *hw_lock;	/**< Hardware lock */
	/** Private of lock holder's file (NULL=kernel) */
	struct drm_file *file_priv;
	kcondvar_t lock_cv;		/* lock queue - SOLARIS Specific */
	kmutex_t lock_mutex;		/* lock - SOLARIS Specific */
	unsigned long lock_time;	/* Time of last lock in clock ticks */
	uint32_t kernel_waiters;
	uint32_t user_waiters;
	int idle_has_lock;
} drm_lock_data_t;

/*
 * This structure, in drm_device_t, is always initialized while the device
 * is open.  dev->dma_lock protects the incrementing of dev->buf_use, which
 * when set marks that no further bufs may be allocated until device teardown
 * occurs (when the last open of the device has closed).  The high/low
 * watermarks of bufs are only touched by the X Server, and thus not
 * concurrently accessed, so no locking is needed.
 */

/**
 * DMA data.
 */
typedef struct drm_device_dma {

	struct drm_buf_entry bufs[DRM_MAX_ORDER + 1];	/**< buffers, grouped by their size order */
	int buf_count;			/**< total number of buffers */
	struct drm_buf **buflist;		/**< Vector of pointers into drm_device_dma::bufs */
	int seg_count;
	int page_count;			/**< number of pages */
	unsigned long *pagelist;	/**< page list */
	unsigned long byte_count;
	enum {
		_DRM_DMA_USE_AGP = 0x01,
		_DRM_DMA_USE_SG = 0x02,
		_DRM_DMA_USE_FB = 0x04,
		_DRM_DMA_USE_PCI_RO = 0x08
	} flags;

} drm_device_dma_t;

/**
 * AGP memory entry.  Stored as a doubly linked list.
 */
typedef struct drm_agp_mem {
	unsigned long handle;		/**< handle */
	unsigned long bound;		/**< address */
	int pages;
	struct list_head head;
} drm_agp_mem_t;

/**
 * AGP data.
 *
 * \sa drm_agp_init() and drm_device::agp.
 */
typedef struct drm_agp_head {
	agp_info_t agp_info;		/**< AGP device information */
	struct list_head memory;
	unsigned long mode;		/**< AGP mode */
	int enabled;			/**< whether the AGP bus as been enabled */
	int acquired;			/**< whether the AGP device has been acquired */
	unsigned long base;
	int mtrr;
	int cant_use_aperture;
	unsigned long page_mask;
	ldi_ident_t agpgart_li;
	ldi_handle_t agpgart_lh;
} drm_agp_head_t;

typedef struct drm_dma_handle {
	ddi_dma_handle_t dma_hdl;
	ddi_acc_handle_t acc_hdl;
	ddi_dma_cookie_t cookie;
	uint_t cookie_num;
	uintptr_t vaddr;   /* virtual addr */
	uintptr_t paddr;   /* physical addr */
	size_t real_sz;    /* real size of memory */
} drm_dma_handle_t;

typedef struct drm_sg_mem {
	unsigned long handle;
	void *virtual;
	int pages;
	dma_addr_t *busaddr;

	ddi_umem_cookie_t *umem_cookie;
	drm_dma_handle_t *dmah_sg;
	drm_dma_handle_t *dmah_gart; /* Handle to PCI memory */
} drm_sg_mem_t;

typedef TAILQ_HEAD(drm_vbl_sig_list, drm_vbl_sig) drm_vbl_sig_list_t;
typedef struct drm_vbl_sig {
	TAILQ_ENTRY(drm_vbl_sig) link;
	unsigned int	sequence;
	int		signo;
	int		pid;
} drm_vbl_sig_t;


/* used for clone device */
typedef TAILQ_HEAD(drm_cminor_list, drm_cminor) drm_cminor_list_t;
typedef struct drm_cminor {
	TAILQ_ENTRY(drm_cminor) link;
	drm_file_t		*fpriv;
	int			minor;
} drm_cminor_t;

/* location of GART table */
#define	DRM_ATI_GART_MAIN	1
#define	DRM_ATI_GART_FB		2

typedef struct ati_pcigart_info {
	int gart_table_location;
	int is_pcie;
	void *addr;
	dma_addr_t bus_addr;
	drm_local_map_t mapping;
} drm_ati_pcigart_info;

/* Size of ringbuffer for vblank timestamps. Just double-buffer
 * in initial implementation.
 */
#define DRM_VBLANKTIME_RBSIZE 2

/* Flags and return codes for get_vblank_timestamp() driver function. */
#define DRM_CALLED_FROM_VBLIRQ 1
#define DRM_VBLANKTIME_SCANOUTPOS_METHOD (1 << 0)
#define DRM_VBLANKTIME_INVBL             (1 << 1)

/* get_scanout_position() return flags */
#define DRM_SCANOUTPOS_VALID        (1 << 0)
#define DRM_SCANOUTPOS_INVBL        (1 << 1)
#define DRM_SCANOUTPOS_ACCURATE     (1 << 2)

/* DRM device structure */
struct drm_device;

struct drm_bus {
	int bus_type;
	int (*get_irq)(struct drm_device *dev);
	const char *(*get_name)(struct drm_device *dev);
	int (*set_busid)(struct drm_device *dev, struct drm_master *master);
	int (*set_unique)(struct drm_device *dev, struct drm_master *master,
			  struct drm_unique *unique);
	int (*irq_by_busid)(struct drm_device *dev, struct drm_irq_busid *p);
	/* hooks that are for PCI */
	int (*agp_init)(struct drm_device *dev);

};

struct drm_driver {
	int (*load)(struct drm_device *, unsigned long);
	int (*firstopen)(struct drm_device *);
	int (*open)(struct drm_device *, drm_file_t *);
	void (*preclose)(struct drm_device *, drm_file_t *);
	void (*postclose)(struct drm_device *, drm_file_t *);
	void (*lastclose)(struct drm_device *);
	int (*unload)(struct drm_device *);
	void (*reclaim_buffers_locked)(struct drm_device *, drm_file_t *);
	int (*presetup)(struct drm_device *);
	int (*postsetup)(struct drm_device *);
	int (*open_helper)(struct drm_device *, drm_file_t *);
	void (*free_filp_priv)(struct drm_device *, drm_file_t *);
	void (*release)(struct drm_device *, void *);
	int (*dma_ioctl)(DRM_IOCTL_ARGS);
	int (*dma_quiescent)(struct drm_device *);
	int (*dma_flush_block_and_flush)(struct drm_device *,
			int, drm_lock_flags_t);
	int (*dma_flush_unblock)(struct drm_device *, int,
					drm_lock_flags_t);
	int (*context_dtor)(struct drm_device *, int);
	int (*device_is_agp) (struct drm_device *);

	/**
	 * Called by vblank timestamping code.
	 *
	 * Return the current display scanout position from a crtc.
	 *
	 * \param dev  DRM device.
	 * \param crtc Id of the crtc to query.
	 * \param *vpos Target location for current vertical scanout position.
	 * \param *hpos Target location for current horizontal scanout position.
	 *
	 * Returns vpos as a positive number while in active scanout area.
	 * Returns vpos as a negative number inside vblank, counting the number
	 * of scanlines to go until end of vblank, e.g., -1 means "one scanline
	 * until start of active scanout / end of vblank."
	 *
	 * \return Flags, or'ed together as follows:
	 *
	 * DRM_SCANOUTPOS_VALID = Query successfull.
	 * DRM_SCANOUTPOS_INVBL = Inside vblank.
	 * DRM_SCANOUTPOS_ACCURATE = Returned position is accurate. A lack of
	 * this flag means that returned position may be offset by a constant
	 * but unknown small number of scanlines wrt. real scanout position.
	 *
	 */
	int (*get_scanout_position) (struct drm_device *dev, int crtc,
				     int *vpos, int *hpos);

	/**
	 * Called by \c drm_get_last_vbltimestamp. Should return a precise
	 * timestamp when the most recent VBLANK interval ended or will end.
	 *
	 * Specifically, the timestamp in @vblank_time should correspond as
	 * closely as possible to the time when the first video scanline of
	 * the video frame after the end of VBLANK will start scanning out,
	 * the time immmediately after end of the VBLANK interval. If the
	 * @crtc is currently inside VBLANK, this will be a time in the future.
	 * If the @crtc is currently scanning out a frame, this will be the
	 * past start time of the current scanout. This is meant to adhere
	 * to the OpenML OML_sync_control extension specification.
	 *
	 * \param dev dev DRM device handle.
	 * \param crtc crtc for which timestamp should be returned.
	 * \param *max_error Maximum allowable timestamp error in nanoseconds.
	 *                   Implementation should strive to provide timestamp
	 *                   with an error of at most *max_error nanoseconds.
	 *                   Returns true upper bound on error for timestamp.
	 * \param *vblank_time Target location for returned vblank timestamp.
	 * \param flags 0 = Defaults, no special treatment needed.
	 * \param       DRM_CALLED_FROM_VBLIRQ = Function is called from vblank
	 *	        irq handler. Some drivers need to apply some workarounds
	 *              for gpu-specific vblank irq quirks if flag is set.
	 *
	 * \returns
	 * Zero if timestamping isn't supported in current display mode or a
	 * negative number on failure. A positive status code on success,
	 * which describes how the vblank_time timestamp was computed.
	 */
	int (*get_vblank_timestamp) (struct drm_device *dev, int crtc,
				     int *max_error,
				     struct timeval *vblank_time,
				     unsigned flags);

	void (*irq_preinstall)(struct drm_device *);
	int (*irq_postinstall)(struct drm_device *);
	void (*irq_uninstall)(struct drm_device *dev);

	uint_t (*irq_handler)(DRM_IRQ_ARGS);
	int (*vblank_wait)(struct drm_device *, unsigned int *);
	int (*vblank_wait2)(struct drm_device *, unsigned int *);
	/* added for intel minimized vblank */
	u32 (*get_vblank_counter)(struct drm_device *dev, int crtc);
	int (*enable_vblank)(struct drm_device *dev, int crtc);
	void (*disable_vblank)(struct drm_device *dev, int crtc);

	/* Master routines */
	int (*master_create)(struct drm_device *dev, struct drm_master *master);
	void (*master_destroy)(struct drm_device *dev, struct drm_master *master);
	/**
	 * master_set is called whenever the minor master is set.
	 * master_drop is called whenever the minor master is dropped.
	 */

	int (*master_set)(struct drm_device *dev, struct drm_file *file_priv,
			  bool from_open);
	void (*master_drop)(struct drm_device *dev, struct drm_file *file_priv,
			    bool from_release);

	void (*entervt)(struct drm_device *dev);
	void (*leavevt)(struct drm_device *dev);
	void (*agp_support_detect)(struct drm_device *dev, unsigned long flags);

	/*
	 * Driver-specific constructor for drm_gem_objects, to set up
	 * obj->driver_private.
	 *
	 * Returns 0 on success.
	 */
	int (*gem_init_object) (struct drm_gem_object *obj);
	void (*gem_free_object) (struct drm_gem_object *obj);

	int (*gem_open_object) (struct drm_gem_object *, struct drm_file *);
	void (*gem_close_object) (struct drm_gem_object *, struct drm_file *);
	void (*gem_fault) (struct drm_gem_object *obj);

	/* vga arb irq handler */
	void (*vgaarb_irq)(struct drm_device *dev, bool state);

	/* dumb alloc support */
	int (*dumb_create)(struct drm_file *file_priv,
			   struct drm_device *dev,
			   struct drm_mode_create_dumb *args);
	int (*dumb_map_offset)(struct drm_file *file_priv,
			       struct drm_device *dev, uint32_t handle,
			       uint64_t *offset);
	int (*dumb_destroy)(struct drm_file *file_priv,
			    struct drm_device *dev,
			    uint32_t handle);

	int major;
	int minor;
	int patchlevel;
	char *name;
	char *desc;
	char *date;

	u32 driver_features;
	drm_ioctl_desc_t *ioctls;
	int num_ioctls;

	int	buf_priv_size;

	unsigned use_agp :1;
	unsigned require_agp :1;
	unsigned use_sg :1;
	unsigned use_dma :1;
	unsigned use_pci_dma :1;
	unsigned use_dma_queue :1;
	unsigned use_irq :1;
	unsigned use_vbl_irq :1;
	unsigned use_vbl_irq2 :1;
	unsigned use_mtrr :1;
	unsigned use_gem;
	unsigned use_kms;

	struct drm_pci_id_list *id_table;
};
#include "drm_crtc.h"
struct drm_master {

	struct kref refcount; /* refcount for this master */

	struct list_head head; /**< each minor contains a list of masters */
	struct drm_minor *minor; /**< link back to minor we are a master for */

	char *unique;			/**< Unique identifier: e.g., busid */
	int unique_len;			/**< Length of unique field */
	int unique_size;		/**< amount allocated */

	int blocked;			/**< Blocked due to VC switch? */

	/** \name Authentication */
	/*@{ */
	drm_magic_head_t magiclist[DRM_HASH_SIZE];
	/*@} */

	struct drm_lock_data lock;	/**< Information on hardware lock */

	void *driver_priv; /**< Private structure for driver to use */
};

struct drm_minor {
	int index;			/**< Minor device number */
	int type;                       /**< Control or render */
	dev_t device;
	struct drm_device *dev;
	struct drm_master *master; /* currently active master for this node */
	struct list_head master_list;
	struct drm_mode_group mode_group;

	char name[32];
	struct idr clone_idr;
	void *private;
};

/* mode specified on the command line */
struct drm_cmdline_mode {
	bool specified;
	bool refresh_specified;
	bool bpp_specified;
	int xres, yres;
	int bpp;
	int refresh;
	bool rb;
	bool interlace;
	bool cvt;
	bool margins;
	enum drm_connector_force force;
};

struct drm_pending_vblank_event {
	struct drm_pending_event base;
	int pipe;
	struct drm_event_vblank event;
};

struct drm_file {
	TAILQ_ENTRY(drm_file) link;

	int authenticated;
	pid_t pid;
	uid_t uid;
	drm_magic_t magic;
	unsigned long ioctl_count;
	struct list_head lhead;
	struct drm_minor *minor;
	unsigned long lock_count;

	/** Mapping of mm object handles to object pointers. */
	struct idr_list object_idr;
	/** Lock for synchronization of access to object_idr. */
	spinlock_t table_lock;

	void *driver_priv;

	int is_master; /* this file private is a master for a minor */
	struct drm_master *master; /* master this node is currently associated with
				      N.B. not always minor->master */

	/**
	 * fbs - List of framebuffers associated with this file.
	 *
	 * Protected by fbs_lock. Note that the fbs list holds a reference on
	 * the fb object to prevent it from untimely disappearing.
	 */
	struct list_head fbs;
	struct mutex fbs_lock;

	wait_queue_head_t event_wait;
	struct list_head event_list;
	int event_space;
	struct pollhead drm_pollhead;
};

/*
 * hardware-specific code needs to initialize mutexes which
 * can be used in interrupt context, so they need to know
 * the interrupt priority. Interrupt cookie in drm_device
 * structure is the intr_block field.
 */
#define	DRM_INTR_PRI(dev) \
	DDI_INTR_PRI((dev)->pdev->intr_block)

struct drm_device {
	int if_version;			/**< Highest interface version set */

	/** \name Locks */
	/*@{ */
	spinlock_t count_lock;		/**< For inuse, drm_device::open_count, drm_device::buf_use */
	kmutex_t struct_mutex;		/* < For others	*/
	/*@} */

	/** \name Usage Counters */
	/*@{ */
	int open_count;			/**< Outstanding files open */
	atomic_t ioctl_count;		/**< Outstanding IOCTLs pending */
	int buf_use;			/**< Buffers in use -- cannot alloc */
	atomic_t buf_alloc;		/**< Buffer allocation in progress */
	/*@} */

	/** \name Performance counters */
	/*@{ */
	unsigned long counters;
	enum drm_stat_type types[15];
	atomic_t counts[15];
	/*@} */

	struct list_head filelist;

	/** \name Memory management */
	/*@{ */
	struct list_head maplist;	/**< Linked list of regions */
	/*@} */

	/** \name Context handle management */
	/*@{ */
	struct list_head ctxlist;	/**< Linked list of context handles */
	int ctx_count;			/**< Number of context handles */
	struct mutex ctxlist_mutex;	/**< For ctxlist */

	struct idr ctx_idr;

	/*@} */

	/** \name DMA queues (contexts) */
	/*@{ */
	struct drm_device_dma *dma;		/**< Optional pointer for DMA support */
	/*@} */

	/** \name Context support */
	/*@{ */
	int irq_enabled;		/* True if the irq handler is enabled */
	atomic_t context_flag;		/* Context swapping flag */
	wait_queue_head_t context_wait;	/**< Processes waiting on ctx switch */
	int last_context;		/* Last current context */
	unsigned long last_switch;	/**< jiffies at last context switch */
	/*@} */

	struct workqueue_struct *drm_wq;
	struct work_struct work;
	/** \name VBLANK IRQ support */
	/*@{ */

	/*
	 * At load time, disabling the vblank interrupt won't be allowed since
	 * old clients may not call the modeset ioctl and therefore misbehave.
	 * Once the modeset ioctl *has* been called though, we can safely
	 * disable them when unused.
	 */
	int vblank_disable_allowed;

	wait_queue_head_t *vbl_queue;   /**< VBLANK wait queue */
	atomic_t *_vblank_count;        /**< number of VBLANK interrupts (driver must alloc the right number of counters) */
	struct timeval *_vblank_time;   /**< timestamp of current vblank_count (drivers must alloc right number of fields) */
	spinlock_t vblank_time_lock;    /**< Protects vblank count and time updates during vblank enable/disable */
	spinlock_t vbl_lock;
	atomic_t *vblank_refcount;      /* number of users of vblank interruptsper crtc */
	u32 *last_vblank;               /* protected by dev->vbl_lock, used */
					/* for wraparound handling */
	int *vblank_enabled;            /* so we don't call enable more than
					   once per disable */
	int *vblank_inmodeset;          /* Display driver is setting mode */
	u32 *last_vblank_wait;		/* Last vblank seqno waited per CRTC */
	struct timer_list vblank_disable_timer;

	u32 max_vblank_count;           /**< size of vblank counter register */

	/**
	  * List of events
	  */
	struct list_head vblank_event_list;
	spinlock_t event_lock;

	/*@} */

	struct drm_agp_head *agp;	/**< AGP data */
	ulong_t	agp_aperbase;

	struct device *dev;             /**< Device structure */
	struct pci_dev *pdev;		/**< PCI device structure */
	int pci_vendor;			/**< PCI vendor id */
	int pci_device;			/**< PCI device id */

	struct drm_sg_mem *sg;	/**< Scatter gather memory */
	unsigned int num_crtcs;                  /**< Number of CRTCs on this device */
	void *dev_private;		/**< device private data */
	void *mm_private;
	struct drm_driver *driver;
	struct drm_local_map *agp_buffer_map;
	unsigned int agp_buffer_token;
	struct drm_minor *control;		/**< Control node for card */
	struct drm_minor *primary;		/**< render type primary screen head */

	struct drm_mode_config mode_config;	/**< Current mode config */
	struct work_struct	output_poll_work;
	struct timer_list	output_poll_timer;

	/* \name GEM information */
	/* @{ */
	kmutex_t object_name_lock;
	struct idr_list object_name_idr;
	/* @} */
	int switch_power_state;

	/* OSOL Begin*/
	dev_info_t *devinfo;
	struct drm_minor *vgatext;
	struct drm_minor *agpmaster;

	struct idr map_idr;

	/* Locks */
	kmutex_t dma_lock;		/* protects dev->dma */
	kmutex_t irq_lock;		/* protects irq condition checks */

	kmutex_t page_fault_lock;

	kstat_t *asoft_ksp;		/* kstat support */

	struct list_head gem_objects_list;
	spinlock_t track_lock;

	uint32_t *old_gtt;
	size_t	old_gtt_size;
	uint32_t *gtt_dump;

	/*
	 * FMA capabilities
	 */
	int	drm_fm_cap;
	/* OSOL End */
};

#define DRM_SWITCH_POWER_ON 0
#define DRM_SWITCH_POWER_OFF 1
#define DRM_SWITCH_POWER_CHANGING 2

static __inline__ int drm_core_check_feature(struct drm_device *dev,
					     int feature)
{
	return ((dev->driver->driver_features & feature) ? 1 : 0);
}
#if __OS_HAS_AGP
static inline int drm_core_has_AGP(struct drm_device *dev)
{
	return drm_core_check_feature(dev, DRIVER_USE_AGP);
}
#else
#define drm_core_has_AGP(dev) (0)
#endif

extern struct idr drm_minors_idr;
extern struct cb_ops drm_cb_ops;

void	*drm_alloc(size_t, int);
void	*drm_calloc(size_t, size_t, int);
void	*drm_realloc(void *, size_t, size_t, int);
void	drm_free(void *, size_t, int);
int 	drm_ioremap(drm_device_t *, drm_local_map_t *);
void	drm_ioremapfree(drm_local_map_t *);
void *drm_sun_ioremap(uint64_t paddr, size_t size, uint32_t mode);
void drm_sun_iounmap(void *addr);
void drm_core_ioremap(struct drm_local_map *, struct drm_device *);
void drm_core_ioremapfree(struct drm_local_map *, struct drm_device *);

void drm_pci_free(drm_dma_handle_t *);
void *drm_pci_alloc(drm_device_t *, size_t, size_t, dma_addr_t, int);

int	drm_ctxbitmap_init(drm_device_t *);
void	drm_ctxbitmap_cleanup(drm_device_t *);
void	drm_ctxbitmap_free(drm_device_t *, int);

/* Locking IOCTL support (drm_lock.c) */
int drm_lock_take(struct drm_lock_data *, unsigned int);
int drm_lock_free(struct drm_lock_data *, unsigned int);
int drm_i_have_hw_lock(struct drm_device *dev, struct drm_file *file_priv);

/* Buffer management support (drm_bufs.c) */
extern int drm_map_handle(struct drm_device *dev, struct drm_map_list *list);
unsigned long drm_get_resource_start(drm_device_t *, unsigned int);
unsigned long drm_get_resource_len(drm_device_t *, unsigned int);
int	drm_initmap(drm_device_t *, unsigned long, unsigned long,
    unsigned int, int, int);
extern int drm_rmmap(struct drm_device *, struct drm_local_map *);
extern int drm_addmap(struct drm_device *, unsigned long, unsigned long,
    enum drm_map_type, enum drm_map_flags, struct drm_local_map **);
int	drm_order(unsigned long);
int drm_rmmap_locked(struct drm_device *dev, struct drm_local_map *map);

/* DMA support (drm_dma.c) */
int	drm_dma_setup(drm_device_t *);
void	drm_dma_takedown(drm_device_t *);
void	drm_free_buffer(drm_device_t *, drm_buf_t *);
void	drm_core_reclaim_buffers(drm_device_t *, drm_file_t *);
#define	drm_reclaim_buffers  drm_core_reclaim_buffers

/* IRQ support (drm_irq.c) */
int	drm_irq_install(drm_device_t *);
int	drm_irq_uninstall(drm_device_t *);
uint_t	drm_irq_handler(DRM_IRQ_ARGS);
void	drm_driver_irq_preinstall(drm_device_t *);
void	drm_driver_irq_postinstall(drm_device_t *);
void	drm_driver_irq_uninstall(drm_device_t *);
int	drm_vblank_wait(drm_device_t *, unsigned int *);
u32	drm_vblank_count(struct drm_device *dev, int crtc);
u32	drm_vblank_count_and_time(struct drm_device *dev, int crtc,
				     struct timeval *vblanktime);
extern void drm_send_vblank_event(struct drm_device *dev, int crtc,
				     struct drm_pending_vblank_event *e);
bool	drm_handle_vblank(struct drm_device *dev, int crtc);
int	drm_vblank_get(struct drm_device *dev, int crtc);
void	drm_vblank_put(struct drm_device *dev, int crtc);
void   drm_vblank_off(struct drm_device *dev, int crtc);
extern void drm_vblank_off(struct drm_device *dev, int crtc);
int	drm_vblank_init(struct drm_device *dev, int num_crtcs);
void	drm_vblank_cleanup(struct drm_device *dev);
u32	drm_get_last_vbltimestamp(struct drm_device *dev, int crtc,
				     struct timeval *tvblank, unsigned flags);
int	drm_calc_vbltimestamp_from_scanoutpos(struct drm_device *dev,
						 int crtc, int *max_error,
						 struct timeval *vblank_time,
						 unsigned flags,
						 struct drm_crtc *refcrtc);
void	drm_calc_timestamping_constants(struct drm_crtc *crtc);

extern struct drm_display_mode *
drm_mode_create_from_cmdline_mode(struct drm_device *dev,
				  struct drm_cmdline_mode *cmd);

/* Modesetting support */
int    drm_modeset_ctl(DRM_IOCTL_ARGS);
void drm_vblank_pre_modeset(struct drm_device *dev, int crtc);
void drm_vblank_post_modeset(struct drm_device *dev, int crtc);
int pci_enable_msi(struct pci_dev *pdev);
void pci_disable_msi(struct pci_dev *pdev);
/* AGP/GART support (drm_agpsupport.h) */
extern struct drm_agp_head *drm_agp_init(struct drm_device *dev);
extern int drm_agp_acquire(struct drm_device *dev);
extern int drm_agp_acquire_ioctl(DRM_IOCTL_ARGS);
extern int drm_agp_release(struct drm_device *dev);
extern int drm_agp_release_ioctl(DRM_IOCTL_ARGS);
extern int drm_agp_enable(struct drm_device *dev, struct drm_agp_mode mode);
extern int drm_agp_enable_ioctl(DRM_IOCTL_ARGS);
extern int drm_agp_info(struct drm_device *dev, struct drm_agp_info *info);
extern int drm_agp_info_ioctl(DRM_IOCTL_ARGS);
extern int drm_agp_alloc(struct drm_device *dev, struct drm_agp_buffer *request);
extern int drm_agp_alloc_ioctl(DRM_IOCTL_ARGS);
extern int drm_agp_free(struct drm_device *dev, struct drm_agp_buffer *request);
extern int drm_agp_free_ioctl(DRM_IOCTL_ARGS);
extern int drm_agp_unbind(struct drm_device *dev, struct drm_agp_binding *request);
extern int drm_agp_unbind_ioctl(DRM_IOCTL_ARGS);
extern int drm_agp_bind(struct drm_device *dev, struct drm_agp_binding *request);
extern int drm_agp_bind_ioctl(DRM_IOCTL_ARGS);
extern void *drm_agp_allocate_memory(size_t pages, uint32_t type, struct drm_device *dev);
extern int drm_agp_free_memory(agp_allocate_t *handle, drm_device_t *dev);
extern int drm_agp_bind_memory(unsigned int, uint32_t, drm_device_t *dev);
extern int drm_agp_unbind_memory(unsigned long, drm_device_t *dev);
extern void drm_agp_chipset_flush(struct drm_device *dev);

extern void drm_agp_cleanup(drm_device_t *);
extern int drm_agp_bind_pages(struct drm_device *dev, pfn_t *pages,
		unsigned long num_pages, uint32_t gtt_offset, unsigned int agp_type);
extern int drm_agp_unbind_pages(struct drm_device *dev, pfn_t *pages,
		unsigned long num_pages, uint32_t gtt_offset, pfn_t scratch, uint32_t type);
extern int drm_agp_rw_gtt(struct drm_device *dev, unsigned long num_pages,
		uint32_t gtt_offset, void *gttp, uint32_t type);

/* kstat support (drm_kstats.c) */
int	drm_init_kstats(drm_device_t *);
void	drm_fini_kstats(drm_device_t *);

/* Scatter Gather Support (drm_scatter.c) */
extern void drm_sg_cleanup(drm_sg_mem_t *);

/* ATI PCIGART support (ati_pcigart.c) */
int	drm_ati_pcigart_init(drm_device_t *, drm_ati_pcigart_info *);
int	drm_ati_pcigart_cleanup(drm_device_t *, drm_ati_pcigart_info *);

				/* Locking IOCTL support (drm_lock.h) */
extern int drm_lock(DRM_IOCTL_ARGS);
extern int drm_unlock(DRM_IOCTL_ARGS);
extern int drm_lock_take(struct drm_lock_data *lock_data, unsigned int context);
extern int drm_lock_free(struct drm_lock_data *lock_data, unsigned int context);
extern void drm_idlelock_take(struct drm_lock_data *lock_data);
extern void drm_idlelock_release(struct drm_lock_data *lock_data);

int	drm_setversion(DRM_IOCTL_ARGS);
struct drm_local_map *drm_getsarea(struct drm_device *dev);
/* Cache management (drm_cache.c) */
void drm_clflush_pages(caddr_t *pages, unsigned long num_pages);

/* Misc. IOCTL support (drm_ioctl.c) */
int	drm_irq_by_busid(DRM_IOCTL_ARGS);
int	drm_getunique(DRM_IOCTL_ARGS);
int	drm_setunique(DRM_IOCTL_ARGS);
int	drm_getmap(DRM_IOCTL_ARGS);
int	drm_getclient(DRM_IOCTL_ARGS);
int	drm_getstats(DRM_IOCTL_ARGS);
int	drm_getcap(DRM_IOCTL_ARGS);
int	drm_noop(DRM_IOCTL_ARGS);

/* Context IOCTL support (drm_context.c) */
int	drm_resctx(DRM_IOCTL_ARGS);
int	drm_addctx(DRM_IOCTL_ARGS);
int	drm_modctx(DRM_IOCTL_ARGS);
int	drm_getctx(DRM_IOCTL_ARGS);
int	drm_switchctx(DRM_IOCTL_ARGS);
int	drm_newctx(DRM_IOCTL_ARGS);
int	drm_rmctx(DRM_IOCTL_ARGS);
int	drm_setsareactx(DRM_IOCTL_ARGS);
int	drm_getsareactx(DRM_IOCTL_ARGS);

/* Drawable IOCTL support (drm_drawable.c) */
int	drm_adddraw(DRM_IOCTL_ARGS);
int	drm_rmdraw(DRM_IOCTL_ARGS);
int	drm_update_drawable_info(DRM_IOCTL_ARGS);
struct drm_drawable_info *drm_get_drawable_info(struct drm_device *dev,
						  drm_drawable_t id);
void drm_drawable_free_all(struct drm_device *dev);


				/* Authentication IOCTL support (drm_auth.h) */
int	drm_getmagic(DRM_IOCTL_ARGS);
int	drm_authmagic(DRM_IOCTL_ARGS);
int	drm_remove_magic(struct drm_master *master, drm_magic_t magic);

/* Buffer management support (drm_bufs.c) */
int	drm_addmap_ioctl(DRM_IOCTL_ARGS);
int	drm_rmmap_ioctl(DRM_IOCTL_ARGS);
int	drm_addbufs(DRM_IOCTL_ARGS);
int	drm_infobufs(DRM_IOCTL_ARGS);
int	drm_markbufs(DRM_IOCTL_ARGS);
int	drm_freebufs(DRM_IOCTL_ARGS);
int	drm_mapbufs(DRM_IOCTL_ARGS);

/* IRQ support (drm_irq.c) */
int	drm_control(DRM_IOCTL_ARGS);
int	drm_wait_vblank(DRM_IOCTL_ARGS);

/* Scatter Gather Support (drm_scatter.c) */
int	drm_sg_alloc_ioctl(DRM_IOCTL_ARGS);
int	drm_sg_free(DRM_IOCTL_ARGS);

extern int drm_debug_flag;
extern int mdb_track_enable;

extern struct list_head drm_iomem_list;

#define MDB_TRACK_ENABLE	mdb_track_enable

#define TRACE_GEM_OBJ_HISTORY(obj, str)					\
do {									\
	if (MDB_TRACK_ENABLE) {						\
		int seq_t = 0;						\
		if (obj->ring)						\
			seq_t = obj->ring->get_seqno(obj->ring, true);	\
		drm_gem_object_track(&obj->base, str,			\
			seq_t, 0,					\
			(void *)obj->ring);				\
	}								\
} while (*"\0")

/* We add function to support DRM_DEBUG,DRM_ERROR,DRM_INFO */
/* PRINTFLIKE4 */
extern void drm_debug_print(int cmn_err, const char* func, int line, const char *fmt, ...);
/* PRINTFLIKE1 */
extern void drm_debug(const char *fmt, ...);
/* PRINTFLIKE1 */
extern void drm_error(const char *fmt, ...);
/* PRINTFLIKE1 */
extern void drm_info(const char *fmt, ...);

// For DEBUG output, enable here
/*
#ifndef DEBUG
#define DEBUG
#endif
*/

// Either use the old way, a single combined gfxp_map_kernel_space()
// or new 2 distinct calls of gfxp_alloc_kernel_space() and gfxp_load_kernel_space()
// Meanwhile it turned out that using the old combined gfxp_map_kernel_space()
// and gfxp_unmap_kernel_space() in the modern DRM gate is unstable, especially on Sandy
/*
#ifndef OLDSYLE_MMAP
#define OLDSYLE_MMAP
#endif
*/

// local case for equal testing conditions on Illumos and Sol11.0 versus modern console 11.1/11.2/11.3/12.x
//
#ifndef LOCALGFXPFUNCS
#define LOCALGFXPFUNCS
#endif
//


#ifdef DEBUG
#define	DRM_DEBUG(...)                                          \
	do {                                                    \
		if (drm_debug_flag & 0x08)                        \
			drm_debug_print(                        \
			    CE_NOTE, __func__, __LINE__, ##__VA_ARGS__);  \
	} while (__lintzero)
#define DRM_DEBUG_KMS(...)					\
	do {                                                    \
		if (drm_debug_flag & 0x04)                        \
			drm_debug_print(                        \
			    CE_NOTE, __func__, __LINE__, ##__VA_ARGS__);  \
	} while (__lintzero)
#define DRM_DEBUG_DRIVER(...)					\
	do {                                                    \
		if (drm_debug_flag & 0x02)                        \
			drm_debug_print(                        \
			    CE_NOTE, __func__, __LINE__, ##__VA_ARGS__);  \
	} while (__lintzero)
#define	DRM_INFO(...)                                           \
	do {                                                    \
		if (drm_debug_flag & 0x01)                        \
			drm_debug_print(                        \
			    CE_NOTE, __func__, __LINE__, ##__VA_ARGS__);  \
	} while (__lintzero)
#else
#define	DRM_DEBUG(...)		do { } while (__lintzero)
#define DRM_DEBUG_KMS(...)	do { } while (__lintzero)
#define DRM_DEBUG_DRIVER(...)	do { } while (__lintzero)
#define	DRM_INFO(...)		do { } while (__lintzero)
#endif

#define	DRM_ERROR(...) \
	drm_debug_print(CE_WARN, __func__, __LINE__, ##__VA_ARGS__)

#define DRM_LOG_KMS       DRM_INFO

extern int drm_lastclose(struct drm_device *dev);

extern int drm_open(struct drm_minor *, int, int, cred_t *);
extern int drm_release(struct drm_file *);
extern ssize_t drm_read(struct drm_file *, struct uio *);
extern short drm_poll(struct drm_file *, short);
extern int drm_init(struct drm_device *, struct drm_driver *);
extern void drm_exit(struct drm_device *);
extern void drm_fm_init(struct drm_device *dev);
extern void drm_fm_fini(struct drm_device *dev);
extern void drm_fm_ereport(struct drm_device *dev, char *detail);
extern int drm_check_dma_handle(struct drm_device *dev, ddi_dma_handle_t handle);
extern int drm_check_acc_handle(struct drm_device *dev, ddi_acc_handle_t handle);
extern int drm_ioctl(dev_t dev_id, struct drm_file *file_priv,
	int cmd, intptr_t arg, int mode, cred_t *credp);

extern int drm_put_minor(struct drm_minor **minor_p);

extern int drm_setmaster_ioctl(DRM_IOCTL_ARGS);
extern int drm_dropmaster_ioctl(DRM_IOCTL_ARGS);
extern struct drm_master *drm_master_create(struct drm_minor *minor);
extern struct drm_master *drm_master_get(struct drm_master *master);
extern void drm_master_put(struct drm_master **master);
extern int drm_get_dev(struct drm_device *dev, struct pci_dev *pdev,
	struct drm_driver *driver, unsigned long driver_data);
extern void drm_put_dev(struct drm_device *dev);

void drm_master_release(struct drm_device *dev, struct drm_file *fpriv);

extern unsigned int drm_vblank_offdelay;
extern unsigned int drm_timestamp_precision;

/* sysfs support (drm_sysfs.c) */
extern int drm_sysfs_device_add(struct drm_minor *minor);
extern void drm_sysfs_device_remove(struct drm_minor *minor);

/* Graphics Execution Manager library functions (drm_gem.c) */
int drm_gem_init(struct drm_device *dev);
void drm_gem_destroy(struct drm_device *dev);
void drm_gem_object_release(struct drm_gem_object *obj);
void drm_gem_object_free(struct kref *kref);
void drm_gem_object_free_unlocked(struct kref *kref);
struct drm_gem_object *drm_gem_object_alloc(struct drm_device *dev,
					    size_t size);
int drm_gem_object_init(struct drm_device *dev,
			struct drm_gem_object *obj, size_t size, int gen);
int drm_gem_private_object_init(struct drm_device *dev,
			struct drm_gem_object *obj, size_t size);
void drm_gem_object_handle_free(struct drm_gem_object *obj);

extern void
drm_gem_object_reference(struct drm_gem_object *obj);

extern void
drm_gem_object_unreference(struct drm_gem_object *obj);

extern void
drm_gem_object_unreference_unlocked(struct drm_gem_object *obj);

int drm_gem_handle_create(struct drm_file *file_priv,
			  struct drm_gem_object *obj,
			  u32 *handlep);
int drm_gem_handle_delete(struct drm_file *filp, u32 handle);

extern void
drm_gem_object_handle_reference(struct drm_gem_object *obj);

extern void
drm_gem_object_handle_unreference(struct drm_gem_object *obj);

extern void
drm_gem_object_handle_unreference_unlocked(struct drm_gem_object *obj);

struct drm_gem_object *drm_gem_object_lookup(struct drm_device *dev,
					     struct drm_file *filp,
					     u32 handle);
int drm_gem_close_ioctl(DRM_IOCTL_ARGS);
int drm_gem_flink_ioctl(DRM_IOCTL_ARGS);
int drm_gem_open_ioctl(DRM_IOCTL_ARGS);
void drm_gem_open(struct drm_device *dev, struct drm_file *file_private);
void drm_gem_release(struct drm_device *dev, struct drm_file *file_private);
int drm_gem_create_mmap_offset(struct drm_gem_object *obj);
void drm_gem_mmap(struct drm_gem_object *obj, pfn_t pfn);
void drm_gem_release_mmap(struct drm_gem_object *obj);
void drm_gem_free_mmap_offset(struct drm_gem_object *obj);

extern struct drm_local_map *drm_core_findmap(struct drm_device *dev,
							 unsigned int token);

#ifdef NEVER
static __inline__ int drm_device_is_pcie(struct drm_device *dev)
{
	return 0;
}
#endif

void drm_gem_object_track(struct drm_gem_object *obj, const char *name,
			uint32_t cur_seq, uint32_t last_seq, void* ptr);

#endif	/* _DRMP_H */
