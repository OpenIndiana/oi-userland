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
 *
 * Copyright (c) 2010, Oracle and/or its affiliates. All rights reserved.
 */

#pragma ident	"@(#)e_devcrypto.c	1.1	10/10/19 SMI"

#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <cryptoutil.h>
#include <sys/crypto/ioctl.h>
#include <sys/crypto/api.h>
#include <openssl/bio.h>
#include <openssl/aes.h>
#include <openssl/engine.h>
#include <security/cryptoki.h>

#define	DEVCRYPTO_LIB_NAME "devcrypto engine"
#include "e_devcrypto_err.c"

/* DEVCRYPTO CONTEXT */
typedef struct devcrypto_ctx {
	uint_t session_id;
} devcrypto_ctx_t;

/* Index for the supported ciphers */
typedef enum {
	DEV_DES_CBC,
	DEV_DES3_CBC,
	DEV_DES_ECB,
	DEV_DES3_ECB,
	DEV_RC4,
	DEV_AES_128_CBC,
	DEV_AES_192_CBC,
	DEV_AES_256_CBC,
	DEV_AES_128_ECB,
	DEV_AES_192_ECB,
	DEV_AES_256_ECB,
	DEV_BLOWFISH_CBC,
	DEV_AES_128_CTR,
	DEV_AES_192_CTR,
	DEV_AES_256_CTR,
	DEV_CIPHER_MAX
} DEV_CIPHER_ID;

typedef struct devcrypto_cipher {
	DEV_CIPHER_ID		id;
	int			nid;
	int			iv_len;
	int			min_key_len;
	int			max_key_len;
	CK_KEY_TYPE		key_type;
	CK_MECHANISM_TYPE	mech_type;
	crypto_mech_type_t	pn_internal_number;
} devcrypto_cipher_t;


/* Constants used when creating the ENGINE */
static const char *ENGINE_DEVCRYPTO_ID = "devcrypto";
static const char *ENGINE_DEVCRYPTO_NAME = "/dev/crypto engine support";
static const char *CRYPTO_DEVICE = "/dev/crypto";

/* static variables */
static int kernel_fd = -1;
static int kernel_fd_ref = 0;
static int slot_count = 0;
static CK_SLOT_ID *kernel_provider_id = NULL;
static int cipher_count = 0;
static int *cipher_nids = NULL;
pthread_mutex_t *kernel_fd_lock;

/*
 * NIDs for AES counter mode. They will be defined during the engine
 * initialization.
 */
static int NID_aes_128_ctr = NID_undef;
static int NID_aes_192_ctr = NID_undef;
static int NID_aes_256_ctr = NID_undef;

/*
 * Cipher Table for all supported symmetric ciphers.
 */
static devcrypto_cipher_t cipher_table[] = {
	{ DEV_DES_CBC,		NID_des_cbc,		8,	 8,   8,
		CKK_DES,	CKM_DES_CBC, CRYPTO_MECH_INVALID},
	{ DEV_DES3_CBC,		NID_des_ede3_cbc,	8,	24,  24,
		CKK_DES3,	CKM_DES3_CBC, CRYPTO_MECH_INVALID},
	{ DEV_DES_ECB,		NID_des_ecb,		0,	 8,   8,
		CKK_DES,	CKM_DES_ECB, CRYPTO_MECH_INVALID},
	{ DEV_DES3_ECB,		NID_des_ede3_ecb,	0,	24,  24,
		CKK_DES3,	CKM_DES3_ECB, CRYPTO_MECH_INVALID},
	{ DEV_RC4,		NID_rc4,		0,	16, 256,
		CKK_RC4,	CKM_RC4, CRYPTO_MECH_INVALID},
	{ DEV_AES_128_CBC,	NID_aes_128_cbc,	16,	16,  16,
		CKK_AES,	CKM_AES_CBC, CRYPTO_MECH_INVALID},
	{ DEV_AES_192_CBC,	NID_aes_192_cbc,	16,	24,  24,
		CKK_AES,	CKM_AES_CBC, CRYPTO_MECH_INVALID},
	{ DEV_AES_256_CBC,	NID_aes_256_cbc,	16,	32,  32,
		CKK_AES,	CKM_AES_CBC, CRYPTO_MECH_INVALID},
	{ DEV_AES_128_ECB,	NID_aes_128_ecb,	0,	16,  16,
		CKK_AES,	CKM_AES_ECB, CRYPTO_MECH_INVALID},
	{ DEV_AES_192_ECB,	NID_aes_192_ecb,	0,	24,  24,
		CKK_AES,	CKM_AES_ECB, CRYPTO_MECH_INVALID},
	{ DEV_AES_256_ECB,	NID_aes_256_ecb,	0,	32,  32,
		CKK_AES,	CKM_AES_ECB, CRYPTO_MECH_INVALID},
	{ DEV_BLOWFISH_CBC,	NID_bf_cbc,		8,	16,  16,
		CKK_BLOWFISH,	CKM_BLOWFISH_CBC, CRYPTO_MECH_INVALID},
	/*
	 * For the following 3 AES counter mode entries, we don't know the
	 * NIDs until the engine is initialized
	 */
	{ DEV_AES_128_CTR,	NID_undef,		16,	16,  16,
		CKK_AES,	CKM_AES_CTR, CRYPTO_MECH_INVALID},
	{ DEV_AES_192_CTR,	NID_undef,		16,	24,  24,
		CKK_AES,	CKM_AES_CTR, CRYPTO_MECH_INVALID},
	{ DEV_AES_256_CTR,	NID_undef,		16,	32,  32,
		CKK_AES,	CKM_AES_CTR, CRYPTO_MECH_INVALID},
	};


/* Formal declaration for functions in EVP_CIPHER structure */
static int devcrypto_cipher_init(EVP_CIPHER_CTX *, const unsigned char *,
    const unsigned char *, int);
static int devcrypto_cipher_do_cipher(EVP_CIPHER_CTX *, unsigned char *,
    const unsigned char *, unsigned int);
static int devcrypto_cipher_cleanup(EVP_CIPHER_CTX *);

/* OpenSSL's libcrypto EVP stuff. This is how this engine gets wired to EVP. */
static const EVP_CIPHER dev_des_cbc = {
	NID_des_cbc,
	8, 8, 8,
	EVP_CIPH_CBC_MODE,
	devcrypto_cipher_init,
	devcrypto_cipher_do_cipher,
	devcrypto_cipher_cleanup,
	sizeof (devcrypto_ctx_t),
	EVP_CIPHER_set_asn1_iv,
	EVP_CIPHER_get_asn1_iv,
	NULL
};

static const EVP_CIPHER dev_3des_cbc = {
	NID_des_ede3_cbc,
	8, 24, 8,
	EVP_CIPH_CBC_MODE,
	devcrypto_cipher_init,
	devcrypto_cipher_do_cipher,
	devcrypto_cipher_cleanup,
	sizeof (devcrypto_ctx_t),
	EVP_CIPHER_set_asn1_iv,
	EVP_CIPHER_get_asn1_iv,
	NULL
};

/*
 * ECB modes don't use an Initial Vector, therefore set_asn1_parameters and
 * get_asn1_parameters fields are set to NULL.
 */
static const EVP_CIPHER dev_des_ecb = {
	NID_des_ecb,
	8, 8, 8,
	EVP_CIPH_ECB_MODE,
	devcrypto_cipher_init,
	devcrypto_cipher_do_cipher,
	devcrypto_cipher_cleanup,
	sizeof (devcrypto_ctx_t),
	NULL,
	NULL,
	NULL
};

static const EVP_CIPHER dev_3des_ecb = {
	NID_des_ede3_ecb,
	8, 24, 8,
	EVP_CIPH_ECB_MODE,
	devcrypto_cipher_init,
	devcrypto_cipher_do_cipher,
	devcrypto_cipher_cleanup,
	sizeof (devcrypto_ctx_t),
	NULL,
	NULL,
	NULL
};

static const EVP_CIPHER dev_rc4 = {
	NID_rc4,
	1, 16, 0,
	EVP_CIPH_VARIABLE_LENGTH,
	devcrypto_cipher_init,
	devcrypto_cipher_do_cipher,
	devcrypto_cipher_cleanup,
	sizeof (devcrypto_ctx_t),
	NULL,
	NULL,
	NULL
};

static const EVP_CIPHER dev_aes_128_cbc = {
	NID_aes_128_cbc,
	16, 16, 16,
	EVP_CIPH_CBC_MODE,
	devcrypto_cipher_init,
	devcrypto_cipher_do_cipher,
	devcrypto_cipher_cleanup,
	sizeof (devcrypto_ctx_t),
	EVP_CIPHER_set_asn1_iv,
	EVP_CIPHER_get_asn1_iv,
	NULL
};

static const EVP_CIPHER dev_aes_192_cbc = {
	NID_aes_192_cbc,
	16, 24, 16,
	EVP_CIPH_CBC_MODE,
	devcrypto_cipher_init,
	devcrypto_cipher_do_cipher,
	devcrypto_cipher_cleanup,
	sizeof (devcrypto_ctx_t),
	EVP_CIPHER_set_asn1_iv,
	EVP_CIPHER_get_asn1_iv,
	NULL
};

static const EVP_CIPHER dev_aes_256_cbc = {
	NID_aes_256_cbc,
	16, 32, 16,
	EVP_CIPH_CBC_MODE,
	devcrypto_cipher_init,
	devcrypto_cipher_do_cipher,
	devcrypto_cipher_cleanup,
	sizeof (devcrypto_ctx_t),
	EVP_CIPHER_set_asn1_iv,
	EVP_CIPHER_get_asn1_iv,
	NULL
};


/*
 * ECB modes don't use IV, therefore set_asn1_parameters and
 * get_asn1_parameters are set to NULL.
 */
static const EVP_CIPHER dev_aes_128_ecb = {
	NID_aes_128_ecb,
	16, 16, 0,
	EVP_CIPH_ECB_MODE,
	devcrypto_cipher_init,
	devcrypto_cipher_do_cipher,
	devcrypto_cipher_cleanup,
	sizeof (devcrypto_ctx_t),
	NULL,
	NULL,
	NULL
};

static const EVP_CIPHER dev_aes_192_ecb = {
	NID_aes_192_ecb,
	16, 24, 0,
	EVP_CIPH_ECB_MODE,
	devcrypto_cipher_init,
	devcrypto_cipher_do_cipher,
	devcrypto_cipher_cleanup,
	sizeof (devcrypto_ctx_t),
	NULL,
	NULL,
	NULL
};

static const EVP_CIPHER dev_aes_256_ecb = {
	NID_aes_256_ecb,
	16, 32, 0,
	EVP_CIPH_ECB_MODE,
	devcrypto_cipher_init,
	devcrypto_cipher_do_cipher,
	devcrypto_cipher_cleanup,
	sizeof (devcrypto_ctx_t),
	NULL,
	NULL,
	NULL
};

static const EVP_CIPHER dev_bf_cbc = {
	NID_bf_cbc,
	8, 16, 8,
	EVP_CIPH_VARIABLE_LENGTH,
	devcrypto_cipher_init,
	devcrypto_cipher_do_cipher,
	devcrypto_cipher_cleanup,
	sizeof (devcrypto_ctx_t),
	EVP_CIPHER_set_asn1_iv,
	EVP_CIPHER_get_asn1_iv,
	NULL
};


/*
 * NID_undef's will be changed for AES counter mode, as soon they are created.
 */
static EVP_CIPHER dev_aes_128_ctr = {
	NID_undef,
	16, 16, 16,
	EVP_CIPH_CBC_MODE,
	devcrypto_cipher_init,
	devcrypto_cipher_do_cipher,
	devcrypto_cipher_cleanup,
	sizeof (devcrypto_ctx_t),
	EVP_CIPHER_set_asn1_iv,
	EVP_CIPHER_get_asn1_iv,
	NULL
};

static EVP_CIPHER dev_aes_192_ctr = {
	NID_undef,
	16, 24, 16,
	EVP_CIPH_CBC_MODE,
	devcrypto_cipher_init,
	devcrypto_cipher_do_cipher,
	devcrypto_cipher_cleanup,
	sizeof (devcrypto_ctx_t),
	EVP_CIPHER_set_asn1_iv,
	EVP_CIPHER_get_asn1_iv,
	NULL
};

static EVP_CIPHER dev_aes_256_ctr = {
	NID_undef,
	16, 32, 16,
	EVP_CIPH_CBC_MODE,
	devcrypto_cipher_init,
	devcrypto_cipher_do_cipher,
	devcrypto_cipher_cleanup,
	sizeof (devcrypto_ctx_t),
	EVP_CIPHER_set_asn1_iv,
	EVP_CIPHER_get_asn1_iv,
	NULL
};



/*
 * This function creates a new NID.
 */
static int
devcrypto_add_NID(char *sn, char *ln)
{
	ASN1_OBJECT *o;
	int nid;

	if ((o = ASN1_OBJECT_create(OBJ_new_nid(1), (unsigned char *)"",
	    1, sn, ln)) == NULL) {
		return (0);
	}

	nid = OBJ_add_object(o); /* will return NID_undef on error */
	ASN1_OBJECT_free(o);
	return (nid);
}


/*
 * This function creates new NIDs for AES counter mode algorithms.
 * Note that OpenSSL doesn't support them now so we have to help
 * ourselves here.
 */
static int
devcrypto_add_aes_ctr_NIDs(void)
{
	if (NID_aes_256_ctr != NID_undef) /* already set */
		return (1);

	NID_aes_128_ctr = devcrypto_add_NID("AES-128-CTR", "aes-128-ctr");
	if (NID_aes_128_ctr == NID_undef)
		goto failed;
	cipher_table[DEV_AES_128_CTR].nid =
	    dev_aes_128_ctr.nid = NID_aes_128_ctr;

	NID_aes_192_ctr = devcrypto_add_NID("AES-192-CTR", "aes-192-ctr");
	if (NID_aes_192_ctr == NID_undef)
		goto failed;
	cipher_table[DEV_AES_192_CTR].nid =
	    dev_aes_192_ctr.nid = NID_aes_192_ctr;

	NID_aes_256_ctr = devcrypto_add_NID("AES-256-CTR", "aes-256-ctr");
	if (NID_aes_256_ctr == NID_undef)
		goto failed;
	cipher_table[DEV_AES_256_CTR].nid =
	    dev_aes_256_ctr.nid = NID_aes_256_ctr;

	return (1);

failed:
	return (0);
}


static void
devcrypto_free_aes_ctr_NIDs(void)
{
	ASN1_OBJECT *ob = NULL;

	if (NID_aes_128_ctr != NID_undef) {
		ob = OBJ_nid2obj(NID_aes_128_ctr);
		if (ob != NULL)
			ASN1_OBJECT_free(ob);
	}

	if (NID_aes_192_ctr != NID_undef) {
		ob = OBJ_nid2obj(NID_aes_192_ctr);
		if (ob != NULL)
			ASN1_OBJECT_free(ob);
	}

	if (NID_aes_256_ctr != NID_undef) {
		ob = OBJ_nid2obj(NID_aes_256_ctr);
		if (ob != NULL)
		ASN1_OBJECT_free(ob);
	}
}

/*
 * Open the /dev/crypto device
 */
static int
devcrypto_open()
{
	int fd = -1;

	if (kernel_fd != -1) {  /* already open */
		(void) pthread_mutex_lock(kernel_fd_lock);
		kernel_fd_ref++;
		(void) pthread_mutex_unlock(kernel_fd_lock);
		return (1);
	}

	(void) pthread_mutex_lock(kernel_fd_lock);
	fd = open(CRYPTO_DEVICE, O_RDWR);
	if (fd == -1) {
#ifdef DEBUG
		(void) fprintf(stderr,
		    "libdevcrypto: open /dev/crypto failed, errno=%x\n",
		    errno);
#endif
		(void) pthread_mutex_unlock(kernel_fd_lock);
		return (0);
	}

	if (fcntl(fd, F_SETFD, FD_CLOEXEC) != 0) {
#ifdef DEBUG
		(void) fprintf(stderr, "libdevcrypto: failed to fcntl\n");
#endif
		(void) close(fd);
		(void) pthread_mutex_unlock(kernel_fd_lock);
		return (0);
	}

	kernel_fd = fd;
	kernel_fd_ref++;
	(void) pthread_mutex_unlock(kernel_fd_lock);
	return (1);
}


/*
 * This function gets the total number of hardware providers presented in
 * the system first.  If there is any hardware providers, then it will get
 * the kernel provider id for each hardware slot also.
 */
static int
devcrypto_get_slot_info()
{
	crypto_get_provider_list_t *pl = NULL;
	int ret = 1;
	int r;
	int i;

	/* Already have the information */
	if (kernel_provider_id != NULL)
		return (1);

	/* Find out how many hardware slots are presented. */
	pl = OPENSSL_malloc(sizeof (crypto_get_provider_list_t));
	if (pl == NULL)
		return (0);

	pl->pl_count = 0;
	while ((r = ioctl(kernel_fd, CRYPTO_GET_PROVIDER_LIST, pl)) < 0) {
		if (errno != EINTR)
			break;
	}
	if (r < 0 || pl->pl_return_value != CRYPTO_SUCCESS) {
#ifdef DEBUG
		(void) fprintf(stderr, "libdevcrypto:CRYPTO_GET_PROVIDER_LIST:"
		    "ret (r) = 0x%x, (rv) = 0x%x\n", r,  pl->pl_return_value);
#endif /* DEBUG */
		ret = 0;
		goto out;
	}

	slot_count = pl->pl_count;
	if (slot_count == 0) {
#ifdef DEBUG
		(void) fprintf(stderr, "libdevcrypto: no hw providers\n");
#endif /* DEBUG */
		ret = 0;
		goto out;
	}

	/* Get the provider ID for each slot from kernel and save it */
	kernel_provider_id = OPENSSL_malloc(sizeof (CK_SLOT_ID) * slot_count);
	if (kernel_provider_id == NULL) {
		ret = 0;
		goto out;
	}

	(void) OPENSSL_free(pl);
	pl = OPENSSL_malloc(slot_count * sizeof (crypto_get_provider_list_t));
	if (pl == NULL) {
		ret = 0;
		goto out;
	}

	pl->pl_count = slot_count;
	while ((r = ioctl(kernel_fd, CRYPTO_GET_PROVIDER_LIST, pl)) < 0) {
		if (errno != EINTR)
			break;
	}
	if (r < 0 || (pl->pl_return_value != CRYPTO_SUCCESS)) {
#ifdef DEBUG
		(void) fprintf(stderr, "libdevcrypto:CRYPTO_GET_PROVIDER_LIST:"
		    "ret (r) = 0x%x, (rv) = 0x%x\n", r,  pl->pl_return_value);
#endif /* DEBUG */
		ret = 0;
		goto out;
	}

	for (i = 0; i < slot_count; i++) {
		kernel_provider_id[i] = pl->pl_list[i].pe_provider_id;
#ifdef DEBUG
		(void) fprintf(stderr, "libdevcrypto: i = %d, "
		    "kernel_provider_id = %d\n", i, kernel_provider_id[i]);
#endif /* DEBUG */
	}

out:
	if (pl != NULL)
		(void) OPENSSL_free(pl);

	if (ret == 0 && kernel_provider_id != NULL) {
		(void) OPENSSL_free(kernel_provider_id);
		kernel_provider_id = NULL;
	}

	return (ret);
}


/*
 * This function checks if the "nid" is already in the nid list.
 */
static int
nid_in_list(int nid, int *nid_list, int count)
{
	int i = 0;

	if (nid_list == NULL || count <= 0)
		return (0);

	while (i < count) {
		if (nid == nid_list[i])
			break;
		i++;
	}
	return (i < count ? 1 : 0);
}

/*
 * This function is to get all the ciphers supported by hardware providers.
 * If this function is successfully completed, then the following 2 global
 * variables will be set.
 * cipher_count - the number of ciphers found in all hardware providers.
 * cipher_nids - the nid list for all the ciphers.
 */
static int
devcrypto_get_hw_ciphers(void)
{
	crypto_get_provider_mechanism_info_t mechinfo;
	int max_cipher_count;
	int *tmp_nids = NULL;
	const char *mech_string;
	int r;
	int i, j;

	if (slot_count <= 0)  /* no hardware provider */
		return (0);

	max_cipher_count = slot_count * DEV_CIPHER_MAX + 1;
	tmp_nids = OPENSSL_malloc(max_cipher_count * sizeof (int));
	if (tmp_nids == NULL) {
		/* not enough memory */
		goto failed;
	}

	for (i = 0; i < slot_count; i++) {
		mechinfo.mi_provider_id = kernel_provider_id[i];
		for (j = 0; j < DEV_CIPHER_MAX; j++) {
			mech_string =
			    pkcs11_mech2str(cipher_table[j].mech_type);
			if (mech_string == NULL) {
				continue; /* shouldn't happen; skip it */
			}

			(void) strlcpy(mechinfo.mi_mechanism_name,
			    mech_string, CRYPTO_MAX_MECH_NAME);
			while ((r = ioctl(kernel_fd,
			    CRYPTO_GET_PROVIDER_MECHANISM_INFO,
			    &mechinfo)) < 0) {
				if (errno != EINTR)
					break;
			}
			if (r < 0) {
				goto failed;
			}

			if (mechinfo.mi_return_value == CRYPTO_SUCCESS) {
				/*
				 * Found this mechanism in hardware providers.
				 * If it is not in the nid list yet, add it.
				 */
				if (!nid_in_list(cipher_table[j].nid,
				    tmp_nids, cipher_count)) {
					tmp_nids[cipher_count] =
					    cipher_table[j].nid;
					cipher_count++;
				}
			}
		}
	}

	if (cipher_count > 0) {
		cipher_nids = tmp_nids;
	}

	return (1);

failed:
	if (r < 0 || cipher_count == 0) {
		if (tmp_nids != NULL)
			OPENSSL_free(tmp_nids);
	}
	return (0);
}

/*
 * Registered by the ENGINE when used to find out how to deal with
 * a particular NID in the ENGINE. This says what we'll do at the
 * top level - note, that list is restricted by what we answer with.
 */
static int
devcrypto_get_all_ciphers(ENGINE *e, const EVP_CIPHER **cipher,
    const int **nids, int nid)
{
	if (!cipher) {
		*nids = (cipher_count > 0) ? cipher_nids : NULL;
		return (cipher_count);
	}

	switch (nid) {
	case NID_des_cbc:
	*cipher = &dev_des_cbc;
		break;
	case NID_des_ede3_cbc:
		*cipher = &dev_3des_cbc;
		break;
	case NID_des_ecb:
		*cipher = &dev_des_ecb;
		break;
	case NID_des_ede3_ecb:
		*cipher = &dev_3des_ecb;
		break;
	case NID_rc4:
		*cipher = &dev_rc4;
		break;
	case NID_aes_128_cbc:
		*cipher = &dev_aes_128_cbc;
		break;
	case NID_aes_192_cbc:
		*cipher = &dev_aes_192_cbc;
		break;
	case NID_aes_256_cbc:
		*cipher = &dev_aes_256_cbc;
		break;
	case NID_aes_128_ecb:
		*cipher = &dev_aes_128_ecb;
		break;
	case NID_aes_192_ecb:
		*cipher = &dev_aes_192_ecb;
		break;
	case NID_aes_256_ecb:
		*cipher = &dev_aes_256_ecb;
		break;
	case NID_bf_cbc:
		*cipher = &dev_bf_cbc;
		break;
	default:
		/*
		 * We cannot put the NIDs for AES counter mode in separated
		 * cases as above because they are not constants.
		 */
		if (nid == NID_aes_128_ctr)
			*cipher = &dev_aes_128_ctr;
		else if (nid == NID_aes_192_ctr)
			*cipher = &dev_aes_192_ctr;
		else if (nid == NID_aes_256_ctr)
			*cipher = &dev_aes_256_ctr;
		else
			*cipher = NULL;
		break;
	}

	return (*cipher != NULL);
}


static int
get_cipher_id_by_nid(int nid)
{
	int i;

	for (i = 0; i < DEV_CIPHER_MAX; i++)
		if (cipher_table[i].nid == nid)
			return (cipher_table[i].id);
	return (-1);
}


static int
get_slotid_by_mechanism(const char *mech_string, CK_SLOT_ID *slot_id)
{
	crypto_get_provider_mechanism_info_t mechanism_info;
	uint_t rv;
	int r;
	int i = 0;

	(void) strlcpy(mechanism_info.mi_mechanism_name, mech_string,
	    CRYPTO_MAX_MECH_NAME);
	while (i < slot_count) {
		mechanism_info.mi_provider_id = kernel_provider_id[i];
		while ((r = ioctl(kernel_fd,
		    CRYPTO_GET_PROVIDER_MECHANISM_INFO,
		    &mechanism_info)) < 0) {
			if (errno != EINTR)
				break;
		}
		if (r < 0) {
			return (0); /* ioctl function failed */
		}
		rv = mechanism_info.mi_return_value;
		if (rv == 0) { /* found it */
			*slot_id = kernel_provider_id[i];
			return (1);
		}
		i++;
	}

	return (0);
}


static int
devcrypto_cipher_init(EVP_CIPHER_CTX *ctx, const unsigned char *key,
    const unsigned char *iv, int enc)
{
	devcrypto_ctx_t *devc_ctx = ctx->cipher_data;
	crypto_encrypt_init_t encrypt_init;
	crypto_decrypt_init_t decrypt_init;
	crypto_open_session_t session;
	crypto_get_mechanism_number_t get_number;
	CK_AES_CTR_PARAMS aes_ctr_params;
	devcrypto_cipher_t *the_cipher;
	const char *mech_string;
	CK_SLOT_ID slot_id;
	int index;
	int r;
	uint_t rv = 0;


	if (key == NULL) {
		DEVCRYPTOerr(DEVC_F_CIPHER_INIT, DEVC_R_CIPHER_KEY);
		return (0);
	}

	/* get the cipher entry index in cipher_table from nid */
	index = get_cipher_id_by_nid(ctx->cipher->nid);
	if (index < 0 || index >= DEV_CIPHER_MAX) {
		DEVCRYPTOerr(DEVC_F_CIPHER_INIT, DEVC_R_CIPHER_NID);
		return (0);
	}
	the_cipher = &cipher_table[index];

	/* check key size */
	if (ctx->cipher->iv_len < the_cipher->iv_len ||
	    ctx->key_len < the_cipher->min_key_len ||
	    ctx->key_len > the_cipher->max_key_len) {
		DEVCRYPTOerr(DEVC_F_CIPHER_INIT, DEVC_R_KEY_OR_IV_LEN_PROBLEM);
		return (0);
	}

	/* get the mechanism string */
	mech_string = pkcs11_mech2str(the_cipher->mech_type);
	if (mech_string == NULL) {
		DEVCRYPTOerr(DEVC_F_CIPHER_INIT, DEVC_R_MECH_STRING);
		return (0);
	}

#ifdef DEBUG
	(void) fprintf(stderr, "libdevcrypto: mech_string=%s\n", mech_string);
#endif

	/* Find the slot that supports this mechanism */
	if (!get_slotid_by_mechanism(mech_string, &slot_id)) {
		DEVCRYPTOerr(DEVC_F_CIPHER_INIT, DEVC_R_FIND_SLOT_BY_MECH);
#ifdef DEBUG
		(void) fprintf(stderr,
		    "libdevcrypto: failed to find a slot with %s\n",
		    mech_string);
#endif
		return (0);
	}

#ifdef DEBUG
	(void) fprintf(stderr, "libdevcrypto: found a slot with %s, "
	    "slot_id = %d\n", mech_string, slot_id);
#endif

	/* Open a session on this slot */
	session.os_provider_id = slot_id;
	session.os_flags = CKF_RW_SESSION | CKF_SERIAL_SESSION;
	while ((r = ioctl(kernel_fd, CRYPTO_OPEN_SESSION, &session)) < 0) {
		if (errno != EINTR)
			break;
	}
	rv = session.os_return_value;
	if (r || rv) {
		DEVCRYPTOerr(DEVC_F_CIPHER_INIT, DEVC_R_OPEN_SESSION);
#ifdef DEBUG
		(void) fprintf(stderr,
		    "libdevcrypto:cipher_init:failed to open a session\n");
#endif /* DEBUG */
		goto failed;
	}

#ifdef DEBUG
	(void) fprintf(stderr, "libdevcrypto:cipher_init: open session = %d\n",
	    session.os_session);
#endif /* DEBUG */

	/* save the session_id */
	devc_ctx->session_id = session.os_session;

	/*
	 * Get the kernel mechanism number for this mechanism, if it has not
	 * been retrieved yet.
	 */
	if (the_cipher->pn_internal_number == CRYPTO_MECH_INVALID) {
		get_number.pn_mechanism_string = (char *)mech_string;
		get_number.pn_mechanism_len = strlen(mech_string) + 1;
		while ((r = ioctl(kernel_fd, CRYPTO_GET_MECHANISM_NUMBER,
		    &get_number)) < 0) {
			if (errno != EINTR)
				break;
		}
		rv = get_number.pn_return_value;
		if (r || rv) {
			DEVCRYPTOerr(DEVC_F_CIPHER_INIT,
			    DEVC_R_GET_MECHANISM_NUMBER);
#ifdef DEBUG
			(void) fprintf(stderr, "libdevcrypto:cipher_init: "
			    "failed to get the kernel mech number.\n");
#endif /* DEBUG */
			goto failed;
		}

		the_cipher->pn_internal_number = get_number.pn_internal_number;
	}

	/* Crypto Init */
	if (ctx->encrypt) {
		encrypt_init.ei_session = session.os_session;
		encrypt_init.ei_key.ck_format = CRYPTO_KEY_RAW;
		encrypt_init.ei_key.ck_obj_id = 0;
		encrypt_init.ei_key.ck_data = (void *) key;
		encrypt_init.ei_key.ck_length = ctx->key_len * 8;
		encrypt_init.ei_mech.cm_type = the_cipher->pn_internal_number;

		if (ctx->cipher->nid == NID_aes_128_ctr ||
		    ctx->cipher->nid == NID_aes_192_ctr ||
		    ctx->cipher->nid == NID_aes_256_ctr) {
			encrypt_init.ei_mech.cm_param =
			    (void *) (&aes_ctr_params);
			encrypt_init.ei_mech.cm_param_len =
			    sizeof (aes_ctr_params);

			aes_ctr_params.ulCounterBits = AES_BLOCK_SIZE * 8;
			OPENSSL_assert(ctx->cipher->iv_len == AES_BLOCK_SIZE);
			(void) memcpy(aes_ctr_params.cb, ctx->iv,
			    AES_BLOCK_SIZE);
		} else {
			if (the_cipher->iv_len > 0) {
				encrypt_init.ei_mech.cm_param =
				    (char *)ctx->iv;
				encrypt_init.ei_mech.cm_param_len =
				    ctx->cipher->iv_len;
			} else {
				encrypt_init.ei_mech.cm_param = NULL;
				encrypt_init.ei_mech.cm_param_len = 0;
			}
		}

		while ((r = ioctl(kernel_fd, CRYPTO_ENCRYPT_INIT,
		    &encrypt_init)) < 0) {
			if (errno != EINTR)
				break;
		}
		rv = encrypt_init.ei_return_value;

	} else {
		decrypt_init.di_session = session.os_session;
		decrypt_init.di_key.ck_format = CRYPTO_KEY_RAW;
		decrypt_init.di_key.ck_obj_id = 0;
		decrypt_init.di_key.ck_data = (void *) key;
		decrypt_init.di_key.ck_length = ctx->key_len * 8;
		decrypt_init.di_mech.cm_type = the_cipher->pn_internal_number;

		if (ctx->cipher->nid == NID_aes_128_ctr ||
		    ctx->cipher->nid == NID_aes_192_ctr ||
		    ctx->cipher->nid == NID_aes_256_ctr) {
			decrypt_init.di_mech.cm_param =
			    (void *)(&aes_ctr_params);
			decrypt_init.di_mech.cm_param_len =
			    sizeof (aes_ctr_params);
			aes_ctr_params.ulCounterBits = AES_BLOCK_SIZE * 8;
			OPENSSL_assert(ctx->cipher->iv_len == AES_BLOCK_SIZE);
			(void) memcpy(aes_ctr_params.cb, ctx->iv,
			    AES_BLOCK_SIZE);
		} else {
			if (the_cipher->iv_len > 0) {
				decrypt_init.di_mech.cm_param =
				    (char *)ctx->iv;
				decrypt_init.di_mech.cm_param_len =
				    ctx->cipher->iv_len;
			} else {
				decrypt_init.di_mech.cm_param = NULL;
				decrypt_init.di_mech.cm_param_len = 0;
			}
		}

		while ((r = ioctl(kernel_fd, CRYPTO_DECRYPT_INIT,
		    &decrypt_init)) < 0) {
			if (errno != EINTR)
				break;
		}
		rv = decrypt_init.di_return_value;
	}

failed:
	if (r || rv) {
		if (ctx->encrypt)
			DEVCRYPTOerr(DEVC_F_CIPHER_INIT, DEVC_R_ENCRYPT_INIT);
		else
			DEVCRYPTOerr(DEVC_F_CIPHER_INIT, DEVC_R_DECRYPT_INIT);

		return (0);
	}

	return (1);
}


/*
 * ENCRYPT_UPDATE or DECRYPT_UPDATE
 */
static int
devcrypto_cipher_do_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, unsigned int inl)
{
	crypto_encrypt_update_t encrypt_update;
	crypto_decrypt_update_t decrypt_update;
	devcrypto_ctx_t *devc_ctx = ctx->cipher_data;
	int r = 0, rv = 0;

	if (ctx->encrypt) {
		encrypt_update.eu_session = devc_ctx->session_id;
		encrypt_update.eu_databuf = (char *)in;
		encrypt_update.eu_datalen = inl;
		encrypt_update.eu_encrbuf = (char *)out;
		encrypt_update.eu_encrlen = inl;

		while ((r = ioctl(kernel_fd, CRYPTO_ENCRYPT_UPDATE,
		    &encrypt_update)) < 0) {
			if (errno != EINTR)
				break;
		}
		rv = encrypt_update.eu_return_value;

	} else { /* decrypt */
		decrypt_update.du_session = devc_ctx->session_id;
		decrypt_update.du_encrbuf = (char *)in;
		decrypt_update.du_encrlen = inl;
		decrypt_update.du_databuf = (char *)out;
		decrypt_update.du_datalen = inl;

		while ((r = ioctl(kernel_fd, CRYPTO_DECRYPT_UPDATE,
		    &decrypt_update)) < 0) {
			if (errno != EINTR)
				break;
		}
		rv = decrypt_update.du_return_value;
	}

	if (r || rv) {
		if (ctx->encrypt)
			DEVCRYPTOerr(DEVC_F_CIPHER_DO_CIPHER,
			    DEVC_R_ENCRYPT_UPDATE);
		else
			DEVCRYPTOerr(DEVC_F_CIPHER_DO_CIPHER,
			    DEVC_R_DECRYPT_UPDATE);

#ifdef DEBUG
		(void) fprintf(stderr, "libdevcrypto:crypto_do ret (r) = 0x%x,"
		    "crypto ret (rv) = 0x%x,", r, rv);
#endif /* DEBUG */
		return (0);
	}

	return (1);
}


/*
 * ENCRYPT_FINAL or DECRYPT_FINAL
 */
static int
devcrypto_cipher_cleanup(EVP_CIPHER_CTX *ctx)
{
	crypto_encrypt_final_t encrypt_final;
	crypto_decrypt_final_t decrypt_final;
	crypto_close_session_t session;
	devcrypto_ctx_t *devc_ctx = ctx->cipher_data;
	char buf[EVP_MAX_BLOCK_LENGTH];
	int r;
	uint_t rv = 0;
	int ret = 1;

	if (ctx->encrypt) {
		encrypt_final.ef_session = devc_ctx->session_id;
		encrypt_final.ef_encrbuf = buf;
		encrypt_final.ef_encrlen = sizeof (buf);
		while ((r = ioctl(kernel_fd, CRYPTO_ENCRYPT_FINAL,
		    &encrypt_final)) < 0) {
			if (errno != EINTR)
				break;
		}
		rv = encrypt_final.ef_return_value;

	} else {
		decrypt_final.df_session = devc_ctx->session_id;
		decrypt_final.df_databuf = buf;
		decrypt_final.df_datalen = sizeof (buf);
		while ((r = ioctl(kernel_fd, CRYPTO_DECRYPT_FINAL,
		    &decrypt_final)) < 0) {
			if (errno != EINTR)
				break;
		}
		rv = decrypt_final.df_return_value;
	}

#ifdef DEBUG
	if (ctx->encrypt)
		(void) fprintf(stderr, "libdevcrypto:CRYPTO_ENCRYPT_FINAL "
		    "ret (r) = 0x%x, (rv) = 0x%x\n", r, rv);
	else
		(void) fprintf(stderr, "libdevcrypto:CRYPTO_DECRYPT_FINAL "
		    "ret (r) = 0x%x, (rv) = 0x%x\n", r, rv);
#endif /* DEBUG */

	if (r || rv) {
		if (ctx->encrypt)
			DEVCRYPTOerr(DEVC_F_CIPHER_CLEANUP,
			    DEVC_R_ENCRYPT_FINAL);
		else
			DEVCRYPTOerr(DEVC_F_CIPHER_CLEANUP,
			    DEVC_R_DECRYPT_FINAL);
		ret = 0;
	}

	/* close the session */
	session.cs_session = devc_ctx->session_id;
	while ((r = ioctl(kernel_fd, CRYPTO_CLOSE_SESSION, &session)) < 0) {
		if (errno != EINTR)
			break;
	}

#ifdef DEBUG
	(void) fprintf(stderr, "libdevcrypto:CRYPTO_CLOSE_SESSION, "
	    "session id = %d ret (r) = 0x%x, crypto ret (rv) = 0x%x\n",
	    devc_ctx->session_id, r, rv);
#endif /* DEBUG */

	if (r || rv) {
		DEVCRYPTOerr(DEVC_F_CIPHER_CLEANUP, DEVC_R_CLOSE_SESSION);
		ret = 0;
	}

	return (ret);
}

static void
devcrypto_cleanup()
{
	if (kernel_fd == -1)
		return;

	(void) pthread_mutex_lock(kernel_fd_lock);
	kernel_fd_ref--;
	(void) pthread_mutex_unlock(kernel_fd_lock);

	if (kernel_fd_ref == 0) {
		(void) pthread_mutex_lock(kernel_fd_lock);
		(void) close(kernel_fd);
		kernel_fd = -1;
		if (kernel_provider_id != NULL) {
			OPENSSL_free(kernel_provider_id);
			kernel_provider_id = NULL;
		}
		if (cipher_nids != NULL) {
			OPENSSL_free(cipher_nids);
			cipher_nids = NULL;
		}
		devcrypto_free_aes_ctr_NIDs();
		(void) pthread_mutex_unlock(kernel_fd_lock);
		(void) pthread_mutex_destroy(kernel_fd_lock);
		OPENSSL_free(kernel_fd_lock);
		kernel_fd_lock = NULL;
	}
}

static int
devcrypto_destroy(ENGINE *e)
{
	ERR_unload_devcrypto_strings();
	return (1);
}

static int
devcrypto_finish(ENGINE *e)
{
	devcrypto_cleanup();
	return (1);
}

/*
 * Set up the engine info and get the /dev/crypto engine ready.
 */
static int
devcrypto_bind(ENGINE *e)
{
#ifdef DEBUG
	int i;
#endif

	/* Get the NIDs for AES counter mode algorithms first. */
	if (devcrypto_add_aes_ctr_NIDs() == 0) {
		return (0);
	}

	/* Create a lock for the devcrypto device file descriptor */
	if (kernel_fd_lock == NULL) {
		kernel_fd_lock = OPENSSL_malloc(sizeof (pthread_mutex_t));
		if (kernel_fd_lock == NULL) {
			devcrypto_free_aes_ctr_NIDs();
			return (0);
		}

		if (pthread_mutex_init(kernel_fd_lock, NULL) != 0) {
			devcrypto_free_aes_ctr_NIDs();
			OPENSSL_free(kernel_fd_lock);
			kernel_fd_lock = NULL;
			return (0);
		}
	}

	/* Open the /dev/crypto device */
	if (devcrypto_open() == 0) {
		devcrypto_free_aes_ctr_NIDs();
		pthread_mutex_destroy(kernel_fd_lock);
		OPENSSL_free(kernel_fd_lock);
		kernel_fd_lock = NULL;
		return (0);
	}

	/* Get all hardware providers' information */
	if (devcrypto_get_slot_info() == 0) {
		goto failed;
	}

	if (devcrypto_get_hw_ciphers() == 0) {
		goto failed;
	}

#ifdef DEBUG
	(void) fprintf(stderr, "cipher_count = %d\n", cipher_count);
	for (i = 0; i < cipher_count; i++) {
		(void) fprintf(stderr,
		    "cipher_nids[i] = %d\n", cipher_nids[i]);
	}
#endif /* DEBUG */

	if (!ENGINE_set_id(e, ENGINE_DEVCRYPTO_ID) ||
	    !ENGINE_set_name(e, ENGINE_DEVCRYPTO_NAME) ||
	    !ENGINE_set_ciphers(e, devcrypto_get_all_ciphers) ||
	    !ENGINE_set_destroy_function(e, devcrypto_destroy) ||
	    !ENGINE_set_finish_function(e, devcrypto_finish)) {
		goto failed;
	}

	/* Set up the devcrypto error handling */
	ERR_load_devcrypto_strings();
	return (1);

failed:
	devcrypto_cleanup();
	return (0);
}


static int
bind_helper(ENGINE *e, const char *id)
{
	if (id != NULL && (strcmp(id, ENGINE_DEVCRYPTO_ID) != 0)) {
#ifdef DEBUG
		(void) fprintf(stderr, "libdevcrypto - bad engine id\n");
#endif /* DEBUG */
		return (0);
	}
	if (!devcrypto_bind(e)) {
#ifdef DEBUG
		(void) fprintf(stderr,
		    "libdevcrypto - failed to bind engine\n");
#endif /* DEBUG */
		return (0);
	}

	return (1);
}

IMPLEMENT_DYNAMIC_CHECK_FN()
IMPLEMENT_DYNAMIC_BIND_FN(bind_helper)
