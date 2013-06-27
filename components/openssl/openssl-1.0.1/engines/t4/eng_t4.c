/*
 * This product includes cryptographic software developed by the OpenSSL
 * Project for use in the OpenSSL Toolkit (http://www.openssl.org/).
 */

/*
 * ====================================================================
 * Copyright (c) 1998-2011 The OpenSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit. (http://www.openssl.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    openssl-core@openssl.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.openssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 */

/*
 * Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * This engine supports SPARC microprocessors that provide T4 MONTMUL
 * instructions, such as the T4 microprocessor.
 */

#include <openssl/opensslconf.h>

#if !defined(OPENSSL_NO_HW)
#include <sys/types.h>
#include <sys/auxv.h>	/* getisax() */
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <openssl/engine.h>

#define	T4_LIB_NAME "SPARC T4 engine"
#include "eng_t4_err.c"

/* Constants used when creating the ENGINE */
static const char *ENGINE_T4_ID = "t4";
static const char *ENGINE_T4_NAME = "SPARC T4 engine support";
static const char *ENGINE_NO_T4_NAME = "SPARC T4 engine support (no T4)";


#if (defined(sun4v) || defined(__sparcv9) || defined(__sparcv8plus) || \
	defined(__sparcv8)) && !defined(OPENSSL_NO_ASM)
#define	COMPILE_HW_T4
static int t4_bind_helper(ENGINE *e, const char *id);
#pragma inline(t4_bind_helper)
#endif

/*
 * This makes the engine "built-in" with OpenSSL.
 * On non-T4 CPUs this just returns.
 * Called by ENGINE_load_builtin_engines().
 */
void
ENGINE_load_t4(void)
{
#ifdef	COMPILE_HW_T4
	ENGINE *toadd = ENGINE_new();
	if (toadd != NULL) {
		if (t4_bind_helper(toadd, ENGINE_T4_ID) != 0) {
			(void) ENGINE_add(toadd);
			(void) ENGINE_free(toadd);
			ERR_clear_error();
		} else {
			(void) ENGINE_free(toadd);
		}
	}
#endif
}


#ifdef	COMPILE_HW_T4
static int t4_bind(ENGINE *e);
#ifndef	DYNAMIC_ENGINE
#pragma inline(t4_bind)
#endif
static void t4_instructions_present(_Bool *montmul_present);
#pragma inline(t4_instructions_present)

/* RSA_METHOD structure used by ENGINE_set_RSA() */
extern RSA_METHOD *t4_RSA(void);

/* DH_METHOD structure used by ENGINE_set_DH() */
extern DH_METHOD *t4_DH(void);

/* DSA_METHOD structure used by ENGINE_set_DSA() */
extern DSA_METHOD *t4_DSA(void);

/*
 * Utility Functions
 */

/*
 * Set montmul_present to B_FALSE or B_TRUE depending on whether the
 * current SPARC processor supports MONTMUL.
 */
static void
t4_instructions_present(_Bool *montmul_present)
{
	uint_t		ui;

	(void) getisax(&ui, 1);
	*montmul_present = ((ui & AV_SPARC_MONT) != 0);
}



/*
 * Is the t4 engine available?
 * Passed to ENGINE_set_init_function().
 */
/* ARGSUSED */
static int
t4_init(ENGINE *e)
{
	return (1);
}

/* Passed to ENGINE_set_destroy_function(). */
/* ARGSUSED */
static int
t4_destroy(ENGINE *e)
{
	ERR_unload_t4_strings();
	return (1);
}


/*
 * Called by t4_bind_helper().
 * Note: too early to use T4err() functions on errors.
 */
/* ARGSUSED */
static int
t4_bind(ENGINE *e)
{
	_Bool montmul_engage;

	/* Register T4 engine ID, name, and functions */
	if (!ENGINE_set_id(e, ENGINE_T4_ID) ||
	    !ENGINE_set_name(e,
	    montmul_engage ? ENGINE_T4_NAME : ENGINE_NO_T4_NAME) ||
	    !ENGINE_set_init_function(e, t4_init) ||
#ifndef OPENSSL_NO_RSA
	    (montmul_engage && !ENGINE_set_RSA(e, t4_RSA())) ||
#endif	/* OPENSSL_NO_RSA */
#ifndef OPENSSL_NO_DH
	    (montmul_engage && !ENGINE_set_DH(e, t4_DH())) ||
#endif	/* OPENSSL_NO_DH */
#ifndef OPENSSL_NO_DSA
	    (montmul_engage && !ENGINE_set_DSA(e, t4_DSA())) ||
#endif	/* OPENSSL_NO_DSA */
	    !ENGINE_set_destroy_function(e, t4_destroy)) {
		return (0);
	}

	return (1);
}


/*
 * Called by ENGINE_load_t4().
 * Note: too early to use T4err() functions on errors.
 */
static int
t4_bind_helper(ENGINE *e, const char *id)
{
	if (id != NULL && (strcmp(id, ENGINE_T4_ID) != 0)) {
		(void) fprintf(stderr, "T4: bad t4 engine ID\n");
		return (0);
	}
	if (!t4_bind(e)) {
		(void) fprintf(stderr,
		    "T4: failed to bind t4 engine\n");
		return (0);
	}

	return (1);
}


#ifdef	DYNAMIC_ENGINE
IMPLEMENT_DYNAMIC_CHECK_FN()
IMPLEMENT_DYNAMIC_BIND_FN(t4_bind_helper)
#endif	/* DYNAMIC_ENGINE */
#endif	/* COMPILE_HW_T4 */
#endif	/* !OPENSSL_NO_HW */
