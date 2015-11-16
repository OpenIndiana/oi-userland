/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
 */

#ifndef	SOLARISDEFS_H
#define	SOLARISDEFS_H

#include <sys/types.h>

#define	u_int8_t uint8_t
#define	u_int16_t uint16_t
#define	u_int32_t uint32_t
#define	u_int64_t uint64_t

struct ip6_ext {
	uint8_t  ip6e_nxt;
	uint8_t  ip6e_len;
};

#endif /* SOLARISDEFS_H */
