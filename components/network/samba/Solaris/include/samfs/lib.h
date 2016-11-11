/*
 * lib.h - SAM-FS API library functions.
 *
 * Definitions for SAM-FS API library functions.
 *
 */

/*
 *    SAM-QFS_notice_begin
 *
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at pkg/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at pkg/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright (c) 2010, Oracle and/or its affiliates. All rights reserved.
 *
 *    SAM-QFS_notice_end
 */
#ifndef	SAMLIB_H
#define	SAMLIB_H

#ifdef sun
#pragma ident "$Revision: 1.19 $"
#endif

#ifdef linux
#include <sam/linux_types.h>	/* uint_t */
#endif /* linux */

#ifdef  __cplusplus
extern "C" {
#endif

int sam_archive(const char *name, const char *opns);
int sam_unarchive(const char *name, int num_opts, ...);
int sam_rearch(const char *name, int num_opts, ...);
int sam_unrearch(const char *name, int num_opts, ...);
int sam_exarchive(const char *name, int num_opts, ...);
int sam_damage(const char *name, int num_opts, ...);
int sam_undamage(const char *name, int num_opts, ...);
char *sam_attrtoa(int attr, char *string);
int sam_cancelstage(const char *name);
char *sam_devstr(uint_t p);
int sam_release(const char *name, const char *opns);
int sam_ssum(const char *name, const char *opns);
int sam_stage(const char *name, const char *opns);
int sam_setfa(const char *name, const char *opns);
int sam_segment(const char *name, const char *opns);
int sam_advise(const int fildes, const char *opns);

#ifdef  __cplusplus
}
#endif

#endif /* SAMLIB_H */
