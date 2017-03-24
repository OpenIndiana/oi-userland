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

#define DES3_BLOCK_SIZE 8
#define DES3_KEY_SIZE 24
#define DES3_KEY_BYTES 21

static krb5_error_code
validate(krb5_key key, const krb5_data *ivec, const krb5_crypto_iov *data,
         size_t num_data, size_t *inlen)
{
    size_t input_length = iov_total_length(data, num_data, FALSE);

    if (key->keyblock.length != DES3_KEY_SIZE)
        return KRB5_BAD_KEYSIZE;
    if ((input_length % DES3_BLOCK_SIZE) != 0)
        return KRB5_BAD_MSIZE;
    if (ivec && (ivec->length != DES3_BLOCK_SIZE))
        return KRB5_BAD_MSIZE;

    if (inlen != NULL)
        *inlen = input_length;

    return 0;
}

static krb5_error_code
k5_des3_encrypt(krb5_key key, const krb5_data *ivec, krb5_crypto_iov *data,
               size_t num_data)
{
    int ret;
    size_t  olen, dlen;
    uchar_t *obuf, *dbuf;
    uchar_t tmp_iv[DES3_BLOCK_SIZE];
    struct iov_cursor cursor;

    ret = validate(key, ivec, data, num_data, &dlen);
    if (ret != 0 || dlen == 0)
        return ret;

    if (ivec && ivec->data)
        memcpy(tmp_iv, ivec->data, ivec->length);
    else
        memset(tmp_iv, 0, sizeof(tmp_iv));

    olen = dlen;
    obuf = malloc(olen);
    if (!obuf)
        return ENOMEM;

    dbuf = malloc(dlen);
    if (!dbuf){
        free(obuf);
        return ENOMEM;
    }

    /* Init iov cursor to gather data for encypting (FALSE) */
    k5_iov_cursor_init(&cursor, data, num_data, dlen, FALSE);
    /* Get all that data into dbuf */
    k5_iov_cursor_get(&cursor, dbuf);

    if (ucrypto_encrypt(CRYPTO_DES3_CBC,
                        key->keyblock.contents,
                        key->keyblock.length,
                        tmp_iv, sizeof(tmp_iv),
                        dbuf, dlen, obuf, &olen) != CRYPTO_SUCCESS) {
        ret = KRB5_CRYPTO_INTERNAL;
    } else {
        k5_iov_cursor_put(&cursor, obuf);
    }

    /*
     * Updating the ivec arg, if present because of an old/obscure concept of
     * cipher state that is being used by only BSD rlogin.  See RFCs 1391 and
     * 1392 in regards to the vague description of cipher state.
     */
    if (!ret && ivec && ivec->data) {
        /* Copy last block of cipher text output */
        memcpy(ivec->data, obuf + (dlen - DES3_BLOCK_SIZE), DES3_BLOCK_SIZE);
    }

    zap(obuf, olen);
    zap(dbuf, dlen);
    free(obuf);
    free(dbuf);

    return ret;
}

static krb5_error_code
k5_des3_decrypt(krb5_key key, const krb5_data *ivec, krb5_crypto_iov *data,
               size_t num_data)
{
    int ret;
    size_t  olen, dlen;
    uchar_t *obuf, *dbuf;
    uchar_t tmp_iv[DES3_BLOCK_SIZE];
    struct iov_cursor cursor;

    ret = validate(key, ivec, data, num_data, &dlen);
    if (ret != 0 || dlen == 0)
        return ret;

    if (ivec && ivec->data)
        memcpy(tmp_iv, ivec->data, ivec->length);
    else
        memset(tmp_iv, 0, sizeof(tmp_iv));

    olen = dlen;
    obuf = malloc(olen);
    if (!obuf)
        return ENOMEM;

    dbuf = malloc(dlen);
    if (!dbuf){
        free(obuf);
        return ENOMEM;
    }

    /* Init iov cursor to gather cipher text for decrypting (FALSE) */
    k5_iov_cursor_init(&cursor, data, num_data, dlen, FALSE);
    /* Gather all that cipher text into dbuf */
    k5_iov_cursor_get(&cursor, dbuf);

    if (ucrypto_decrypt(CRYPTO_DES3_CBC,
                        key->keyblock.contents,
                        key->keyblock.length,
                        tmp_iv, sizeof(tmp_iv),
                        dbuf, dlen, obuf, &olen) != CRYPTO_SUCCESS) {
        ret = KRB5_CRYPTO_INTERNAL;
    } else {
        k5_iov_cursor_put(&cursor, obuf);
    }

    /*
     * Updating the ivec arg, if present because of an old/obscure concept of
     * cipher state that is being used by only BSD rlogin.  See RFCs 1391 and
     * 1392 in regards to the vague description of cipher state.
     */
    if (!ret && ivec && ivec->data) {
        /* Copy last block of cipher text input */
        memcpy(ivec->data, dbuf + (dlen - DES3_BLOCK_SIZE), DES3_BLOCK_SIZE);
    }

    zap(obuf, olen);
    zap(dbuf, dlen);
    free(obuf);
    free(dbuf);

    return ret;
}

const struct krb5_enc_provider krb5int_enc_des3 = {
    DES3_BLOCK_SIZE,
    DES3_KEY_BYTES, DES3_KEY_SIZE,
    k5_des3_encrypt,
    k5_des3_decrypt,
    NULL,
    krb5int_des_init_state,
    krb5int_default_free_state
};
