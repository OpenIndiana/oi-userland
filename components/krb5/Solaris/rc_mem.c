/*
 * Copyright (c) 2004, 2015, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * mech_krb5/krb5/rcache/rc_mem.c
 *
 * This file of the Kerberos V5 software is derived from public-domain code
 * contributed by Daniel J. Bernstein, <brnstnd@acf10.nyu.edu>.
 */

/*
 * An implementation for the memory only (mem) replay cache type.
 * This file was derived from rc_dfl.c with NOIOSTUFF defined.
 */
#include "rc_mem.h"

#ifndef	HASHSIZE
#define	HASHSIZE 997 /* a convenient prime */
#endif

#define	CMP_MALLOC -3
#define	CMP_EXPIRED -2
#define	CMP_REPLAY -1
#define	CMP_HOHUM 0

struct authlist
{
    krb5_donot_replay rep;
    struct authlist *na;
    struct authlist *nh;
};

/*
 * We want the replay cache to hang around for the entire life span of the
 * process, regardless if the auth_context or acceptor_cred handles are
 * destroyed.
 */
struct global_rcache grcache = {K5_MUTEX_PARTIAL_INITIALIZER, NULL};

static unsigned int
hash(krb5_donot_replay *rep, unsigned int hsize)
{
    unsigned int h = rep->cusec + rep->ctime;
    h += *rep->server;
    h += *rep->client;
    return h % hsize;
}

/*ARGSUSED*/
static int
cmp(krb5_donot_replay *old, krb5_donot_replay *new1, krb5_deltat t)
{
    if ((old->cusec == new1->cusec) && /* most likely to distinguish */
	(old->ctime == new1->ctime) &&
	(strcmp(old->client, new1->client) == 0) &&
	(strcmp(old->server, new1->server) == 0)) { /* always true */
	/* If both records include message hashes, compare them as well. */
	if (old->msghash == NULL || new1->msghash == NULL ||
	    strcmp(old->msghash, new1->msghash) == 0)
	    return CMP_REPLAY;
    }
    return CMP_HOHUM;
}

static int
alive(krb5_int32 mytime, krb5_donot_replay *new1, krb5_deltat t)
{
    if (mytime == 0)
	return CMP_HOHUM; /* who cares? */
    /* I hope we don't have to worry about overflow */
    if (new1->ctime + t < mytime)
	return CMP_EXPIRED;
    return CMP_HOHUM;
}
/*
 * of course, list is backwards
 * hash could be forwards since we have to search on match, but naaaah
 */
static int
rc_store(krb5_context context, krb5_rcache id, krb5_donot_replay *rep)
{
	struct mem_data *t = (struct mem_data *)id->data;
	int rephash;
	struct authlist *ta, *pta = NULL, *head;
	krb5_int32 time;

	rephash = hash(rep, t->hsize);

	/* Calling krb_timeofday() here, once for better perf. */
	krb5_timeofday(context, &time);

	/*
	 * Calling alive() on rep since it doesn't make sense to store
	 * an expired replay.
	 */
	if (alive(time, rep, t->lifespan) == CMP_EXPIRED)
		return (CMP_EXPIRED);

	for (ta = t->h[rephash]; ta; ta = ta->nh) {
		switch (cmp(&ta->rep, rep, t->lifespan)) {
			case CMP_REPLAY:
				return (CMP_REPLAY);
			case CMP_HOHUM:
				if (alive(time, &ta->rep, t->lifespan)
				    == CMP_EXPIRED) {
					free(ta->rep.client);
					free(ta->rep.server);
					free(ta->rep.msghash);
					if (pta) {
						pta->nh = ta->nh;
						free(ta);
						ta = pta;
					} else {
						head = t->h[rephash];
						t->h[rephash] = ta->nh;
						free(head);
					}
					continue;
				}
		}
		pta = ta;
	}

	if (!(ta = (struct authlist *)malloc(sizeof (struct authlist))))
		return (CMP_MALLOC);
	ta->rep = *rep;
	ta->rep.client = ta->rep.server = ta->rep.msghash = NULL;
	if (!(ta->rep.client = strdup(rep->client)))
		goto error;
	if (!(ta->rep.server = strdup(rep->server)))
		goto error;
	if (!(ta->rep.msghash = strdup(rep->msghash)))
		goto error;
	ta->nh = t->h[rephash];
	t->h[rephash] = ta;
	return (CMP_HOHUM);
error:
	if (ta->rep.client)
		free(ta->rep.client);
	if (ta->rep.server)
		free(ta->rep.server);
	if (ta->rep.msghash)
		free(ta->rep.msghash);
	free(ta);
	return (CMP_MALLOC);
}

/*ARGSUSED*/
char *KRB5_CALLCONV
krb5_rc_mem_get_name(krb5_context context, krb5_rcache id)
{
	return (((struct mem_data *)(id->data))->name);
}

/*ARGSUSED*/
krb5_error_code KRB5_CALLCONV
krb5_rc_mem_get_span(krb5_context context, krb5_rcache id,
    krb5_deltat *lifespan)
{
	struct mem_data *t;

	k5_mutex_lock(&id->lock);
	k5_mutex_lock(&grcache.lock);

	t = (struct mem_data *)id->data;
	*lifespan = t->lifespan;

	k5_mutex_unlock(&grcache.lock);
	k5_mutex_unlock(&id->lock);

	return (0);
}

krb5_error_code KRB5_CALLCONV
krb5_rc_mem_init_locked(krb5_context context, krb5_rcache id,
    krb5_deltat lifespan)
{
	struct mem_data *t = (struct mem_data *)id->data;

	t->lifespan = lifespan ? lifespan : context->clockskew;
	/* default to clockskew from the context */
	return (0);
}

krb5_error_code KRB5_CALLCONV
krb5_rc_mem_init(krb5_context context, krb5_rcache id, krb5_deltat lifespan)
{
	krb5_error_code retval;

	k5_mutex_lock(&id->lock);
	k5_mutex_lock(&grcache.lock);

	retval = krb5_rc_mem_init_locked(context, id, lifespan);

	k5_mutex_unlock(&grcache.lock);
	k5_mutex_unlock(&id->lock);

	return (retval);
}

/*
 * We want the replay cache to be persistent since we can't
 * read from a file to retrieve the rcache, so we must not free
 * here.  Just return success.
 */
krb5_error_code KRB5_CALLCONV
krb5_rc_mem_close(krb5_context context, krb5_rcache id)
{
	return (0);
}

krb5_error_code KRB5_CALLCONV
krb5_rc_mem_destroy(krb5_context context, krb5_rcache id)
{
	return (krb5_rc_mem_close(context, id));
}

/*ARGSUSED*/
krb5_error_code KRB5_CALLCONV
krb5_rc_mem_resolve(krb5_context context, krb5_rcache id, char *name)
{
	struct mem_data *t = 0;
	krb5_error_code retval;

	k5_mutex_lock(&grcache.lock);

	/*
	 * If the global rcache has already been initialized through a prior
	 * call to this function then just set the rcache to point to it for
	 * any subsequent operations.
	 */
	if (grcache.data != NULL) {
		id->data = (krb5_pointer)grcache.data;
		k5_mutex_unlock(&grcache.lock);
		return (0);
	}
	/* allocate id? no */
	if (!(t = (struct mem_data *)malloc(sizeof (struct mem_data)))) {
		k5_mutex_unlock(&grcache.lock);
		return (KRB5_RC_MALLOC);
	}
	grcache.data = id->data = (krb5_pointer)t;
	memset(t, 0, sizeof (struct mem_data));
	if (name) {
		t->name = malloc(strlen(name)+1);
		if (!t->name) {
			retval = KRB5_RC_MALLOC;
			goto cleanup;
		}
		strcpy(t->name, name);
	} else
		t->name = 0;
	t->hsize = HASHSIZE; /* no need to store---it's memory-only */
	t->h = (struct authlist **)malloc(t->hsize*sizeof (struct authlist *));
	if (!t->h) {
		retval = KRB5_RC_MALLOC;
		goto cleanup;
	}
	memset(t->h, 0, t->hsize*sizeof (struct authlist *));
	k5_mutex_unlock(&grcache.lock);
	return (0);

cleanup:
	if (t) {
		if (t->name)
			free(t->name);
		if (t->h)
			free(t->h);
		free(t);
		grcache.data = NULL;
		id->data = NULL;
	}
	k5_mutex_unlock(&grcache.lock);

	return (retval);
}

/*
 * Recovery (retrieval) of the replay cache occurred during
 * krb5_rc_resolve().  So we just return error here.
 */
krb5_error_code KRB5_CALLCONV
krb5_rc_mem_recover(krb5_context context, krb5_rcache id)
{
	return (KRB5_RC_NOIO);
}

krb5_error_code KRB5_CALLCONV
krb5_rc_mem_recover_or_init(krb5_context context, krb5_rcache id,
			    krb5_deltat lifespan)
{
	krb5_error_code retval;

	retval = krb5_rc_mem_recover(context, id);
	if (retval)
		retval = krb5_rc_mem_init(context, id, lifespan);

	return (retval);
}

krb5_error_code KRB5_CALLCONV
krb5_rc_mem_store(krb5_context context, krb5_rcache id, krb5_donot_replay *rep)
{
	k5_mutex_lock(&id->lock);
	k5_mutex_lock(&grcache.lock);

	switch (rc_store(context, id, rep)) {
		case CMP_MALLOC:
			k5_mutex_unlock(&grcache.lock);
			k5_mutex_unlock(&id->lock);
			return (KRB5_RC_MALLOC);
		case CMP_REPLAY:
			k5_mutex_unlock(&grcache.lock);
			k5_mutex_unlock(&id->lock);
			return (KRB5KRB_AP_ERR_REPEAT);
		case CMP_EXPIRED:
			k5_mutex_unlock(&grcache.lock);
			k5_mutex_unlock(&id->lock);
			return (KRB5KRB_AP_ERR_SKEW);
		case CMP_HOHUM:
			break;
	}

	k5_mutex_unlock(&grcache.lock);
	k5_mutex_unlock(&id->lock);

	return (0);
}

const krb5_rc_ops krb5_rc_mem_ops = {
    0,
    "MEMORY",
    krb5_rc_mem_init,
    krb5_rc_mem_recover,
    krb5_rc_mem_recover_or_init,
    krb5_rc_mem_destroy,
    krb5_rc_mem_close,
    krb5_rc_mem_store,
    /* expunging not used in memory rcache type */
    NULL,
    krb5_rc_mem_get_span,
    krb5_rc_mem_get_name,
    krb5_rc_mem_resolve
};
