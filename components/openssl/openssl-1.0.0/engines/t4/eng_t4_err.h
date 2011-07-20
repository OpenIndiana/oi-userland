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
 * Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
 */

#ifndef	ENG_T4_ERR_H
#define	ENG_T4_ERR_H

#ifdef	__cplusplus
extern "C" {
#endif

static void ERR_unload_t4_strings(void);
#pragma inline(ERR_unload_t4_strings)
static void ERR_t4_error(int function, int reason, char *file, int line);

#define	T4err(f, r)	ERR_t4_error((f), (r), __FILE__, __LINE__)

/* Function codes */
#define	T4_F_INIT 				100
#define	T4_F_DESTROY 				101
#define	T4_F_FINISH				102
#define	T4_F_CIPHER_INIT_AES			103
#define	T4_F_ADD_NID				104
#define	T4_F_GET_ALL_CIPHERS			105
#define	T4_F_CIPHER_DO_AES			106
#define	T4_F_CIPHER_CLEANUP			107

/* Reason codes */
#define	T4_R_CIPHER_KEY				100
#define	T4_R_CIPHER_NID				101
#define	T4_R_IV_LEN_INCORRECT			102
#define	T4_R_KEY_LEN_INCORRECT			103
#define	T4_R_ASN1_OBJECT_CREATE			104
#define	T4_R_NOT_BLOCKSIZE_LENGTH		105

#ifdef	__cplusplus
}
#endif

#endif	/* ENG_T4_ERR_H */
