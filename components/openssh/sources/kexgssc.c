/*
 * Copyright (c) 2001-2009 Simon Wilkinson. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR `AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * May 22, 2015
 * In version 6.8 a new packet interface has been introduced to OpenSSH,
 * while the old packet API has been provided in opacket.c.
 * At this moment we are not rewritting GSS-API key exchange code to the new
 * API, just adjusting it to still work with new struct ssh.
 * Rewritting to the new API can be considered in the future.
 */
/*
 * Copyright (c) 2004, 2016, Oracle and/or its affiliates. All rights reserved.
 */

#include "includes.h"

#ifdef GSSAPI

#include "includes.h"

#include <openssl/crypto.h>
#include <openssl/bn.h>

#include <signal.h>	/* for sig_atomic_t in kex.h */
#include <string.h>

#include "xmalloc.h"
#include "buffer.h"
#include "ssh2.h"
#include "key.h"
#include "cipher.h"
#include "digest.h"
#include "kex.h"
#include "log.h"
#include "packet.h"
#include "dh.h"
#include "ssherr.h"

#include "ssh-gss.h"

#define	GSSKEX_ERRHINT \
	"Disable GSS-API key exchange by including '-o GSSAPIKeyExchange=no'\n"\
	"in the ssh(1) command line invocation and try again."
#define	GSSKEX_ERRMSG \
	"GSS-API protected key exchange failed due to an unspecified error \n" \
	"encountered on the server.  This may be due to a misconfiguration \n" \
	"of Kerberos on the server.\n" \
	GSSKEX_ERRHINT

int
kexgss_client(struct ssh *ssh) {
	gss_buffer_desc send_tok = GSS_C_EMPTY_BUFFER;
	gss_buffer_desc recv_tok, gssbuf, msg_tok, *token_ptr;
	Gssctxt *ctxt;
	OM_uint32 maj_status, min_status, ret_flags, smaj_status, smin_status;
	uint_t klen, kout, slen = 0, strlen;
	BIGNUM *dh_server_pub = NULL;
	BIGNUM *shared_secret = NULL;
	BIGNUM *p = NULL;
	BIGNUM *g = NULL;
	uchar_t *kbuf;
	uchar_t *serverhostkey = NULL;
	uchar_t *empty = "";
	char *msg;
	char *lang;
	uchar_t type = 0;
	int first = 1;
	int nbits = 0, min = DH_GRP_MIN, max = DH_GRP_MAX;
	struct kex *kex = ssh->kex;
	int r, err;
	uchar_t hash[SSH_DIGEST_MAX_LENGTH];
	size_t hashlen;

	/* Initialise our GSSAPI world */
	ssh_gssapi_build_ctx(&ctxt);
	if (ssh_gssapi_id_kex(ctxt, kex->name, kex->kex_type)
	    == GSS_C_NO_OID)
		fatal("Couldn't identify host exchange");

	if (ssh_gssapi_import_name(ctxt, kex->gss_host))
		fatal("Couldn't import hostname");

	switch (kex->kex_type) {
	case KEX_GSS_GRP1_SHA1:
		kex->dh = dh_new_group1();
		break;
	case KEX_GSS_GRP14_SHA1:
		kex->dh = dh_new_group14();
		break;
	case KEX_GSS_GEX_SHA1:
		debug("Doing group exchange\n");
		nbits = dh_estimate(kex->we_need * 8);
		packet_start(SSH2_MSG_KEXGSS_GROUPREQ);
		packet_put_int(min);
		packet_put_int(nbits);
		packet_put_int(max);

		packet_send();

		packet_read_expect(SSH2_MSG_KEXGSS_GROUP);

		if ((p = BN_new()) == NULL)
			fatal("BN_new() failed");
		packet_get_bignum2(p);
		if ((g = BN_new()) == NULL)
			fatal("BN_new() failed");
		packet_get_bignum2(g);
		packet_check_eom();

		if (BN_num_bits(p) < min || BN_num_bits(p) > max)
			fatal("GSSGRP_GEX group out of range: %d !< %d !< %d",
			    min, BN_num_bits(p), max);

		kex->dh = dh_new_group(g, p);
		break;
	default:
		fatal("%s: Unexpected KEX type %d", __func__, kex->kex_type);
	}

	/* Step 1 - e is dh->pub_key */
	dh_gen_key(kex->dh, kex->we_need * 8);

	/* This is f, we initialise it now to make life easier */
	dh_server_pub = BN_new();
	if (dh_server_pub == NULL)
		fatal("dh_server_pub == NULL");

	token_ptr = GSS_C_NO_BUFFER;

	do {
		debug("Calling gss_init_sec_context");

		maj_status = ssh_gssapi_init_ctx(ctxt,
		    kex->gss_deleg_creds, token_ptr, &send_tok,
		    &ret_flags);

		if (GSS_ERROR(maj_status)) {
			ssh_gssapi_error(ctxt);
			(void) gss_release_buffer(&min_status, &send_tok);
			packet_disconnect("A GSS-API error occurred during "
			    "GSS-API protected key exchange\n");
		}

		/* If we've got an old receive buffer get rid of it */
		if (token_ptr != GSS_C_NO_BUFFER)
			free(recv_tok.value);

		if (maj_status == GSS_S_COMPLETE) {
			/* If mutual state flag is not true, kex fails */
			if (!(ret_flags & GSS_C_MUTUAL_FLAG))
				fatal("Mutual authentication failed");

			/* If integ avail flag is not true kex fails */
			if (!(ret_flags & GSS_C_INTEG_FLAG))
				fatal("Integrity check failed");
		}

		/*
		 * If we have data to send, then the last message that we
		 * received cannot have been a 'complete'.
		 */
		if (send_tok.length != 0) {
			if (first) {
				packet_start(SSH2_MSG_KEXGSS_INIT);
				packet_put_string(send_tok.value,
				    send_tok.length);
				packet_put_bignum2(kex->dh->pub_key);
				first = 0;
			} else {
				packet_start(SSH2_MSG_KEXGSS_CONTINUE);
				packet_put_string(send_tok.value,
				    send_tok.length);
			}
			packet_send();
			gss_release_buffer(&min_status, &send_tok);

			/* If we've sent them data, they should reply */
			do {
				err = ssh_packet_read_seqnr(active_state,
				    &type, NULL);
				if (err != 0) {
					fatal("%s: %s.\n%s", __func__,
					    ssh_err(err), GSSKEX_ERRMSG);
				}
				if (type == SSH2_MSG_KEXGSS_HOSTKEY) {
					debug("Received KEXGSS_HOSTKEY");
					if (serverhostkey)
						fatal("Server host key received"
						    "more than once");
					serverhostkey =
					    packet_get_string(&slen);
				}
			} while (type == SSH2_MSG_KEXGSS_HOSTKEY);

			switch (type) {
			case SSH2_MSG_KEXGSS_CONTINUE:
				debug("Received GSSAPI_CONTINUE");
				if (maj_status == GSS_S_COMPLETE)
					packet_disconnect("Protocol error: "
					    "received GSS-API context token "
					    "but the context was already "
					    "established");
				recv_tok.value = packet_get_string(&strlen);
				recv_tok.length = strlen;
				break;
			case SSH2_MSG_KEXGSS_COMPLETE:
				debug("Received GSSAPI_COMPLETE");
				packet_get_bignum2(dh_server_pub);
				msg_tok.value =  packet_get_string(&strlen);
				msg_tok.length = strlen;

				/* Is there a token included? */
				if (packet_get_char()) {
					recv_tok.value=
					    packet_get_string(&strlen);
					recv_tok.length = strlen;
				}
				if (recv_tok.length > 0 &&
				    maj_status == GSS_S_COMPLETE) {
					packet_disconnect("Protocol error: "
					    "received GSS-API context token "
					    "but the context was already "
					    "established");
				} else if (recv_tok.length == 0 &&
				    maj_status == GSS_S_CONTINUE_NEEDED) {
					/* No token included */
					packet_disconnect("Protocol error: "
					    "did not receive expected "
					    "GSS-API context token");
				}
				break;
			case SSH2_MSG_KEXGSS_ERROR:
				debug("Received Error");
				smaj_status = packet_get_int();
				smin_status = packet_get_int();
				msg = packet_get_string(NULL);
				lang = packet_get_string(NULL);
				free(lang);
				error("Server had a GSS-API error; the "
				    "connection will close (%u/%u):\n%s",
				    smaj_status, smin_status, msg);
				free(msg);
				error(GSSKEX_ERRHINT);
				packet_disconnect("The server encountered "
				    "a GSS-API error during GSS-API protected "
				    "key exchange\n");
				break;
			default:
				packet_disconnect("Protocol error: didn't"
				    " expect packet type %d", type);
			}
			token_ptr = &recv_tok;
		} else {
			/* No data, and not complete */
			if (maj_status != GSS_S_COMPLETE)
				fatal("Not complete, and no token output");
		}
	} while (maj_status & GSS_S_CONTINUE_NEEDED);

	/*
	 * We _must_ have received a COMPLETE message in reply from the
	 * server, which will have set dh_server_pub and msg_tok
	 */

	if (type != SSH2_MSG_KEXGSS_COMPLETE)
		fatal("Didn't receive SSH2_MSG_KEXGSS_COMPLETE when expected");
	if (maj_status != GSS_S_COMPLETE)
		fatal("Internal error in GSS-API protected key exchange");

	/* Check f in range [1, p-1] */
	if (!dh_pub_is_valid(kex->dh, dh_server_pub))
		packet_disconnect("bad server public DH value");

	/* compute K=f^x mod p */
	klen = DH_size(kex->dh);
	kbuf = xmalloc(klen);
	kout = DH_compute_key(kbuf, dh_server_pub, kex->dh);
	if (kout < 0)
		fatal("DH_compute_key: failed");

	shared_secret = BN_new();
	if (shared_secret == NULL)
		fatal("kexgss_client: BN_new failed");

	if (BN_bin2bn(kbuf, kout, shared_secret) == NULL)
		fatal("kexdh_client: BN_bin2bn failed");

	memset(kbuf, 0, klen);
	free(kbuf);

	hashlen = sizeof (hash);
	switch (kex->kex_type) {
	case KEX_GSS_GRP1_SHA1:
	case KEX_GSS_GRP14_SHA1:
		kex_dh_hash(
		    kex->hash_alg,
		    kex->client_version_string,
		    kex->server_version_string,
		    buffer_ptr(kex->my), buffer_len(kex->my),
		    buffer_ptr(kex->peer), buffer_len(kex->peer),
		    (serverhostkey ? serverhostkey : empty), slen,
		    kex->dh->pub_key,	/* e */
		    dh_server_pub,	/* f */
		    shared_secret,	/* K */
		    hash, &hashlen);
		break;
	case KEX_GSS_GEX_SHA1:
		kexgex_hash(
		    kex->hash_alg,
		    kex->client_version_string,
		    kex->server_version_string,
		    buffer_ptr(kex->my), buffer_len(kex->my),
		    buffer_ptr(kex->peer), buffer_len(kex->peer),
		    (serverhostkey ? serverhostkey : empty), slen,
		    min, nbits, max,
		    kex->dh->p, kex->dh->g,
		    kex->dh->pub_key,
		    dh_server_pub,
		    shared_secret,
		    hash, &hashlen);
		break;
	default:
		fatal("%s: Unexpected KEX type %d", __func__, kex->kex_type);
	}

	gssbuf.value = hash;
	gssbuf.length = hashlen;

	/* Verify that the hash matches the MIC we just got. */
	if (GSS_ERROR(ssh_gssapi_checkmic(ctxt, &gssbuf, &msg_tok)))
		packet_disconnect("Hash's MIC didn't verify");

	free(msg_tok.value);

	DH_free(kex->dh);
	if (serverhostkey)
		free(serverhostkey);
	BN_clear_free(dh_server_pub);

	/* save session id */
	if (kex->session_id == NULL) {
		kex->session_id_len = hashlen;
		kex->session_id = xmalloc(kex->session_id_len);
		memcpy(kex->session_id, hash, kex->session_id_len);
	}

	if (gss_kex_context == NULL)
		gss_kex_context = ctxt;
	else
		ssh_gssapi_delete_ctx(&ctxt);

	if ((r = kex_derive_keys_bn(ssh, hash, hashlen, shared_secret)) == 0)
		r = kex_send_newkeys(ssh);
	return (r);
}

#endif /* GSSAPI */
