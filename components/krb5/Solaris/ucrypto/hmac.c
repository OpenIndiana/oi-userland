/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/* lib/crypto/ucrypto/hmac.c */
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
 * This a copy from the EVP_MAX_MD_SIZE define in /usr/include/openssl/evp.h
 */
#define MAX_MAC_SIZE 64

/* ucrypto doesn't support this so creating this define for convenience */
#define CRYPTO_MD4_HMAC -4

/* Return ucrypto hmac mech type (mostly, see above) */
static int
map_digest(const struct krb5_hash_provider *hash)
{
    if (!strncmp(hash->hash_name, "SHA1",4))
        return CRYPTO_SHA1_HMAC;
    else if (!strncmp(hash->hash_name, "MD5", 3))
        return CRYPTO_MD5_HMAC;
    else if (!strncmp(hash->hash_name, "MD4", 3))
        return CRYPTO_MD4_HMAC;
    else
        return -1;
}

/*
 * Took this from the MIT builtin hmac.c since libucrypto does not support HMAC
 * MD4.  This does a HMAC processing using the basic MD4 hash.
 */
static krb5_error_code
krb5int_hmac_keyblock_builtin(const struct krb5_hash_provider *hash,
                      const krb5_keyblock *keyblock,
                      const krb5_crypto_iov *data, size_t num_data,
                      krb5_data *output)
{
    unsigned char *xorkey = NULL, *ihash = NULL;
    unsigned int i;
    krb5_crypto_iov *ihash_iov = NULL, ohash_iov[2];
    krb5_data hashout;
    krb5_error_code ret;

    /* Allocate space for the xor key, hash input vector, and inner hash */
    xorkey = k5alloc(hash->blocksize, &ret);
    if (xorkey == NULL)
        goto cleanup;
    ihash = k5alloc(hash->hashsize, &ret);
    if (ihash == NULL)
        goto cleanup;
    ihash_iov = k5calloc(num_data + 1, sizeof(krb5_crypto_iov), &ret);
    if (ihash_iov == NULL)
        goto cleanup;

    /* Create the inner padded key. */
    memset(xorkey, 0x36, hash->blocksize);
    for (i = 0; i < keyblock->length; i++)
        xorkey[i] ^= keyblock->contents[i];

    /* Compute the inner hash over the inner key and input data. */
    ihash_iov[0].flags = KRB5_CRYPTO_TYPE_DATA;
    ihash_iov[0].data = make_data(xorkey, hash->blocksize);
    memcpy(ihash_iov + 1, data, num_data * sizeof(krb5_crypto_iov));
    hashout = make_data(ihash, hash->hashsize);
    ret = hash->hash(ihash_iov, num_data + 1, &hashout);
    if (ret != 0)
        goto cleanup;

    /* Create the outer padded key. */
    memset(xorkey, 0x5c, hash->blocksize);
    for (i = 0; i < keyblock->length; i++)
        xorkey[i] ^= keyblock->contents[i];

    /* Compute the outer hash over the outer key and inner hash value. */
    ohash_iov[0].flags = KRB5_CRYPTO_TYPE_DATA;
    ohash_iov[0].data = make_data(xorkey, hash->blocksize);
    ohash_iov[1].flags = KRB5_CRYPTO_TYPE_DATA;
    ohash_iov[1].data = make_data(ihash, hash->hashsize);
    output->length = hash->hashsize;
    ret = hash->hash(ohash_iov, 2, output);
    if (ret != 0)
        memset(output->data, 0, output->length);

cleanup:
    zapfree(xorkey, hash->blocksize);
    zapfree(ihash, hash->hashsize);
    free(ihash_iov);
    return ret;
}

static krb5_error_code
krb5int_hmac_keyblock_ucrypto(int ucrypto_hmac_type,
                              const krb5_keyblock *keyblock,
                              const krb5_crypto_iov *data, size_t num_data,
                              krb5_data *output)
{
    uchar_t mac[MAX_MAC_SIZE];
    size_t mac_len = sizeof (mac);
    uchar_t *dbuf;
    size_t dlen;
    struct iov_cursor cursor;
    int ret = 0;

    /* find total amount/length of signing data (TRUE) */
    dlen = iov_total_length(data, num_data, TRUE);
    dbuf = malloc(dlen);
    if (!dbuf){
        return ENOMEM;
    }

    /* Init iovec cursor to gather signing data (TRUE) */
    k5_iov_cursor_init(&cursor, data, num_data, dlen, TRUE);
    /* gather all data that the MAC will cover into dbuf */
    k5_iov_cursor_get(&cursor, dbuf);

    if (ucrypto_mac(ucrypto_hmac_type,
                    keyblock->contents, keyblock->length,
                    NULL, 0,
                    dbuf, dlen,
                    mac, &mac_len) != CRYPTO_SUCCESS) {
        ret = KRB5_CRYPTO_INTERNAL;
        memset(output->data, 0, output->length);
    } else {
        if (mac_len <= output->length) {
            output->length = (uint_t)mac_len;
            memcpy(output->data, mac, output->length);
        }
    }

    free(dbuf);
    return ret;
}

krb5_error_code
krb5int_hmac_keyblock(const struct krb5_hash_provider *hash,
                      const krb5_keyblock *keyblock,
                      const krb5_crypto_iov *data, size_t num_data,
                      krb5_data *output)
{
    int ucrypto_hmac_type;

    if (keyblock->length > hash->blocksize)
        return KRB5_CRYPTO_INTERNAL;
    if (output->length < hash->hashsize)
        return KRB5_BAD_MSIZE;

    ucrypto_hmac_type = map_digest(hash);
    switch (ucrypto_hmac_type) {
    case CRYPTO_SHA1_HMAC:
    case CRYPTO_MD5_HMAC:
        return krb5int_hmac_keyblock_ucrypto(ucrypto_hmac_type, keyblock,
                                             data, num_data, output);
    case CRYPTO_MD4_HMAC:
        return krb5int_hmac_keyblock_builtin(hash, keyblock, data, num_data,
                                             output);
    default:
        return (KRB5_CRYPTO_INTERNAL); /* unsupported alg */
    }
}

krb5_error_code
krb5int_hmac(const struct krb5_hash_provider *hash, krb5_key key,
             const krb5_crypto_iov *data, size_t num_data,
             krb5_data *output)
{
    return krb5int_hmac_keyblock(hash, &key->keyblock, data, num_data, output);
}
