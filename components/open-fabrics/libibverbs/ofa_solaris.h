/*
 * Copyright (c) 2010, Oracle and/or its affiliates. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * NAME: ofa_solaris.h
 * DESC: OFED Solaris wrapper
 */
#ifndef _OFA_SOLARIS_H
#define _OFA_SOLARIS_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/byteorder.h>
#include <sys/sockio.h>
#include <sys/mman.h>
#include <stdio.h>
#include <inttypes.h>
#include <alloca.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef		uint8_t 	__u8;
typedef		uint16_t	__u16;
typedef		uint32_t	__u32;
typedef		uint64_t	__u64;
typedef		int32_t		__s32;
typedef		int64_t		__s64;

typedef		uint8_t 	u8;
typedef		uint16_t	u16;
typedef		uint32_t	u32;
typedef		uint64_t	u64;
typedef		int32_t		s32;

typedef		__u8		u_int8_t;
typedef		__u16		u_int16_t;
typedef		__u32		u_int32_t;

#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
typedef		__u64		u_int64_t;
typedef		__s64		int64_t;
#endif

typedef        uint8_t         __be8;
typedef        uint16_t        __be16;
typedef        uint32_t        __be32;
typedef        uint64_t        __be64;

/* Size of a pointer */
#if defined(_LP64) || defined(_I32LPx)
#define __WORDSIZE 64
#else
#define __WORDSIZE 32
#endif


/*
 * Endian definitions
 */
#define __LITTLE_ENDIAN 1234
#define __BIG_ENDIAN    4321

#ifdef _BIG_ENDIAN
#define __BYTE_ORDER __BIG_ENDIAN
#elif defined _LITTLE_ENDIAN
#define __BYTE_ORDER __LITTLE_ENDIAN
#else
#error unknown endianness
#endif

/*
 * byteswap functions.
 */
#define	bswap_8(x)	((x) & 0xff)

#if !defined(__i386) && !defined(__amd64)
#define bswap_16(x)	((bswap_8(x) << 8) | bswap_8((x) >> 8))
#define bswap_32(x)     (((uint32_t)(x) << 24) | \
                        (((uint32_t)(x) << 8) & 0xff0000) | \
                        (((uint32_t)(x) >> 8) & 0xff00) | \
                        ((uint32_t)(x)  >> 24))
#else /* x86 */
#define bswap_16(x)     htons(x)
#define bswap_32(x)     htonl(x)
#endif  /* !__i386 && !__amd64 */

#if defined(_LP64) || defined(_LONGLONG_TYPE)
#if (!defined(__i386) && !defined(__amd64))
#define bswap_64(x)     (((uint64_t)(x) << 56) | \
                        (((uint64_t)(x) << 40) & 0xff000000000000ULL) | \
                        (((uint64_t)(x) << 24) & 0xff0000000000ULL) | \
                        (((uint64_t)(x) << 8)  & 0xff00000000ULL) | \
                        (((uint64_t)(x) >> 8)  & 0xff000000ULL) | \
                        (((uint64_t)(x) >> 24) & 0xff0000ULL) | \
                        (((uint64_t)(x) >> 40) & 0xff00ULL) | \
                        ((uint64_t)(x)  >> 56))
#else /* x86 */
#define bswap_64(x)	htonll(x)
#endif  /* !__i386 && !__amd64 */
#else /* no uint64_t */ 
#define bswap_64(x)	((bswap_32(x) << 32) | bswap_32((x) >> 32))
#endif

typedef struct sol_cpu_info_s {
	char	cpu_name[64];
	uint_t	cpu_mhz;
	uint_t	cpu_num;
} sol_cpu_info_t;

int sol_get_cpu_info(sol_cpu_info_t *);

#ifdef __cplusplus
}
#endif

#endif /* _OFA_SOLARIS_H */
