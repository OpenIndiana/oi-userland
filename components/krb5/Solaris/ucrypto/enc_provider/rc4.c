/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/* lib/crypto/openssl/enc_provider/des.c */
/*
 * Copyright (C) 2009 by the Massachusetts Institute of Technology.
 * All rights reserved.
 *
 * Export of this software from the United States of America may
 *   require a specific license from the United States Government.
 *   It is the responsibility of any person or organization contemplating
 *   export to obtain such a license before exporting.
 *
 * WITHIN THAT CONSTRAINT, permission to use, copy, modify, and
 * distribute this software and its documentation for any purpose and
 * without fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation, and that
 * the name of M.I.T. not be used in advertising or publicity pertaining
 * to distribution of the software without specific, written prior
 * permission.  Furthermore if you modify this software you must label
 * your software as modified software and not distribute it in such a
 * fashion that it might be confused with the original M.I.T. software.
 * M.I.T. makes no representations about the suitability of
 * this software for any purpose.  It is provided "as is" without express
 * or implied warranty.
 */

/*
 * Copyright (C) 1998 by the FundsXpress, INC.
 *
 * All rights reserved.
 *
 * Export of this software from the United States of America may require
 * a specific license from the United States Government.  It is the
 * responsibility of any person or organization contemplating export to
 * obtain such a license before exporting.
 *
 * WITHIN THAT CONSTRAINT, permission to use, copy, modify, and
 * distribute this software and its documentation for any purpose and
 * without fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation, and that
 * the name of FundsXpress. not be used in advertising or publicity pertaining
 * to distribution of the software without specific, written prior
 * permission.  FundsXpress makes no representations about the suitability of
 * this software for any purpose.  It is provided "as is" without express
 * or implied warranty.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */
/*
 * Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.
 */

#include "crypto_int.h"
#include <libucrypto.h>

/*
 * The loopback field is NULL if uctx is uninitialized (no encrypt or decrypt
 * operation has taken place), or is a pointer to the structure address if uctx
 * is initialized.  If an application copies the state (not a valid operation,
 * but one which happens to works with some other enc providers), we can detect
 * it via the loopback field and return a sane error code.
 */
struct arcfour_state {
    struct arcfour_state *loopback;
    int op_type; /* encrypt, decrypt */
    crypto_ctx_t uctx; /* ucrypto context */
};
#define ENCRYPT_OP 1
#define DECRYPT_OP 2

#define RC4_KEY_SIZE 16
#define RC4_BLOCK_SIZE 1

static krb5_error_code
k5_arcfour_docrypt(krb5_key key, const krb5_data *state, krb5_crypto_iov *data,
                   size_t num_data, int op_type)
{
    int ret = 0;
    crypto_ctx_t local_uctx, *uctx; /* ucrypto context */
    size_t len, i;
    struct arcfour_state *arcstate;
    krb5_boolean do_init = TRUE;

    arcstate = (state != NULL) ? (struct arcfour_state *)state->data : NULL;
    if (arcstate != NULL) {
        /*
         * If loopback points to arcstate we know that uctx has been init'ed
         * but if it doesn't and it isn't NULL then arcstate has been corrupted
         * which means we can't trust that uctx is valid.
         */
        if (arcstate->loopback == arcstate)
            do_init = FALSE;
        else if (arcstate->loopback != NULL)
            return KRB5_CRYPTO_INTERNAL;

        uctx = &arcstate->uctx;
    } else {
        /* Use the local ucrypto context, will need to be cleaned up in this
         * function. */
        uctx = &local_uctx;
    }

    if (do_init) {
        if (op_type == ENCRYPT_OP) {
            if (ucrypto_encrypt_init(uctx, CRYPTO_RC4,
                                     key->keyblock.contents,
                                     key->keyblock.length,
                                     NULL, 0) != CRYPTO_SUCCESS) {
                return KRB5_CRYPTO_INTERNAL;
            }
        } else {
            if (ucrypto_decrypt_init(uctx, CRYPTO_RC4,
                                     key->keyblock.contents,
                                     key->keyblock.length,
                                     NULL, 0) != CRYPTO_SUCCESS) {
                return KRB5_CRYPTO_INTERNAL;
            }
        }

        /* Saved ucrypto context is init'ed, mark as initialized. */
        if (arcstate) {
            arcstate->loopback = arcstate;
            arcstate->op_type = op_type;
        }
    }

    for (i = 0; i < num_data; i++) {
        krb5_crypto_iov *iov = &data[i];

        if (ENCRYPT_IOV(iov)) {
            len = (size_t)iov->data.length;

            if (op_type == ENCRYPT_OP) {
                if (ucrypto_encrypt_update(uctx,
                                           (const uchar_t *)iov->data.data,
                                           len,
                                           (uchar_t *)iov->data.data,
                                           &len) != CRYPTO_SUCCESS) {
                    ret = KRB5_CRYPTO_INTERNAL;
                    break;
                }
            } else {
                if (ucrypto_decrypt_update(uctx,
                                           (const uchar_t *)iov->data.data,
                                           len,
                                           (uchar_t *)iov->data.data,
                                           &len) != CRYPTO_SUCCESS) {
                    ret = KRB5_CRYPTO_INTERNAL;
                    break;
                }
            }
        }
    }

    if (!arcstate) {
        /* Local ucrypto context is not saved, clean it up now. */
        len = 0;
        if (op_type == ENCRYPT_OP)
            (void)ucrypto_encrypt_final(uctx, NULL, &len);
        else
            (void)ucrypto_decrypt_final(uctx, NULL, &len);
    }

    return ret;
}

static krb5_error_code
k5_arcfour_encrypt(krb5_key key, const krb5_data *state, krb5_crypto_iov *data,
                   size_t num_data)
{
    return k5_arcfour_docrypt(key, state, data, num_data, ENCRYPT_OP);
}

static krb5_error_code
k5_arcfour_decrypt(krb5_key key, const krb5_data *state, krb5_crypto_iov *data,
                   size_t num_data)
{
    return k5_arcfour_docrypt(key, state, data, num_data, DECRYPT_OP);
}

static krb5_error_code
krb5int_arcfour_init_state(const krb5_keyblock *key, krb5_keyusage usage,
                           krb5_data *state)
{
    struct arcfour_state *arcstate;

    arcstate = calloc(1, sizeof (*arcstate));
    if (arcstate == NULL)
        return ENOMEM;

    state->data = (char *)arcstate;
    state->length = sizeof (*arcstate);

    return 0;
}

static void
krb5int_arcfour_free_state(krb5_data *state)
{
    struct arcfour_state *arcstate = (struct arcfour_state *)state->data;

    /* If arcstate->loopback == arcstate then the ucrypto context was init'ed
     * and uctx clean up is required. */
    if (arcstate && arcstate->loopback == arcstate) {
        size_t len = 0;

        if (arcstate->op_type == ENCRYPT_OP)
            (void) ucrypto_encrypt_final(&arcstate->uctx, NULL, &len);
        else
            (void) ucrypto_decrypt_final(&arcstate->uctx, NULL, &len);
    }

    free(arcstate);
    state->data = NULL;
    state->length = 0;

    return;
}

const struct krb5_enc_provider krb5int_enc_arcfour = {
    /* This seems to work... although I am not sure what the
       implications are in other places in the kerberos library */
    RC4_BLOCK_SIZE,
    /* Keysize is arbitrary in arcfour, but the constraints of the
       system, and to attempt to work with the MSFT system forces us
       to 16byte/128bit.  Since there is no parity in the key, the
       byte and length are the same.  */
    RC4_KEY_SIZE, RC4_KEY_SIZE,
    k5_arcfour_encrypt,
    k5_arcfour_decrypt,
    NULL,
    krb5int_arcfour_init_state,
    krb5int_arcfour_free_state
};
