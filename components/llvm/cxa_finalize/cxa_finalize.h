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
 *
 * Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
 */

/* A Solaris implementation of the Itanium C++ ABI __cxa_atexit
 * and __cxa_finalize functions.
 */

#ifndef _CXA_FINALIZE_H
#define _CXA_FINALIZE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int
__attribute__((visibility("hidden")))
__cxa_atexit(void (*destructor)(void*), void* arg, void* dso);

extern int __attribute__((visibility("hidden")))
__cxa_finalize(void* dso);

#ifdef __cplusplus
}
#endif

#endif /* _CXA_FINALIZE_H */

