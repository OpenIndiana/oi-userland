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

#ifndef _OS_HEADER_H
#define _OS_HEADER_H
/*
 * os_header.h
 *
 * Operating system specific defines.
 */
#if defined(THREADX) || defined(NO_OS_ARM)

/* THREADX/ARM is 32 bit */
#define OS_PRIx64 "llx"
#define OS_U64DEF "unsigned long long"

#else /* !THREADX */

#ifdef SOLARIS

#include "solaris.h"

#define OS_PRIx64 PRIx64
#define OS_U64DEF "unsigned long"

#else /* LINUX */

#include <asm-generic/int-ll64.h>
#include <endian.h>

#if defined HAVE_DECL_BE64TOH_HTOBE64 && !HAVE_DECL_BE64TOH_HTOBE64
#define be64toh(x) htonll(x)
#define htobe64(x) ntohll(x)
#define be32toh(x) htonl(x)
#define htobe32(x) ntohl(x)
#define be16toh(x) htons(x)
#define htobe16(x) ntohs(x)

#define be64_to_cpu(x) htonll(x)
#define cpu_to_be64(x) ntohll(x)
#define be32_to_cpu(x) htonl(x)
#define cpu_to_be32(x) ntohl(x)
#define be16_to_cpu(x) htons(x)
#define cpu_to_be16(x) ntohs(x)

#else

#define be64_to_cpu(x) be64toh(x)
#define cpu_to_be64(x) htobe64(x)
#define be32_to_cpu(x) be32toh(x)
#define cpu_to_be32(x) htobe32(x)
#define be16_to_cpu(x) be16toh(x)
#define cpu_to_be16(x) htobe16(x)

#define le64_to_cpu(x) le64toh(x)
#define cpu_to_le64(x) htole64(x)
#define le32_to_cpu(x) le32toh(x)
#define cpu_to_le32(x) htole32(x)
#define le16_to_cpu(x) le16toh(x)
#define cpu_to_le16(x) htole16(x)

#endif

#if defined(OS_PRIx64)
/* Do not override... */
#elif defined(_STDINT_H)
#include <inttypes.h>
#define OS_PRIx64 PRIx64
#else
/*
 * Linux statically defines 64 bit words as type 'long long'
 * regardless of 64 bit vs 32 bit compilation.  However,
 * the PRIx64 macro expands to 'lx' (type long) on 64 bit
 * compilation, which is incompatible with the Linux 64 bit
 * word definition.
 */
#define OS_PRIx64 "llx"
#define OS_U64DEF "unsigned long long"
#endif
#endif /* LINUX */
#endif /* !THREADX */

#endif /* _OS_HEADER_H */
