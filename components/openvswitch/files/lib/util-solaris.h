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

/*
 * While we make changes to kstat2_open, we must manually define the functions.
 * This can be stripped out once the changes in ON appear on the build machines.
 */
#ifndef	_KSTAT2_H
#define	_KSTAT2_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/kstat2_common.h>

typedef enum kstat2_status {
    KSTAT2_S_OK = 0,		/**< Request was successful */
    KSTAT2_S_NO_PERM,		/**< Insufficient permissions for request */
    KSTAT2_S_NO_MEM,		/**< Insufficient memory available */
    KSTAT2_S_NO_SPACE,		/**< No space available for operation */
    KSTAT2_S_INVAL_ARG,		/**< Invalid argument supplied */
    KSTAT2_S_INVAL_STATE,	/**< Invalid state for this request */
    KSTAT2_S_INVAL_TYPE,	/**< Invalid data type found */
    KSTAT2_S_NOT_FOUND,		/**< Resource not found */
    KSTAT2_S_CONC_MOD,		/**< Concurrent modification of map detected */
    KSTAT2_S_DEL_MAP,		/**< Referenced map has been deleted */
    KSTAT2_S_SYS_FAIL		/**< System call has failed, see errno */
} kstat2_status_t;

typedef const struct __kstat2_handle *kstat2_handle_t;
typedef const struct __kstat2_map *kstat2_map_t;

typedef struct kstat2_nv {
	const char *const	name;		/**< Name of the pair */
	const uint8_t		type;		/**< Value type of the pair */
	const uint8_t		kind;		/**< Kind of the pair */
	const uint16_t		flags;		/**< Flags of the pair */
	union {					/**< Data value */
		const struct __kstat2_map *const	map;
		const uint64_t				integer;
		struct {
			const uint64_t *const		array;
			const uint32_t			length;
		} integers;
		const char *const			string;
		struct {
			const char *const *const	array;
			const uint32_t			length;
		} strings;
	} data;
} *kstat2_nv_t;

#define	kstat2_map  data.map    /**< sub-map member */
#define	kstat2_integer  data.integer    /**< integer member */
#define	kstat2_integers data.integers   /**< integers member */
#define	kstat2_string   data.string /**< string member */
#define	kstat2_strings  data.strings    /**< strings member */

extern const char *kstat2_status_string(kstat2_status_t status);
extern kstat2_status_t kstat2_open(kstat2_handle_t *handle, void *);
extern kstat2_status_t kstat2_lookup_map(kstat2_handle_t handle,
    const char *uri, kstat2_map_t *map);
extern kstat2_status_t kstat2_update(kstat2_handle_t handle);
extern kstat2_status_t kstat2_close(kstat2_handle_t *handle);

extern kstat2_status_t kstat2_map_get(kstat2_map_t map, char *name,
    kstat2_nv_t *nv);
#endif  /* _KSTAT2_H */


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
uint64_t solaris_flow_walk(void *, struct ofpbuf *, boolean_t,
    void (*)(void *, const char *, boolean_t, struct flow *, struct flow *,
    struct ofpbuf *, uint64_t, uint64_t, uint64_t));

boolean_t solaris_is_uplink_class(const char *);
boolean_t solaris_dlparse_zonelinkname(const char *, char *, zoneid_t *);

void solaris_parse_cpuinfo(long int *);

#define	SOLARIS_MAX_BUFSIZE	1024
#endif	/* UTIL_SOLARIS_H */
