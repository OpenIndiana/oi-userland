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
 * Copyright (c) 2009, 2013, Oracle and/or its affiliates. All rights reserved.
 */

#include <sys/types.h>
#include <stropts.h>
#include <sys/conf.h>
#include <net/if.h>
#include <sys/sockio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <rad/adr.h>
#include <rad/rad_modapi.h>

#include "api_network.h"

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <ifaddrs.h>

static int
if_count(int fd, int *count)
{
	struct lifnum ifnum;

	ifnum.lifn_family = AF_INET;
	ifnum.lifn_flags = 0;
	if (ioctl(fd, SIOCGLIFNUM, &ifnum) == -1) {
		(void) close(fd);
		return (-1);
	}

	*count = ifnum.lifn_count;
	return (0);
}

/* ARGSUSED */
conerr_t
interface_Network_read_networkInterfaces(rad_instance_t *inst,
    adr_attribute_t *attr, adr_data_t **data, adr_data_t **error)
{
	int fd;
	int count, rcount;
	int reqsize;
	struct lifreq *reqs = NULL;
	struct lifconf ifconf;
	adr_data_t *result;

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		return (CE_OBJECT);

	do {
		if (reqs != NULL)
			free(reqs);

		if (if_count(fd, &count) == -1)
			return (CE_OBJECT);

		if (count == 0) {
			(void) close(fd);
			*data = adr_data_new_array(&adr_t_array_string, 0);
			return (CE_OK);
		}

		count += 5;
		reqsize = count * sizeof (struct lifreq);
		if ((reqs = malloc(reqsize)) == NULL) {
			(void) close(fd);
			return (CE_OBJECT);
		}

		ifconf.lifc_family = AF_INET;
		ifconf.lifc_len = reqsize;
		ifconf.lifc_buf = (char *)reqs;
		ifconf.lifc_flags = 0;
		if (ioctl(fd, SIOCGLIFCONF, &ifconf) == -1) {
			(void) close(fd);
			free(reqs);
			return (CE_OBJECT);
		}
		rcount = ifconf.lifc_len / sizeof (struct lifreq);
	} while (rcount >= count);

	result = adr_data_new_array(&adr_t_array_string, rcount);
	for (int i = 0; i < rcount; i++) {
		struct lifreq *r = &ifconf.lifc_req[i];
		if (strchr(r->lifr_name, ':') != NULL)
			continue;
		if (ioctl(fd, SIOCGLIFFLAGS, r) == -1)
			continue;
		if ((r->lifr_flags & (IFF_LOOPBACK | IFF_VIRTUAL)) != 0)
			continue;
		(void) adr_array_add(result, adr_data_new_string(r->lifr_name,
		    LT_COPY));
	}
	(void) close(fd);
	free(reqs);

	*data = adr_data_purify_deep(result);
	return (CE_OK);
}

/* ARGSUSED */
conerr_t
interface_Network_invoke_getHostNameForIP(rad_instance_t *inst,
    adr_method_t *meth, adr_data_t **ret, adr_data_t **args, int count,
    adr_data_t **error)
{
	int errnum;
	struct hostent *he;
	ipaddr_t addr;

	if (inet_pton(AF_INET, adr_data_to_string(args[0]), &addr) != 1)
		return (CE_OBJECT);

	if ((he = getipnodebyaddr(&addr, sizeof (addr), AF_INET, &errnum))
	    == NULL) {
		/* Not found?  Bounce it back. */
		(void) adr_data_ref(args[0]);
		*ret = args[0];
		return (CE_OK);
	}

	adr_data_t *result = adr_data_new_string(he->h_name, LT_COPY);
	freehostent(he);
	*ret = result;

	return (CE_OK);
}

/* ARGSUSED */
conerr_t
interface_Network_invoke_hostGetIPs(rad_instance_t *inst, adr_method_t *meth,
    adr_data_t **ret, adr_data_t **args, int count, adr_data_t **error)
{
	int errnum;
	struct hostent *he;

	if ((he = getipnodebyname(adr_data_to_string(args[0]), AF_INET,
	    AI_DEFAULT, &errnum)) == NULL) {
		*ret = NULL;
		return (CE_OBJECT);
	}

	int n = 0;
	for (char **aptr = he->h_addr_list; *aptr != NULL; aptr++)
		n++;
	adr_data_t *result = adr_data_new_array(&adr_t_array_string, n);
	for (int i = 0; i < n; i++) {
		char abuf[INET_ADDRSTRLEN];
		if (inet_ntop(AF_INET, he->h_addr_list[i], abuf,
		    sizeof (abuf)) != NULL)
			(void) adr_array_add(result, adr_data_new_string(abuf,
			    LT_COPY));
	}

	*ret = adr_data_purify_deep(result);
	freehostent(he);

	return (CE_OK);
}

/* ARGSUSED */
conerr_t
interface_Network_invoke_isLocalAddress(rad_instance_t *inst,
    adr_method_t *meth, adr_data_t **ret, adr_data_t **args, int count,
    adr_data_t **error)
{
	struct ifaddrs *ifaddr;
	struct ifaddrs *ifa;
	struct sockaddr_in *sin;
	struct sockaddr_in6 *sin6;

	char buf[1024];
	(void) memset(buf, 0, sizeof (buf));

	/* Set default return value */
	*ret = adr_data_new_boolean(B_FALSE);

	// Get IP addresses of each network interface.
	//
	// ifa_name	ifa_addr->sin_addr.s_addr
	//
	// lo0		0.0.0.0
	// lo0		::1 (AF_INET6)
	// lo0		127.0.0.1 (AF_INET)
	// e1000g0	129.XXX.XXX.XXX (AF_INET)
	//
	// See: man -s3 socket getifaddrs
	if (getifaddrs(&ifaddr) == -1) {
		return (CE_OBJECT);
	}

	/* Iterate over linked list of IP addresses */
	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_flags & IFF_IPV4) {
			/* LINTED */
			sin = (struct sockaddr_in *)ifa->ifa_addr;

			/* Match given IP address */
			if (strcmp(adr_data_to_string(args[0]),
			    inet_ntop(AF_INET,
			    &sin->sin_addr.s_addr, buf, 1024)) == 0) {
				*ret = adr_data_new_boolean(B_TRUE);
				break;
			}
		} else {
			/* LINTED */
			sin6 = (struct sockaddr_in6 *)ifa->ifa_addr;

			/* Match given IP address */
			if (strcmp(adr_data_to_string(args[0]),
			    inet_ntop(AF_INET6,
			    &sin6->sin6_addr.s6_addr, buf, 1024)) == 0) {
				*ret = adr_data_new_boolean(B_TRUE);
				break;
			}
		}
	}
	freeifaddrs(ifaddr);
	return (CE_OK);
}

int
_rad_init(void)
{
	adr_name_t *aname = adr_name_vcreate(MOD_DOMAIN, 1, "type", "Network");
	conerr_t cerr =  rad_cont_insert_singleton(rad_container, aname,
	    &modinfo, &interface_Network_svr);
	adr_name_rele(aname);
	if (cerr != CE_OK) {
		rad_log(RL_ERROR, "(mod_network) failed to insert Network");
		return (-1);
	}

	return (0);
}

/*
 * _rad_fini is called by the RAD daemon when the module is unloaded. Any
 * module finalisation is completed here.
 */
/*ARGSUSED*/
void
_rad_fini(void *unused)
{
}
