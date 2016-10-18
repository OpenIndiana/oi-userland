/*
 * Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef	_PSIF_ENDIAN_H
#define	_PSIF_ENDIAN_H

#if defined(__arm__)
#undef HOST_BIG_ENDIAN
#define HOST_LITTLE_ENDIAN
#else /* __arm__ */
#if defined(__KERNEL__)
#  if defined(__BIG_ENDIAN) || defined(_BIG_ENDIAN)
#    define HOST_BIG_ENDIAN
#  elif defined(__LITTLE_ENDIAN) || defined(_LITTLE_ENDIAN)
#    define HOST_LITTLE_ENDIAN
#  else
#    error "could not determine byte order"
#  endif
#else /* defined(__KERNEL__) */
#  include "os_header.h"
#  if defined(__BYTE_ORDER)
#    if __BYTE_ORDER == __BIG_ENDIAN
#      define HOST_BIG_ENDIAN
#    elif __BYTE_ORDER == __LITTLE_ENDIAN
#      define HOST_LITTLE_ENDIAN
#    else
#      error "could not determine byte order"
#    endif
#  else /* defined(__BYTE_ORDER) */
#    error "could not determine byte order"
#  endif
#endif /* defined(__KERNEL__) */
#endif

#if !defined(__KERNEL__)

#if !defined(__arm__)
#include <stdlib.h>
#endif /* !__arm__ */

#if defined(HOST_BIG_ENDIAN)

#define copy_convert(dest, src, n) { memcpy((void *)dest, (void const *)(src), n); wmb(); }
#define copy_convert_to_hw(dest, src, n) copy_convert(dest, src, n)
#define copy_convert_to_sw(dest, src, n) copy_convert(dest, src, n)

#else /* HOST_LITTLE_ENDIAN */

#if defined(__arm__)
#include <stdint.h>
#include "epsfw_misc.h"
#define htobe64(x) eps_htobe64(x)
#define htobe32(x) eps_htobe32(x)
#define htobe16(x) eps_htobe16(x)
#define be64toh(x) eps_be64toh(x)
#define be32toh(x) eps_be32toh(x)
#define be16toh(x) eps_be16toh(x)

#define cpu_to_be64(x) htobe64(x)
#define cpu_to_be32(x) htobe32(x)
#define cpu_to_be16(x) htobe16(x)
#define be64_to_cpu(x) be64toh(x)
#define be32_to_cpu(x) be32toh(x)
#define be16_to_cpu(x) be16toh(x)

#define u64 uint64_t

static inline void __DSB(void)
{
/* __dsb() doesn't serve as sequence point in armcc so adding
 * __schedule_barrier() around it to force the compiler to see it as a
 * sequence point
 */
__schedule_barrier();
__dsb(0xf);
__schedule_barrier();
}
#define wmb() __DSB()

/*
 * Alternatively, use this one as barrier?
 * #define wmb() __memory_changed()
 */
#endif /* __arm__ */

/*
 * assertions:
 * - dest and src are 8 bytes aligned
 * - n is an integer multiple of 8
 */
static inline void _copy_convert(void *dest, void const *src, size_t n)
{
	int i, words = n / 8;
	volatile u64       *dp = (volatile u64       *) dest;
	const volatile u64 *sp = (const volatile u64 *) src;

	for (i = 0; i < words; i++) {
		*dp++ = htobe64(*sp);
		sp++;
	}
	wmb();
}

/*
 * assertions:
 * - dest and src are 8 bytes aligned
 * - n is an integer multiple of 8
 */
static inline void _copy_convert_to_hw(volatile void *dest, void const *src, size_t n)
{
	int i, words = n / 8;
	volatile u64 *dp = (volatile u64 *) dest;
	const u64    *sp = (const u64    *) src;

	for (i = 0; i < words; i++) {
		*dp++ = htobe64(*sp);
		sp++;
	}
	wmb();
}

/*
 * assertions:
 * - dest and src are 8 bytes aligned
 * - n is an integer multiple of 8
 */
static inline void _copy_convert_to_sw(void *dest, volatile void const *src, size_t n)
{
	int i, words = n / 8;
	u64                *dp = (u64                *) dest;
	const volatile u64 *sp = (const volatile u64 *) src;

	for (i = 0; i < words; i++) {
		*dp++ = htobe64(*sp);
		sp++;
	}
	wmb();
}

#define copy_convert(dest, src, n) _copy_convert(dest, src, n)
#define copy_convert_to_hw(dest, src, n) _copy_convert_to_hw(dest, src, n)
#define copy_convert_to_sw(dest, src, n) _copy_convert_to_sw(dest, src, n)

#endif /* HOST_ENDIAN */
#endif /* !__KERNEL__ */
#endif	/* _PSIF_ENDIAN_H */
