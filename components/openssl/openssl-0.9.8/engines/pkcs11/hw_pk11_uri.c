/*
 * Copyright 2010 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
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

#pragma ident	"@(#)hw_pk11_uri.c	1.2	10/02/01 SMI"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <strings.h>
#include <libgen.h>
#include <pthread.h>
#include <assert.h>
#include <errno.h>

#include <openssl/crypto.h>

#ifndef OPENSSL_NO_HW
#ifndef OPENSSL_NO_HW_PK11

#include <security/cryptoki.h>
#include <security/pkcs11.h>
#include "hw_pk11.h"
#include "hw_pk11_uri.h"

/*
 * The keystore used is always from the pubkey slot so we need to know which one
 * was selected so that we can get the information needed for the URI
 * processing.
 */
extern CK_SLOT_ID pubkey_SLOTID;
extern CK_FUNCTION_LIST_PTR pFuncList;

/*
 * Cached PIN so that child can use it during the re-login. Note that we do not
 * cache the PIN by default.
 */
static char *token_pin;

static int mlock_pin_in_memory(char *pin);
static char *run_askpass(char *dialog);

/*
 * Get the PIN. Either run the command and use its standard output as a PIN to
 * fill in the PKCS11 URI structure, or read the PIN from the terminal. Using
 * the external command is of higher precedence. The memory for PIN is allocated
 * in this function and the PIN is always NULL terminated. The caller must take
 * care of freeing the memory used for the PIN. The maximum PIN length accepted
 * is PK11_MAX_PIN_LEN.
 *
 * The function is used also during the re-initialization of the engine after
 * the fork.
 *
 * The function must not be called under the protection of the mutex "uri_lock"
 * because the lock is acquired in the prefork function.
 *
 * Returns:
 *	0 in case of troubles (and sets "*pin" to NULL)
 *	1 if we got the PIN
 */
#define	EXEC_SPEC	"exec:"
#define	BUILTIN_SPEC	"builtin"
int
pk11_get_pin(char *dialog, char **pin)
	{
	/* Initialize as an error. */
	*pin = NULL;

	if (strcmp(dialog, BUILTIN_SPEC) == 0)
		{
		/* The getpassphrase() function is not MT safe. */
		(void) pthread_mutex_lock(uri_lock);
		/* Note that OpenSSL is not localized at all. */
		*pin = getpassphrase("Enter token PIN: ");
		if (*pin == NULL)
			{
			PK11err(PK11_F_GET_PIN, PK11_R_COULD_NOT_READ_PIN);
			(void) pthread_mutex_unlock(uri_lock);
			goto err;
			}
		else
			{
			char *pw;

			/*
			 * getpassphrase() uses an internal  buffer to hold the
			 * entered password. Note that it terminates the buffer
			 * with '\0'.
			 */
			if ((pw = strdup(*pin)) == NULL)
				{
				PK11err(PK11_F_GET_PIN, PK11_R_MALLOC_FAILURE);
				(void) pthread_mutex_unlock(uri_lock);
				goto err;
				}
			/* Zero the internal buffer to get rid of the PIN. */
			memset(*pin, 0, strlen(*pin));
			*pin = pw;
			(void) pthread_mutex_unlock(uri_lock);
			}
		}
	else
		{
		/*
		 * This is the "exec:" case. We will get the PIN from the output
		 * of an external command.
		 */
		if (strncmp(dialog, EXEC_SPEC, strlen(EXEC_SPEC)) == 0)
			{
			dialog += strlen(EXEC_SPEC);
			if ((*pin = run_askpass(dialog)) == NULL)
				goto err;
			}
		else
			{
			/*
			 * Invalid specification in the passphrasedialog
			 * keyword.
			 */
			PK11err(PK11_F_GET_PIN, PK11_R_BAD_PASSPHRASE_SPEC);
			goto err;
			}
		}

	return (1);
err:
	return (0);
	}

/*
 * Process the PKCS#11 URI and get the PIN. It uses information from the
 * passphrasedialog keyword to get the PIN. If passphrasedialog is not present
 * it is not considered an error since it depends on the token attributes
 * whether C_Login() is required. The function expects an allocated 'uri_struct'
 * structure.
 *
 * Returns:
 *	0 if URI is not valid at all, or if we could not get the PIN
 * 	1 if all is OK
 *	2 if the URI is not the PKCS#11 URI. In that case, put the string
 *	pointer to the filename to "*file". Note that the pointer just points
 *	inside of the "uristr", possibly skipping the file:// prefix if present.
 */
int
pk11_process_pkcs11_uri(const char *uristr, pkcs11_uri *uri_struct,
	const char **file)
	{
	char *uristr2, *l1, *l2, *tok, *name;

	/* Check the "file://" case. */
	if (strncmp(uristr, FILE_URI_PREFIX, strlen(FILE_URI_PREFIX)) == 0)
		{
		*file = uristr + strlen(FILE_URI_PREFIX);
		return (2);
		}

	/*  This is the "pkcs11:" case. */
	if (strncmp(uristr, PK11_URI_PREFIX, strlen(PK11_URI_PREFIX)) != 0)
		{
		/* Not PKCS#11 URI at all, could be a filename. */
		*file = (const char *)uristr;
		return (2);
		}
	else
		{
		/* Dup the string and skip over the pkcs11: prefix then. */
		uristr2 = strdup(uristr + strlen(PK11_URI_PREFIX));
		if (uristr2 == NULL)
			{
			PK11err(PK11_F_CHECK_TOKEN_ATTRS,
			    PK11_R_MALLOC_FAILURE);
			goto err;
			}
		}

	/* Initialize the structure. */
	memset(uri_struct, 0, sizeof (*uri_struct));

	/*
	 * Using strtok_r() would silently skip over multiple semicolons. We
	 * must check that before moving on. We must also avoid ';' as the first
	 * and the last character in the URI.
	 */
	if (strstr(uristr2, ";;") != NULL || uristr2[0] == ';' ||
	    (strlen(uristr2) > 0 && uristr2[strlen(uristr2) - 1] == ';'))
		goto bad_uri;

	tok = strtok_r(uristr2, ";", &l1);
	for (; tok != NULL; tok = strtok_r(NULL, ";", &l1))
		{
		/* "tok" is not empty so there will be something in "name". */
		name = strtok_r(tok, "=", &l2);
		/* Check whether there is '=' at all. */
		if (l2 == NULL)
			goto bad_uri;

		/*
		 * Fill out the URI structure. We do not accept duplicit
		 * attributes.
		 */
		if (strcmp(name, PK11_TOKEN) == 0)
			if (uri_struct->token == NULL)
				{
				if ((uri_struct->token = strdup(l2)) == NULL)
					goto no_mem;
				}
			else
				goto bad_uri;
		else if (strcmp(name, PK11_MANUF) == 0)
			if (uri_struct->manuf == NULL)
				{
				if ((uri_struct->manuf = strdup(l2)) == NULL)
					goto no_mem;
				}
			else
				goto bad_uri;
		else if (strcmp(name, PK11_SERIAL) == 0)
			if (uri_struct->serial == NULL)
				{
				if ((uri_struct->serial = strdup(l2)) == NULL)
					goto no_mem;
				}
			else
				goto bad_uri;
		else if (strcmp(name, PK11_MODEL) == 0)
			if (uri_struct->model == NULL)
				{
				if ((uri_struct->model = strdup(l2)) == NULL)
					goto no_mem;
				}
			else
				goto bad_uri;
		else if (strcmp(name, PK11_OBJECT) == 0)
			if (uri_struct->object == NULL)
				{
				if ((uri_struct->object = strdup(l2)) == NULL)
					goto no_mem;
				}
			else
				goto bad_uri;
		else if (strcmp(name, PK11_OBJECTTYPE) == 0)
			if (uri_struct->objecttype == NULL)
				{
				uri_struct->objecttype = strdup(l2);
				if (uri_struct->objecttype == NULL)
					goto no_mem;
				}
			else
				goto bad_uri;
		else if (strcmp(name, PK11_ASKPASS) == 0)
			if (uri_struct->askpass == NULL)
				{
				if ((uri_struct->askpass = strdup(l2)) == NULL)
					goto no_mem;
				}
			else
				goto bad_uri;
		else
			goto bad_uri;
		}

	/* The "object" token is mandatory in the PKCS#11 URI. */
	if (uri_struct->object == NULL)
		{
		PK11err(PK11_F_LOAD_PRIVKEY, PK11_R_MISSING_OBJECT_LABEL);
		goto err;
		}

	free(uristr2);
	return (1);
bad_uri:
	PK11err(PK11_F_LOAD_PRIVKEY, PK11_R_INVALID_PKCS11_URI);
	if (uristr2 != NULL)
		free(uristr2);
	return (0);
no_mem:
	PK11err(PK11_F_LOAD_PRIVKEY, PK11_R_MALLOC_FAILURE);
err:
	pk11_free_pkcs11_uri(uri_struct, CK_FALSE);
	if (uristr2 != NULL)
		free(uristr2);
	return (0);
	}

/*
 * Free the PKCS11 URI structure and anything that might be inside.
 */
void
pk11_free_pkcs11_uri(pkcs11_uri *uri_struct, CK_BBOOL free_uri_itself)
	{
	if (uri_struct->token != NULL)
		free(uri_struct->token);
	if (uri_struct->manuf != NULL)
		free(uri_struct->manuf);
	if (uri_struct->serial != NULL)
		free(uri_struct->serial);
	if (uri_struct->model != NULL)
		free(uri_struct->model);
	if (uri_struct->object != NULL)
		free(uri_struct->object);
	if (uri_struct->objecttype != NULL)
		free(uri_struct->objecttype);
	if (uri_struct->askpass != NULL)
		free(uri_struct->askpass);

	if (free_uri_itself == CK_TRUE)
		OPENSSL_free(uri_struct);
	}

/*
 * While our keystore is always the one used by the pubkey slot (which is
 * usually the Metaslot) we must make sure that those URI attributes that
 * specify the keystore match the real attributes of our slot keystore. Note
 * that one can use the METASLOT_OBJECTSTORE_TOKEN environment variable to
 * change the Metaslot's keystore from the softtoken to something else (see
 * libpkcs11(3LIB)). The user might want to use such attributes in the PKCS#11
 * URI to make sure that the intended keystore is used.
 *
 * Returns:
 *	1 on success
 *	0 on failure
 */
int
pk11_check_token_attrs(pkcs11_uri *uri_struct)
	{
	CK_RV rv;
	static CK_TOKEN_INFO_PTR token_info = NULL;

	(void) pthread_mutex_lock(uri_lock);
	if (token_info == NULL)
		{
		token_info = OPENSSL_malloc(sizeof (CK_TOKEN_INFO));
		if (token_info == NULL)
			{
			PK11err(PK11_F_CHECK_TOKEN_ATTRS,
			    PK11_R_MALLOC_FAILURE);
			goto err;
			}

		rv = pFuncList->C_GetTokenInfo(pubkey_SLOTID, token_info);
		if (rv != CKR_OK)
			{
			PK11err_add_data(PK11_F_CHECK_TOKEN_ATTRS,
			    PK11_R_GETTOKENINFO, rv);
			goto err;
			}
		}

	if (uri_struct->token != NULL)
		if (strncmp(uri_struct->token, (char *)token_info->label,
		    strlen(uri_struct->token) > 32 ? 32 :
		    strlen(uri_struct->token)) != 0)
			{
			goto urierr;
			}

	if (uri_struct->manuf != NULL)
		if (strncmp(uri_struct->manuf,
		    (char *)token_info->manufacturerID,
		    strlen(uri_struct->manuf) > 32 ? 32 :
		    strlen(uri_struct->manuf)) != 0)
			goto urierr;

	if (uri_struct->model != NULL)
		if (strncmp(uri_struct->model, (char *)token_info->model,
		    strlen(uri_struct->model) > 16 ? 16 :
		    strlen(uri_struct->model)) != 0)
			goto urierr;

	if (uri_struct->serial != NULL)
		if (strncmp(uri_struct->serial,
		    (char *)token_info->serialNumber,
		    strlen(uri_struct->serial) > 16 ? 16 :
		    strlen(uri_struct->serial)) != 0)
			goto urierr;

	(void) pthread_mutex_unlock(uri_lock);
	return (1);

urierr:
	PK11err(PK11_F_CHECK_TOKEN_ATTRS, PK11_R_TOKEN_ATTRS_DO_NOT_MATCH);
	/* Correct error already set above for the "err" label. */
err:
	(void) pthread_mutex_unlock(uri_lock);
	return (0);
	}

/*
 * Return the process PIN caching policy. We initialize it just once so if the
 * process change OPENSSL_PKCS11_PIN_CACHING_POLICY during the operation it will
 * not have any affect on the policy.
 *
 * We assume that the "uri_lock" mutex is already locked.
 *
 * Returns the caching policy number.
 */
int
pk11_get_pin_caching_policy(void)
	{
	char *value = NULL;
	static int policy = POLICY_NOT_INITIALIZED;

	if (policy != POLICY_NOT_INITIALIZED)
		return (policy);

	value = getenv("OPENSSL_PKCS11_PIN_CACHING_POLICY");

	if (value == NULL || strcmp(value, "none") == 0)
		{
		policy = POLICY_NONE;
		goto done;
		}

	if (strcmp(value, "memory") == 0)
		{
		policy = POLICY_MEMORY;
		goto done;
		}

	if (strcmp(value, "mlocked-memory") == 0)
		{
		policy = POLICY_MLOCKED_MEMORY;
		goto done;
		}

	return (POLICY_WRONG_VALUE);
done:
	return (policy);
	}

/*
 * Cache the PIN in memory once. We already know that we have either "memory" or
 * "mlocked-memory" keyword correctly set.
 *
 * Returns:
 *	1 on success
 *	0 on failure
 */
int
pk11_cache_pin(char *pin)
	{
	(void) pthread_mutex_lock(uri_lock);
	/* We set the PIN only once since all URIs must have it the same. */
	if (token_pin != NULL)
		goto ok;

	if (pk11_get_pin_caching_policy() == POLICY_MEMORY)
		if ((token_pin = strdup(pin)) == NULL)
			{
			PK11err(PK11_F_CACHE_PIN, PK11_R_MALLOC_FAILURE);
			goto err;
			}
	else
		if (pk11_get_pin_caching_policy() == POLICY_MLOCKED_MEMORY)
			{
			if (mlock_pin_in_memory(pin) == 0)
				goto err;
			}

ok:
	(void) pthread_mutex_unlock(uri_lock);
	return (1);
err:
	(void) pthread_mutex_unlock(uri_lock);
	return (0);
	}

/*
 * Cache the PIN in mlock(3C)ed memory. If mlock(3C) fails we will not resort to
 * the normal memory caching.
 *
 * Note that this function must be called under the protection of the "uri_lock"
 * mutex.
 *
 * Returns:
 *	1 on success
 *	0 on failure
 */
static int
mlock_pin_in_memory(char *pin)
	{
	void *addr = NULL;
	long pagesize = 0;

	/* mlock(3C) locks pages so we need one whole page for the PIN. */
	if ((pagesize = sysconf(_SC_PAGESIZE)) == -1)
		{
		PK11err(PK11_F_MLOCK_PIN_IN_MEMORY, PK11_R_SYSCONF_FAILED);
		goto err;
		}

	/* This will ensure we have a page aligned pointer... */
	if ((addr = mmap(0, pagesize, PROT_READ | PROT_WRITE,
	    MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
		{
		PK11err(PK11_F_MLOCK_PIN_IN_MEMORY, PK11_R_MMAP_FAILED);
		goto err;
		}

	/* ...because "addr" must be page aligned here. */
	if (mlock(addr, pagesize) == -1)
		{
		/*
		 * Missing the PRIV_PROC_LOCK_MEMORY privilege might be a common
		 * problem so distinguish this situation from other issues.
		 */
		if (errno == EPERM)
			PK11err(PK11_F_MLOCK_PIN_IN_MEMORY,
			    PK11_R_PRIV_PROC_LOCK_MEMORY_MISSING);
		else
			PK11err(PK11_F_MLOCK_PIN_IN_MEMORY,
			    PK11_R_MLOCK_FAILED);

		/*
		 * We already have a problem here so there is no need to check
		 * that we could unmap the page. The PIN is not there yet
		 * anyway.
		 */
		(void) munmap(addr, pagesize);
		goto err;
		}

	/* Copy the PIN to the mlocked memory. */
	token_pin = (char *)addr;
	strlcpy(token_pin, pin, PK11_MAX_PIN_LEN + 1);
	return (1);
err:
	return (0);
	}

/*
 * Log in to the keystore if we are supposed to do that at all. Take care of
 * reading and caching the PIN etc. Log in only once even when called from
 * multiple threads.
 *
 * Returns:
 *	1 on success
 *	0 on failure
 */
int
pk11_token_login(CK_SESSION_HANDLE session, CK_BBOOL *login_done,
    pkcs11_uri *uri_struct, CK_BBOOL is_private)
	{
	CK_RV rv;

	if ((pubkey_token_flags & CKF_TOKEN_INITIALIZED) == 0)
		{
		PK11err(PK11_F_TOKEN_LOGIN,
		    PK11_R_TOKEN_NOT_INITIALIZED);
		goto err;
		}

	/*
	 * If login is required or needed but the PIN has not been even
	 * initialized we can bail out right now. Note that we are supposed to
	 * always log in if we are going to access private keys. However, we may
	 * need to log in even for accessing public keys in case that the
	 * CKF_LOGIN_REQUIRED flag is set.
	 */
	if ((pubkey_token_flags & CKF_LOGIN_REQUIRED ||
	    is_private == CK_TRUE) && ~pubkey_token_flags &
	    CKF_USER_PIN_INITIALIZED)
		{
		PK11err(PK11_F_TOKEN_LOGIN, PK11_R_TOKEN_PIN_NOT_SET);
		goto err;
		}

	/*
	 * Note on locking: it is possible that more than one thread gets into
	 * pk11_get_pin() so we must deal with that. We cannot avoid it since we
	 * cannot guard fork() in there with a lock because we could end up in
	 * a dead lock in the child. Why? Remember we are in a multithreaded
	 * environment so we must lock all mutexes in the prefork function to
	 * avoid a situation in which a thread that did not call fork() held a
	 * lock, making future unlocking impossible. We lock right before
	 * C_Login().
	 */
	if (pubkey_token_flags & CKF_LOGIN_REQUIRED || is_private == CK_TRUE)
		{
		if (*login_done == CK_FALSE &&
		    uri_struct->askpass == NULL)
			{
			PK11err(PK11_F_TOKEN_LOGIN,
			    PK11_R_TOKEN_PIN_NOT_PROVIDED);
			goto err;
			}

		if (*login_done == CK_FALSE &&
		    uri_struct->askpass != NULL)
			{
			if (pk11_get_pin(uri_struct->askpass,
			    &uri_struct->pin) == 0)
				{
				PK11err(PK11_F_TOKEN_LOGIN,
				    PK11_R_TOKEN_PIN_NOT_PROVIDED);
				goto err;
				}
			}

		/*
		 * Note that what we are logging into is the keystore from
		 * pubkey_SLOTID because we work with OP_RSA session type here.
		 * That also means that we can work with only one keystore in
		 * the engine.
		 *
		 * We must make sure we do not try to login more than once.
		 * Also, see the comment above on locking strategy.
		 */
		(void) pthread_mutex_lock(uri_lock);
		if (*login_done == CK_FALSE)
			{
			if ((rv = pFuncList->C_Login(session,
			    CKU_USER, (CK_UTF8CHAR*)uri_struct->pin,
			    strlen(uri_struct->pin))) != CKR_OK)
				{
				PK11err_add_data(PK11_F_TOKEN_LOGIN,
				    PK11_R_TOKEN_LOGIN_FAILED, rv);
				goto err_locked;
				}

			*login_done = CK_TRUE;

			/*
			 * Cache the passphrasedialog for possible child (which
			 * would need to relogin).
			 */
			if (passphrasedialog == NULL &&
			    uri_struct->askpass != NULL)
				{
				passphrasedialog =
				    strdup(uri_struct->askpass);

				if (passphrasedialog == NULL)
					{
					PK11err_add_data(PK11_F_TOKEN_LOGIN,
					    PK11_R_MALLOC_FAILURE, rv);
					goto err_locked;
					}
				}

			/*
			 * Check the PIN caching policy. Note that user might
			 * have provided a PIN even when no PIN was required -
			 * in that case we always remove the PIN from memory.
			 */
			if (pk11_get_pin_caching_policy() ==
			    POLICY_WRONG_VALUE)
				{
				PK11err(PK11_F_TOKEN_LOGIN,
				    PK11_R_PIN_CACHING_POLICY_INVALID);
				goto err_locked;
				}

			if (pk11_get_pin_caching_policy() != POLICY_NONE)
				if (pk11_cache_pin(uri_struct->pin) == 0)
					goto err_locked;
			}
		(void) pthread_mutex_unlock(uri_lock);
		}
	else
		{
			/*
			 * If token does not require login we take it as the
			 * login was done.
			 */
			*login_done = CK_TRUE;
		}

	/*
	 * If we raced at pk11_get_pin() we must make sure that all threads that
	 * called pk11_get_pin() will erase the PIN from memory, not just the
	 * one that called C_Login(). Note that if we were supposed to cache the
	 * PIN it was already cached by now so filling "uri_struct.pin" with
	 * zero bytes is always OK since pk11_cache_pin() makes a copy of it.
	 */
	if (uri_struct->pin != NULL)
		memset(uri_struct->pin, 0, strlen(uri_struct->pin));

	return (1);

err_locked:
	(void) pthread_mutex_unlock(uri_lock);
err:
	/* Always get rid of the PIN. */
	if (uri_struct->pin != NULL)
		memset(uri_struct->pin, 0, strlen(uri_struct->pin));
	return (0);
	}

/*
 * Log in to the keystore in the child if we were logged in in the parent. There
 * are similarities in the code with pk11_token_login() but still it is quite
 * different so we need a separate function for this.
 *
 * Note that this function is called under the locked session mutex when fork is
 * detected. That means that C_Login() will be called from the child just once.
 *
 * Returns:
 *	1 on success
 *	0 on failure
 */
int
pk11_token_relogin(CK_SESSION_HANDLE session)
	{
	CK_RV rv;

	/*
	 * We are in the child so check if we should login to the token again.
	 * Note that it is enough to log in to the token through one session
	 * only, all already open and all future sessions can access the token
	 * then.
	 */
	if (passphrasedialog != NULL)
		{
		char *pin = NULL;

		/* If we cached the PIN then use it. */
		if (token_pin != NULL)
			pin = token_pin;
		else if (pk11_get_pin(passphrasedialog, &pin) == 0)
			goto err;

		(void) pthread_mutex_lock(uri_lock);
		if ((rv = pFuncList->C_Login(session, CKU_USER,
		    (CK_UTF8CHAR_PTR)pin, strlen(pin))) != CKR_OK)
			{
			PK11err_add_data(PK11_F_TOKEN_RELOGIN,
			    PK11_R_TOKEN_LOGIN_FAILED, rv);
			(void) pthread_mutex_unlock(uri_lock);
			goto err;
			}
		(void) pthread_mutex_unlock(uri_lock);

		/* Forget the PIN now if we did not cache it before. */
		if (pin != token_pin)
			{
			memset(pin, 0, strlen(pin));
			OPENSSL_free(pin);
			}
		}

	return (1);
err:
	return (0);
	}

/*
 * This function forks and runs an external command. It would be nice if we
 * could use popen(3C)/pclose(3C) for that but unfortunately we need to be able
 * to get rid of the PIN from the memory. With p(open|close) function calls we
 * cannot control the stdio's memory used for buffering and our tests showed
 * that the PIN really stays there even after pclose().
 *
 * Returns:
 *	allocated buffer on success
 *	NULL on failure
 */
static char *
run_askpass(char *dialog)
	{
	pid_t pid;
	int n, p[2];
	char *buf = NULL;

	if (pipe(p) == -1)
		{
		PK11err(PK11_F_RUN_ASKPASS, PK11_R_PIPE_FAILED);
		return (NULL);
		}

	switch (pid = fork())
		{
		case -1:
			PK11err(PK11_F_RUN_ASKPASS, PK11_R_FORK_FAILED);
			return (NULL);
		/* child */
		case 0:
			/*
			 * This should make sure that dup2() will not fail on
			 * file descriptor shortage.
			 */
			close(p[0]);
			(void) dup2(p[1], 1);
			close(p[1]);
			/*
			 * Note that we cannot use PK11err() here since we are
			 * in the child. However, parent will get read() error
			 * so do not worry.
			 */
			(void) execl(dialog, basename(dialog), NULL);
			exit(1);
		/* parent */
		default:
			/* +1 is for the terminating '\0' */
			buf = (char *)OPENSSL_malloc(PK11_MAX_PIN_LEN + 1);
			if (buf == NULL)
				{
				PK11err(PK11_F_RUN_ASKPASS,
				    PK11_R_MALLOC_FAILURE);
				return (NULL);
				}

			close(p[1]);
			n = read(p[0], buf, PK11_MAX_PIN_LEN);
			if (n == -1 || n == 0)
				{
				PK11err(PK11_F_RUN_ASKPASS,
				    PK11_R_PIN_NOT_READ_FROM_COMMAND);
				OPENSSL_free(buf);
				return (NULL);
				}
			buf[n] = '\0';

			(void) waitpid(pid, NULL, 0);
		}

	return (buf);
	}

#endif	/* OPENSSL_NO_HW_PK11 */
#endif	/* OPENSSL_NO_HW */
