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
 */
/*
 * Copyright (c) 1998, 2015, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * lib/kad5/kadm_host_srv_names.c
 */

#include <k5-int.h>
#include "admin.h"
#include <stdio.h>
#include "fake-addrinfo.h"
/* HACK!!! need struct serverlist*/
#include "../krb5/os/os-proto.h"

/* HACK!!! */
#define	KADM5_ADMIN_HOST_SERVICE	"kadmin"
#define	KADM5_CHANGEPW_HOST_SERVICE	"changepw"

extern krb5_error_code
k5_locate_kadmin(krb5_context context, const krb5_data *realm,
		                 struct serverlist *serverlist);

extern krb5_error_code
locate_kpasswd(krb5_context context, const krb5_data *realm,
	       struct serverlist *serverlist, krb5_boolean no_udp);

/*
 * Find the admin server for the given realm. If the realm is null or
 * the empty string, find the admin server for the default realm.
 * Returns 0 on succsess (KADM5_OK). It is the callers responsibility to
 * free the storage allocated to the admin server, master.
 */
kadm5_ret_t
kadm5_get_master(krb5_context context, const char *realm, char **master)
{
    kadm5_ret_t		ret = KADM5_OK;
    char		*def_realm = NULL;
    krb5_error_code	code;
    struct serverlist	serverlist = SERVERLIST_INIT;
    struct server_entry	*entry;
    krb5_data		krealm;

    if (realm == 0 || *realm == '\0')
	krb5_get_default_realm(context, &def_realm);

    krealm = string2data(def_realm ? def_realm : (char *) realm);

    code = k5_locate_server(context, &krealm, &serverlist,
				locate_service_kadmin, TRUE);
    if (code == 0) {
	entry = &serverlist.servers[0];
	*master = strdup(entry->hostname);
	if (*master == NULL)
	    ret = ENOMEM;
    } else
	ret = KADM5_NO_SRV;
			
    if (def_realm != NULL)
	krb5_free_default_realm(context, def_realm);

    k5_free_serverlist(&serverlist);

    return (ret);
}

void
free_srv_names(char **srv_names)
{
    int i;

    if (srv_names == NULL)
        return;
    
    for (i = 0; srv_names[i] != NULL; i++) {
        free(srv_names[i]);
    }

    free(srv_names);
}

/*
 * Get the host base service name for the admin principal. Returns
 * KADM5_OK on success. Caller must call free_srv_names() on
 * host_service_names.
 */
kadm5_ret_t
kadm5_get_adm_host_srv_names(krb5_context context,
			    const char *realm, char ***host_service_names)
{
    kadm5_ret_t ret;
    char **tmp_srv_names;
    struct serverlist sl = SERVERLIST_INIT;
    int i;
    krb5_data realm_data;

    /* get list of admin servers */
    if (realm == NULL)
        return (EINVAL);
    realm_data.magic = KV5M_DATA;
    realm_data.data = (char *) realm;
    realm_data.length = strlen(realm);
    if (ret = k5_locate_kadmin(context, (const krb5_data *) &realm_data, &sl))
        return (ret);

    /* + 1 for array terminator */
    tmp_srv_names = calloc(sl.nservers + 1, sizeof (char *));
    if (tmp_srv_names == NULL) {
        k5_free_serverlist(&sl);
        return (ENOMEM);
    }

    for (i = 0; i < sl.nservers; i++) {
        tmp_srv_names[i] = malloc(strlen(KADM5_ADMIN_HOST_SERVICE) +
                                  strlen(sl.servers[i].hostname) + 2);
        if (tmp_srv_names[i] == NULL) {
            free_srv_names(tmp_srv_names);
            k5_free_serverlist(&sl);
            return (ENOMEM);
        }
        sprintf(tmp_srv_names[i], "%s@%s", KADM5_ADMIN_HOST_SERVICE,
                sl.servers[i].hostname);
    }

    k5_free_serverlist(&sl);
    *host_service_names = tmp_srv_names;
    return (KADM5_OK);
}

/*
 * Get the host base service name for the changepw principal. Returns
 * KADM5_OK on success. Caller must call free_srv_names() on
 * host_service_names.
 */
kadm5_ret_t
kadm5_get_cpw_host_srv_names(krb5_context context,
			    const char *realm, char ***host_service_names)
{
    kadm5_ret_t ret;
    char **tmp_srv_names;
    struct serverlist sl = SERVERLIST_INIT;
    int i;
    krb5_data realm_data;

    /* get list of admin servers */
    if (realm == NULL)
        return (EINVAL);
    realm_data.magic = KV5M_DATA;
    realm_data.data = (char *) realm;
    realm_data.length = strlen(realm);
    if (ret = locate_kpasswd(context, (const krb5_data *) &realm_data, &sl, 0))
        return (ret);

    /* + 1 for array terminator */
    tmp_srv_names = calloc(sl.nservers + 1, sizeof (char *));
    if (tmp_srv_names == NULL) {
        k5_free_serverlist(&sl);
        return (ENOMEM);
    }

    for (i = 0; i < sl.nservers; i++) {
        tmp_srv_names[i] = malloc(strlen(KADM5_CHANGEPW_HOST_SERVICE) +
                                  strlen(sl.servers[i].hostname) + 2);
        if (tmp_srv_names[i] == NULL) {
            free_srv_names(tmp_srv_names);
            k5_free_serverlist(&sl);
            return (ENOMEM);
        }
        sprintf(tmp_srv_names[i], "%s@%s", KADM5_CHANGEPW_HOST_SERVICE,
                sl.servers[i].hostname);
    }

    k5_free_serverlist(&sl);
    *host_service_names = tmp_srv_names;
    return (KADM5_OK);
}

/*
 * Get the host base service name for the kiprop principal. Returns
 * KADM5_OK on success. Caller must free the storage allocated
 * for host_service_name.
 */
kadm5_ret_t
kadm5_get_kiprop_host_srv_names(krb5_context context,
                               const char *realm,
                               char ***host_service_names)
{
    kadm5_ret_t ret;
    char **tmp_srv_names;
    struct serverlist sl = SERVERLIST_INIT;
    int i;
    krb5_data realm_data;

    /* get list of admin servers */
    if (realm == NULL)
        return (EINVAL);
    realm_data.magic = KV5M_DATA;
    realm_data.data = (char *) realm;
    realm_data.length = strlen(realm);
    if (ret = k5_locate_kadmin(context, (const krb5_data *) &realm_data, &sl))
        return (ret);

    /* + 1 for array terminator */
    tmp_srv_names = calloc(sl.nservers + 1, sizeof (char *));
    if (tmp_srv_names == NULL) {
        k5_free_serverlist(&sl);
        return (ENOMEM);
    }

    for (i = 0; i < sl.nservers; i++) {
        tmp_srv_names[i] = malloc(strlen(KADM5_KIPROP_HOST_SERVICE) +
                                  strlen(sl.servers[i].hostname) + 2);
        if (tmp_srv_names[i] == NULL) {
            free_srv_names(tmp_srv_names);
            k5_free_serverlist(&sl);
            return (ENOMEM);
        }
        sprintf(tmp_srv_names[i], "%s@%s", KADM5_KIPROP_HOST_SERVICE,
                sl.servers[i].hostname);
    }

    k5_free_serverlist(&sl);
    *host_service_names = tmp_srv_names;
    return (KADM5_OK);
}
