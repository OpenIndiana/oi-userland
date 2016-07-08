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

/*
 *   sif_int_user.h: This file defines special internal data structures used
 *   to communicate between libsif and the sif driver.
 *   This file is included both from user space and kernel space so
 *   it must not contain any kernel/user specific header file includes.
 *   This file is internal to libsif/sif driver since it relies on HW specific
 *   include files.
 */

#ifndef _SIF_INT_USER_H
#define	_SIF_INT_USER_H


#include <psif_hw_data.h>

#ifdef __cplusplus
extern "C" {
#endif

#define	SIF_CACHE_BYTES 64

/*
 * We use the extension here to communicate with the driver
 * (for correct debugfs reporting)
 */

enum sq_sw_state {
	FLUSH_SQ_IN_PROGRESS = 0,
	FLUSH_SQ_IN_FLIGHT   = 1,
};

typedef struct sif_sq_sw {
	struct psif_sq_sw d;	/* Hardware visible descriptor */
	/* separate the cache lines */
	__u8 fill[SIF_CACHE_BYTES - sizeof (struct psif_sq_sw)];
	__u16 last_seq;		/* Last used sq seq.num (req. sq->lock) */
	/* Last sq seq.number seen in a compl (req. cq->lock) */
	volatile __u16 head_seq;
	__u16 trusted_seq;
	__u8 tsl;
	volatile __u64 flags;
}sif_sq_sw_t;

enum rq_sw_state {
	FLUSH_RQ_IN_PROGRESS = 0,
	FLUSH_RQ_IN_FLIGHT   = 1,
	FLUSH_RQ_FIRST_TIME  = 2,
	RQ_IS_INVALIDATED    = 3,
};

typedef struct sif_rq_sw {
	struct psif_rq_sw d;	/* Hardware visible descriptor */
	/* separate the cache lines */
	__u8 fill[SIF_CACHE_BYTES - sizeof (struct psif_rq_sw)];
	/* current length of queue as #posted - #completed */
	volatile uint32_t length;
	__u32 next_seq; 	/* First unused sequence number */
	volatile __u64 flags;
}sif_rq_sw_t;

enum cq_sw_state {
	CQ_POLLING_NOT_ALLOWED = 0,
	CQ_POLLING_IGNORED_SEQ = 1,
	FLUSH_SQ_FIRST_TIME    = 2,
};

typedef struct sif_cq_sw {
	struct psif_cq_sw d;	/* Hardware visible descriptor */
	/* separate the cache lines */
	__u8 fill[SIF_CACHE_BYTES - sizeof (struct psif_cq_sw)];
	__u32 next_seq;		/* First unused sequence number */
	/* Local copy kept in sync w/hw visible head_indx */
	__u32 cached_head;
	/* Last next_seq reported in completion for req_notify_cq */
	__u32 last_hw_seq;
	/* Set if req_notify_cq has been called but event not processed */
	__u32 armed;
	/* Number of in-flight completions observed by poll_cq */
	__u32 miss_cnt;
	/* Number of times 1 or more in-flight completions was seen */
	__u32 miss_occ;
	volatile __u64 flags;
}sif_cq_sw_t;

#ifdef __cplusplus
}
#endif

#endif /* _SIF_INT_USER_H */
