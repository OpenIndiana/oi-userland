/*
 * Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Copyright (c) 2010, 2011 Nicira, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef	DPIF_SOLARIS_H
#define	DPIF_SOLARIS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "openvswitch/types.h"
#include "smap.h"
#include "util-solaris.h"

#define	PORT_PF_PACKET_UPLINK	1
struct dpif_flow_stats;

int dpif_solaris_get_priority_details(void *, odp_port_t, uint_t,
    struct smap *);
void dpif_log(int, const char *, ...);
void dpif_solaris_migrate_internal_port(const char *, const char *);
struct netdev *dpif_solaris_obtain_netdev_to_migrate(char *, bool *);
void dpif_solaris_send_rarp(const char *);

#endif	/* DPIF_SOLARIS_H */
