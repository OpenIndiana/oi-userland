/*
 * Copyright (c) 2004, 2013, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * This product includes software developed by the OpenSSL Project for
 * use in the OpenSSL Toolkit (http://www.openssl.org/).
 *
 * This project also referenced hw_pkcs11-0.9.7b.patch written by
 * Afchine Madjlessi.
 */
/*
 * ====================================================================
 * Copyright (c) 2000-2001 The OpenSSL Project.  All rights reserved.
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
 * ====================================================================
 *
 * This product includes cryptographic software written by Eric Young
 * (eay@cryptsoft.com).  This product includes software written by Tim
 * Hudson (tjh@cryptsoft.com).
 *
 */

#ifndef	E_PK11_ERR_H
#define	E_PK11_ERR_H

#ifdef	__cplusplus
extern "C" {
#endif

void ERR_pk11_error(int function, int reason, char *file, int line);
void PK11err_add_data(int function, int reason, CK_RV rv);
#define	PK11err(f, r)	ERR_pk11_error((f), (r), __FILE__, __LINE__)

/* Error codes for the PK11 functions. */

/* Function codes. */

#define	PK11_F_INIT 				100
#define	PK11_F_FINISH				101
#define	PK11_F_DESTROY 				102
#define	PK11_F_CTRL 				103
#define	PK11_F_RSA_INIT 			104
#define	PK11_F_RSA_FINISH 			105
#define	PK11_F_GET_PUB_RSA_KEY 			106
#define	PK11_F_GET_PRIV_RSA_KEY 		107
#define	PK11_F_RSA_GEN_KEY 			108
#define	PK11_F_RSA_PUB_ENC 			109
#define	PK11_F_RSA_PRIV_ENC 			110
#define	PK11_F_RSA_PUB_DEC 			111
#define	PK11_F_RSA_PRIV_DEC 			112
#define	PK11_F_RSA_SIGN 			113
#define	PK11_F_RSA_VERIFY 			114
#define	PK11_F_RAND_ADD 			115
#define	PK11_F_RAND_BYTES 			116
#define	PK11_F_GET_SESSION 			117
#define	PK11_F_FREE_SESSION 			118
#define	PK11_F_LOAD_PUBKEY 			119
#define	PK11_F_LOAD_PRIVKEY 			120
#define	PK11_F_RSA_PUB_ENC_LOW 			121
#define	PK11_F_RSA_PRIV_ENC_LOW 		122
#define	PK11_F_RSA_PUB_DEC_LOW 			123
#define	PK11_F_RSA_PRIV_DEC_LOW 		124
#define	PK11_F_DSA_SIGN				125
#define	PK11_F_DSA_VERIFY			126
#define	PK11_F_DSA_INIT				127
#define	PK11_F_DSA_FINISH			128
#define	PK11_F_GET_PUB_DSA_KEY			129
#define	PK11_F_GET_PRIV_DSA_KEY 		130
#define	PK11_F_DH_INIT 				131
#define	PK11_F_DH_FINISH 			132
#define	PK11_F_MOD_EXP_DH 			133
#define	PK11_F_GET_DH_KEY 			134
#define	PK11_F_FREE_ALL_SESSIONS		135
#define	PK11_F_SETUP_SESSION			136
#define	PK11_F_DESTROY_OBJECT			137
#define	PK11_F_CIPHER_INIT			138
#define	PK11_F_CIPHER_DO_CIPHER			139
#define	PK11_F_GET_CIPHER_KEY			140
#define	PK11_F_DIGEST_INIT			141
#define	PK11_F_DIGEST_UPDATE			142
#define	PK11_F_DIGEST_FINAL			143
#define	PK11_F_CHOOSE_SLOT			144
#define	PK11_F_CIPHER_FINAL			145
#define	PK11_F_LIBRARY_INIT 			146
#define	PK11_F_LOAD 				147
#define	PK11_F_DH_GEN_KEY			148
#define	PK11_F_DH_COMP_KEY 			149
#define	PK11_F_DIGEST_COPY 			150
#define	PK11_F_CIPHER_CLEANUP			151
#define	PK11_F_ACTIVE_ADD			152
#define	PK11_F_ACTIVE_DELETE			153
#define	PK11_F_CHECK_HW_MECHANISMS		154
#define	PK11_F_INIT_SYMMETRIC			155
#define	PK11_F_ADD_AES_CTR_NIDS			156
#define	PK11_F_INIT_ALL_LOCKS			157
#define	PK11_F_RETURN_SESSION			158
#define	PK11_F_GET_PIN				159
#define	PK11_F_FIND_ONE_OBJECT 			160
#define	PK11_F_CHECK_TOKEN_ATTRS 		161
#define	PK11_F_CACHE_PIN			162
#define	PK11_F_MLOCK_PIN_IN_MEMORY		163
#define	PK11_F_TOKEN_LOGIN 			164
#define	PK11_F_TOKEN_RELOGIN 			165
#define	PK11_F_RUN_ASKPASS 			166

/* Reason codes. */
#define	PK11_R_ALREADY_LOADED 			100
#define	PK11_R_DSO_FAILURE 			101
#define	PK11_R_NOT_LOADED 			102
#define	PK11_R_PASSED_NULL_PARAMETER 		103
#define	PK11_R_COMMAND_NOT_IMPLEMENTED 		104
#define	PK11_R_INITIALIZE 			105
#define	PK11_R_FINALIZE 			106
#define	PK11_R_GETINFO 				107
#define	PK11_R_GETSLOTLIST 			108
#define	PK11_R_NO_MODULUS_OR_NO_EXPONENT 	109
#define	PK11_R_ATTRIBUT_SENSITIVE_OR_INVALID 	110
#define	PK11_R_GETATTRIBUTVALUE 		111
#define	PK11_R_NO_MODULUS 			112
#define	PK11_R_NO_EXPONENT 			113
#define	PK11_R_FINDOBJECTSINIT 			114
#define	PK11_R_FINDOBJECTS 			115
#define	PK11_R_FINDOBJECTSFINAL 		116
#define	PK11_R_CREATEOBJECT 			118
#define	PK11_R_DESTROYOBJECT 			119
#define	PK11_R_OPENSESSION 			120
#define	PK11_R_CLOSESESSION 			121
#define	PK11_R_ENCRYPTINIT 			122
#define	PK11_R_ENCRYPT 				123
#define	PK11_R_SIGNINIT 			124
#define	PK11_R_SIGN 				125
#define	PK11_R_DECRYPTINIT 			126
#define	PK11_R_DECRYPT 				127
#define	PK11_R_VERIFYINIT 			128
#define	PK11_R_VERIFY 				129
#define	PK11_R_VERIFYRECOVERINIT 		130
#define	PK11_R_VERIFYRECOVER 			131
#define	PK11_R_GEN_KEY 				132
#define	PK11_R_SEEDRANDOM 			133
#define	PK11_R_GENERATERANDOM 			134
#define	PK11_R_INVALID_MESSAGE_LENGTH 		135
#define	PK11_R_UNKNOWN_ALGORITHM_TYPE 		136
#define	PK11_R_UNKNOWN_ASN1_OBJECT_ID 		137
#define	PK11_R_UNKNOWN_PADDING_TYPE 		138
#define	PK11_R_PADDING_CHECK_FAILED 		139
#define	PK11_R_DIGEST_TOO_BIG 			140
#define	PK11_R_MALLOC_FAILURE 			141
#define	PK11_R_CTRL_COMMAND_NOT_IMPLEMENTED 	142
#define	PK11_R_DATA_GREATER_THAN_MOD_LEN 	143
#define	PK11_R_DATA_TOO_LARGE_FOR_MODULUS 	144
#define	PK11_R_MISSING_KEY_COMPONENT		145
#define	PK11_R_INVALID_SIGNATURE_LENGTH		146
#define	PK11_R_INVALID_DSA_SIGNATURE_R		147
#define	PK11_R_INVALID_DSA_SIGNATURE_S		148
#define	PK11_R_INCONSISTENT_KEY			149
#define	PK11_R_ENCRYPTUPDATE			150
#define	PK11_R_DECRYPTUPDATE			151
#define	PK11_R_DIGESTINIT			152
#define	PK11_R_DIGESTUPDATE			153
#define	PK11_R_DIGESTFINAL			154
#define	PK11_R_ENCRYPTFINAL			155
#define	PK11_R_DECRYPTFINAL			156
#define	PK11_R_NO_PRNG_SUPPORT			157
#define	PK11_R_GETTOKENINFO			158
#define	PK11_R_DERIVEKEY			159
#define	PK11_R_GET_OPERATION_STATE		160
#define	PK11_R_SET_OPERATION_STATE		161
#define	PK11_R_INVALID_HANDLE			162
#define	PK11_R_KEY_OR_IV_LEN_PROBLEM		163
#define	PK11_R_INVALID_OPERATION_TYPE		164
#define	PK11_R_ADD_NID_FAILED			165
#define	PK11_R_ATFORK_FAILED			166
#define	PK11_R_TOKEN_LOGIN_FAILED		167
#define	PK11_R_MORE_THAN_ONE_OBJECT_FOUND	168
#define	PK11_R_INVALID_PKCS11_URI		169
#define	PK11_R_COULD_NOT_READ_PIN		170
#define	PK11_R_COULD_NOT_OPEN_COMMAND		171
#define	PK11_R_PIPE_FAILED			172
#define	PK11_R_PIN_NOT_READ_FROM_COMMAND	173
#define	PK11_R_BAD_PASSPHRASE_SPEC		174
#define	PK11_R_TOKEN_NOT_INITIALIZED		175
#define	PK11_R_TOKEN_PIN_NOT_SET		176
#define	PK11_R_TOKEN_PIN_NOT_PROVIDED		177
#define	PK11_R_MISSING_OBJECT_LABEL		178
#define	PK11_R_TOKEN_ATTRS_DO_NOT_MATCH		179
#define	PK11_R_PRIV_KEY_NOT_FOUND		180
#define	PK11_R_NO_OBJECT_FOUND			181
#define	PK11_R_PIN_CACHING_POLICY_INVALID	182
#define	PK11_R_SYSCONF_FAILED			183
#define	PK11_R_MMAP_FAILED			183
#define	PK11_R_PRIV_PROC_LOCK_MEMORY_MISSING	184
#define	PK11_R_MLOCK_FAILED			185
#define	PK11_R_FORK_FAILED			186

#ifdef	__cplusplus
}
#endif
#endif /* E_PK11_ERR_H */
