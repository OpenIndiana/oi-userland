/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
 * Copyright (C) 2015 by the Massachusetts Institute of Technology.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.
 */

#include "crypto_int.h"
#include <libucrypto.h>

#define MD5_DIGEST_LENGTH 16
#define MD5_DATASIZE    64
#define SHA_DIGEST_LENGTH  20
#define SHA_DATASIZE    64

static krb5_error_code
hash_ucrypto(int ucrypto_type, size_t digest_size, const krb5_crypto_iov *data,
             size_t num_data, krb5_data *output)
{
    crypto_ctx_t uctx; /* ucrypto context */
    size_t i;
    int ret = 0;

    if (output->length != digest_size)
        return KRB5_CRYPTO_INTERNAL;

    if (ucrypto_digest_init(&uctx, ucrypto_type, NULL, 0) != CRYPTO_SUCCESS)
        return KRB5_CRYPTO_INTERNAL;

    for (i = 0; i < num_data; i++) {
        const krb5_data *d = &data[i].data;
        if (SIGN_IOV(&data[i])) {
            if (ucrypto_digest_update(&uctx, (uchar_t *)d->data,
                                      (size_t)d->length) != CRYPTO_SUCCESS) {
                ret = KRB5_CRYPTO_INTERNAL;
                break;
            }
        }
    }

    if (ret) {
        /* error, just clean up ucrypto context */
        (void)ucrypto_digest_final(&uctx, NULL, 0);
    } else {
        size_t outlen = (size_t)output->length;

        if (ucrypto_digest_final(&uctx, (uchar_t *)output->data, &outlen)
            != CRYPTO_SUCCESS) {
            ret = KRB5_CRYPTO_INTERNAL;
        } else {
            output->length = (uint_t)outlen;
        }
    }

    return ret;
}

static krb5_error_code
hash_md5(const krb5_crypto_iov *data, size_t num_data, krb5_data *output)
{
    return hash_ucrypto(CRYPTO_MD5, MD5_DIGEST_LENGTH, data, num_data, output);
}

static krb5_error_code
hash_sha1(const krb5_crypto_iov *data, size_t num_data, krb5_data *output)
{
    return hash_ucrypto(CRYPTO_SHA1, SHA_DIGEST_LENGTH, data, num_data,
                        output);
}

const struct krb5_hash_provider krb5int_hash_md5 = {
    "MD5",
    MD5_DIGEST_LENGTH,
    MD5_DATASIZE,
    hash_md5
};

const struct krb5_hash_provider krb5int_hash_sha1 = {
    "SHA1",
    SHA_DIGEST_LENGTH,
    SHA_DATASIZE,
    hash_sha1
};
