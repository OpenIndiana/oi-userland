/*
 * Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
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

#ifndef _SOLARIS_H
#define _SOLARIS_H

/*
 * Endian specific conversion macros
 */
#if defined(_LITTLE_ENDIAN)
#define htobe64(x)		htonll(x)
#define be64toh(x)		htonll(x)
#define        be64_to_cpu(x)          BSWAP_64(x)
#define        cpu_to_be64(x)          BSWAP_64(x)
#define        be32_to_cpu(x)          BSWAP_32(x)
#define        cpu_to_be32(x)          BSWAP_32(x)
#define        be16_to_cpu(x)          BSWAP_16(x)
#define        cpu_to_be16(x)          BSWAP_16(x)
#else /* BIG_ENDIAN */
#define htobe64(x)		(x)
#define be64toh(x)		(x)
#define        be64_to_cpu(x)          BMASK_64(x)
#define        cpu_to_be64(x)          BMASK_64(x)
#define        be32_to_cpu(x)          BMASK_32(x)
#define        cpu_to_be32(x)          BMASK_32(x)
#define        be16_to_cpu(x)          BMASK_16(x)
#define        cpu_to_be16(x)          BMASK_16(x)

#endif /* BIG_ENDIAN */

#endif /* _SOLARIS_H */
