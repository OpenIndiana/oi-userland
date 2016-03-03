/*
 * Copyright (c) 2004, 2013, Oracle and/or its affiliates. All rights reserved.
 */

/*
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
 *    for use in the OpenSSL Toolkit. (http://www.OpenSSL.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    licensing@OpenSSL.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.OpenSSL.org/)"
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
 */

#ifndef	E_PK11_URI_H
#define	E_PK11_URI_H

#include <security/pkcs11t.h>

#ifdef	__cplusplus
extern "C" {
#endif

/* PKCS#11 URI related prefixes and attributes. */
#define	PK11_URI_PREFIX		"pkcs11:"
#define	FILE_URI_PREFIX		"file://"
#define	PK11_TOKEN		"token"
#define	PK11_MANUF		"manuf"
#define	PK11_SERIAL		"serial"
#define	PK11_MODEL		"model"
#define	PK11_OBJECT		"object"
#define	PK11_OBJECTTYPE		"objecttype"
#define	PK11_ASKPASS		"passphrasedialog"

/* PIN caching policy. */
#define	POLICY_NOT_INITIALIZED	0
#define	POLICY_NONE		1
#define	POLICY_MEMORY		2
#define	POLICY_MLOCKED_MEMORY	3
#define	POLICY_WRONG_VALUE	4

/*
 * That's what getpassphrase(3c) supports.
 */
#define	PK11_MAX_PIN_LEN	256

/* Add new attributes of the PKCS#11 URI here. */
typedef struct pkcs11_uri_struct
	{
	char	*object;	/* object label, the only mandatory info */
	char	*objecttype;	/* (private|public|cert), currently unused */
	char	*token;		/* token label */
	char	*manuf;		/* manufacturer label */
	char	*serial;	/* serial number label */
	char	*model;		/* model label */
	char	*askpass;	/* full path to the command to get the PIN */
	/* Not part of the PKCS11 URI itself. */
	char	*pin;		/* token PIN */
	} pkcs11_uri;

/* For URI processing. */
extern pthread_mutex_t *uri_lock;

int pk11_get_pin(char *dialog, char **pin);
int pk11_get_pin_caching_policy(void);
int pk11_process_pkcs11_uri(const char *uristr, pkcs11_uri *uri_struct,
	const char **file);
int pk11_check_token_attrs(pkcs11_uri *uri_struct);
void pk11_free_pkcs11_uri(pkcs11_uri *uri_struct, CK_BBOOL free_uri_itself);
int pk11_cache_pin(char *pin);
int pk11_token_login(CK_SESSION_HANDLE session, CK_BBOOL *login_done,
	pkcs11_uri *uri_struct, CK_BBOOL is_private);
int pk11_token_relogin(CK_SESSION_HANDLE session);

#ifdef	__cplusplus
}
#endif
#endif /* E_PK11_URI_H */
