/*
 * Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Copyright (c) 2008, 2009, 2010, 2011, 2012, 2013, 2014 Nicira, Inc.
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

#include <config.h>
#include "dpif-solaris.h"
#include <fcntl.h>
#include <strings.h>
#include <unistd.h>
#include "classifier.h"
#include "dpif-provider.h"
#include "dynamic-string.h"
#include "netdev-solaris.h"
#include "netdev-vport.h"
#include "netlink.h"
#include "odp-execute.h"
#include "poll-loop.h"
#include "shash.h"
#include "socket-util.h"
#include "sset.h"
#include "vlog.h"
#include <netpacket/packet.h>
#include <zone.h>
#include <libdllink.h>

VLOG_DEFINE_THIS_MODULE(dpif_solaris);

static kstat2_handle_t	dpif_khandle;
static boolean_t	kstat2_handle_initialized = B_FALSE;
static struct ovs_mutex	kstat_mutex = OVS_MUTEX_INITIALIZER;

#ifndef  MAC_OVS_AUX_DATA_VERSION
/* Auxillary data from OVS if it wants to send packet directly out on a port */
typedef struct mac_ovs_aux_data_s {
	uint16_t	moad_ofport;
	uint16_t	moad_ofaction;
	mactun_info_t	moad_tuninfo;
} mac_ovs_aux_data_t;

struct ovs_tpacket_auxdata {		/* tp_macoff/tp_netoff */
	tpkt_status_t		tp_status;
	uint32_t		tp_len;
	uint32_t		tp_snaplen;
	uint16_t		tp_macoff;
	uint16_t		tp_netoff;
	uint16_t		tp_vlan_vci;
	mac_ovs_aux_data_t	tp_ovs_info;
};

#define	tpacket_auxdata	ovs_tpacket_auxdata
#define	tp_of_action	tp_ovs_info.moad_ofaction
#define	tp_of_port	tp_ovs_info.moad_ofport
#define	tp_tun_info	tp_ovs_info.moad_tuninfo
#define	tp_tun_type	tp_ovs_info.moad_tuninfo.mti_type
#define	tp_tun_id	tp_ovs_info.moad_tuninfo.mti_id
#define	tp_tun_dstip	tp_ovs_info.moad_tuninfo.mti_dst
#endif

/* Datapath interface for the openvswitch Solaris kernel module. */
struct dpif_solaris {
	struct dpif dpif;
	dladm_handle_t dh;
	int dp_ifindex;	/* datapath id */
	const struct dpif_class *class;
	char *name;
	atomic_flag destroyed;
	struct ovs_refcount ref_cnt;

	/* BRIDGES */
	struct ovs_rwlock bridge_rwlock;
	struct hmap bridges;

	/* PORT */
	struct ovs_rwlock port_rwlock;
	struct hmap ports;

	/* FLOW */
	struct ovs_rwlock flow_rwlock;
	struct hmap flows OVS_GUARDED;
	struct classifier cls;		/* rule, flow & mask */

	/* Upcall messages. */
	struct ovs_rwlock upcall_lock;
	bool recv_set;
	int event_rfd;
	int event_wfd;
};

static struct ovs_mutex dp_solaris_mutex = OVS_MUTEX_INITIALIZER;

/* Contains all 'struct dpif_solaris's. */
static struct shash dp_all_solaris OVS_GUARDED_BY(dp_solaris_mutex) =
    SHASH_INITIALIZER(&dp_all_solaris);

static struct vlog_rate_limit error_rl = VLOG_RATE_LIMIT_INIT(9999, 5);

struct dpif_solaris_bridge {
	char *name;
	struct hmap_node node;	/* Node in dpif_solaris's 'bridges'. */
	struct hmap ports;
	struct list uplink_port_list;	/* List of all uplinks to the bridge */
};

struct dpif_solaris_port {
	struct hmap_node node;		/* Node in dpif_solaris's 'ports'. */
	struct hmap_node brnode;	/* Node in dpif_bridge's 'ports'. */
	odp_port_t port_no;		/* OF port no of this port */
	odp_port_t pf_port_no;		/* OF port no of the PF_PACKET socket */
	char *type;			/* Port type as requested by user. */
	char *name;
	char *linkname;
	char *physname;
	enum ovs_vport_type vtype;
	struct netdev *netdev;
	struct dpif_solaris_bridge *bridge;
	boolean_t is_uplink;
	struct list uplink_node;	/* Node in dpif_solaris_bridge's */
					/* uplink_port_list */

	/* Receive the upcalls */
	int upcall_fd;			/* PF_PACKET fd for MISS event */

	/* Send the packet */
	int xfd;			/* PF_PACKET to execute output action */
};

struct dpif_solaris_flow {
	/* Packet classification. */
	struct cls_rule cr;	/* Node in dpif_solaris's 'cls'. */

	/* Hash table index by unmasked flow. */
	struct hmap_node node;	/* Node in dpif_solaris's 'flows'. */
	struct flow flow;	/* The flow that created this entry. */
	struct flow mask;	/* The flow that created this entry. */
	char *physname;
	char flowname[MAXUSERFLOWNAMELEN];
};

static void dpif_solaris_port_del__(struct dpif_solaris *dpif,
    struct dpif_solaris_port *port)
    OVS_REQ_WRLOCK(dpif->port_rwlock);
static void dpif_solaris_destroy_channels(struct dpif_solaris *dpif)
    OVS_REQ_WRLOCK(dpif->upcall_lock);
static int dpif_solaris_refresh_port_channel(struct dpif_solaris *dpif,
    struct dpif_solaris_port *port, const char *physname, boolean_t notify)
    OVS_REQ_WRLOCK(dpif->port_rwlock);
static int dpif_solaris_get_port_by_number(struct dpif_solaris *dpif,
    odp_port_t port_no, struct dpif_solaris_port **portp)
    OVS_REQ_RDLOCK(dpif->port_rwlock);
static int
dpif_solaris_get_uplink_port_info(struct dpif_solaris *dpif,
    odp_port_t port_no, odp_port_t *uport_nop, int *xfdp);
static void dpif_solaris_flow_remove(struct dpif_solaris *dpif,
    struct dpif_solaris_flow *flow)
    OVS_REQ_WRLOCK(dpif->flow_rwlock);
static int dpif_solaris_flow_flush__(struct dpif_solaris *dpif);

static struct dpif_solaris *
dpif_solaris_cast(const struct dpif *dpif)
{
	dpif_assert_class(dpif, &dpif_solaris_class);
	return (CONTAINER_OF(dpif, struct dpif_solaris, dpif));
}

static int
dpif_solaris_enumerate(struct sset *all_dps)
{
	int error;

	VLOG_DBG("dpif_solaris_enumerate");

	error = solaris_init_rad();
	if (error != 0)
		return (error);

	if (netdev_impl_etherstub_exists()) {
		VLOG_DBG("dpif_solaris_enumerate ovs-system");
		sset_add(all_dps, "ovs-system");
	}
	return (0);
}

static int
dpif_solaris_open(const struct dpif_class *class, const char *name,
    bool create, struct dpif **dpifp)
{
	struct dpif_solaris *dpif;
	int error = 0;
	boolean_t dp_exists;
	dladm_status_t status;

	VLOG_DBG("dpif_solaris_open class type %s name %s do %screate",
	    class->type, name, create ? "" : "not ");

	if (strcmp(name, "ovs-system") != 0)
		return (ENODEV);

	error = solaris_init_rad();
	if (error != 0)
		return (error);

	ovs_mutex_lock(&dp_solaris_mutex);

	dp_exists = netdev_impl_etherstub_exists();
	dpif = shash_find_data(&dp_all_solaris, name);

	/*
	 * The same function is shared by ovs-vswitchd and other utilities as
	 * they call into the same library. Note that for other utilities,
	 * dpif does not exists at first, create it here if dp_exists indicate
	 * the datapath already exists.
	 */
again:
	if ((dp_exists && dpif == NULL) || (!dp_exists && create)) {
		dladm_handle_t dh = NULL;

		status = dladm_open(&dh);
		error = solaris_dladm_status2error(status);
		if (error != 0) {
			ovs_mutex_unlock(&dp_solaris_mutex);
			return (error);
		}

		if (!dp_exists) {
			error = netdev_create_impl_etherstub();
			if (error != 0) {
				ovs_mutex_unlock(&dp_solaris_mutex);
				dladm_close(dh);
				return (error);
			}
		}

		dpif = xzalloc(sizeof (*dpif));
		dpif->dh = dh;
		dpif->dp_ifindex = getzoneid();
		dpif->class = class;
		dpif->name = xstrdup(name);
		atomic_flag_clear(&dpif->destroyed);

		/* UPCALL related */
		ovs_rwlock_init(&dpif->upcall_lock);
		dpif->recv_set = false;

		/* uplink related */
		ovs_rwlock_init(&dpif->bridge_rwlock);
		hmap_init(&dpif->bridges);

		/* port related */
		ovs_rwlock_init(&dpif->port_rwlock);
		hmap_init(&dpif->ports);
		dpif->event_rfd = dpif->event_wfd = -1;

		/* flow related */
		ovs_rwlock_init(&dpif->flow_rwlock);
		classifier_init(&dpif->cls, NULL);
		hmap_init(&dpif->flows);

		ovs_refcount_init(&dpif->ref_cnt);
		shash_add(&dp_all_solaris, name, dpif);
		if (!create) {
			ovs_refcount_ref(&dpif->ref_cnt);
			goto again;
		}
	} else if (!dp_exists) {
		error = ENODEV;
	} else {
		error = (dpif->class != class ? EOPNOTSUPP :
		    create ? EEXIST : 0);
	}

	if (!error) {
		ovs_refcount_ref(&dpif->ref_cnt);

		/* Choose dp_ifindex to be used as netflow engine type and id */
		dpif_init(&dpif->dpif, class, name, dpif->dp_ifindex,
		    dpif->dp_ifindex);
		*dpifp = &dpif->dpif;
	}
	ovs_mutex_unlock(&dp_solaris_mutex);
	return (error);
}

/*
 * Requires dp_netdev_mutex so that we can't get a new reference to 'dp'
 * through the 'dp_netdevs' shash while freeing 'dp'.
 */
static void
dp_solaris_free(struct dpif_solaris *dpif)
    OVS_REQUIRES(dp_solaris_mutex)
{
	struct dpif_solaris_port *port, *next;

	VLOG_DBG("dp_solaris_free %s", dpif->name);

	shash_find_and_delete(&dp_all_solaris, dpif->name);
	ovs_rwlock_wrlock(&dpif->port_rwlock);
	HMAP_FOR_EACH_SAFE(port, next, node, &dpif->ports) {
		dpif_solaris_port_del__(dpif, port);
	}
	ovs_rwlock_unlock(&dpif->port_rwlock);

	dpif_solaris_flow_flush__(dpif);
	classifier_destroy(&dpif->cls);

	hmap_destroy(&dpif->bridges);
	ovs_rwlock_destroy(&dpif->bridge_rwlock);

	hmap_destroy(&dpif->ports);
	ovs_rwlock_destroy(&dpif->port_rwlock);

	hmap_destroy(&dpif->flows);
	ovs_rwlock_destroy(&dpif->flow_rwlock);

	(void) close(dpif->event_rfd);
	(void) close(dpif->event_wfd);

	free(dpif->name);
	dladm_close(dpif->dh);
	netdev_delete_impl_etherstub();
	ovs_rwlock_destroy(&dpif->upcall_lock);
	free(dpif);
}

static void
dp_solaris_unref(struct dpif_solaris *dpif)
{
	if (dpif != NULL) {
		/*
		 * Take dp_solaris_mutex so that, if dpif->ref_cnt falls to
		 * zero, we can't get a hold of 'dpif'.
		 */
		ovs_mutex_lock(&dp_solaris_mutex);

		if (ovs_refcount_unref(&dpif->ref_cnt) == 2) {
			dp_solaris_free(dpif);
		}
		ovs_mutex_unlock(&dp_solaris_mutex);
	}
}

static void
dpif_solaris_close(struct dpif *dpif_)
{
	struct dpif_solaris *dpif = dpif_solaris_cast(dpif_);

	VLOG_DBG("dpif_solaris_close %s", dpif->name);

	ovs_rwlock_wrlock(&dpif->upcall_lock);
	dpif_solaris_destroy_channels(dpif);
	ovs_rwlock_unlock(&dpif->upcall_lock);

	dp_solaris_unref(dpif);
}

static int
dpif_solaris_destroy(struct dpif *dpif_)
{
	struct dpif_solaris *dpif = dpif_solaris_cast(dpif_);
	int cnt;

	VLOG_DBG("dpif_solaris_destroy %s", dpif->name);
	if (!atomic_flag_test_and_set(&dpif->destroyed)) {
		cnt = ovs_refcount_unref(&dpif->ref_cnt);
		if (cnt <= 2) {
			OVS_NOT_REACHED();
		}
	}

	return (0);
}

static int
dpif_solaris_get_stats(const struct dpif *dpif_, struct dpif_dp_stats *stats)
{
	struct dpif_solaris		*dpif = dpif_solaris_cast(dpif_);
	struct dpif_solaris_bridge	*bridge;
	struct dpif_solaris_port	*port;
	kstat2_status_t			stat;
	kstat2_map_t			map;
	char				kuri[1024];
	char				kstat_name[MAXLINKNAMELEN];
	char				*name;
	zoneid_t			zid;
	uint_t				instance;

	bzero(stats, sizeof (struct dpif_dp_stats));
	ovs_mutex_lock(&kstat_mutex);
	if (!kstat2_handle_initialized) {
		VLOG_DBG("dpif_solaris_get_stats initializing handle");
		if (!kstat_handle_init(&dpif_khandle)) {
			ovs_mutex_unlock(&kstat_mutex);
			VLOG_DBG("dpif_solaris_get_stats: error initializing"
			    " kstat handle");
			return (-1);
		}
		kstat2_handle_initialized = B_TRUE;
	} else if (!kstat_handle_update(dpif_khandle)) {
		kstat_handle_close(&dpif_khandle);
		kstat2_handle_initialized = B_FALSE;
		ovs_mutex_unlock(&kstat_mutex);
		VLOG_DBG("dpif_solaris_get_stats: error updating kstats");
		return (-1);
	}
	ovs_rwlock_rdlock(&dpif->bridge_rwlock);
	HMAP_FOR_EACH(bridge, node, &dpif->bridges) {

		LIST_FOR_EACH(port, uplink_node, &bridge->uplink_port_list) {
			name = (char *)port->physname;
			instance = 0;
			if (strchr(port->physname, '/') != NULL) {
				(void) solaris_dlparse_zonelinkname(
				    port->physname, kstat_name, &zid);
				name = kstat_name;
				instance = zid;
			}
			(void) snprintf(kuri, sizeof (kuri),
			    "kstat:/net/link/%s/%d", name, instance);
			stat = kstat2_lookup_map(dpif_khandle, kuri, &map);

			if (stat != KSTAT2_S_OK) {
				ovs_rwlock_unlock(&dpif->bridge_rwlock);
				ovs_mutex_unlock(&kstat_mutex);
				VLOG_WARN("dpif_solaris_get_stats kstat_lookup "
				    "of %s failed: %s", kuri,
				    kstat2_status_string(stat));
				return (-1);
			}
			stats->n_hit += (get_nvvt_int(map, "ipkthit") +
			    get_nvvt_int(map, "opkthit"));
			stats->n_missed += (get_nvvt_int(map, "ipktmiss") +
			    get_nvvt_int(map, "opktmiss"));
		}
	}
	ovs_rwlock_unlock(&dpif->bridge_rwlock);
	ovs_mutex_unlock(&kstat_mutex);
	stats->n_lost   = 0;
	stats->n_flows  = solaris_flow_walk(NULL, NULL, B_TRUE, NULL);
	stats->n_masks  = UINT32_MAX;
	stats->n_mask_hit  = UINT64_MAX;
	return (0);
}

static enum ovs_vport_type
netdev_to_ovs_vport_type(const struct netdev *netdev)
{
	const char *type = netdev_get_type(netdev);

	if (strcmp(type, "system") == 0) {
		return (OVS_VPORT_TYPE_NETDEV);
	} else if (strcmp(type, "internal") == 0) {
		return (OVS_VPORT_TYPE_INTERNAL);
	} else if (strcmp(type, "vxlan") == 0) {
		return (OVS_VPORT_TYPE_VXLAN);
	} else {
		return (OVS_VPORT_TYPE_UNSPEC);
	}
}

static int
dpif_solaris_create_xsocket(struct dpif_solaris *dpif OVS_UNUSED,
    struct dpif_solaris_port *port)
{
	int fd;
	struct sockaddr_ll sll;
	datalink_id_t linkid;
	dladm_status_t status;
	int error;

	if (port->vtype != OVS_VPORT_TYPE_NETDEV &&
	    port->vtype != OVS_VPORT_TYPE_VXLAN &&
	    port->vtype != OVS_VPORT_TYPE_INTERNAL)
		return (0);

	if ((fd = socket(PF_PACKET, SOCK_RAW, ETH_P_ALL)) == -1) {
		return (errno);
	}

	status = dladm_name2info(dpif->dh, port->linkname, &linkid,
	    NULL, NULL, NULL);
	error = solaris_dladm_status2error(status);
	if (error != 0) {
		(void) close(fd);
		return (error);
	}

	(void) memset(&sll, 0, sizeof (sll));
	sll.sll_family = AF_PACKET;
	sll.sll_ifindex = linkid;
	sll.sll_protocol = ETH_P_ALL;
	if (bind(fd, (struct sockaddr *)&sll, sizeof (sll)) == -1) {
		error = errno;
		(void) close(fd);
		return (error);
	}
	port->xfd = fd;
	VLOG_DBG("dpif_solaris_create_xsocket %d on %s port_no: %d", fd,
	    port->name, port->port_no);

	return (0);
}

static boolean_t
port_not_used(struct dpif_solaris *dpif, uint32_t port_no)
    OVS_REQ_WRLOCK(dp->port_rwlock)
{
	struct dpif_solaris_port *port;
	HMAP_FOR_EACH(port, node, &dpif->ports) {

		if (port->port_no == port_no ||
		    port->pf_port_no == port_no) {
			return (true);
		}
	}
	return (false);
}

/*
 * Choose an unused, non-zero port number and return it on success.
 * Return ODPP_NONE on failure.
 * The current approach to choose unused port number is quite inefficient,
 * need improvement. TBD
 */
static odp_port_t
choose_port(struct dpif_solaris *dpif, uint32_t exclude_port_no)
    OVS_REQ_WRLOCK(dp->port_rwlock)
{
	uint32_t port_no;

	for (port_no = PORT_PF_PACKET_UPLINK + 1; port_no < OFPP_MAX;
	    port_no++) {
		if ((exclude_port_no == ODPP_NONE ||
		    port_no != exclude_port_no) &&
		    (!port_not_used(dpif, port_no))) {
			return (u32_to_odp(port_no));
		}
	}

	return (ODPP_NONE);
}

static struct dpif_solaris_bridge *
dpif_solaris_lookup_bridge(const struct dpif_solaris *dpif,
    const char *brname)
    OVS_REQ_RDLOCK(dpif->bridge_rwlock)
{
	struct dpif_solaris_bridge *bridge;

	HMAP_FOR_EACH(bridge, node, &dpif->bridges) {
		if (strcmp(bridge->name, brname) == 0) {
			return (bridge);
		}
	}

	return (NULL);
}

static struct dpif_solaris_bridge *
dpif_solaris_bridge_add_port(struct dpif_solaris *dpif,
    const char *physname, struct dpif_solaris_port *port)
    OVS_REQ_WRLOCK(dpif->port_rwlock)
{
	struct dpif_solaris_bridge *bridge;
	const char *brname = NULL;

	ovs_rwlock_wrlock(&dpif->bridge_rwlock);
	VLOG_DBG("dpif_solaris_bridge_add_port adding port %d to uplink %s",
	    port->port_no, physname);

	if (strcmp(physname, NETDEV_IMPL_ETHERSTUB) == 0)
		brname = port->name;
	else
		brname = shash_find_data(&port_to_bridge_map, port->name);

	if (brname == NULL) {
		/*
		 * For vxlan or for such cases where we couldn't obtain
		 * brname
		 */
		brname = physname;
	}
	bridge = dpif_solaris_lookup_bridge(dpif, brname);
	if (bridge == NULL) {
		VLOG_DBG("dpif_solaris_bridge_add_port creating bridge %s",
		    brname);
		bridge = xzalloc(sizeof (*bridge));
		bridge->name = xstrdup(brname);
		hmap_insert(&dpif->bridges, &bridge->node,
		    hash_string(bridge->name, 0));
		hmap_init(&bridge->ports);
		list_init(&bridge->uplink_port_list);
	}
	port->bridge = bridge;
	hmap_insert(&bridge->ports, &port->brnode,
	    hash_odp_port(port->port_no));
	VLOG_DBG("dpif_solaris_bridge_add_port add port %s portno %d to "
	    "bridge %s", port->name, port->port_no, brname);

	if ((port->is_uplink) && (port->vtype != OVS_VPORT_TYPE_VXLAN)) {
		VLOG_DBG("Insert port %s into bridge %s uplink_port_list",
		    port->name, bridge->name);
		list_push_back(&bridge->uplink_port_list, &port->uplink_node);
	}
	ovs_rwlock_unlock(&dpif->bridge_rwlock);
	return (bridge);
}

static void
dpif_solaris_bridge_del_port(struct dpif_solaris *dpif,
    struct dpif_solaris_port *port)
    OVS_REQ_WRLOCK(dpif->port_rwlock)
{
	struct dpif_solaris_bridge *bridge = port->bridge;
	struct dpif_solaris_port *i_port;

	if (bridge == NULL) {
		VLOG_DBG("dpif_solaris_bridge_del_port port %d not assigned "
		    "to a bridge", port->port_no);
		return;
	}
	VLOG_DBG("dpif_solaris_bridge_del_port deleting port %d from %s",
	    port->port_no, bridge->name);

	ovs_rwlock_wrlock(&dpif->bridge_rwlock);

	if ((port->is_uplink) && (port->vtype != OVS_VPORT_TYPE_VXLAN)) {
		/*
		 * The extra thing we do if it's uplink (other than vxlan)
		 * is to remove the uplink port from bridge's uplink_port_list.
		 */
		LIST_FOR_EACH(i_port, uplink_node, &bridge->uplink_port_list) {
			if (strcmp(i_port->name, port->name) == 0) {
				list_remove(&port->uplink_node);
				VLOG_DBG("dpif_solaris_port_del__: Removed the "
				    "uplink %s from bridge's(%s) "
				    "uplink_port_list\n", i_port->name,
				    bridge->name);
				break;
			}
		}
	}

	hmap_remove(&bridge->ports, &port->brnode);

	if (hmap_is_empty(&bridge->ports)) {
		VLOG_DBG("dpif_solaris_bridge_del_port destroying bridge");
		hmap_destroy(&bridge->ports);
		hmap_remove(&dpif->bridges, &bridge->node);
		free(bridge->name);
		free(bridge);
	}
	ovs_rwlock_unlock(&dpif->bridge_rwlock);
}

static int
dpif_solaris_port_add__(struct dpif_solaris *dpif, struct netdev *netdev,
			odp_port_t *port_nop)
{
	char namebuf[NETDEV_VPORT_NAME_BUFSIZE];
	const char *name = netdev_vport_get_dpif_port(netdev,
	    namebuf, sizeof (namebuf));
	const char *linkname = netdev_get_name(netdev);
	const char *type = netdev_get_type(netdev);
	enum ovs_vport_type vtype;
	struct dpif_solaris_port *port = NULL;
	char physname[MAXLINKNAMELEN];
	char dlbuffer[DLADM_PROP_VAL_MAX];
	int error = 0;
	odp_port_t pf_port_no;
	boolean_t is_uplink = false;

	vtype = netdev_to_ovs_vport_type(netdev);
	if (vtype == OVS_VPORT_TYPE_UNSPEC) {
		VLOG_WARN_RL(&error_rl, "%s: cannot create port `%s' because "
		    "it has unsupported type `%s'", dpif_name(&dpif->dpif),
		    name, type);
		return (EINVAL);
	}

	VLOG_DBG("dpif_solaris_port_add %s (%s) type %s port_no %d vtype %d",
	    name, linkname, type, *port_nop, vtype);

	physname[0] = '\0';
	if (vtype == OVS_VPORT_TYPE_NETDEV || vtype == OVS_VPORT_TYPE_VXLAN ||
	    vtype == OVS_VPORT_TYPE_INTERNAL) {
		error = solaris_get_dlclass(linkname, dlbuffer,
		    sizeof (dlbuffer));
		if (error != 0)
			return (error);

		if (solaris_is_uplink_class(dlbuffer)) {
			if (strlcpy(physname, linkname, sizeof (physname)) >=
			    sizeof (physname))
				return (EINVAL);
			VLOG_DBG("dpif_solaris_port_add primary port %s",
			    name);
			is_uplink = true;
		} else {
			error = solaris_get_dllower(linkname, dlbuffer,
			    sizeof (dlbuffer));
			if (error != 0)
				return (error);
			if (strlcpy(physname, dlbuffer, sizeof (physname)) >=
			    sizeof (physname))
				return (EINVAL);
			VLOG_DBG("dpif_solaris_port_add non-primary port "
			    "%s to %s", name, dlbuffer);
		}
	} else {
		VLOG_DBG("dpif_solaris_port_add adding unknown type");
		return (EINVAL);
	}
	ovs_rwlock_wrlock(&dpif->upcall_lock);
	ovs_rwlock_wrlock(&dpif->port_rwlock);

	if (*port_nop == ODPP_NONE) {
		*port_nop = choose_port(dpif, ODPP_NONE);
		if (*port_nop == ODPP_NONE) {
			error = EFBIG;
			goto fail;
		}
	}
	pf_port_no = is_uplink ? PORT_PF_PACKET_UPLINK : choose_port(dpif,
	    *port_nop);
	if (pf_port_no == ODPP_NONE) {
		error = EFBIG;
		goto fail;
	}
	if (vtype == OVS_VPORT_TYPE_NETDEV || vtype == OVS_VPORT_TYPE_VXLAN ||
	    vtype == OVS_VPORT_TYPE_INTERNAL) {
		uint64_t u64 = (uint32_t)(*port_nop);

		VLOG_DBG("set portno %d on %s", (uint32_t)(*port_nop),
		    linkname);
		if ((error = solaris_set_dlprop_ulong(linkname, "ofport",
		    &u64, B_TRUE)) != 0) {
			VLOG_ERR("set portno %d on %s failed: %s",
			    (uint32_t)(*port_nop), linkname,
			    ovs_strerror(error));
			goto fail;
		}
	}

	port = xzalloc(sizeof (*port));
	port->port_no = *port_nop;
	port->pf_port_no = pf_port_no;
	port->name = xstrdup(name);
	port->linkname = xstrdup(linkname);
	port->physname = xstrdup(physname);
	port->type = xstrdup(type);
	port->vtype = vtype;
	port->netdev = netdev;
	port->upcall_fd = -1;
	port->xfd = -1;
	port->is_uplink = is_uplink;

	/* Only create the TX PF_SOCKET on the physical link */
	if (is_uplink) {
		error = dpif_solaris_create_xsocket(dpif, port);
		if (error != 0) {
			VLOG_ERR("dpif_solaris_create_xsocket on %s failed: %s",
			    port->linkname, ovs_strerror(error));
			goto fail;
		}
	}

	error = dpif_solaris_refresh_port_channel(dpif, port, physname, true);
	if (error != 0) {
		VLOG_ERR("dpif_solaris_refresh_port_channel on %s failed: %s",
		    linkname, ovs_strerror(error));
		goto fail;
	}

	if (vtype == OVS_VPORT_TYPE_NETDEV || vtype == OVS_VPORT_TYPE_VXLAN ||
	    vtype == OVS_VPORT_TYPE_INTERNAL)
		dpif_solaris_bridge_add_port(dpif, physname, port);
	hmap_insert(&dpif->ports, &port->node, hash_odp_port(port->port_no));

	ovs_rwlock_unlock(&dpif->port_rwlock);
	ovs_rwlock_unlock(&dpif->upcall_lock);
	return (0);
fail:
	if (port != NULL) {
		if (port->xfd != -1)
			(void) close(port->xfd);
		if (port->upcall_fd != -1) {
			(void) setsockopt(port->upcall_fd, SOL_PACKET,
			    PACKET_REM_OF_DEFFLOW, NULL, 0);
			(void) close(port->upcall_fd);
		}
		free(port->name);
		free(port->linkname);
		free(port->type);
		free(port->physname);
		free(port);
	}
	if (vtype == OVS_VPORT_TYPE_NETDEV || vtype == OVS_VPORT_TYPE_VXLAN ||
	    vtype == OVS_VPORT_TYPE_INTERNAL) {
		VLOG_DBG("reset portno on %s", linkname);
		(void) solaris_set_dlprop_ulong(linkname, "ofport", NULL,
		    B_TRUE);
	}
	ovs_rwlock_unlock(&dpif->port_rwlock);
	ovs_rwlock_unlock(&dpif->upcall_lock);
	return (error);
}

static int
dpif_solaris_port_add(struct dpif *dpif_, struct netdev *netdev,
    odp_port_t *port_nop)
{
	struct dpif_solaris *dpif = dpif_solaris_cast(dpif_);
	int error;

	error = dpif_solaris_port_add__(dpif, netdev, port_nop);
	return (error);
}

static int
dpif_solaris_get_port_by_number(struct dpif_solaris *dpif, odp_port_t port_no,
    struct dpif_solaris_port **portp)
    OVS_REQ_RDLOCK(dpif->port_rwlock)
{
	struct dpif_solaris_port *port;

	if (port_no == ODPP_NONE) {
		*portp = NULL;
		return (EINVAL);
	}

	HMAP_FOR_EACH_WITH_HASH(port, node,
	    hash_odp_port(port_no), &dpif->ports) {
		if (port->port_no == port_no) {
			*portp = port;
			return (0);
		}
	}

	*portp = NULL;
	return (ENOENT);
}

static int
dpif_solaris_get_uplink_port_info(struct dpif_solaris *dpif,
    odp_port_t port_no, odp_port_t *uport_nop, int *xfdp)
{
	struct dpif_solaris_port *port, *uport;

	ovs_rwlock_rdlock(&dpif->port_rwlock);
	HMAP_FOR_EACH(port, node, &dpif->ports)
		if (port->port_no == port_no)
			break;

	if (port == NULL)
		goto done;

	HMAP_FOR_EACH(uport, node, &dpif->ports) {
		if (uport->is_uplink &&
		    strcmp(port->physname, uport->linkname) == 0) {
			if (uport_nop != NULL)
				*uport_nop = uport->port_no;
			if (xfdp != NULL)
				*xfdp = uport->xfd;
			ovs_rwlock_unlock(&dpif->port_rwlock);
			return (0);
		}
	}

done:
	ovs_rwlock_unlock(&dpif->port_rwlock);
	return (ENOENT);
}

static void
dpif_solaris_port_del__(struct dpif_solaris *dpif,
    struct dpif_solaris_port *port)
    OVS_REQ_WRLOCK(dpif->port_rwlock)
{
	VLOG_DBG("dpif_solaris_port_del__ port %s # %d", port->name,
	    port->port_no);

	hmap_remove(&dpif->ports, &port->node);
	dpif_solaris_bridge_del_port(dpif, port);

	if (port->xfd != -1)
		(void) close(port->xfd);
	if (port->upcall_fd != -1) {
		(void) setsockopt(port->upcall_fd, SOL_PACKET,
		    PACKET_REM_OF_DEFFLOW, NULL, 0);
		(void) close(port->upcall_fd);
	}
	if (port->vtype == OVS_VPORT_TYPE_NETDEV || port->vtype ==
	    OVS_VPORT_TYPE_VXLAN || port->vtype == OVS_VPORT_TYPE_INTERNAL) {
			VLOG_DBG("1.reset portno on %s", port->linkname);
			(void) solaris_set_dlprop_ulong(port->linkname,
			    "ofport", NULL, B_TRUE);
		if (port->is_uplink) {
			VLOG_DBG("dpif_solaris_port_del__ primary port "
			    "%s", port->name);
		}
	}
	VLOG_DBG("dpif_solaris_port_del %s close xfd %d upcall_fd %d",
	    port->name, port->xfd, port->upcall_fd);

	free(port->type);
	free(port->name);
	free(port->linkname);
	free(port->physname);
	free(port);
}

static int
dpif_solaris_port_del(struct dpif *dpif_, odp_port_t port_no)
{
	struct dpif_solaris *dpif = dpif_solaris_cast(dpif_);
	struct dpif_solaris_port *port;
	int error;

	VLOG_DBG("dpif_solaris_port_del port # %d", port_no);

	if (port_no == ODPP_LOCAL) {
		VLOG_ERR("dpif_solaris_port_del invalid port # %d", port_no);
		return (EINVAL);
	}

	ovs_rwlock_wrlock(&dpif->port_rwlock);
	error = dpif_solaris_get_port_by_number(dpif, port_no, &port);
	if (error) {
		ovs_rwlock_unlock(&dpif->port_rwlock);
		VLOG_ERR("dpif_solaris_port_del port # %d failed %d", port_no,
		    error);
		return (error);
	}
	dpif_solaris_port_del__(dpif, port);
	ovs_rwlock_unlock(&dpif->port_rwlock);
	return (0);
}

static int
dpif_solaris_port_query_by_number(const struct dpif *dpif_, odp_port_t port_no,
    struct dpif_port *dpif_port)
{
	struct dpif_solaris *dpif = dpif_solaris_cast(dpif_);
	struct dpif_solaris_port *port = NULL;
	int error;

	ovs_rwlock_rdlock(&dpif->port_rwlock);
	error = dpif_solaris_get_port_by_number(dpif, port_no, &port);
	ovs_rwlock_unlock(&dpif->port_rwlock);
	if (!error && dpif_port) {
		dpif_port->name = xstrdup(port->name);
		dpif_port->type = xstrdup(port->type);
		dpif_port->port_no = port->port_no;
	}
	return (error);
}

static int
dpif_solaris_port_query_by_name(const struct dpif *dpif_, const char *devname,
				struct dpif_port *dpif_port)
{
	struct dpif_solaris *dpif = dpif_solaris_cast(dpif_);
	struct dpif_solaris_port *port = NULL;

	ovs_rwlock_wrlock(&dpif->port_rwlock);
	HMAP_FOR_EACH(port, node, &dpif->ports) {
		if (strcmp(port->name, devname) == 0) {
			if (dpif_port) {
				dpif_port->name = xstrdup(devname);
				dpif_port->type = xstrdup(port->type);
				dpif_port->port_no = port->port_no;
			}
			ovs_rwlock_unlock(&dpif->port_rwlock);
			return (0);
		}
	}
	ovs_rwlock_unlock(&dpif->port_rwlock);
	return (ENOENT);
}

struct dpif_solaris_port_state {
	struct hmap ports;
	struct ovs_rwlock port_rwlock;
	uint32_t bucket;
	uint32_t offset;
	char *name;
};

static void
port_dump_start(void *arg, const char *name, char *type, odp_port_t portno)
{
	struct dpif_solaris_port_state *state = arg;
	struct dpif_solaris_port *port;

	port = xzalloc(sizeof (struct dpif_solaris_port));
	port->name = xstrdup(name);
	port->type = type;
	port->port_no = portno;
	ovs_rwlock_wrlock(&state->port_rwlock);
	hmap_insert(&state->ports, &port->node, hash_odp_port(port->port_no));
	ovs_rwlock_unlock(&state->port_rwlock);
}

static int
dpif_solaris_port_dump_start(const struct dpif *dpif_ OVS_UNUSED,
    void **statep)
{
	struct dpif_solaris_port_state *state;

	*statep = state = xzalloc(sizeof (struct dpif_solaris_port_state));
	hmap_init(&state->ports);
	ovs_rwlock_init(&state->port_rwlock);
	solaris_port_walk(state, port_dump_start);
	return (0);
}

static int
dpif_solaris_port_dump_next(const struct dpif *dpif_ OVS_UNUSED, void *state_,
    struct dpif_port *dpif_port)
{
	struct dpif_solaris_port_state *state = state_;
	struct hmap_node *node;
	int retval;

	ovs_rwlock_wrlock(&state->port_rwlock);
	node = hmap_at_position(&state->ports, &state->bucket, &state->offset);
	if (node) {
		struct dpif_solaris_port *port;

		port = CONTAINER_OF(node, struct dpif_solaris_port, node);

		free(state->name);
		state->name = xstrdup(port->name);
		dpif_port->name = state->name;
		dpif_port->type = port->type;
		dpif_port->port_no = port->port_no;
		retval = 0;
	} else {
		retval = EOF;
	}
	ovs_rwlock_unlock(&state->port_rwlock);

	return (retval);
}

static int
dpif_solaris_port_dump_done(const struct dpif *dpif_ OVS_UNUSED, void *state_)
{
	struct dpif_solaris_port_state *state = state_;
	struct dpif_solaris_port *port, *next;

	ovs_rwlock_wrlock(&state->port_rwlock);
	HMAP_FOR_EACH_SAFE(port, next, node, &state->ports) {
		free(port->name);
		hmap_remove(&state->ports, &port->node);
	}
	ovs_rwlock_unlock(&state->port_rwlock);
	hmap_destroy(&state->ports);
	ovs_rwlock_destroy(&state->port_rwlock);
	free(state->name);
	free(state);
	return (0);
}

static int
dpif_solaris_port_poll(const struct dpif *dpif_ OVS_UNUSED,
    char **devnamep OVS_UNUSED)
{
	return (EAGAIN);
}

static void
dpif_solaris_port_poll_wait(const struct dpif *dpif_ OVS_UNUSED)
{
}

static int
dpif_solaris_key_to_flow(const struct nlattr *key, size_t key_len,
    struct flow *f)
{
	if (odp_flow_key_to_flow(key, key_len, f)) {
		/*
		 * This should not happen: it indicates that
		 * odp_flow_key_from_flow() and odp_flow_key_to_flow()
		 * disagree on the acceptable form of a flow.
		 * Log the problem as an error, with enough details to enable
		 * debugging.
		 */
		static struct vlog_rate_limit rl = VLOG_RATE_LIMIT_INIT(1, 5);

		if (!VLOG_DROP_ERR(&rl)) {
			struct ds s;

			ds_init(&s);

			odp_flow_format(key, key_len, NULL, 0, NULL, &s, true);
			VLOG_ERR("internal error parsing flow key %s",
			    ds_cstr(&s));
			ds_destroy(&s);
		}

		return (EINVAL);
	}
	return (0);
}

static int
dpif_solaris_key_to_mask(const struct nlattr *key, uint32_t key_len,
    const struct nlattr *mask_key, uint32_t mask_key_len,
    const struct flow *f, struct flow *m)
{
	enum mf_field_id id;
	enum odp_key_fitness fitness;

	/*
	 * Force unwildcard the in_port.
	 * We need to do this even in the case where we unwildcard "everything"
	 * above because "everything" only includes the 16-bit OpenFlow port
	 * number mask->in_port.ofp_port, which only covers half of the 32-bit
	 * datapath port number mask->in_port.odp_port.
	 */
	m->in_port.odp_port = ODPP_NONE;

	if (!mask_key_len) {
		/*
		 * No mask key, unwildcard everything except fields whose
		 * prerequisities are not met.
		 */
		memset(m, 0x0, sizeof (*m));

		for (id = 0; id < MFF_N_IDS; ++id) {
			/* Skip registers and metadata. */
			if (!(id >= MFF_REG0 && id < MFF_REG0 + FLOW_N_REGS) &&
			    id != MFF_METADATA) {
				const struct mf_field *mf = mf_from_id(id);
				if (mf_are_prereqs_ok(mf, f)) {
					mf_mask_field(mf, m);
				}
			}
		}
		return (0);
	}

	fitness = odp_flow_key_to_mask(mask_key, mask_key_len, m, f);
	if (fitness) {
		/*
		 * This should not happen: it indicates that
		 * odp_flow_key_from_mask() and odp_flow_key_to_mask()
		 * disagree on the acceptable form of a mask.
		 * Log the problem as an error, with enough details to
		 * enable debugging.
		 */
		static struct vlog_rate_limit rl = VLOG_RATE_LIMIT_INIT(1, 5);

		if (!VLOG_DROP_ERR(&rl)) {
			struct ds s;

			ds_init(&s);
			odp_flow_format(key, key_len, mask_key, mask_key_len,
			    NULL, &s, true);
			VLOG_ERR("internal error parsing flow mask %s (%s)",
			    ds_cstr(&s), odp_key_fitness_to_string(fitness));
			ds_destroy(&s);
		}

		return (EINVAL);
	}

	return (0);
}

static struct dpif_solaris_flow *
dpif_solaris_flow_cast(const struct cls_rule *cr)
{
	return (cr ? CONTAINER_OF(cr, struct dpif_solaris_flow, cr) : NULL);
}

static struct dpif_solaris_flow *
dpif_solaris_lookup_flow(const struct dpif_solaris *dpif,
    const struct miniflow *key)
    OVS_EXCLUDED(dpif->cls.rwlock)
{
	struct dpif_solaris_flow *solaris_flow;
	struct cls_rule *rule;

	fat_rwlock_rdlock(&dpif->cls.rwlock);
	rule = classifier_lookup_miniflow_first(&dpif->cls, key);
	solaris_flow = dpif_solaris_flow_cast(rule);
	fat_rwlock_unlock(&dpif->cls.rwlock);

	return (solaris_flow);
}

static struct dpif_solaris_flow *
dpif_solaris_find_flow(const struct dpif_solaris *dpif, const struct flow *flow)
{
	struct dpif_solaris_flow *solaris_flow;

	HMAP_FOR_EACH_WITH_HASH(solaris_flow, node, flow_hash(flow, 0),
	    &dpif->flows) {
		if (flow_equal(&solaris_flow->flow, flow)) {
			return (solaris_flow);
		}
	}

	return (NULL);
}

static struct dpif_solaris_flow *
dpif_solaris_find_flow_by_name(const struct dpif_solaris *dpif,
    const char *flowname)
{
	struct dpif_solaris_flow *solaris_flow;

	HMAP_FOR_EACH(solaris_flow, node, &dpif->flows) {
		if (strcmp(solaris_flow->flowname, flowname) == 0) {
			return (solaris_flow);
		}
	}

	return (NULL);
}

static struct dpif_solaris_flow *
dpif_solaris_flow_add(struct dpif_solaris *dpif, const char *physname,
    struct flow *flow, struct flow *mask, const struct flow_wildcards *wc)
    OVS_REQ_WRLOCK(dpif->flow_rwlock)
{
	struct dpif_solaris_flow *solaris_flow;
	struct match match;

	solaris_flow = xzalloc(sizeof (*solaris_flow));

	solaris_flow->physname = xstrdup(physname);
	(void) snprintf(solaris_flow->flowname, MAXUSERFLOWNAMELEN,
	    "%p.sys.of", (void *)solaris_flow);
	solaris_flow->flow = *flow;
	solaris_flow->mask = *mask;
	match_init(&match, flow, wc);
	fat_rwlock_wrlock(&dpif->cls.rwlock);
	cls_rule_init(&solaris_flow->cr, &match, 0x8001);
	hmap_insert(&dpif->flows, &solaris_flow->node, flow_hash(flow, 0));
	classifier_insert(&dpif->cls, &solaris_flow->cr);
	fat_rwlock_unlock(&dpif->cls.rwlock);
	return (solaris_flow);
}

static void
dpif_solaris_flow_remove(struct dpif_solaris *dpif,
    struct dpif_solaris_flow *solaris_flow) OVS_REQ_WRLOCK(dpif->flow_rwlock)
{
	struct cls_rule *cr;
	struct hmap_node *node;

	fat_rwlock_wrlock(&dpif->cls.rwlock);
	cr = &solaris_flow->cr;
	node = CONST_CAST(struct hmap_node *, &solaris_flow->node);
	classifier_remove(&dpif->cls, cr);
	hmap_remove(&dpif->flows, node);
	cls_rule_destroy(CONST_CAST(struct cls_rule *, cr));
	fat_rwlock_unlock(&dpif->cls.rwlock);
	free(solaris_flow->physname);
	free(solaris_flow);
}

static int
dpif_solaris_get_flowstats(char *flowname, struct dpif_flow_stats *stats)
{
	uint64_t npackets, nbytes, lastused;
	int error;

	bzero(stats, sizeof (*stats));
	error = solaris_get_flowstats(flowname, &npackets, &nbytes, &lastused);
	if (error == 0) {
		stats->n_packets = npackets;
		stats->n_bytes = nbytes;
		stats->used = lastused / 1000000;
	}
	return (error);
}

static int
dpif_solaris_flow_get(const struct dpif *dpif_,
    const struct nlattr *key, size_t key_len,
    struct ofpbuf **bufp,
    struct nlattr **maskp, size_t *mask_len,
    struct nlattr **actionsp, size_t *actions_len,
    struct dpif_flow_stats *stats)
{
	const struct dpif_solaris *dpif = dpif_solaris_cast(dpif_);
	struct flow f, m;
	struct dpif_solaris_flow *solaris_flow;
	char flowname[MAXUSERFLOWNAMELEN];
	struct ofpbuf actions;
	int error;

	VLOG_DBG("dpif_solaris_flow_get");

	error = dpif_solaris_key_to_flow(key, key_len, &f);
	if (error) {
		VLOG_ERR("dpif_solaris_key_to_flow failed %d", error);
		return (error);
	}

	ovs_rwlock_rdlock(&dpif->flow_rwlock);
	solaris_flow = dpif_solaris_find_flow(dpif, &f);
	if (solaris_flow == NULL) {
		ovs_rwlock_unlock(&dpif->flow_rwlock);
		error = ENOENT;
		VLOG_ERR("dpif_solaris_flow_get failed %d", error);
		return (error);
	}
	(void) strlcpy(flowname, solaris_flow->flowname, MAXUSERFLOWNAMELEN);
	error = solaris_get_flowattr(flowname, &f, &m);
	if (error) {
		VLOG_ERR("solaris_get_flowattr failed %d", error);
		ovs_rwlock_unlock(&dpif->flow_rwlock);
		return (error);
	}

	ovs_rwlock_unlock(&dpif->flow_rwlock);

	/* Allocate buffer big enough for everything. */
	*bufp = ofpbuf_new(4096);
	ofpbuf_init(*bufp, 4096);

	/* Mask. */
	odp_flow_key_from_mask(*bufp, &m, &f, m.in_port.odp_port,
	    SIZE_MAX);
	*maskp = ofpbuf_data(*bufp);
	*mask_len = ofpbuf_size(*bufp);

	/* Actions. */
	ofpbuf_init(&actions, 0);
	(void) solaris_get_flowaction(flowname, &actions);
	if (ofpbuf_size(&actions) == 0) {
		*actionsp = NULL;
		*actions_len = 0;
	} else {
		*actionsp = ofpbuf_put(*bufp, ofpbuf_data(&actions),
		    ofpbuf_size(&actions));
		*actions_len = ofpbuf_size(&actions);
	}
	ofpbuf_uninit(&actions);

	/* Stats. */
	error = dpif_solaris_get_flowstats(flowname, stats);
	return (0);
}

int
dpif_solaris_get_priority_details(void *cookie, odp_port_t outport,
    uint_t queueid, struct smap *details)
{
	struct dpif_solaris		*dpif = (struct dpif_solaris *)cookie;
	struct dpif_solaris_port	*port = NULL;
	int				error = 0;
	struct netdev			*netdev;

	VLOG_DBG("dpif_solaris_get_priority_details: "
	" Port : %d, Queue: %d\n", outport, queueid);

	ovs_rwlock_wrlock(&dpif->port_rwlock);
	error = dpif_solaris_get_port_by_number(dpif, outport, &port);
	ovs_rwlock_unlock(&dpif->port_rwlock);
	if (error != 0) {
		VLOG_DBG("dpif_solaris_get_priority_details: "
		"Error getting port %d\n", outport);
		return (error);
	}

	netdev = port->netdev;
	error = netdev_get_queue(netdev, queueid, details);
	if (error != 0) {
		VLOG_DBG("dpif_solaris_get_priority_details: "
		" Error getting queue %d\n", queueid);
		return (error);
	}
	VLOG_DBG("dpif_solaris_get_priority_details: done");
	return (0);
}

void
dpif_log(int err, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	if (err == 0)
		vlog_valist(THIS_MODULE, VLL_DBG, fmt, ap);
	else
		vlog_valist(THIS_MODULE, VLL_ERR, fmt, ap);
	va_end(ap);
}

static int
dpif_solaris_flow_put(struct dpif *dpif_, const struct dpif_flow_put *put)
{
	struct dpif_solaris *dpif = dpif_solaris_cast(dpif_);
	struct flow f;
	struct flow_wildcards wc;
	struct miniflow miniflow;
	struct dpif_solaris_flow *solaris_flow;
	char flowname[MAXUSERFLOWNAMELEN];
	int error;
	struct ds fs, as;

	VLOG_DBG("dpif_solaris_flow_put");

	ds_init(&fs);
	ds_init(&as);
	odp_flow_format(put->key, put->key_len, put->mask,
	    put->mask_len, NULL, &fs, true);
	ds_put_cstr(&as, ", actions:");
	format_odp_actions(&as, put->actions, put->actions_len);

	error = dpif_solaris_key_to_flow(put->key, put->key_len, &f);
	if (error) {
		VLOG_ERR("dpif_solaris_key_to_flow failed %d", error);
		goto done;
	}
	error = dpif_solaris_key_to_mask(put->key, put->key_len, put->mask,
	    put->mask_len, &f, &wc.masks);
	if (error) {
		VLOG_ERR("dpif_solaris_key_to_mask failed %d", error);
		goto done;
	}

	miniflow_init(&miniflow, &f);

	ovs_rwlock_wrlock(&dpif->flow_rwlock);
	solaris_flow = dpif_solaris_lookup_flow(dpif, &miniflow);
	miniflow_destroy(&miniflow);

	if (solaris_flow == NULL) {
		if (put->flags & DPIF_FP_CREATE) {
			struct dpif_solaris_port *port = NULL;
			odp_port_t		inport;
			char			physname[MAXLINKNAMESPECIFIER];
			char			portname[MAXLINKNAMESPECIFIER];

			inport = f.in_port.odp_port;
			ovs_rwlock_rdlock(&dpif->port_rwlock);
			error = dpif_solaris_get_port_by_number(dpif, inport,
			    &port);
			if (error == 0) {
				(void) strlcpy(physname, port->physname,
				    sizeof (physname));
				(void) strlcpy(portname, port->name,
				    sizeof (portname));
			}
			ovs_rwlock_unlock(&dpif->port_rwlock);
			if (error == 0) {
				VLOG_DBG("dpif_solaris_flow_put on %s",
				    physname);

				solaris_flow = dpif_solaris_flow_add(dpif,
				    physname, &f, &wc.masks, &wc);
				(void) strlcpy(flowname,
				    solaris_flow->flowname,
				    MAXUSERFLOWNAMELEN);
				VLOG_DBG("dpif_solaris_flow_put %s mask %s "
				    "actions %s", flowname, ds_cstr(&fs),
				    ds_cstr(&as));
				/*
				 * workaround to passing a struct dpif to
				 * solaris_add_flow adding dpif_provider.h to
				 * util-solaris brings up a conflict in
				 * Solaris's list and the OVS list
				 * implementations.
				 */
				error = solaris_add_flow((void *)dpif,
				    physname, flowname, &f,
				    &wc.masks, put->actions, put->actions_len);
				if (error == 0) {
					VLOG_DBG("dpif_solaris_flow_put "
					    "solaris_add_flow %s on %s succeed"
					    "(port:%s)",
					    flowname, physname, portname);
				} else {
					VLOG_ERR("dpif_solaris_flow_put "
					    "solaris_add_flow %s on %s failed "
					    "(port:%s)"
					    "%d", flowname,
					    physname,
					    portname,
					    error);
					dpif_solaris_flow_remove(dpif,
					    solaris_flow);
				}
			} else {
				VLOG_DBG("dpif_solaris_flow_put(): "
				    "Error getting inport %d\n", inport);
			}
		} else {
			VLOG_ERR("dpif_solaris_flow_put mask %s "
			    "actions %s not found", ds_cstr(&fs),
			    ds_cstr(&as));
			error = ENOENT;
		}
	} else {
		VLOG_DBG("dpif_solaris_flow_put exsting flow %s found for"
		    " mask %s actions %s", solaris_flow->flowname,
		    ds_cstr(&fs), ds_cstr(&as));
		if ((put->flags & DPIF_FP_MODIFY) &&
		    flow_equal(&f, &solaris_flow->flow)) {
			(void) strlcpy(flowname, solaris_flow->flowname,
			    MAXUSERFLOWNAMELEN);
			error = solaris_modify_flow((void *)dpif,
			    flowname, put->actions, put->actions_len);
			if (error == 0) {
				VLOG_DBG("dpif_solaris_flow_put "
				    "exsting flow %s found and updated,"
				    "for mask %s actions %s", flowname,
				    ds_cstr(&fs), ds_cstr(&as));
			} else {
				VLOG_ERR("dpif_solaris_flow_put "
				    "exsting flow %s found but update "
				    "failed %d, for mask %s actions %s",
				    flowname, error, ds_cstr(&fs),
				    ds_cstr(&as));
			}
		} else if (put->flags & DPIF_FP_CREATE) {
			VLOG_DBG("dpif_solaris_flow_put existing flow "
			    "%s already exists for mask %s actions %s",
			    solaris_flow->flowname, ds_cstr(&fs),
			    ds_cstr(&as));
			error = EEXIST;
		} else {
			/*
			 * Overlapping flow. (Flow & Mask) matches but flow
			 * itself does not match
			 */
			VLOG_ERR("dpif_solaris_flow_put overlapped "
			    "with existing flow %s, for mask %s actions %s",
			    solaris_flow->flowname, ds_cstr(&fs),
			    ds_cstr(&as));
			error = EINVAL;
		}
	}

	if (error == 0) {
		if (put->stats) {
			if (dpif_solaris_get_flowstats(flowname,
			    put->stats) == 0) {
				VLOG_DBG("dpif_solaris_flow_put "
				    "get_flowstats %s succeed", flowname);
			} else {
				VLOG_ERR("dpif_solaris_flow_put "
				    "get_flowstats %s failed", flowname);
			}
		}
		/*
		 * If DPIF_FP_MODIFY and DPIF_FP_ZERO_STATS is set in
		 * put->flags, we should zero out the statistics of the
		 * given flow. This is currently not supported, and so far,
		 * we don't see any problem yet.
		 */
	}
	ovs_rwlock_unlock(&dpif->flow_rwlock);
done:
	ds_destroy(&fs);
	ds_destroy(&as);
	return (error);
}

static int
dpif_solaris_flow_del(struct dpif *dpif_, const struct dpif_flow_del *del)
{
	struct dpif_solaris *dpif = dpif_solaris_cast(dpif_);
	struct dpif_solaris_flow *solaris_flow;
	char flowname[MAXUSERFLOWNAMELEN];
	char *physname;
	struct flow f;
	int error;
	struct ds fs;

	ds_init(&fs);
	odp_flow_format(del->key, del->key_len, NULL, 0, NULL, &fs, true);
	VLOG_DBG("dpif_solaris_flow_del %s", ds_cstr(&fs));
	ds_destroy(&fs);

	error = dpif_solaris_key_to_flow(del->key, del->key_len, &f);
	if (error) {
		VLOG_ERR("dpif_solaris_key_to_flow failed %d", error);
		return (error);
	}

	ovs_rwlock_wrlock(&dpif->flow_rwlock);
	solaris_flow = dpif_solaris_find_flow(dpif, &f);
	if (solaris_flow == NULL) {
		ovs_rwlock_unlock(&dpif->flow_rwlock);
		error = ENOENT;
		VLOG_ERR("dpif_solaris_flow_del failed %d", error);
		return (error);
	}
	(void) strlcpy(flowname, solaris_flow->flowname, MAXUSERFLOWNAMELEN);
	physname = xstrdup(solaris_flow->physname);
	dpif_solaris_flow_remove(dpif, solaris_flow);
	if (del->stats) {
		error = dpif_solaris_get_flowstats(flowname, del->stats);
		if (error == 0) {
			VLOG_DBG("dpif_solaris_flow_del "
			    "get_flowstats %s succeed", flowname);
		} else {
			VLOG_ERR("dpif_solaris_flow_del "
			    "get_flowstats %s failed %d", flowname, error);
		}
	}
	error = solaris_remove_flow(physname, flowname);
	if (error == 0) {
		VLOG_DBG("dpif_solaris_flow_del solaris_remove_flow %s "
		    "succeed", flowname);
	} else {
		VLOG_ERR("dpif_solaris_flow_del solaris_remove_flow %s "
		    "failed %d", flowname, error);
	}
	ovs_rwlock_unlock(&dpif->flow_rwlock);

	free(physname);
	return (error);
}

static int
dpif_solaris_flow_flush__(struct dpif_solaris *dpif)
{
	struct dpif_solaris_flow *solaris_flow, *next;

	ovs_rwlock_wrlock(&dpif->flow_rwlock);
	HMAP_FOR_EACH_SAFE(solaris_flow, next, node, &dpif->flows) {
		(void) solaris_remove_flow(solaris_flow->physname,
		    solaris_flow->flowname);
		dpif_solaris_flow_remove(dpif, solaris_flow);
	}
	ovs_rwlock_unlock(&dpif->flow_rwlock);
	return (0);
}

static int
dpif_solaris_flow_flush(struct dpif *dpif_)
{
	struct dpif_solaris *dpif = dpif_solaris_cast(dpif_);
	return (dpif_solaris_flow_flush__(dpif));
}

struct dpif_solaris_flow_state {
	struct odputil_keybuf keybuf;
	struct odputil_keybuf maskbuf;
};

struct dpif_solaris_flow_ent {
	struct hmap_node node;
	char flowname[MAXUSERFLOWNAMELEN];
	struct flow f;
	struct flow m;
	struct ofpbuf action;
	struct dpif_flow_stats stats;
};

struct dpif_solaris_flow_iter {
	struct dpif_solaris *dpif;
	struct hmap flows;
	uint32_t bucket;
	uint32_t offset;
	int status;
	struct ovs_mutex mutex;
};

static void
dpif_solaris_flow_dump_state_init(void **statep)
{
	struct dpif_solaris_flow_state *state;

	*statep = state = xmalloc(sizeof (*state));
}

static void
dpif_solaris_flow_dump_state_uninit(void *state_)
{
	struct dpif_solaris_flow_state *state = state_;

	free(state);
}

static void
walk_flow(void *arg, const char *name, boolean_t is_default, struct flow *f,
    struct flow *m, struct ofpbuf *action, uint64_t npackets, uint64_t nbytes,
    uint64_t lastused)
{
	struct dpif_solaris_flow_iter *iter = arg;
	struct dpif_solaris *dpif = iter->dpif;
	struct dpif_solaris_flow_ent *flow;
	struct dpif_solaris_flow *dsflow;

	VLOG_DBG("dpif_solaris_flow_dump_start walk flow %s", name);
	ovs_assert(!is_default);
	flow = xzalloc(sizeof (*flow));
	strlcpy(flow->flowname, name, sizeof (flow->flowname));
	bcopy(f, &flow->f, sizeof (*f));
	bcopy(m, &flow->m, sizeof (*m));
	fat_rwlock_rdlock(&dpif->cls.rwlock);
	if ((dsflow = dpif_solaris_find_flow_by_name(dpif, name)) != NULL) {
		bcopy(&dsflow->flow, &flow->f, sizeof (struct flow));
		bcopy(&dsflow->mask, &flow->m, sizeof (struct flow));
		VLOG_DBG("dpif_solaris_flow_dump_start walk flow %s found "
		    "tunnel 0x%lx src 0x%x dst 0x%x\n", name,
		    flow->f.tunnel.tun_id, flow->f.tunnel.ip_src,
		    flow->f.tunnel.ip_dst);
	} else {
		VLOG_DBG("dpif_solaris_flow_dump_start walk flow %s not found"
		    "\n", name);
	}
	fat_rwlock_unlock(&dpif->cls.rwlock);
	flow->stats.n_packets = npackets;
	flow->stats.n_bytes = nbytes;
	flow->stats.used = lastused / 1000000;
	ofpbuf_init(&flow->action, 0);
	if (ofpbuf_size(action) != 0) {
		ofpbuf_put(&flow->action, ofpbuf_data(action),
		    ofpbuf_size(action));
	}

	hmap_insert(&iter->flows, &flow->node,
	    hash_words((const uint32_t *)flow, sizeof (*flow) / 4, 0));
	ofpbuf_reinit(action, 0);
}

static int
dpif_solaris_flow_dump_start(const struct dpif *dpif_, void **iterp)
{
	struct dpif_solaris *dpif = dpif_solaris_cast(dpif_);
	struct dpif_solaris_flow_iter *iter;
	struct ofpbuf action;

	*iterp = iter = xmalloc(sizeof (*iter));
	iter->dpif = dpif;
	iter->bucket = 0;
	iter->offset = 0;
	iter->status = 0;
	hmap_init(&iter->flows);
	ovs_mutex_init(&iter->mutex);
	ovs_mutex_lock(&iter->mutex);
	ofpbuf_init(&action, 0);
	(void) solaris_flow_walk(iter, &action, B_TRUE, walk_flow);
	ofpbuf_uninit(&action);
	ovs_mutex_unlock(&iter->mutex);
	return (0);
}

static int
dpif_solaris_flow_dump_next(const struct dpif *dpif_ OVS_UNUSED, void *iter_,
    void *state_, const struct nlattr **key, size_t *key_len,
    const struct nlattr **mask, size_t *mask_len,
    const struct nlattr **actions, size_t *actions_len,
    const struct dpif_flow_stats **stats)
{
	struct dpif_solaris_flow_iter *iter = iter_;
	struct dpif_solaris_flow_state *state = state_;
	struct dpif_solaris_flow_ent *flow;
	int error;

	ovs_mutex_lock(&iter->mutex);
	error = iter->status;
	if (!error) {
		struct hmap_node *node;

		node = hmap_at_position(&iter->flows, &iter->bucket,
		    &iter->offset);
		if (node) {
			flow = CONTAINER_OF(node,
			    struct dpif_solaris_flow_ent, node);
			VLOG_DBG("dpif_solaris_flow_dump_next %s",
			    flow->flowname);
		} else {
			iter->status = error = EOF;
		}
	}
	ovs_mutex_unlock(&iter->mutex);
	if (error) {
		return (error);
	}

	if (key) {
		struct ofpbuf buf;
		struct ds s;

		ofpbuf_use_stack(&buf, &state->keybuf, sizeof (state->keybuf));
		odp_flow_key_from_flow(&buf, &flow->f, &flow->m,
		    flow->f.in_port.odp_port);

		*key = ofpbuf_data(&buf);
		*key_len = ofpbuf_size(&buf);

		ds_init(&s);
		odp_flow_format(*key, *key_len, NULL, 0, NULL, &s, true);

		VLOG_DBG("dpif_solaris_flow_dump_next %s key %s",
		    flow->flowname, ds_cstr(&s));
		ds_destroy(&s);
	}

	if (key && mask) {
		struct ofpbuf buf;
		struct ds s;

		ofpbuf_use_stack(&buf, &state->maskbuf,
		    sizeof (state->maskbuf));
		odp_flow_key_from_mask(&buf, &flow->m, &flow->m,
		    flow->f.in_port.odp_port, SIZE_MAX);

		*mask = ofpbuf_data(&buf);
		*mask_len = ofpbuf_size(&buf);

		ds_init(&s);
		odp_flow_format(*key, *key_len, *mask, *mask_len, NULL, &s,
		    true);
		VLOG_DBG("dpif_solaris_flow_dump_next %s mask %s "
		    "mask_key_len %"PRIuSIZE, flow->flowname,
		    ds_cstr(&s), *mask_len);
		ds_destroy(&s);
	}

	if (actions || stats) {
		if (actions) {
			*actions = ofpbuf_data(&flow->action);
			*actions_len = ofpbuf_size(&flow->action);
		}

		if (stats) {
			*stats = &flow->stats;
		}
	}
	VLOG_DBG("dpif_solaris_flow_dump_next %s succeed",
	    flow->flowname);

	return (0);
}

static int
dpif_solaris_flow_dump_done(const struct dpif *dpif OVS_UNUSED, void *iter_)
{
	struct dpif_solaris_flow_iter *iter = iter_;
	struct dpif_solaris_flow_ent *flow, *next;

	ovs_mutex_lock(&iter->mutex);
	HMAP_FOR_EACH_SAFE(flow, next, node, &iter->flows) {
		ofpbuf_uninit(&flow->action);
		hmap_remove(&iter->flows, &flow->node);
		free(flow);
	}
	ovs_mutex_unlock(&iter->mutex);
	hmap_destroy(&iter->flows);
	ovs_mutex_destroy(&iter->mutex);
	free(iter);
	return (0);
}

static int
dpif_solaris_port_output(struct dpif_solaris *dpif, odp_port_t port_no,
    struct ofpbuf *packet, struct flow_tnl *tnl, bool may_steal)
{
	struct msghdr			msghdr;
	struct iovec 			iov;
	struct cmsghdr			*cmsg;
	struct tpacket_auxdata	auxdata;
	char coutmsg[sizeof (auxdata) + sizeof (*cmsg) + _CMSG_HDR_ALIGNMENT];
	size_t		nwritten;
	ssize_t		nbytes = 0;
	const char	*buf = ofpbuf_data(packet);
	size_t		buflen = ofpbuf_size(packet);
	int		error, fd = -1;

	VLOG_DBG("dpif_solaris_port_output %d tunnel %ld", port_no,
	    tnl == NULL ? 0 : tnl->tun_id);

	error = dpif_solaris_get_uplink_port_info(dpif, port_no, NULL, &fd);
	if (error != 0 || fd == -1) {
		if (may_steal) {
			ofpbuf_delete(packet);
		}
		return (error);
	}

	bzero(&msghdr, sizeof (msghdr));
	msghdr.msg_iov = &iov;
	msghdr.msg_iovlen = 1;
	msghdr.msg_control = (void *)_CMSG_HDR_ALIGN(coutmsg);
	msghdr.msg_controllen = sizeof (*cmsg) + sizeof (auxdata);

	iov.iov_len = buflen;
	iov.iov_base = (char *)buf;

	cmsg = CMSG_FIRSTHDR(&msghdr);
	cmsg->cmsg_level = SOL_PACKET;
	cmsg->cmsg_type = PACKET_AUXDATA;
	cmsg->cmsg_len = CMSG_DATA(cmsg) + sizeof (auxdata) - (uchar_t *)cmsg;

	memcpy(&auxdata, CMSG_DATA(cmsg), sizeof (auxdata));
	auxdata.tp_of_port = port_no;
	auxdata.tp_tun_id = 0;
	IN6_IPADDR_TO_V4MAPPED(0, &auxdata.tp_tun_dstip);
	if (tnl != NULL) {
		auxdata.tp_tun_type = 0;
		auxdata.tp_tun_id = htonll(tnl->tun_id);
		IN6_IPADDR_TO_V4MAPPED(tnl->ip_dst, &auxdata.tp_tun_dstip);
	}
	memcpy(CMSG_DATA(cmsg), &auxdata, sizeof (auxdata));
	for (nwritten = 0; nwritten < buflen; nwritten += nbytes) {
		nbytes = sendmsg(fd, &msghdr, 0);
		if (nbytes == -1) {
			if (errno != EAGAIN) {
				error = errno;
				break;
			}
			nbytes = 0;
		} else if (nbytes == 0) {
			error = EIO;
			break;
		}
		iov.iov_len = buflen - (nwritten + nbytes);
		iov.iov_base = (char *)buf + (nwritten + nbytes);
	}

	VLOG_DBG("dpif_solaris_port_output len %"PRIuSIZE" to %d %s",
	    buflen, port_no, error == 0 ? "succeed" :
	    ovs_strerror(error));
	ovs_assert(error != 0 || nwritten == buflen);

	return (0);
}

static struct dpif_solaris *
get_dp_by_name(char *dp_name)
{
	struct dpif_solaris *dpif = NULL;

	ovs_mutex_lock(&dp_solaris_mutex);
	dpif = shash_find_data(&dp_all_solaris, dp_name);
	if (!dpif) {
		VLOG_ERR("get_dp_by_name: couldn't get a hold on dpif for %s",
		    dp_name);
	}
	ovs_mutex_unlock(&dp_solaris_mutex);
	return (dpif);
}

struct netdev *
dpif_solaris_obtain_netdev_to_migrate(char *brname, bool *error)
{
	struct dpif_solaris		*dpif;
	struct dpif_solaris_bridge	*bridge;
	struct dpif_solaris_port	*i_port;
	struct netdev			*i_netdev;
	struct netdev			*netdev_to_migrate = NULL;

	dpif = get_dp_by_name("ovs-system");
	if (dpif == NULL) {
		*error = true;
		return (NULL);
	}
	ovs_rwlock_wrlock(&dpif->bridge_rwlock);
	bridge = dpif_solaris_lookup_bridge(dpif, brname);
	if (bridge == NULL) {
		VLOG_ERR("dpif_solaris_obtain_netdev_to_migrate: Could not "
		    "locate bridge for %s", brname);
		ovs_rwlock_unlock(&dpif->bridge_rwlock);
		*error = true;
		return (NULL);
	}
	/*
	 * If bridge has no uplinks migrate bridge vnic to implicit etherstub.
	 * If it has uplinks, look for an uplink which is not etherstub. If not
	 * get the first uplink from the uplink_port_list.
	 */

	if (list_is_empty(&bridge->uplink_port_list)) {
		ovs_rwlock_unlock(&dpif->bridge_rwlock);
		return (NULL);
	} else {
		LIST_FOR_EACH(i_port, uplink_node, &bridge->uplink_port_list) {
			i_netdev = i_port->netdev;
			if (i_netdev == NULL) {
				VLOG_ERR(
				    "dpif_solaris_obtain_netdev_to_migrate:"
				    " Could not obtain netdev for %s",
				    i_port->name);
				ovs_rwlock_unlock(&dpif->bridge_rwlock);
				*error = true;
				return (NULL);
			}

			if (strcmp(netdev_solaris_get_class(i_netdev),
			    "etherstub") != 0) {
				netdev_to_migrate = i_netdev;
				break;
			}
		}

		if (netdev_to_migrate == NULL) {
			VLOG_DBG("Couldn't find a netdev other than etherstub. "
			    "Thus migrating to first etherstub");
			ASSIGN_CONTAINER(i_port,
			    (&(bridge->uplink_port_list))->next,
			    uplink_node);
			netdev_to_migrate = i_port->netdev;
			if (netdev_to_migrate == NULL) {
				VLOG_ERR(
				    "dpif_solaris_obtain_netdev_to_migrate:"
				    " Could not obtain netdev for %s",
				    i_port->name);
				ovs_rwlock_unlock(&dpif->bridge_rwlock);
				*error = true;
				return (NULL);
			}
		}
	}

	ovs_rwlock_unlock(&dpif->bridge_rwlock);
	return (netdev_to_migrate);
}

/*
 * Migrate the internal port to a different lower link, sets its physname, and
 * refresh its port channel.
 *
 * Note that the internal port's name is the same as bridge name
 */
void
dpif_solaris_migrate_internal_port(const char *bridge, const char *physname)
{
	struct dpif_solaris		*dpif;
	struct dpif_solaris_port	*port;
	int				err;

	VLOG_DBG("dpif_solaris_migrate_internal_port port %s on %s", bridge,
	    physname);

	if ((dpif = get_dp_by_name("ovs-system")) != NULL) {
		ovs_rwlock_wrlock(&dpif->port_rwlock);
		HMAP_FOR_EACH(port, node, &dpif->ports) {
			if (strcmp(port->name, bridge) != 0)
				continue;
			if (port->upcall_fd != -1) {
				(void) setsockopt(port->upcall_fd, SOL_PACKET,
				    PACKET_REM_OF_DEFFLOW, NULL, 0);
				(void) close(port->upcall_fd);
			}
			free(port->physname);
			port->physname = xstrdup(physname);
			err = dpif_solaris_refresh_port_channel(dpif, port,
			    physname, false);
			if (err == 0)
				VLOG_DBG("dpif_solaris_migrate_internal_port %s"
				    " on %s succeed", bridge, physname);
			else
				VLOG_ERR("dpif_solaris_migrate_internal_port %s"
				    " on %s failed %d", bridge, physname, err);
			break;
		}
		ovs_rwlock_unlock(&dpif->port_rwlock);
	}

}

static void
dp_solaris_execute_cb(void *aux_, struct ofpbuf *packet,
    struct pkt_metadata *md, const struct nlattr *a, bool may_steal)
{
	struct dpif_solaris *dpif = aux_;
	int type = nl_attr_type(a);
	odp_port_t pin, pout;
	struct flow_tnl *tnl = NULL;
	int err;

	VLOG_DBG("dp_solaris_execute_cb type %d", type);

	switch ((enum ovs_action_attr)type) {
	case OVS_ACTION_ATTR_OUTPUT: {
		odp_port_t			port_no;

		port_no = u32_to_odp(nl_attr_get_u32(a));

		VLOG_DBG("dp_solaris_execute_cb OVS_ACTION_ATTR_OUTPUT "
		    "%d: inport is %d", port_no, md->in_port.odp_port);

		/*
		 * If in_port number is OFPP_NONE, this means this packet out
		 * request comes from the controller.
		 */
		if (md->in_port.odp_port != ODPP_NONE) {
			err = dpif_solaris_get_uplink_port_info(dpif,
			    md->in_port.odp_port, &pin, NULL);
			if (err != 0) {
				VLOG_DBG("dp_solaris_execute_cb "
				    "OVS_ACTION_ATTR_OUTPUT Error getting "
				    "uplink for inport %d ",
				    md->in_port.odp_port);
				if (may_steal)
					ofpbuf_delete(packet);
				break;
			}
			err = dpif_solaris_get_uplink_port_info(dpif, port_no,
			    &pout, NULL);
			if (err != 0) {
				VLOG_DBG("dp_solaris_execute_cb "
				    "OVS_ACTION_ATTR_OUTPUT Error getting "
				    "uplink for outport %d ", port_no);
				if (may_steal)
					ofpbuf_delete(packet);
				break;
			}
			/*
			 * Bridging across different uplinks is not supported
			 * in the kernel currently, so we disable that support
			 * here as well.
			 */
			if (pin != pout) {
				VLOG_DBG("dp_solaris_execute_cb "
				    "OVS_ACTION_ATTR_OUTPUT inport %d and "
				    "outport %d on different uplinks",
				    md->in_port.odp_port, port_no);
				if (may_steal)
					ofpbuf_delete(packet);
				break;
			}
		}
		if (md->tunnel.ip_dst && (port_no == pout))
			tnl = &md->tunnel;
		(void) dpif_solaris_port_output(dpif, port_no, packet, tnl,
		    may_steal);
		break;
	}

	/*
	 * We'll send the packet back to the kernel and it'll be classified
	 * and we should get it back. XXX Check if this could cause an
	 * infinite loop. This is not terribly effective, but if we use
	 * sockets, it will still get to the kernel before coming back.
	 * Need a short-cut. Note we don't care about any userland data
	 * since we will get it when the packets comes back from the
	 * kernel. Also, currently we always send using the uplink associated
	 * with the in_port number.
	 */
	case OVS_ACTION_ATTR_USERSPACE:	{	/* controller */
		VLOG_DBG("dp_solaris_execute_cb OVS_ACTION_ATTR_USERSPACE");

		err = dpif_solaris_get_uplink_port_info(dpif,
		    md->in_port.odp_port, &pin, NULL);
		if (err != 0) {
			VLOG_DBG("dp_solaris_execute_cb OVS_ACTION_ATTR_OUTPUT "
			    "Error getting uplink for inport %d",
			    md->in_port.odp_port);
			if (may_steal)
				ofpbuf_delete(packet);
			break;
		}
		if (md->tunnel.ip_dst)
			tnl = &md->tunnel;
		VLOG_DBG("dp_solaris_execute_cb OVS_ACTION_ATTR_USERSPACE "
		    "%d", pin);
		(void) dpif_solaris_port_output(dpif, pin, packet, tnl,
		    may_steal);
		break;
	}
	case OVS_ACTION_ATTR_HASH:		/* for bonding */
	case OVS_ACTION_ATTR_RECIRC:		/* for bonding */
	case OVS_ACTION_ATTR_PUSH_VLAN:
	case OVS_ACTION_ATTR_POP_VLAN:
	case OVS_ACTION_ATTR_PUSH_MPLS:
	case OVS_ACTION_ATTR_POP_MPLS:
	case OVS_ACTION_ATTR_SET:
	case OVS_ACTION_ATTR_SAMPLE:
	case OVS_ACTION_ATTR_UNSPEC:
	case __OVS_ACTION_ATTR_MAX:
		VLOG_DBG("dp_solaris_execute_cb type %d", type);
		OVS_NOT_REACHED();
	}
}

static int
dpif_solaris_execute(struct dpif *dpif_, struct dpif_execute *execute)
{
	struct dpif_solaris *dpif = dpif_solaris_cast(dpif_);
	struct pkt_metadata *md = &execute->md;

	if (ofpbuf_size(execute->packet) < ETH_HEADER_LEN ||
	    ofpbuf_size(execute->packet) > UINT16_MAX) {
		VLOG_ERR("dpif_solaris_execute invalid size %d",
		    ofpbuf_size(execute->packet));
		return (EINVAL);
	}

	odp_execute_actions(dpif, execute->packet, false, md, execute->actions,
	    execute->actions_len, dp_solaris_execute_cb);
	return (0);
}

static void
dpif_solaris_destroy_channels(struct dpif_solaris *dpif)
    OVS_REQ_WRLOCK(dpif->upcall_lock)
{
	struct dpif_solaris_port *port;

	if (!dpif->recv_set)
		return;

	ovs_rwlock_wrlock(&dpif->port_rwlock);
	HMAP_FOR_EACH(port, node, &dpif->ports) {
		if (port->upcall_fd != -1) {
			(void) close(port->upcall_fd);
			port->upcall_fd = -1;
		}
	}
	ovs_rwlock_unlock(&dpif->port_rwlock);
	(void) close(dpif->event_rfd);
	(void) close(dpif->event_wfd);
	dpif->event_rfd = dpif->event_wfd = -1;
	dpif->recv_set = false;
}

static int
dpif_solaris_refresh_port_channel(struct dpif_solaris *dpif,
    struct dpif_solaris_port *port, const char *physname, boolean_t notify)
    OVS_REQ_WRLOCK(dpif->port_rwlock)
{
	int fd, flags, onoff = 1;
	struct sockaddr_ll sll;
	datalink_id_t linkid;
	mac_of_ports_t mofport;
	dladm_status_t status;
	int error;

	if (!dpif->recv_set || (port->vtype != OVS_VPORT_TYPE_NETDEV &&
	    port->vtype != OVS_VPORT_TYPE_VXLAN && port->vtype !=
	    OVS_VPORT_TYPE_INTERNAL))
		return (0);

	VLOG_DBG("dpif_solaris_refresh_port_channel(%s) port_no: %d on %s%s",
	    port->linkname, port->port_no, physname, notify ? " notify" : "");

	fd = socket(PF_PACKET, SOCK_RAW, ETH_P_ALL);
	if (fd == -1) {
		VLOG_ERR("dpif_solaris_refresh_port_channel %s failed to "
		    "create socket: %s", port->linkname, ovs_strerror(errno));
		return (errno);
	}

	status = dladm_name2info(dpif->dh, physname, &linkid,
	    NULL, NULL, NULL);
	error = solaris_dladm_status2error(status);
	if (error != 0) {
		VLOG_ERR("dpif_solaris_refresh_port_channel %s failed to get "
		    "linkid: %s", port->linkname, ovs_strerror(error));
		(void) close(fd);
		return (error);
	}

	(void) memset(&sll, 0, sizeof (sll));
	sll.sll_family = AF_PACKET;
	sll.sll_ifindex = linkid;
	sll.sll_protocol = ETH_P_ALL;
	if (bind(fd, (struct sockaddr *)&sll, sizeof (sll)) == -1) {
		error = errno;
		VLOG_ERR("dpif_solaris_refresh_port_channel %s failed to bind: "
		    "%s", port->name, ovs_strerror(error));
		(void) close(fd);
		return (error);
	}

	mofport.mop_port = port->pf_port_no;
	mofport.mop_sport = port->port_no;
	if (setsockopt(fd, SOL_PACKET,
	    PACKET_ADD_OF_DEFFLOW, &mofport, sizeof (mac_of_ports_t)) != 0) {
		error = errno;
		VLOG_ERR("dpif_solaris_refresh_port_channel %s failed to set "
		    "PACKET_ADD_OF_DEFFLOW: %s", port->name,
		    ovs_strerror(error));
		(void) close(fd);
		return (error);
	}

	if (setsockopt(fd, SOL_PACKET,
	    PACKET_AUXDATA, &onoff, sizeof (onoff)) != 0) {
		error = errno;
		VLOG_ERR("dpif_solaris_refresh_port_channel %s failed to set "
		    "PACKET_AUXDATAQ: %s", port->name,
		    ovs_strerror(error));
		(void) setsockopt(fd, SOL_PACKET, PACKET_REM_OF_DEFFLOW,
		    NULL, 0);
		(void) close(fd);
		return (error);
	}

	/* must not block */
	if (((flags = fcntl(fd, F_GETFL, 0)) == -1) ||
	    (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)) {
		error = errno;
		VLOG_ERR("dpif_solaris_refresh_port_channel %s failed to set "
		    "non-block: %s", port->name, ovs_strerror(error));
		(void) setsockopt(fd, SOL_PACKET, PACKET_REM_OF_DEFFLOW,
		    NULL, 0);
		(void) close(fd);
		return (error);
	}

	port->upcall_fd = fd;

	VLOG_DBG("dpif_solaris_refresh_port_channel %s upcall_fd=%d",
	    port->name, port->upcall_fd);

	/* Inform the event_rfd that the port->upcall_fd has been changed */
	if (notify && write(dpif->event_wfd, (char *)(&port->port_no),
	    sizeof (odp_port_t)) < 0) {
		VLOG_ERR("dpif_solaris_refresh_port_channel %s event "
		    "notify failed: %s", port->name, ovs_strerror(errno));
	}

	return (0);
}

/*
 * Synchronizes 'channels' in 'dpif->handlers'  with the set of vports
 * currently in 'dpif' in the kernel, by adding a new set of channels for
 * any kernel vport that lacks one and deleting any channels that have no
 * backing kernel vports.
 */
static int
dpif_solaris_refresh_channels(struct dpif_solaris *dpif, uint32_t n_handlers)
    OVS_REQ_WRLOCK(dpif->upcall_lock)
{
	struct dpif_solaris_port *port;
	int error, flags;
	odp_port_t port_no = 0;
	int fds[2];

	VLOG_DBG("dpif_solaris_refresh_channels %d", n_handlers);
	dpif_solaris_destroy_channels(dpif);

	/*
	 * Setup the event pipe to monitor the port changes, so that
	 * port_channel_fd is able to be refreshed into the pollfds set.
	 */
	if ((pipe(fds)) < 0) {
		error = errno;
		return (error);
	}
	/* must not block */
	if (((flags = fcntl(fds[0], F_GETFL, 0)) == -1) ||
	    (fcntl(fds[0], F_SETFL, flags | O_NONBLOCK) == -1)) {
		error = errno;
		(void) close(fds[0]);
		(void) close(fds[1]);
		return (error);
	}
	if (((flags = fcntl(fds[1], F_GETFL, 0)) == -1) ||
	    (fcntl(fds[1], F_SETFL, flags | O_NONBLOCK) == -1)) {
		error = errno;
		(void) close(fds[0]);
		(void) close(fds[1]);
		return (error);
	}

	dpif->recv_set = true;
	dpif->event_rfd = fds[0];
	dpif->event_wfd = fds[1];

	ovs_rwlock_wrlock(&dpif->port_rwlock);
	HMAP_FOR_EACH(port, node, &dpif->ports) {
		error = dpif_solaris_refresh_port_channel(dpif, port,
		    port->physname, false);
		if (error != 0) {
			ovs_rwlock_unlock(&dpif->port_rwlock);
			dpif_solaris_destroy_channels(dpif);
			return (error);
		}
	}
	ovs_rwlock_unlock(&dpif->port_rwlock);

	/* Inform the event_rfd that all ports' upcall_fd has been changed */
	if (write(dpif->event_wfd, (char *)&port_no, sizeof (odp_port_t)) < 0) {
		VLOG_ERR("dpif_solaris_refresh_channels event notify"
		    "failed: %s", ovs_strerror(errno));
	}
	return (0);
}

static int
dpif_solaris_recv_set_(struct dpif_solaris *dpif, bool enable)
{
	if (dpif->recv_set == enable)
		return (0);

	if (!enable) {
		dpif_solaris_destroy_channels(dpif);
		return (0);
	} else {
		return (dpif_solaris_refresh_channels(dpif, 1));
	}
}

static int
dpif_solaris_recv_set(struct dpif *dpif_, bool enable)
{
	struct dpif_solaris *dpif = dpif_solaris_cast(dpif_);
	int error = 0;

	VLOG_DBG("dpif_solaris_recv_set %s", enable ? "true" : "false");

	ovs_rwlock_wrlock(&dpif->upcall_lock);
	dpif_solaris_recv_set_(dpif, enable);
	ovs_rwlock_unlock(&dpif->upcall_lock);
	return (error);
}

/*
 * For Solaris we will use the queue_id as the priority. The queue id
 * will be used to get the QoS information and used to configure
 * the bandwidth and priority
 */
static int
dpif_solaris_queue_to_priority(const struct dpif *dpif OVS_UNUSED,
    uint32_t queue_id, uint32_t *priority)
{
	*priority = queue_id;
	return (0);
}

static int
dpif_solaris_parse_pkt(struct dpif_solaris *dpif OVS_UNUSED,
    struct ofpbuf *packet, struct pkt_metadata *md, uint16_t action_type,
    struct dpif_upcall *upcall, struct ofpbuf *buf)
{
	struct flow flow;
	void *data;
	size_t buf_size;
	const struct nlattr *userdata = NULL;

	VLOG_DBG("dpif_solaris_parse_pkt");

	if ((buf_size = ofpbuf_size(packet)) < ETH_HEADER_LEN) {
		VLOG_ERR("dpif_solaris_parse_pkt bufsize too small %"PRIuSIZE,
		    buf_size);
		return (EINVAL);
	}

	flow_extract(packet, md, &flow);
	upcall->type = (action_type == FLOW_ACTION_MISSED_PKT) ? DPIF_UC_MISS :
	    DPIF_UC_ACTION;

	/* Allocate buffer big enough for everything. */
	buf_size = ODPUTIL_FLOW_KEY_BYTES;
	if (action_type == FLOW_ACTION_OF_CONTROLLER) {
		struct ofpbuf abuf;
		char slow_path_buf[128];
		const struct nlattr *a;

		VLOG_DBG("dpif_solaris_parse_p:: FLOW_ACTION_OF_CONTROLLER!!");
		ofpbuf_use_stack(&abuf, slow_path_buf, sizeof (slow_path_buf));
		slowpath_to_actions(SLOW_CONTROLLER, &abuf);
		a = nl_attr_find(&abuf, 0, OVS_ACTION_ATTR_USERSPACE);
		if (a != NULL) {
			userdata = nl_attr_find_nested(a,
			    OVS_USERSPACE_ATTR_USERDATA);
			if (userdata != NULL)
				buf_size += NLA_ALIGN(userdata->nla_len);
		}
	}
	buf_size += ofpbuf_size(packet);
	ofpbuf_init(buf, buf_size);

	VLOG_DBG("PARSE flow in_port %d tunnel dst %u", flow.in_port.odp_port,
	    flow.tunnel.ip_dst);
	odp_flow_key_from_flow(buf, &flow, NULL, flow.in_port.odp_port);
	upcall->key = ofpbuf_data(buf);
	upcall->key_len = ofpbuf_size(buf);

	if (userdata != NULL) {
		upcall->userdata = ofpbuf_put(buf, userdata,
		    NLA_ALIGN(userdata->nla_len));
	}

	data = ofpbuf_put(buf, ofpbuf_data(packet), ofpbuf_size(packet));
	ofpbuf_use_stub(&upcall->packet, data, ofpbuf_size(packet));
	ofpbuf_set_size(&upcall->packet, ofpbuf_size(packet));
	return (0);
}

static int
dpif_solaris_recv__(struct dpif_solaris *dpif, uint32_t handler_id OVS_UNUSED,
    struct dpif_upcall *upcall, struct ofpbuf *buf)
    OVS_REQ_WRLOCK(dpif->upcall_lock)
{
	struct iovec iov;
	struct msghdr msg;
	struct cmsghdr *cmsg;
	char cmsg_buf[sizeof (*cmsg) + sizeof (struct tpacket_auxdata) +
	    _CMSG_HDR_ALIGNMENT];
	uint8_t pktbuf[65536];
	int pktlen;
	struct dpif_solaris_port *port;
	odp_port_t port_no;
	uint16_t action_type;
	int error;

	if (!dpif->recv_set) {
		return (EAGAIN);
	}

	(void) read(dpif->event_rfd, (char *)&port_no,
	    sizeof (odp_port_t));

	ovs_rwlock_wrlock(&dpif->port_rwlock);
	HMAP_FOR_EACH(port, node, &dpif->ports) {
		if (port->upcall_fd == -1)
			continue;

		msg.msg_name = NULL;
		msg.msg_namelen = 0;
		msg.msg_iov = &iov;
		msg.msg_iovlen = 1;
		msg.msg_control = (void *)_CMSG_HDR_ALIGN(cmsg_buf);
		msg.msg_controllen = sizeof (cmsg_buf) -
		    (_CMSG_HDR_ALIGN(cmsg_buf) - (uintptr_t)cmsg_buf);
		msg.msg_flags = 0;

		iov.iov_len = sizeof (pktbuf);
		iov.iov_base = pktbuf;
		pktlen = recvmsg(port->upcall_fd, &msg, MSG_TRUNC);
		if (pktlen > 0) {
			struct pkt_metadata	md;
			mactun_info_t		*tuninfop = NULL;
			struct flow_tnl		*tun;
			struct ofpbuf		pkt;
			struct tpacket_auxdata	aux;

			action_type = FLOW_ACTION_OF_MAX;
			for (cmsg = CMSG_FIRSTHDR(&msg); cmsg;
			    cmsg = CMSG_NXTHDR(&msg, cmsg)) {
				if (cmsg->cmsg_len <
				    CMSG_LEN(sizeof (struct tpacket_auxdata)) ||
				    cmsg->cmsg_level != SOL_PACKET ||
				    cmsg->cmsg_type != PACKET_AUXDATA)
					continue;

				memcpy(&aux, CMSG_DATA(cmsg), sizeof (aux));
				action_type = aux.tp_of_action;
				port_no = aux.tp_of_port;
				tuninfop = &aux.tp_tun_info;
				break;
			}

			if (action_type != FLOW_ACTION_MISSED_PKT &&
			    action_type != FLOW_ACTION_OF_CONTROLLER) {
				VLOG_ERR("dpif_solaris_recv__ on port %s len %d"
				    " but with unknown auxdata type %d",
				    port->name, pktlen, action_type);
				continue;
			}

			VLOG_DBG("dpif_solaris_recv__ on port %s len %d "
			    "type %s (src_port = %u)", port->name, pktlen,
			    action_type == FLOW_ACTION_MISSED_PKT ?
			    "miss_pkt" : "fwd_controller", port_no);

			ovs_assert(tuninfop != NULL);
			md = PKT_METADATA_INITIALIZER(port_no);
			if (tuninfop->mti_dst._S6_un._S6_u32[3] != 0) {
				tun = &md.tunnel;
				tun->tun_id = htonll(tuninfop->mti_id);
				tun->flags |= FLOW_TNL_F_KEY;
				tun->ip_src =
				    tuninfop->mti_src._S6_un._S6_u32[3];
				tun->ip_dst =
				    tuninfop->mti_dst._S6_un._S6_u32[3];
				tun->ip_tos = tuninfop->mti_tos;
				tun->ip_ttl = tuninfop->mti_ttl;
				/* TBD? */
				tun->flags |= FLOW_TNL_F_DONT_FRAGMENT;
			}
			ofpbuf_use_const(&pkt, pktbuf, pktlen);
			error = dpif_solaris_parse_pkt(dpif, &pkt, &md,
			    action_type, upcall, buf);
			if (error != 0) {
				VLOG_ERR("dpif_solaris_recv__ parse_pkt on "
				    "port %s action %s failed %d", port->name,
				    action_type == FLOW_ACTION_MISSED_PKT ?
				    "miss_pkt" : "fwd_to_controller",
				    error);
			} else {
				ovs_rwlock_unlock(&dpif->port_rwlock);
				return (0);
			}
		}
	}

	ovs_rwlock_unlock(&dpif->port_rwlock);
	return (EAGAIN);
}

static int
dpif_solaris_recv(struct dpif *dpif_, uint32_t handler_id,
    struct dpif_upcall *upcall, struct ofpbuf *buf)
{
	struct dpif_solaris *dpif = dpif_solaris_cast(dpif_);
	int error;

	ovs_rwlock_rdlock(&dpif->upcall_lock);
	error = dpif_solaris_recv__(dpif, handler_id, upcall, buf);
	ovs_rwlock_unlock(&dpif->upcall_lock);

	return (error);
}

static void
dpif_solaris_recv_wait(struct dpif *dpif_, uint32_t handler_id OVS_UNUSED)
{
	struct dpif_solaris *dpif = dpif_solaris_cast(dpif_);
	struct dpif_solaris_port *port;

	ovs_rwlock_rdlock(&dpif->upcall_lock);
	if (dpif->recv_set) {
		poll_fd_wait(dpif->event_rfd, POLLIN);
		ovs_rwlock_wrlock(&dpif->port_rwlock);
		HMAP_FOR_EACH(port, node, &dpif->ports) {
			if (port->upcall_fd != -1) {
				poll_fd_wait(port->upcall_fd, POLLIN);
			}
		}
		ovs_rwlock_unlock(&dpif->port_rwlock);
	}
	ovs_rwlock_unlock(&dpif->upcall_lock);
}

static void
dpif_solaris_recv_purge__(struct dpif_solaris *dpif)
    OVS_REQ_WRLOCK(dpif->upcall_lock)
{
	struct dpif_solaris_port *port;

	if (dpif->recv_set) {
		drain_rcvbuf(dpif->event_rfd);
		ovs_rwlock_wrlock(&dpif->port_rwlock);
		HMAP_FOR_EACH(port, node, &dpif->ports) {
			drain_rcvbuf(port->upcall_fd);
		}
		ovs_rwlock_unlock(&dpif->port_rwlock);
	}
}

static void
dpif_solaris_recv_purge(struct dpif *dpif_)
{
	struct dpif_solaris *dpif = dpif_solaris_cast(dpif_);

	VLOG_DBG("dpif_solaris_recv_purge");
	ovs_rwlock_wrlock(&dpif->upcall_lock);
	dpif_solaris_recv_purge__(dpif);
	ovs_rwlock_unlock(&dpif->upcall_lock);
}

static int
dpif_solaris_handlers_set(struct dpif *dpif OVS_UNUSED,
    uint32_t n_handlers OVS_UNUSED)
{
	return (0);
}

const struct dpif_class dpif_solaris_class = {
	"system",
	dpif_solaris_enumerate,
	NULL,					/* port_open_type */
	dpif_solaris_open,
	dpif_solaris_close,
	dpif_solaris_destroy,
	NULL,					/* run */
	NULL,					/* wait */
	dpif_solaris_get_stats,
	dpif_solaris_port_add,
	dpif_solaris_port_del,
	dpif_solaris_port_query_by_number,
	dpif_solaris_port_query_by_name,
	NULL, 					/* port_get_pid */
	dpif_solaris_port_dump_start,
	dpif_solaris_port_dump_next,
	dpif_solaris_port_dump_done,
	dpif_solaris_port_poll,
	dpif_solaris_port_poll_wait,
	dpif_solaris_flow_get,
	dpif_solaris_flow_put,
	dpif_solaris_flow_del,
	dpif_solaris_flow_flush,
	dpif_solaris_flow_dump_state_init,
	dpif_solaris_flow_dump_start,
	dpif_solaris_flow_dump_next,
	NULL,				/* flow_dump_next_may_destroy_keys */
	dpif_solaris_flow_dump_done,
	dpif_solaris_flow_dump_state_uninit,
	dpif_solaris_execute,
	NULL,					/* operate */
	dpif_solaris_recv_set,
	dpif_solaris_handlers_set,		/* handlers_set */
	dpif_solaris_queue_to_priority,
	dpif_solaris_recv,
	dpif_solaris_recv_wait,
	dpif_solaris_recv_purge
};
