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
 * Copyright (c) 2010, Oracle and/or its affiliates. All rights reserved.
 */

#pragma ident	"@(#)e_devcrypto_err.h	1.1	10/10/19 SMI"

#ifndef HEADER_DEVCRYPTO_ERR_H
#define	HEADER_DEVCRYPTO_ERR_H

static void ERR_load_devcrypto_strings(void);
static void ERR_unload_devcrypto_strings(void);
static void ERR_devcrypto_error(int function, int reason, char *file, int line);

#define	DEVCRYPTOerr(f, r) ERR_devcrypto_error((f), (r), __FILE__, __LINE__)


/* Function codes */
#define	DEVC_F_INIT 				100
#define	DEVC_F_DESTROY 				101
#define	DEVC_F_FINISH				102
#define	DEVC_F_CIPHER_INIT			103
#define	DEVC_F_CIPHER_DO_CIPHER			104
#define	DEVC_F_CIPHER_CLEANUP			105


/* Reason codes */
#define	DEVC_R_CIPHER_KEY			100
#define	DEVC_R_CIPHER_NID			101
#define	DEVC_R_KEY_OR_IV_LEN_PROBLEM		102
#define	DEVC_R_MECH_STRING			103
#define	DEVC_R_FIND_SLOT_BY_MECH		104
#define	DEVC_R_OPEN_SESSION			105
#define	DEVC_R_GET_MECHANISM_NUMBER		106
#define	DEVC_R_ENCRYPT_INIT			107
#define	DEVC_R_ENCRYPT_UPDATE			108
#define	DEVC_R_ENCRYPT_FINAL			109
#define	DEVC_R_DECRYPT_INIT			110
#define	DEVC_R_DECRYPT_UPDATE			111
#define	DEVC_R_DECRYPT_FINAL			112
#define	DEVC_R_CLOSE_SESSION			113

#endif /* HEADER_DEVCRYPTO_ERR_H */
