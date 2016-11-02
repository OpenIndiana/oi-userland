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
 * Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
 */

#ifndef	UTIL_SOLARIS_H
#define	UTIL_SOLARIS_H

#include <libdladm.h>
#include <linux/openvswitch.h>
#include <lib/packets.h>
#include <sys/types.h>
#include <kstat2.h>
#include "odp-util.h"

extern kstat2_handle_t	khandle;

/*
 * These functions are Solaris specific, so they should be used directly
 * only by Solaris-specific code.
 */

struct action_output {
	int nofports;
	uint32_t ofports[MAC_OF_MAXPORT];
};

struct action_set {
	uint_t	flags;
	uint_t	priority;
};

#define	FLOW_SET_PRIORITY 	0x1
#define	MAX_FLOW_ACTIONS	64

struct flow;
struct nlattr;

int solaris_dladm_status2error(dladm_status_t);
int solaris_if_enabled(int, const char *, uint64_t *);
int solaris_init_rad(void);
int solaris_get_dlclass(const char *, char *, size_t);
int solaris_get_devname(const char *, char *, size_t);
int solaris_get_dllower(const char *, char *, size_t);
int solaris_get_dlprop(const char *, const char *, const char *, char *,
    size_t);
int solaris_set_dlprop_ulong(const char *, const char *, void *, boolean_t);
int solaris_set_dlprop_boolean(const char *, const char *, void *, boolean_t);
int solaris_set_dlprop_string(const char *, const char *, void *, boolean_t);
int solaris_plumb_if(int, const char *, sa_family_t);
int solaris_unplumb_if(int, const char *, sa_family_t);
boolean_t dlparse_drvppa(const char *, char *, uint_t, uint_t *);

int solaris_create_vnic(const char *, const char *);
int solaris_delete_vnic(const char *);
int solaris_modify_vnic(const char *, const char *);
int solaris_create_etherstub(const char *);
int solaris_delete_etherstub(const char *);
boolean_t solaris_etherstub_exists(const char *);

/* void * since struct dpif causes conflict with the list implementation */
int solaris_add_flow(void *, const char *, const char *, struct flow *,
    struct flow *, const struct nlattr *, size_t);
int solaris_modify_flow(void *, const char *, const struct nlattr *, size_t);
int solaris_remove_flow(const char *, const char *);
int solaris_get_flowattr(const char *, struct flow *, struct flow *);
int solaris_get_flowaction(const char *, struct ofpbuf *);
void slowpath_to_actions(enum slow_path_reason, struct ofpbuf *);
int solaris_get_flowstats(const char *, uint64_t *, uint64_t *, uint64_t *);

boolean_t kstat_handle_init(kstat2_handle_t *);
boolean_t kstat_handle_update(kstat2_handle_t);
void kstat_handle_close(kstat2_handle_t *);
uint64_t get_nvvt_int(kstat2_map_t, char *);

void solaris_port_walk(void *, void (*)(void *, const char *, char *,
    odp_port_t));
void solaris_flow_walk(void *, struct ofpbuf *,
    void (*)(void *, const char *, struct flow *, struct flow *,
    struct ofpbuf *, uint64_t, uint64_t, uint64_t));

boolean_t solaris_is_uplink_class(const char *);
boolean_t solaris_dlparse_zonelinkname(const char *, char *, zoneid_t *);

void solaris_parse_cpuinfo(long int *);

#define	SOLARIS_MAX_BUFSIZE	1024
#endif	/* UTIL_SOLARIS_H */
