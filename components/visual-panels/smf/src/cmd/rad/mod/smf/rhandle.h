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
 * Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
 */

#ifndef	_RHANDLE_H
#define	_RHANDLE_H

#include <libscf.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * A rad_handle_t is a wrapper around a single scf_handle_t that
 * permits sharing it between multiple users and facilitates
 * reconnecting in case svc.configd dies.
 *
 * A caller uses rh_fetch() to get the rad_handle_t.  The enclosed
 * scf_handle_t is guaranteed to be valid (though not necessarily
 * functional) until they call rh_rele().
 *
 * If the scf_handle_t doesn't work, the caller should call rh_kill()
 * before calling rh_rele(), and then call rh_fetch() to get a fresh
 * (hopefully working) handle.
 */

typedef struct rad_handle {
	scf_handle_t *rh_hdl;	/* handle */
	int rh_refs;		/* references */
} rad_handle_t;

rad_handle_t *rh_fetch(void);
void rh_rele(rad_handle_t *);
void rh_kill(rad_handle_t *);
#define	rh_hdl(rh)	(rh == NULL ? NULL : rh->rh_hdl)

#ifdef	__cplusplus
}
#endif

#endif	/* _RHANDLE_H */
