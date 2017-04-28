/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/* lib/crypto/ucrypto/enc_provider/aes.c */
/*
 * Copyright (C) 2003, 2007, 2008, 2009 by the Massachusetts Institute of Technology.
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
 * Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.
 */

#include "crypto_int.h"
#include <libucrypto.h>

#define BLOCK_SIZE 16

#define ENCRYPT_OP 1
#define DECRYPT_OP 2

/*
 * xorblock is used in the camellia cbc mac fuction, copied from the openssl
 * camellia.c.
 */
static void
xorblock(unsigned char *out, const unsigned char *in)
{
    int z;
    for (z = 0; z < BLOCK_SIZE / 4; z++) {
        unsigned char *outptr = &out[z * 4];
        unsigned char *inptr = (unsigned char *)&in[z * 4];
        /*
         * Use unaligned accesses.  On x86, this will probably still be faster
         * than multiple byte accesses for unaligned data, and for aligned data
         * should be far better.  (One test indicated about 2.4% faster
         * encryption for 1024-byte messages.)
         *
         * If some other CPU has really slow unaligned-word or byte accesses,
         * perhaps this function (or the load/store helpers?) should test for
         * alignment first.
         *
         * If byte accesses are faster than unaligned words, we may need to
         * conditionalize on CPU type, as that may be hard to determine
         * automatically.
         */
        store_32_n(load_32_n(outptr) ^ load_32_n(inptr), outptr);
    }
}

/*
 * The cbc_docrypt function is here to handle the case where there is only 1
 * block of plain/cipher text to process.
 */
static krb5_error_code
cbc_docrypt(krb5_key key, const krb5_data *ivec, krb5_crypto_iov *data,
            size_t num_data, int op_type)
{
    int                    ret = 0;
    unsigned char          iblock[BLOCK_SIZE], oblock[BLOCK_SIZE];
    size_t                 olen = sizeof (oblock);
    unsigned char          tmp_iv[BLOCK_SIZE];
    struct iov_cursor      cursor;

    if (ivec && ivec->data){
        if (ivec->length != sizeof (tmp_iv))
            return KRB5_CRYPTO_INTERNAL;
        memcpy(tmp_iv, ivec->data, ivec->length);
    } else {
        memset(tmp_iv, 0, sizeof (tmp_iv));
    }

    /* Init iovec cursor to gather data for encypting (FALSE) */
    k5_iov_cursor_init(&cursor, data, num_data, BLOCK_SIZE, FALSE);
    k5_iov_cursor_get(&cursor, iblock);

    if (op_type == ENCRYPT_OP) {
        if (ucrypto_encrypt(CRYPTO_CAMELLIA_CBC,
                            key->keyblock.contents,
                            key->keyblock.length,
                            tmp_iv, sizeof (tmp_iv),
                            iblock, sizeof (iblock),
                            oblock, &olen) != CRYPTO_SUCCESS) {
            ret = KRB5_CRYPTO_INTERNAL;
        }
    } else {
        if (ucrypto_decrypt(CRYPTO_CAMELLIA_CBC,
                            key->keyblock.contents,
                            key->keyblock.length,
                            tmp_iv, sizeof (tmp_iv),
                            iblock, sizeof (iblock),
                            oblock, &olen) != CRYPTO_SUCCESS) {
            ret = KRB5_CRYPTO_INTERNAL;
        }
    }

    if (!ret) {
        assert(olen == BLOCK_SIZE);
        k5_iov_cursor_put(&cursor, oblock);

        if (ivec && ivec->data) {
            if (op_type == ENCRYPT_OP)
                memcpy(ivec->data, oblock, BLOCK_SIZE);
            else
                memcpy(ivec->data, iblock, BLOCK_SIZE);
        }
    }

    zap(iblock, sizeof (iblock));
    zap(oblock, sizeof (oblock));

    return ret;
}

static krb5_error_code
cts_docrypt(krb5_key key, const krb5_data *ivec, krb5_crypto_iov *data,
            size_t num_data, size_t dlen, size_t dblks, int op_type)
{
    int                    ret = 0;
    size_t                 olen = dlen;
    unsigned char         *obuf, *dbuf;
    unsigned char          iv_cts[BLOCK_SIZE];
    struct iov_cursor      cursor;

    if (ivec && ivec->data){
        if (ivec->length != sizeof (iv_cts))
            return KRB5_CRYPTO_INTERNAL;
        memcpy(iv_cts, ivec->data, ivec->length);
    } else {
        memset(iv_cts, 0, sizeof (iv_cts));
    }

    obuf = malloc(olen);
    if (!obuf)
        return ENOMEM;

    dbuf = malloc(dlen);
    if (!dbuf){
        free(obuf);
        return ENOMEM;
    }

    /* Init iov cursor to gather data for encypting/decrypting (FALSE) */
    k5_iov_cursor_init(&cursor, data, num_data, dlen, FALSE);
    /* Get all the data to be encrypted/decrypted into dbuf */
    k5_iov_cursor_get(&cursor, dbuf);

    if (op_type == ENCRYPT_OP) {
        if (ucrypto_encrypt(CRYPTO_CAMELLIA_CTS,
                            key->keyblock.contents,
                            key->keyblock.length,
                            iv_cts, sizeof (iv_cts),
                            dbuf, dlen, obuf, &olen) != CRYPTO_SUCCESS) {
            ret = KRB5_CRYPTO_INTERNAL;
        }
    } else {
        if (ucrypto_decrypt(CRYPTO_CAMELLIA_CTS,
                            key->keyblock.contents,
                            key->keyblock.length,
                            iv_cts, sizeof (iv_cts),
                            dbuf, dlen, obuf, &olen) != CRYPTO_SUCCESS) {
            ret = KRB5_CRYPTO_INTERNAL;
        }
    }

    if (!ret) {
        assert(olen == dlen);
        k5_iov_cursor_put(&cursor, obuf);
        /*
         * Updating the ivec arg, if present because of an old/obscure concept
         * of cipher state that is being used by only BSD rlogin.  See RFCs
         * 1391 and 1392 in regards to the vague description of cipher state.
         * For encrypt/decrypt use the second to the last block of ciphertext
         * if > 1 block.
         */
        if (ivec && ivec->data) {
            unsigned char *bufptr = (op_type == ENCRYPT_OP) ? obuf : dbuf;
            /*
             * For encrypt obuf is ciphertext, for decrypt its dbuf which was
             * input.
             */
            memcpy(ivec->data, bufptr + ((dblks - 2) * BLOCK_SIZE),
                   BLOCK_SIZE);
        }
    }

    zapfree(obuf, olen);
    zapfree(dbuf, dlen);

    return ret;
}

krb5_error_code
krb5int_camellia_encrypt(krb5_key key, const krb5_data *ivec,
                    krb5_crypto_iov *data, size_t num_data)
{
    size_t input_length, nblocks;

    input_length = iov_total_length(data, num_data, FALSE);
    nblocks = (input_length + BLOCK_SIZE - 1) / BLOCK_SIZE;
    if (nblocks == 1) {
        if (input_length != BLOCK_SIZE)
            return KRB5_BAD_MSIZE;
        /*
	 * Note, there is bug here (see MIT bug ticket 8551 Crypto providers not
	 * updating cipher state when 1 block plaintext is encrypted) hence the
	 * NULL ivec arg.  For now we leave the bug in since it has existed in
	 * MIT code a long time and the tests need the buggy behavior to pass at
	 * this point.
         */
        return cbc_docrypt(key, NULL, data, num_data, ENCRYPT_OP);
    } else {  /* nblocks > 1 */
        return cts_docrypt(key, ivec, data, num_data, input_length, nblocks,
                           ENCRYPT_OP);
    }
}

krb5_error_code
krb5int_camellia_decrypt(krb5_key key, const krb5_data *ivec,
                    krb5_crypto_iov *data, size_t num_data)
{
    size_t input_length, nblocks;

    input_length = iov_total_length(data, num_data, FALSE);
    nblocks = (input_length + BLOCK_SIZE - 1) / BLOCK_SIZE;
    if (nblocks == 1) {
        if (input_length != BLOCK_SIZE)
            return KRB5_BAD_MSIZE;
        return cbc_docrypt(key, NULL, data, num_data, DECRYPT_OP);
    } else {  /* nblocks > 1 */
        return cts_docrypt(key, ivec, data, num_data, input_length, nblocks,
                           DECRYPT_OP);
    }
}

/*
 * This function is based on the openssl enc_provider/camellia.c version.
 */
krb5_error_code
krb5int_camellia_cbc_mac(krb5_key key, const krb5_crypto_iov *data,
                         size_t num_data, const krb5_data *ivec,
                         krb5_data *output)
{
    unsigned char blockY[BLOCK_SIZE], blockB[BLOCK_SIZE];
    size_t        olen = BLOCK_SIZE;
    struct iov_cursor cursor;

    if (output->length < BLOCK_SIZE)
        return KRB5_BAD_MSIZE;

    if (ivec != NULL && ivec->data != NULL)
        memcpy(blockY, ivec->data, BLOCK_SIZE);
    else
        memset(blockY, 0, BLOCK_SIZE);

    k5_iov_cursor_init(&cursor, data, num_data, BLOCK_SIZE, FALSE);
    while (k5_iov_cursor_get(&cursor, blockB)) {
        xorblock(blockB, blockY);
        olen = sizeof(blockY);
        if (ucrypto_encrypt(CRYPTO_CAMELLIA_ECB,
                            key->keyblock.contents,
                            key->keyblock.length,
                            NULL, 0,
                            blockB, sizeof(blockB),
                            blockY, &olen) != CRYPTO_SUCCESS) {
            return KRB5_CRYPTO_INTERNAL;
        }
    }

    assert(olen == BLOCK_SIZE);
    output->length = BLOCK_SIZE;
    memcpy(output->data, blockY, BLOCK_SIZE);

    return 0;
}

static krb5_error_code
krb5int_camellia_init_state (const krb5_keyblock *key, krb5_keyusage usage,
                        krb5_data *state)
{
    state->data = calloc(1, BLOCK_SIZE);
    if (state->data == NULL)
        return ENOMEM;
    state->length = BLOCK_SIZE;
    return 0;
}

const struct krb5_enc_provider krb5int_enc_camellia128 = {
    BLOCK_SIZE,
    16, 16,
    krb5int_camellia_encrypt,
    krb5int_camellia_decrypt,
    krb5int_camellia_cbc_mac,
    krb5int_camellia_init_state,
    krb5int_default_free_state
};

const struct krb5_enc_provider krb5int_enc_camellia256 = {
    BLOCK_SIZE,
    32, 32,
    krb5int_camellia_encrypt,
    krb5int_camellia_decrypt,
    krb5int_camellia_cbc_mac,
    krb5int_camellia_init_state,
    krb5int_default_free_state
};
