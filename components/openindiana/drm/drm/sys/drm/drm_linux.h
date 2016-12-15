/*
 * Copyright (c) 2006, 2015, Oracle and/or its affiliates. All rights reserved.
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/*
 * Copyright (c) 2012, 2012 Intel Corporation.  All rights reserved.
 */

#ifndef __DRM_LINUX_H__
#define __DRM_LINUX_H__

#include <sys/types.h>
#include <sys/byteorder.h>
#include "drm_atomic.h"

#define DRM_MEM_CACHED	0
#define DRM_MEM_UNCACHED 	1
#define DRM_MEM_WC 		2

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

#define clamp_int64_t(val)			\
	val = min((int64_t)INT_MAX, val);	\
	val = max((int64_t)INT_MIN, val);

#define ioremap_wc(base,size) drm_sun_ioremap((base), (size), DRM_MEM_WC)
#define ioremap(base, size)   drm_sun_ioremap((base), (size), DRM_MEM_UNCACHED)
#define iounmap(addr)         drm_sun_iounmap((addr))

#define spinlock_t                       kmutex_t
#define	spin_lock_init(l)                mutex_init((l), NULL, MUTEX_DRIVER, NULL);
#define	spin_lock(l)	                 mutex_enter(l)
#define	spin_unlock(u)                   mutex_exit(u)
#define	spin_lock_irq(l)		mutex_enter(l)
#define	spin_unlock_irq(u)		mutex_exit(u)
#ifdef __lint
/*
 * The following is to keep lint happy when it encouters the use of 'flag'.
 * On Linux, this allows a local variable to be used to retain context,
 * but is unused on Solaris.  Rather than trying to place LINTED
 * directives in the source, we actually consue the flag for lint here.
 */
#define	spin_lock_irqsave(l, flag)       flag = 0; mutex_enter(l)
#define	spin_unlock_irqrestore(u, flag)  flag &= flag; mutex_exit(u)
#else
#define	spin_lock_irqsave(l, flag)       mutex_enter(l)
#define	spin_unlock_irqrestore(u, flag)  mutex_exit(u)
#endif

#define mutex_lock(l)			mutex_enter(l)
#define mutex_unlock(u)			mutex_exit(u)
#define mutex_is_locked(l)		mutex_owned(l)

#define assert_spin_locked(l)		ASSERT(MUTEX_HELD(l))

#define kmalloc           kmem_alloc
#define kzalloc           kmem_zalloc
#define kcalloc(x, y, z)  kzalloc((x)*(y), z)
#define kfree             kmem_free

#define do_gettimeofday   (void) uniqtime
#define msleep_interruptible(s)  DRM_UDELAY(s)
#define	timeval_to_ns(tvp)	TICK_TO_NSEC(TIMEVAL_TO_TICK(tvp))
#define	ns_to_timeval(nsec, tvp)	TICK_TO_TIMEVAL(NSEC_TO_TICK(nsec), tvp)

#define GFP_KERNEL KM_SLEEP
#define GFP_ATOMIC KM_SLEEP

#define	KHZ2PICOS(a)		(1000000000UL/(a))

#define udelay			drv_usecwait
#define mdelay(x)		udelay((x) * 1000)
#define msleep(x)		mdelay((x))
#define msecs_to_jiffies(x)	drv_usectohz((x) * 1000)
#define jiffies_to_msecs(x)	drv_hztousec(x) / 1000
#define time_after(a,b)	((long)(b) - (long)(a) < 0)
#define	time_after_eq(a,b)	((long)(a) - (long)(b) >= 0)
#define time_before_eq(a,b)	time_after_eq(b,a)
#define time_in_range(a,b,c) \
	(time_after_eq(a,b) && \
	 time_before_eq(a,c))

#define	jiffies	ddi_get_lbolt()

#ifdef _BIG_ENDIAN
#define cpu_to_le16(x) LE_16(x)
#define le16_to_cpu(x) LE_16(x)
#else
#define cpu_to_le16(x) (x)
#define le16_to_cpu(x) (x)
#endif

#define swap(a, b) \
	do { int tmp = (a); (a) = (b); (b) = tmp; } while (__lintzero)

#define abs(x) ((x < 0) ? -x : x)

#define div_u64(x, y) ((unsigned long long)(x))/((unsigned long long)(y))  /* XXX FIXME */
#define roundup(x, y) ((((x) + ((y) - 1)) / (y)) * (y))

#define put_user(val,ptr) DRM_COPY_TO_USER(ptr,(&val),sizeof(val))
#define get_user(x,ptr) DRM_COPY_FROM_USER((&x),ptr,sizeof(x))
#define copy_to_user DRM_COPY_TO_USER
#define copy_from_user DRM_COPY_FROM_USER
#define unlikely(a)  (a)

#define AGP_USER_TYPES (1 << 16)
#define AGP_USER_MEMORY (AGP_USER_TYPES)
#define AGP_USER_CACHED_MEMORY (AGP_USER_TYPES + 1)

#define ALIGN(x, a)	(((x) + ((a) - 1)) & ~((a) - 1))

#define page_to_phys(x)	*(uint32_t *)(uintptr_t)(x)
#define in_dbg_master()	0

#define BITS_PER_BYTE		8
#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
#define BITS_TO_LONGS(nr)	DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))
#define	POS_DIV_ROUND_CLOSEST(x, d)	((x + (d / 2)) / d)
#define POS_DIV_ROUND_UP_ULL(x, d)	DIV_ROUND_UP(x,d)

typedef unsigned long dma_addr_t;
typedef uint64_t	u64;
typedef int64_t		s64;
typedef uint32_t	u32;
typedef int32_t		s32;
typedef uint16_t	u16;
typedef uint8_t		u8;
typedef uint_t		irqreturn_t;

typedef int		bool;

#define true		(1)
#define false		(0)

#define __init
#define __exit
#define __iomem

#ifdef _ILP32
typedef u32 resource_size_t;
#else /* _LP64 */
typedef u64 resource_size_t;
#endif

typedef struct kref {
	atomic_t refcount;
} kref_t;

extern void kref_init(struct kref *kref);
extern void kref_get(struct kref *kref);
extern void kref_put(struct kref *kref, void (*release)(struct kref *kref));

extern unsigned int hweight16(unsigned int w);

extern long IS_ERR(const void *ptr);
#define	IS_ERR_OR_NULL(ptr)	(!ptr || IS_ERR(ptr))

#ifdef __lint
/*
 * The actual code for _wait_for() causes Solaris lint2 to fail, though
 * by all appearances, the code actually works (may try and peek at
 * the compiled code to understand why).  So to get around the problem,
 * we create a special lint version for _wait_for().
 */
#define _wait_for(COND, MS, W) (! (COND))
#else /* !__lint */
#define _wait_for(COND, MS, W) ({ \
	unsigned long timeout__ = jiffies + msecs_to_jiffies(MS);	\
	int ret__ = 0;							\
	while (! (COND)) {						\
		if (time_after(jiffies, timeout__)) {			\
			ret__ = -ETIMEDOUT;				\
			break;						\
		}							\
		if (W) udelay(W);					\
	}								\
	ret__;								\
})
#endif /* __lint */

#define wait_for(COND, MS) _wait_for(COND, MS, 1)
#define wait_for_atomic(COND, MS) _wait_for(COND, MS, 0)

#endif /* __DRM_LINUX_H__ */
