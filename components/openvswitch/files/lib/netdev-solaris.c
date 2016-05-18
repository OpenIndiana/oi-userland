/*
 * Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Copyright (c) 2009, 2010, 2011, 2012, 2013, 2014 Nicira, Inc.
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

#include <errno.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <net/route.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/sockio.h>
#include <strings.h>

#include <libdllink.h>
#include <kstat2.h>

#include "coverage.h"
#include "dpif-netdev.h"
#include "dynamic-string.h"
#include "fatal-signal.h"
#include "hash.h"
#include "hmap.h"
#include "netdev-provider.h"
#include "netdev-vport.h"
#include "ofpbuf.h"
#include "openflow/openflow.h"
#include "ovs-atomic.h"
#include "packets.h"
#include "poll-loop.h"
#include "shash.h"
#include "socket-util.h"
#include "sset.h"
#include "timer.h"
#include "unaligned.h"
#include "vlog.h"

#include "netdev-solaris.h"
#include "util-solaris.h"
#include "dpif-solaris.h"

/*
 * Enable vlog() for this module
 */
VLOG_DEFINE_THIS_MODULE(netdev_solaris);

/*
 * Per-network device state.
 */
struct netdev_solaris {
	struct netdev up;

	/* Protects all members below. */
	struct ovs_mutex mutex;

	/*
	 * Bit mask of cached properties. These can be cached because
	 * nothing besides vswitchd is altering the properties.
	 */
	unsigned int cache_valid;

	/*
	 * Network device features (e.g., speed, duplex, etc)
	 */
	enum netdev_features current;
	enum netdev_features advertised;
	enum netdev_features supported;
	int get_features_error;

	int ifindex;			/* interface index */
	struct in_addr in4;		/* IPv4 address */
	struct in_addr netmask;		/* IPv4 netmask */
	struct in6_addr in6;		/* IPv6 address */
	unsigned int plumbed;		 /* per-family plumbed */
	unsigned int implicitly_plumbed; /* per-family implicitly plumbed */

	char class[DLADM_PROP_VAL_MAX];	/* datalink class */
	char brname[MAXLINKNAMELEN];	/* bridge name */
	int mtu;			/* datalink MTU */
	uint8_t etheraddr[ETH_ADDR_LEN]; /* MAC address */

	struct tc *tc;			/* traffic control */
};

/*
 * Bits indicating what network device configuration is cached.
 * See cache_valid field above.
 */
enum {
	VALID_IFINDEX		= 1 << 0,
	VALID_ETHERADDR		= 1 << 1,
	VALID_IN4		= 1 << 2,
	VALID_IN6		= 1 << 3,
	VALID_MTU		= 1 << 4,
	VALID_LINKCLASS		= 1 << 5,
	VALID_FEATURES		= 1 << 6
};

/*
 * Used to track state of IP plumbing on network devices.
 */
#define	SOLARIS_IPV4 0x01
#define	SOLARIS_IPV6 0x02

/*
 * Cached socket descriptors.
 */
static int sock4;
static int sock6;

/*
 * Cached kstat2_handle_t. Re-use unless an error causes it to be
 * closed. In that case, cache the handle on the next open.
 */
static kstat2_handle_t	nd_khandle;
static boolean_t	kstat2_handle_initialized = B_FALSE;
static struct ovs_mutex	kstat_mutex = OVS_MUTEX_INITIALIZER;

static int netdev_solaris_init(void);
static struct netdev_solaris *netdev_solaris_cast(const struct netdev *);

/* Maintaining a mapping of every netdev->name to its bridge name. */
struct shash port_to_bridge_map = SHASH_INITIALIZER(&port_to_bridge_map);

/*
 * An instance of a traffic control class.
 *
 * Always associated with a particular network device.
 *
 * Each TC implementation subclasses this with whatever additional data
 * it needs.
 */
struct tc {
	const struct tc_ops *ops;

	/*
	 * Contains "struct tc_queues"s.
	 * Read by generic TC layer.
	 * Written only by TC implementation.
	 */
	struct hmap queues;
};

#define	TC_INITIALIZER(TC, OPS)	{ OPS, HMAP_INITIALIZER(&(TC)->queues) }

/*
 * One traffic control queue.
 *
 * Each TC implementation subclasses this with whatever additional
 * data it needs.
 */
struct tc_queue {
	struct hmap_node hmap_node;	/* In struct tc's "queues" hmap. */
	unsigned int	queue_id;	/* OpenFlow queue ID. */
	long long int	created;	/* Time queue was created, in msecs. */
};

/*
 * A particular kind of traffic control.
 *
 * Each implementation generally maps to one particular Linux qdisc class.
 *
 * The functions below return 0 if successful or a positive errno value on
 * failure, except where otherwise noted.  All of them must be provided,
 * except where otherwise noted.
 */
struct tc_ops {
	/*
	 * Name used by kernel in the TCA_KIND attribute of tcmsg, e.g. "htb".
	 * This is null for tc_ops_default since there is no appropriate
	 * value.
	 */
	const char *linux_name;

	/*
	 * Name used in OVS database, e.g. "linux-htb".  Must be nonnull.
	 */
	const char *ovs_name;

	/*
	 * Number of supported OpenFlow queues, 0 for qdiscs that have no
	 * queues.  The queues are numbered 0 through n_queues - 1.
	 */
	unsigned int n_queues;

	/*
	 * Called to install this TC class on 'netdev'.  The implementation
	 * should make the calls required to set up 'netdev' with the right
	 * qdisc and configure it according to 'details'.  The implementation
	 * may assume that the current qdisc is the default; that is, there
	 * is no need for it to delete the current qdisc before installing
	 * itself.
	 *
	 * The contents of 'details' should be documented as valid for
	 * 'ovs_name' in the "other_config" column in the "QoS" table in
	 * vswitchd/vswitch.xml (which is built as ovs-vswitchd.conf.db(8)).
	 *
	 * This function must return 0 if and only if it sets 'netdev->tc'
	 * to an initialized 'struct tc'.
	 *
	 * This function should always be nonnull.
	 */
	int (*tc_install)(struct netdev *netdev, const struct smap *details);

	/*
	 * Called when the netdev code determines that this TC class's qdisc
	 * is installed on 'netdev', but we didn't install it ourselves and
	 * so don't know any of the details.
	 *
	 * There is nothing for this function to do on Solaris.
	 *
	 * This function must return 0 if and only if it sets 'netdev->tc'
	 * to an initialized 'struct tc'.
	 */
	int (*tc_load)(struct netdev *netdev, struct ofpbuf *nlmsg);

	/*
	 * Destroys the data structures allocated by the implementation as
	 * part of 'tc'.  (This includes destroying 'tc->queues' by calling
	 * tc_destroy(tc).
	 *
	 * This function may be null if 'tc' is trivial.
	 */
	void (*tc_destroy)(struct tc *tc);

	/*
	 * Retrieves details of 'netdev->tc' configuration into 'details'.
	 *
	 * The contents of 'details' should be documented as valid for
	 * 'ovs_name' in the "other_config" column in the "QoS" table in
	 * vswitchd/vswitch.xml (which is built as ovs-vswitchd.conf.db(8)).
	 *
	 * This function may be null if 'tc' is not configurable.
	 */
	int (*qdisc_get)(const struct netdev *netdev, struct smap *details);

	/*
	 * Reconfigures 'netdev->tc' according to 'details'.
	 *
	 * The contents of 'details' should be documented as valid for
	 * 'ovs_name' in the "other_config" column in the "QoS" table in
	 * vswitchd/vswitch.xml (which is built as ovs-vswitchd.conf.db(8)).
	 *
	 * This function may be null if 'tc' is not configurable.
	 */
	int (*qdisc_set)(struct netdev *, const struct smap *details);

	/*
	 * Retrieves details of 'queue' on 'netdev->tc' into 'details'.
	 * 'queue' is one of the 'struct tc_queue's within
	 * 'netdev->tc->queues'.
	 *
	 * The contents of 'details' should be documented as valid for
	 * 'ovs_name' in the "other_config" column in the "Queue" table in
	 * vswitchd/vswitch.xml (which is built as ovs-vswitchd.conf.db(8)).
	 *
	 * This function may be null if 'tc' does not have queues
	 * ('n_queues' is 0).
	 */
	int (*class_get)(const struct netdev *netdev,
	    const struct tc_queue *queue, struct smap *details);

	/*
	 * Configures or reconfigures 'queue_id' on 'netdev->tc' according to
	 * 'details'. The caller ensures that 'queue_id' is less than
	 * 'n_queues'.
	 *
	 * The contents of 'details' should be documented as valid for
	 * 'ovs_name' in the "other_config" column in the "Queue" table in
	 * vswitchd/vswitch.xml (which is built as ovs-vswitchd.conf.db(8)).
	 *
	 * This function may be null if 'tc' does not have queues or its
	 * queues are not configurable.
	 */
	int (*class_set)(struct netdev *, unsigned int queue_id,
	    const struct smap *details);

	/*
	 * Deletes 'queue' from 'netdev->tc'.  'queue' is one of the 'struct
	 * tc_queue's within 'netdev->tc->queues'.
	 *
	 * This function may be null if 'tc' does not have queues or its queues
	 * cannot be deleted.
	 */
	int (*class_delete)(struct netdev *, struct tc_queue *queue);

	/*
	 * Obtains stats for 'queue' from 'netdev->tc'.  'queue' is one of the
	 * 'struct tc_queue's within 'netdev->tc->queues'.
	 *
	 * On success, initializes '*stats'.
	 *
	 * This function may be null if 'tc' does not have queues or if it
	 * cannot report queue statistics.
	 */
	int (*class_get_stats)(const struct netdev *netdev,
	    const struct tc_queue *queue, struct netdev_queue_stats *stats);

	/*
	 * Extracts queue stats from 'nlmsg', which is a response to a
	 * RTM_GETTCLASS message, and passes them to 'cb' along with 'aux'.
	 *
	 * This function may be null if 'tc' does not have queues or if it
	 * cannot report queue statistics.
	 */
	int (*class_dump_stats)(const struct netdev *netdev,
	    const struct ofpbuf *nlmsg, netdev_dump_queue_stats_cb *cb,
	    void *aux);
};

static void
tc_init(struct tc *tc, const struct tc_ops *ops)
{
	tc->ops = ops;
	hmap_init(&tc->queues);
}

static void
tc_destroy(struct tc *tc)
{
	hmap_destroy(&tc->queues);
}

static const struct tc_ops tc_ops_htb;
static const struct tc_ops tc_ops_default;

static const struct tc_ops *const tcs[] = {
	&tc_ops_htb,		/* Hierarchy token bucket */
	&tc_ops_default,	/* Default qdisc */
	NULL
};

static const struct tc_ops *
tc_lookup_ovs_name(const char *name)
{
	const struct tc_ops *const *opsp;

	for (opsp = tcs; *opsp != NULL; opsp++) {
		const struct tc_ops *ops = *opsp;
		if (strcmp(name, ops->ovs_name) == 0) {
			return (ops);
		}
	}
	return (NULL);
}

static struct tc_queue *
tc_find_queue__(const struct netdev *netdev_, unsigned int queue_id,
    size_t hash)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	struct tc_queue		*queue;

	HMAP_FOR_EACH_IN_BUCKET(queue, hmap_node, hash, &netdev->tc->queues) {
		if (queue->queue_id == queue_id) {
			return (queue);
		}
	}
	return (NULL);
}

static struct tc_queue *
tc_find_queue(const struct netdev *netdev, unsigned int queue_id)
{
	return (tc_find_queue__(netdev, queue_id, hash_int(queue_id, 0)));
}

static int
tc_delete_class(const struct netdev *netdev OVS_UNUSED,
    unsigned int handle OVS_UNUSED)
{
	return (0);
}

static int
tc_del_qdisc(struct netdev *netdev_)
{
	const char		*netdev_name = netdev_get_name(netdev_);
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);

	VLOG_DBG("tc_del_qdisc device %s", netdev_name);
	if (netdev->tc) {
		if (netdev->tc->ops->tc_destroy) {
			netdev->tc->ops->tc_destroy(netdev->tc);
		}
		netdev->tc = NULL;
	}
	return (0);
}

/*
 * If 'netdev''s qdisc type and parameters are not yet known, queries the
 * kernel to determine what they are.  Returns 0 if successful, otherwise a
 * positive errno value.
 */
static int
tc_query_qdisc(const struct netdev *netdev_)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const struct tc_ops	*ops;
	int			load_error;
	int			error;

	if (netdev->tc) {
		return (0);
	}

	/*
	 * Either it's a built-in qdisc, or it's a qdisc set up by some
	 * other entity that doesn't have a handle 1:0.  We will assume
	 * that it's the system default qdisc.
	 */
	ops = &tc_ops_default;
	error = 0;

	/* Instantiate it. */
	load_error = ops->tc_load(CONST_CAST(struct netdev *, netdev_), NULL);
	ovs_assert((load_error == 0) == (netdev->tc != NULL));

	return (error ? error : load_error);
}

static bool
is_netdev_solaris_class(const struct netdev_class *netdev_class)
{
	return (netdev_class->init == netdev_solaris_init);
}

static struct netdev_solaris *
netdev_solaris_cast(const struct netdev *netdev)
{
	ovs_assert(is_netdev_solaris_class(netdev_get_class(netdev)));

	return (CONTAINER_OF(netdev, struct netdev_solaris, up));
}

char *
netdev_solaris_get_class(struct netdev *netdev)
{
	return ((netdev_solaris_cast(netdev))->class);
}

static int
netdev_solaris_plumb(const struct netdev *netdev_, sa_family_t af)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	char			*astring;
	int			sock;
	int			proto;
	int			error;

	ovs_assert(af == AF_INET || af == AF_INET6);

	if (af == AF_INET) {
		sock = sock4;
		astring = "IPv4";
		proto = SOLARIS_IPV4;
	} else {
		sock = sock6;
		astring = "IPv6";
		proto = SOLARIS_IPV6;
	}

	if ((netdev->plumbed & proto) != 0)
		return (0);

	error = solaris_plumb_if(sock, netdev_name, af);
	if (error != 0) {
		VLOG_ERR("%s device could not be plumbed", netdev_name);
		return (error);
	}
	VLOG_DBG("%s device plumbed for %s", netdev_name, astring);

	netdev->implicitly_plumbed |= proto;
	netdev->plumbed |= proto;
	return (0);
}

static int
netdev_solaris_unplumb(const struct netdev *netdev_, sa_family_t af)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	char			*astring;
	int			sock;
	int			proto;
	int			error;

	ovs_assert(af == AF_INET || af == AF_INET6);

	if (af == AF_INET) {
		sock = sock4;
		astring = "IPv4";
		proto = SOLARIS_IPV4;
	} else {
		sock = sock6;
		astring = "IPv6";
		proto = SOLARIS_IPV6;
	}

	if ((netdev->implicitly_plumbed & proto) == 0 &&
	    (netdev->up.netdev_class != &netdev_internal_class)) {
		return (0);
	}

	error = solaris_unplumb_if(sock, netdev_name, af);
	if (error != 0) {
		if (error == ENXIO &&
		    netdev->up.netdev_class == &netdev_internal_class) {
			return (0);
		}
		VLOG_ERR("%s device could not be unplumbed %d", netdev_name,
		    error);
	}
	VLOG_ERR("%s device unplumbed for %s", netdev_name, astring);
	netdev->implicitly_plumbed &= ~proto;
	netdev->plumbed &= ~proto;

	return (0);
}

struct solaris_netdev_sdmap {
	const char *sns_val;
	enum netdev_features sns_feature;
};

static int
netdev_solaris_chk_speed_duplex(const char *netdev_name,
    const char *field_name, enum netdev_features *features)
{
	struct solaris_netdev_sdmap map [] = {
		{"10G-f", NETDEV_F_10GB_FD},
		{"1G-f", NETDEV_F_1GB_FD},
		{"1G-h", NETDEV_F_1GB_HD},
		{"100M-f", NETDEV_F_100MB_FD},
		{"100M-h", NETDEV_F_100MB_HD},
		{"10M-f", NETDEV_F_100MB_FD},
		{"10M-h", NETDEV_F_10MB_HD},
		{"40G-f", NETDEV_F_40GB_FD},
		{"100G-f", NETDEV_F_100GB_FD},
		{"1T-f", NETDEV_F_1TB_FD},
		{NULL, 	NETDEV_F_OTHER},
	};
	struct solaris_netdev_sdmap *snsp;
	char	buffer[DLADM_PROP_VAL_MAX];
	int	i;
	int	error;

	error = solaris_get_dlprop(netdev_name, "speed-duplex", field_name,
	    buffer, sizeof (buffer));
	if (error != 0) {
		VLOG_ERR("Unable to retrieve feature speed-duplex for %s "
		    "device", netdev_name);
		return (error);
	}
	snsp = map;
	for (i = 0; snsp[i].sns_val != NULL; i++) {
		if (strstr(buffer, snsp[i].sns_val) != NULL)
			*features |= snsp[i].sns_feature;
	}
	return (0);
}

static int
netdev_solaris_read_features(struct netdev_solaris *netdev,
    const char *netdev_name)
{
	char	buffer[DLADM_PROP_VAL_MAX];
	int	error = 0;
	int	speed;
	bool	full;

	if (netdev->cache_valid & VALID_FEATURES)
		goto exit;

	/*
	 * Supported features
	 *
	 * Unsupported features:
	 * NETDEV_F_COPPER
	 * NETDEV_F_FIBER
	 * NETDEV_F_PAUSE;
	 * NETDEV_F_PAUSE_ASYM;
	 */
	netdev->supported = 0;
	if ((error = netdev_solaris_chk_speed_duplex(netdev_name,
	    "possible", &netdev->supported)) != 0)
		goto exit;
	/*
	 * Advertised features.
	 *
	 * Unsupported features:
	 * NETDEV_F_COPPER
	 * NETDEV_F_FIBER
	 * NETDEV_F_PAUSE;
	 * NETDEV_F_PAUSE_ASYM;
	 */
	netdev->advertised = 0;
	if ((error = netdev_solaris_chk_speed_duplex(netdev_name,
	    "current", &netdev->advertised)) != 0)
		goto exit;

	/* Current settings. */
	error = solaris_get_dlprop(netdev_name, "speed", "current", buffer,
	    sizeof (buffer));
	if (error != 0) {
		VLOG_ERR("Unable to retrieve speed for %s device",
		    netdev_name);
		goto exit;
	}
	speed = atoi(buffer);

	error = solaris_get_dlprop(netdev_name, "duplex", "current", buffer,
	    sizeof (buffer));
	if (error != 0) {
		VLOG_ERR("Unable to retrieve duplex for %s device",
		    netdev_name);
		goto exit;
	}
	full = (strcmp(buffer, "full") == 0);

	speed /= 1000000;
	if (speed == 10) {
		netdev->current = full ? NETDEV_F_10MB_FD : NETDEV_F_10MB_HD;
	} else if (speed == 100) {
		netdev->current = full ? NETDEV_F_100MB_FD : NETDEV_F_100MB_HD;
	} else if (speed == 1000) {
		netdev->current = full ? NETDEV_F_1GB_FD : NETDEV_F_1GB_HD;
	} else if (speed == 10000) {
		netdev->current = NETDEV_F_10GB_FD;
	} else if (speed == 40000) {
		netdev->current = NETDEV_F_40GB_FD;
	} else if (speed == 100000) {
		netdev->current = NETDEV_F_100GB_FD;
	} else if (speed == 1000000) {
		netdev->current = NETDEV_F_1TB_FD;
	} else {
		netdev->current = 0;
	}
	netdev->advertised |= (netdev->supported & NETDEV_F_AUTONEG);
	netdev->cache_valid |= VALID_FEATURES;
exit:
	netdev->get_features_error = error;
	return (error);
}

static int
netdev_solaris_init(void)
{
	int error;

	sock4 = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock4 < 0) {
		error = errno;
		VLOG_ERR("failed to create AF_INET socket (%s)",
		    ovs_strerror(error));
		return (error);
	}

	sock6 = socket(AF_INET6, SOCK_DGRAM, 0);
	if (sock6 < 0) {
		error = errno;
		VLOG_ERR("failed to create AF_INET6 socket (%s)",
		    ovs_strerror(error));
		return (error);
	}

	error = solaris_init_rad();
	return (error);
}

static void
netdev_solaris_run(void)
{
}

static void
netdev_solaris_wait(void)
{
}

static struct netdev *
netdev_solaris_alloc(void)
{
	struct netdev_solaris *netdev = xzalloc(sizeof (*netdev));

	return (&netdev->up);
}

static void
netdev_solaris_add_port_to_bridge_mapping(const struct netdev
		*netdev, const char *brname)
{
	VLOG_DBG("netdev_solaris_add_port_to_bridge_mapping: adding a mapping "
	    "<%s,%s> to port_to_bridge_map", netdev->name, brname);
	shash_add_nocopy(&port_to_bridge_map, netdev->name, brname);
}

static int
netdev_solaris_unconfigure_uplink(const struct netdev *netdev_)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	int			error;
	char			curr_lower[DLADM_PROP_VAL_MAX];
	struct netdev		*netdev_to_migrate = NULL;
	char			*new_lower = NULL;
	bool			b_error = false;

	VLOG_DBG("netdev_solaris_unconfigure_uplink device %s", netdev_name);

	error = solaris_get_dlprop(netdev->brname, "lower-link", "current",
	    curr_lower, sizeof (curr_lower));
	if (error) {
		VLOG_ERR("netdev_solaris_unconfigure_uplink couldn't obtain "
		    "bridge(%s) lowerlink", netdev->brname);
		return (0);
	}

	if (strcmp(netdev_name, curr_lower) == 0) {
		/*
		 * The uplink which we are trying to remove has bridge vnic on
		 * top of it. We need to migrate bridge vnic to a different
		 * uplink or to ovs.etherstub0 if uplink_port_list is empty.
		 */
		VLOG_DBG("netdev_solaris_unconfigure_uplink: unconfiguring the "
		    "uplink (%s) which is the bridge %s's lowerlink (%s)",
		    netdev_name, netdev->brname, curr_lower);

		netdev_to_migrate = dpif_solaris_obtain_netdev_to_migrate(
		    netdev->brname, &b_error);
		if (b_error) {
			VLOG_ERR("netdev_solaris_unconfigure_uplink: couldn't "
			    "obtain netdev_to_migrate for bridge vnic %s",
			    netdev->brname);
			return (0);
		}

		if (netdev_to_migrate == NULL)
			new_lower = NETDEV_IMPL_ETHERSTUB;
		else
			new_lower = netdev_to_migrate->name;

		VLOG_DBG("netdev_solaris_unconfigure_uplink migrating bridge "
		    "vnic to %s", new_lower);

		error = solaris_modify_vnic(new_lower, netdev->brname);
		if (error != 0) {
			VLOG_ERR("failed to unconfigure %s as uplink for %s: "
			    "%s", netdev_name, netdev->brname,
			    ovs_strerror(error));
			return (0);
		}

		/*
		 * reset internal port's physname and refresh its port channel.
		 */
		dpif_solaris_migrate_internal_port(netdev->brname, new_lower);
	}
	return (0);
}

static int
netdev_solaris_configure_uplink(const struct netdev *netdev_,
    const char *brname)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*new_uplink = netdev_get_name(netdev_);
	char			curr_lower[DLADM_PROP_VAL_MAX];
	int			error;
	const char		*netdev_existing_class;
	struct netdev		*i_netdev;
	boolean_t		migrated = B_FALSE;

	VLOG_DBG("netdev_solaris_configure_uplink device %s", new_uplink);

	/*
	 * Normally, we would expect to see that the bridge VNIC has already
	 * been created by a call to netdev_solaris_construct() to create the
	 * bridge netdev. However, on a service restart ovs-vswitchd sometimes
	 * adds the lower-link port prior to adding the bridge's internal port.
	 * As a result, we need to create the bridge VNIC here if it does not
	 * already exist.
	 */
	error = solaris_get_dlprop(brname, "lower-link", "current",
	    curr_lower, sizeof (curr_lower));
	VLOG_DBG("netdev_solaris_configure_uplink lower-link:%s", curr_lower);

	if (error == ENODEV) {
		/*
		 * No implicit VNIC being created yet, create it now
		 */
		VLOG_DBG("%s vnic being created on %s", brname, new_uplink);
		error = solaris_create_vnic(new_uplink, brname);
		if (error == 0) {
			(void) strlcpy(netdev->brname, brname,
			    sizeof (netdev->brname));
		} else {
			VLOG_ERR("Failed to create vnic for %s: %s",
			    brname, ovs_strerror(error));
		}
		goto exit;
	} else if (error != 0) {
		VLOG_ERR("Failed to get the lower-link for %s: %s",
		    brname, ovs_strerror(error));
		goto exit;
	}

	/*
	 * If the lower-link is already set correctly, then return with
	 * success.
	 */
	if (strcmp(curr_lower, new_uplink) == 0) {
		VLOG_DBG("netdev_solaris_configure_uplink lower-link(%s) is "
		    "already correctly set. (%s)", curr_lower, new_uplink);
		error = 0;
		goto exit;
	}

	if (strcmp(curr_lower, NETDEV_IMPL_ETHERSTUB) == 0) {
		/*
		 * Bridge vnic is on ovs.etherstub0. We have to migrate the
		 * bridge vnic to the uplink
		 */
		VLOG_DBG("bridge vnic %s is on %s, migrating it to %s",
		    brname, curr_lower, new_uplink);

		error = solaris_modify_vnic(new_uplink, brname);
		if (error != 0) {
			VLOG_ERR("failed to configure %s as uplink: %s",
			    new_uplink, ovs_strerror(error));
			goto exit;
		}
		migrated = B_TRUE;
	} else {
		/*
		 * Bridge vnic is already on an uplink. Now we see if the
		 * uplink to be added is other than etherstub or not.
		 * If the bridge vnic is currently residing on an etherstub
		 * and the one to be configured is not etherstub,
		 * then we migrate the bridge vnic.
		 */
		i_netdev = netdev_from_name(curr_lower);
		if (!i_netdev) {
			VLOG_ERR("netdev_solaris_configure_uplink error "
			    "in fetching lower-link netdev for %s", curr_lower);
			goto exit;
		}
		/* i_netdev->ref_cnt--; */
		netdev_close(i_netdev);

		netdev_existing_class = netdev_solaris_get_class(i_netdev);
		if ((strcmp(netdev_existing_class, "etherstub") == 0) &&
		    (strcmp(netdev->class, "etherstub") != 0)) {
			error = solaris_modify_vnic(new_uplink, brname);
			if (error != 0) {
				VLOG_ERR("failed to configure %s as uplink: %s",
				    new_uplink, ovs_strerror(error));
				goto exit;
			}
			migrated = B_TRUE;
		}
	}
	(void) strlcpy(netdev->brname, brname, sizeof (netdev->brname));

exit:
	/*
	 * reset internal port's physname and refresh its port channel.
	 */
	if (migrated)
		dpif_solaris_migrate_internal_port(brname, new_uplink);
	return (error);
}

static boolean_t
solaris_is_if_plumbed(struct netdev *netdev_, sa_family_t af, uint64_t *flags)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	int			sock;
	int			proto;
	int			error;
	char			*astring;

	ovs_assert(af == AF_INET || af == AF_INET6);

	if (af == AF_INET) {
		sock = sock4;
		astring = "IPv4";
		proto = SOLARIS_IPV4;
	} else {
		sock = sock6;
		astring = "IPv6";
		proto = SOLARIS_IPV6;
	}
	error = solaris_if_enabled(sock, netdev_name, flags);
	if (error == 0) {
		netdev->plumbed |= proto;
	} else if (error != ENXIO) {
		VLOG_DBG("netdev_is_if_plumbed %s device encountered "
		    "error %d for %s", netdev_name, error, astring);
	}
	return (error == 0);
}

int
netdev_create_impl_etherstub(void)
{
	int error;

	error = solaris_create_etherstub(NETDEV_IMPL_ETHERSTUB);
	if (error != 0) {
		VLOG_ERR("netdev_create_impl_etherstub: failed to create %s: "
		    "%s", NETDEV_IMPL_ETHERSTUB, ovs_strerror(error));
	} else {
		boolean_t bval = B_TRUE;
		error = solaris_set_dlprop_boolean(NETDEV_IMPL_ETHERSTUB,
		    "openvswitch", &bval, B_FALSE);
		if (error != 0) {
			(void) solaris_delete_etherstub(NETDEV_IMPL_ETHERSTUB);
			VLOG_ERR("netdev_create_impl_etherstub: failed to "
			    "set 'openvswitch' property on %s: %s: ",
			    NETDEV_IMPL_ETHERSTUB, ovs_strerror(error));
		}
	}
	return (error);
}

void
netdev_delete_impl_etherstub(void)
{
	boolean_t	bval = B_FALSE;
	int		error;

	error = solaris_set_dlprop_boolean(NETDEV_IMPL_ETHERSTUB,
	    "openvswitch", &bval, B_FALSE);
	if (error != 0) {
		VLOG_ERR("netdev_create_impl_etherstub: failed to "
		    "set 'openvswitch' property on %s: %s: ",
		    NETDEV_IMPL_ETHERSTUB, ovs_strerror(error));
	} else {
		error = solaris_delete_etherstub(NETDEV_IMPL_ETHERSTUB);
		if (error != 0) {
			VLOG_ERR("netdev_delete_impl_etherstub: failed to "
			    "delete %s: %s", NETDEV_IMPL_ETHERSTUB,
			    ovs_strerror(error));
		}
	}
}

boolean_t
netdev_impl_etherstub_exists(void)
{
	char	prop[DLADM_PROP_VAL_MAX];
	int	error;

	error = solaris_get_dlprop(NETDEV_IMPL_ETHERSTUB, "openvswitch",
	    "current", prop, sizeof (prop));
	if (error == ENODEV)
		return (B_FALSE);

	/*
	 * If the implicit etherstub exists, but the openvswitch
	 * property is not set, then something has gone wrong.
	 */
	if (strcmp(prop, "1") != 0) {
		VLOG_FATAL("%s does not have openvswitch property set",
		    NETDEV_IMPL_ETHERSTUB);
	}

	return (B_TRUE);
}

/*
 * Creates system and internal devices. Really very little to
 * do here given that neither system or internal devices must
 * exist in the kernel yet.
 */
static int
netdev_solaris_construct(struct netdev *netdev_)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	char			buffer[DLADM_PROP_VAL_MAX];
	uint64_t		flags;
	int			error;

	ovs_mutex_init(&netdev->mutex);
	if (netdev->up.netdev_class != &netdev_internal_class) {
		VLOG_DBG("netdev_solaris_construct system device %s",
		    netdev_name);
	} else {
		VLOG_DBG("netdev_solaris_construct internal device %s",
		    netdev_name);
	}
	netdev->implicitly_plumbed = 0;
	netdev->plumbed = 0;

	(void) solaris_is_if_plumbed(netdev_, AF_INET, &flags);
	(void) solaris_is_if_plumbed(netdev_, AF_INET6, &flags);

	/*
	 * loopback is illegal.
	 */
	if (netdev->plumbed != 0 && flags & NETDEV_LOOPBACK) {
		VLOG_ERR("%s: cannot add a loopback device",
		    netdev_name);
		return (EINVAL);
	}

	if (netdev->up.netdev_class == &netdev_internal_class) {
		error = solaris_get_dlprop(netdev_name, "lower-link",
		    "current", buffer, sizeof (buffer));
		if (error == ENODEV) {
			error = solaris_create_vnic(NETDEV_IMPL_ETHERSTUB,
			    netdev_name);
			if (error != 0) {
				VLOG_ERR("failed to configure %s as uplink: "
				"%s", netdev_name, ovs_strerror(error));
				return (error);
			}
		} else if (error != 0) {
			VLOG_ERR("Failed to get the lower-link for %s: %s",
			    netdev_name, ovs_strerror(error));
		}
	}
	return (0);
}

static void
netdev_solaris_destruct(struct netdev *netdev_)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	int			error;

	VLOG_DBG("netdev_solaris_destruct device %s", netdev_name);

	/*
	 * If implicitly plumbed, then unplumb it.
	 */
	(void) netdev_solaris_unplumb(netdev_, AF_INET);
	(void) netdev_solaris_unplumb(netdev_, AF_INET6);

	if (netdev->up.netdev_class == &netdev_internal_class) {
		error = solaris_delete_vnic(netdev_name);
		if (error != 0) {
			VLOG_ERR("failed to delete %s: %s",
			    netdev_name, ovs_strerror(error));
		}
	} else {
		if (netdev->brname[0] != '\0') {
			netdev_solaris_unconfigure_uplink(netdev_);
		}
	}

	ovs_mutex_destroy(&netdev->mutex);
}

static void
netdev_solaris_dealloc(struct netdev *netdev_)
{
	struct netdev_solaris *netdev = netdev_solaris_cast(netdev_);

	free(netdev);
}

/*
 * Attempts to set 'netdev''s MAC address to 'mac'. Returns 0 if successful,
 * otherwise a positive errno value.
 */
static int
netdev_solaris_set_etheraddr(struct netdev *netdev_,
    const uint8_t mac[ETH_ADDR_LEN])
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	char			buffer[128];
	int			error = 0;

	VLOG_DBG("netdev_solaris_set_etheraddr device %s", netdev_name);

	ovs_mutex_lock(&netdev->mutex);
	if ((netdev->cache_valid & VALID_ETHERADDR) &&
	    (eth_addr_equals(netdev->etheraddr, mac))) {
		goto exit;
	}

	/*
	 * In case there is some kind of failure, invalidate
	 * the cached value.
	 */
	netdev->cache_valid &= ~VALID_ETHERADDR;

	/*
	 * MAC addresses are datalink properties.
	 */
	(void) snprintf(buffer, sizeof (buffer), ETH_ADDR_FMT,
	    ETH_ADDR_ARGS(mac));
	error = solaris_set_dlprop_string(netdev_name, "mac-address", buffer,
	    B_TRUE);
	if (error != 0) {
		VLOG_ERR("set etheraddr %s on %s device failed: %s",
		    buffer, netdev_name, ovs_strerror(error));
		goto exit;
	}

	memcpy(netdev->etheraddr, mac, ETH_ADDR_LEN);
	netdev->cache_valid |= VALID_ETHERADDR;
	netdev_change_seq_changed(netdev_);

exit:
	ovs_mutex_unlock(&netdev->mutex);
	return (error);
}

static int
netdev_solaris_get_dlclass(const struct netdev *netdev_)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	char			buffer[DLADM_PROP_VAL_MAX];
	int			error = 0;

	if (netdev->cache_valid & VALID_LINKCLASS)
		goto exit;

	/*
	 * Get the datalink class for this link.
	 */
	error = solaris_get_dlclass(netdev_name, buffer, sizeof (buffer));
	if (error != 0) {
		VLOG_ERR("Unable to retrieve linkclass for %s device, %d",
		    netdev_name, error);
		goto exit;
	}

	(void) strlcpy(netdev->class, buffer, sizeof (netdev->class));
	netdev->cache_valid |= VALID_LINKCLASS;
exit:
	return (error);
}

/*
 * Determines if this netdev is an uplink for the bridge.
 */
static bool
netdev_solaris_is_uplink(const struct netdev *netdev_)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);

	VLOG_DBG("netdev_solaris_is_uplink device %s", netdev_name);
	if (netdev_solaris_get_dlclass(netdev_) != 0)
		return (false);
	return (solaris_is_uplink_class(netdev->class));
}

static int
netdev_solaris_get_etheraddr(const struct netdev *netdev_,
    uint8_t mac[ETH_ADDR_LEN])
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	char			buffer[DLADM_PROP_VAL_MAX];
	int			error = 0;

	VLOG_DBG("netdev_solaris_get_etheraddr device %s", netdev_name);

	ovs_mutex_lock(&netdev->mutex);
	/*
	 * Only the bridge ethernet address can be changed outside the
	 * knowledge of vswitchd (when the uplink is added and the bridge
	 * VNIC is moved to the uplink).
	 */
	if ((netdev->cache_valid & VALID_ETHERADDR) &&
	    (netdev->up.netdev_class != &netdev_internal_class)) {
		memcpy(mac, netdev->etheraddr, ETH_ADDR_LEN);
		goto exit;
	}

	/*
	 * MAC addresses are datalink properties.
	 */
	error = solaris_get_dlprop(netdev_name, "mac-address", "current",
	    buffer, sizeof (buffer));
	if (error != 0) {
		VLOG_ERR("Unable to retrieve etheraddr for %s device",
		    netdev_name);
		goto exit;
	}

	if (!eth_addr_from_string(buffer, mac)) {
		VLOG_ERR("Invalid etheraddr for %s device", netdev_name);
		error = EINVAL;
		goto exit;
	}

	memcpy(netdev->etheraddr, mac, ETH_ADDR_LEN);
	netdev->cache_valid |= VALID_ETHERADDR;
exit:
	ovs_mutex_unlock(&netdev->mutex);
	return (error);
}

static int
netdev_solaris_get_mtu__(struct netdev_solaris *netdev, int *mtup,
    const char *netdev_name)
{
	char	buffer[DLADM_PROP_VAL_MAX];
	int	mtu;
	int	error = 0;

	if (netdev->cache_valid & VALID_MTU) {
		*mtup = netdev->mtu;
		return (0);
	}

	/*
	 * MTU is a datalink property
	 */
	error = solaris_get_dlprop(netdev_name, "mtu", "current", buffer,
	    sizeof (buffer));
	if (error != 0) {
		VLOG_ERR("Unable to retrieve mtu for %s device",
		    netdev_name);
		return (error);
	}

	mtu = atoi(buffer);
	if (mtu == 0) {
		VLOG_ERR("Invalid mtu for %s device", netdev_name);
		error = EINVAL;
		return (error);
	}

	netdev->mtu = *mtup = mtu;
	netdev->cache_valid |= VALID_MTU;
	return (0);
}

/*
 * Returns the maximum size of transmitted (and received) packets on 'netdev',
 * in bytes, not including the hardware header; thus, this is typically 1500
 * bytes for Ethernet devices.
 */
static int
netdev_solaris_get_mtu(const struct netdev *netdev_, int *mtup)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	int			error = 0;

	VLOG_DBG("netdev_solaris_get_mtu device %s", netdev_name);

	if (!netdev_) {
		VLOG_DBG("netdev_solaris_get_mtu null netdevs");
		return (error);
	}

	ovs_mutex_lock(&netdev->mutex);
	error = netdev_solaris_get_mtu__(netdev, mtup, netdev_name);
	ovs_mutex_unlock(&netdev->mutex);
	return (error);
}

/*
 * Sets the maximum size of transmitted (MTU) for given device.
 */
static int
netdev_solaris_set_mtu(const struct netdev *netdev_ OVS_UNUSED, int mtu)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	uint64_t		ulval = mtu;
	int			error = 0;

	VLOG_DBG("netdev_solaris_set_mtu device %s", netdev_name);

	ovs_mutex_lock(&netdev->mutex);
	if ((netdev->cache_valid & VALID_MTU && netdev->mtu == mtu))
		goto exit;

	/*
	 * In case there is some kind of failure, invalidate
	 * the cached value.
	 */
	netdev->cache_valid &= ~VALID_MTU;

	/*
	 * MTU is a datalink property.
	 */
	error = solaris_set_dlprop_ulong(netdev_name, "mtu", &ulval, B_TRUE);
	if (error != 0) {
		VLOG_ERR("set mtu on %s device failed: %s",
		    netdev_name, ovs_strerror(error));
		goto exit;
	}

	netdev->mtu = mtu;
	netdev->cache_valid |= VALID_MTU;
	netdev_change_seq_changed(netdev_);

exit:
	ovs_mutex_unlock(&netdev->mutex);
	return (error);
}

/*
 * Returns the ifindex of 'netdev', if successful, as a positive number.
 * On failure, returns a negative errno.
 */
static int
netdev_solaris_get_ifindex(const struct netdev *netdev_)
{
	struct netdev_solaris 	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	int			ifindex;
	int			error = 0;

	VLOG_DBG("netdev_solaris_get_ifindex device %s", netdev_name);

	ovs_mutex_lock(&netdev->mutex);
	if (netdev->cache_valid & VALID_IFINDEX) {
		ifindex = netdev->ifindex;
		goto exit;
	}

	ifindex = (int)if_nametoindex(netdev_name);
	if (ifindex <= 0) {
		error = errno;
		goto exit;
	}

	netdev->ifindex = ifindex;
	netdev->cache_valid |= VALID_IFINDEX;

exit:
	ovs_mutex_unlock(&netdev->mutex);
	return (error ? -error : ifindex);
}

/*
 * Retrieves current device stats for 'netdev-solaris'.
 */
static int
netdev_solaris_get_stats(const struct netdev *netdev_,
    struct netdev_stats *stats)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	kstat2_status_t		stat;
	kstat2_map_t		map;
	char			kuri[1024];
	char			devname[DLADM_PROP_VAL_MAX];
	char			modname[DLADM_PROP_VAL_MAX];
	char			kstat_name[MAXLINKNAMELEN];
	char			*name;
	zoneid_t		zid;
	uint_t			instance;
	int			error = 0;
	boolean_t		is_uplink;

	VLOG_DBG("netdev_solaris_get_stats device %s", netdev_name);

	is_uplink = netdev_solaris_is_uplink(netdev_);

	/*
	 * Initialize statistics only supported on uplink.
	 */
	stats->rx_length_errors = 0;
	stats->rx_missed_errors = 0;
	stats->rx_over_errors = 0;

	/*
	 * Unsupported on Solaris.
	 */
	stats->rx_crc_errors = UINT64_MAX;
	stats->rx_frame_errors = UINT64_MAX;
	stats->rx_fifo_errors = UINT64_MAX;
	stats->tx_aborted_errors = UINT64_MAX;
	stats->tx_carrier_errors = UINT64_MAX;
	stats->tx_fifo_errors = UINT64_MAX;
	stats->tx_heartbeat_errors = UINT64_MAX;
	stats->tx_window_errors	= UINT64_MAX;

	ovs_mutex_lock(&kstat_mutex);
	if (!kstat2_handle_initialized) {
		VLOG_DBG("netdev_solaris_get_stats initializing handle");
		if (!kstat_handle_init(&nd_khandle)) {
			error = -1;
			goto done;
		}
		kstat2_handle_initialized = B_TRUE;
	} else if (!kstat_handle_update(nd_khandle)) {
		VLOG_DBG("netdev_solaris_get_stats error updating stats");
		kstat_handle_close(&nd_khandle);
		kstat2_handle_initialized = B_FALSE;
		error = -1;
		goto done;
	}
	name = (char *)netdev_name;
	instance = 0;
	if (strchr(netdev_name, '/') != NULL) {
		(void) solaris_dlparse_zonelinkname(netdev_name, kstat_name,
		    &zid);
		name = kstat_name;
		instance = zid;
	}
	(void) snprintf(kuri, sizeof (kuri), "kstat:/net/link/%s/%d",
	    name, instance);
	stat = kstat2_lookup_map(nd_khandle, kuri, &map);
	if (stat != KSTAT2_S_OK) {
		VLOG_WARN("kstat2_lookup_map of %s failed: %s", kuri,
		    kstat2_status_string(stat));
	} else {
		if (is_uplink) {
			stats->rx_packets = get_nvvt_int(map, "ipackets64");
			stats->tx_packets = get_nvvt_int(map, "opackets64");
			stats->rx_bytes = get_nvvt_int(map, "rbytes");
			stats->tx_bytes = get_nvvt_int(map, "obytes");
			stats->rx_errors = get_nvvt_int(map, "ierrors");
			stats->tx_errors = get_nvvt_int(map, "oerrors");
		} else {
			stats->tx_packets = get_nvvt_int(map, "ipackets64");
			stats->rx_packets = get_nvvt_int(map, "opackets64");
			stats->tx_bytes = get_nvvt_int(map, "rbytes");
			stats->rx_bytes = get_nvvt_int(map, "obytes");
			stats->tx_errors = get_nvvt_int(map, "ierrors");
			stats->rx_errors = get_nvvt_int(map, "oerrors");
		}
		stats->collisions = get_nvvt_int(map, "collisions");
		stats->multicast = get_nvvt_int(map, "multircv") +
		    get_nvvt_int(map, "multixmt");
	}

	(void) snprintf(kuri, sizeof (kuri), "kstat:/net/%s/link/%d",
	    name, instance);
	stat = kstat2_lookup_map(nd_khandle, kuri, &map);
	if (stat != KSTAT2_S_OK) {
		VLOG_WARN("kstat2_lookup_map of %s failed: %s", kuri,
		    kstat2_status_string(stat));
	} else {
		if (is_uplink) {
			stats->rx_dropped = get_nvvt_int(map, "idrops");
			stats->tx_dropped = get_nvvt_int(map, "odrops");
		} else {
			stats->tx_dropped = get_nvvt_int(map, "idrops");
			stats->rx_dropped = get_nvvt_int(map, "odrops");
		}
	}

	if (!is_uplink)
		goto done;

	/*
	 * Can we do anything for aggr?
	 */
	if (strcmp("phys", netdev->class) != 0)
		goto done;

	if (solaris_get_devname(netdev_name, devname, sizeof (devname)) != 0) {
		VLOG_WARN("Failed to retrieve devname of uplink\n");
		error = -1;
		goto done;
	}

	if (!dlparse_drvppa(devname, modname, sizeof (modname),
	    &instance)) {
		VLOG_DBG("netdev_solaris_get_stats error getting "
		    "mod/instance for %s\n", devname);
		error = -1;
		goto done;
	}

	(void) snprintf(kuri, sizeof (kuri), "kstat:/net/%s/statistics/%d",
	    modname, instance);
	stat = kstat2_lookup_map(nd_khandle, kuri, &map);
	if (stat != KSTAT2_S_OK) {
		VLOG_WARN("kstat2_lookup_map of %s failed: %s", kuri,
		    kstat2_status_string(stat));
		error = -1;
		goto done;
	}
	stats->rx_length_errors = get_nvvt_int(map, "Recv_Length_Errors");
	stats->rx_missed_errors = get_nvvt_int(map, "Recv_Missed_Packets");
	stats->rx_over_errors = get_nvvt_int(map, "Recv_Oversize");

done:
	ovs_mutex_unlock(&kstat_mutex);
	return (error);
}

/*
 * Stores the features supported by 'netdev' into of '*current', '*advertised',
 * '*supported', and '*peer'.  Each value is a bitmap of NETDEV_* bits.
 * Returns 0 if successful, otherwise a positive errno value.
 */
static int
netdev_solaris_get_features(const struct netdev *netdev_,
    enum netdev_features *current,
    enum netdev_features *advertised,
    enum netdev_features *supported,
    enum netdev_features *peer)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	const char		*physname;
	char			buffer[DLADM_PROP_VAL_MAX];
	int			error = 0;

	VLOG_DBG("netdev_solaris_get_features device %s", netdev_name);
	ovs_mutex_lock(&netdev->mutex);

	if (netdev_solaris_is_uplink(netdev_)) {
		physname = netdev_name;
	} else {
		error = solaris_get_dllower(netdev_name, buffer,
		    sizeof (buffer));
		if (error != 0)
			goto exit;
		physname = buffer;
	}

	error = netdev_solaris_read_features(netdev, physname);
	if (error != 0)
		goto exit;

	*current = netdev->current;
	*advertised = netdev->advertised;
	*supported = netdev->supported;
	*peer = 0;

exit:
	ovs_mutex_unlock(&netdev->mutex);
	return (error);
}

/*
 * Attempts to set input rate limiting (policing) policy.  Returns 0 if
 * successful, otherwise a positive errno value.
 */
static int
netdev_solaris_set_policing(struct netdev *netdev_,
    uint32_t kbits_rate OVS_UNUSED, uint32_t kbits_burst OVS_UNUSED)
{
	const char	*netdev_name = netdev_get_name(netdev_);
	int		error = 0;

	VLOG_DBG("netdev_solaris_set_policing device %s", netdev_name);

	/* XXXSolaris check libdladm:setlinkrop maxbw/priority */

	return (error);
}

static int
netdev_solaris_get_qos_types(const struct netdev *netdev_,
    struct sset *types)
{
	const char	*netdev_name = netdev_get_name(netdev_);
	const struct tc_ops *const *opsp;

	VLOG_DBG("netdev_solaris_get_qos_types device %s", netdev_name);

	/*
	 * XXXSolaris we will support only HTB-equivalent which will translate
	 * to maxbw/priority.
	 */
	for (opsp = tcs; *opsp != NULL; opsp++) {
		const struct tc_ops	*ops = *opsp;

		if (ops->tc_install && ops->ovs_name[0] != '\0')
			sset_add(types, ops->ovs_name);
	}
	return (0);
}

static int
netdev_solaris_get_qos_capabilities(const struct netdev *netdev_,
    const char *type, struct netdev_qos_capabilities *caps)
{
	const char	*netdev_name = netdev_get_name(netdev_);
	int		error = EOPNOTSUPP;
	const struct tc_ops *ops = tc_lookup_ovs_name(type);

	VLOG_DBG("netdev_solaris_get_qos_capabilities device %s",
	    netdev_name);

	if (!ops)
		return (EOPNOTSUPP);

	/*
	 * Arbit number for now. In theory we are not limited for bandwidth
	 * limit. But, with shares and priority this can be revisited.
	 */
	caps->n_queues = ops->n_queues;

	return (error);
}

static int
netdev_solaris_get_qos(const struct netdev *netdev_,
    const char **typep, struct smap *details)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	int			error = 0;

	VLOG_DBG("netdev_solaris_get_qos device %s", netdev_name);

	ovs_mutex_lock(&netdev->mutex);
	error = tc_query_qdisc(netdev_);
	if (!error) {
		*typep = netdev->tc->ops->ovs_name;
		error = (netdev->tc->ops->qdisc_get ?
		    netdev->tc->ops->qdisc_get(netdev_, details) : 0);
	}
	ovs_mutex_unlock(&netdev->mutex);
	return (error);
}

static int
netdev_solaris_set_qos(struct netdev *netdev_,
    const char *type, const struct smap *details)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	const struct tc_ops	*new_ops;
	int			error = 0;

	VLOG_DBG("netdev_solaris_set_qos device %s", netdev_name);
	new_ops = tc_lookup_ovs_name(type);
	if (!new_ops) {
		VLOG_DBG("netdev_solaris_set_qos type %s not found", type);
		return (EOPNOTSUPP);
	}
	ovs_mutex_lock(&netdev->mutex);
	error = tc_query_qdisc(netdev_);
	if (error) {
		VLOG_DBG("netdev_solaris_set_qos qdisc querry failed");
		goto exit;
	}

	if (new_ops == netdev->tc->ops) {
		error = new_ops->qdisc_set ?
		    new_ops->qdisc_set(netdev_, details) :
		    0;
	} else {
		error = tc_del_qdisc(netdev_);
		if (error) {
			VLOG_DBG("netdev_solaris_set_qos error deleting %s",
			    type);
			goto exit;
		}
		ovs_assert(netdev->tc == NULL);
		/* Install new qdisc. */
		error = new_ops->tc_install(netdev_, details);
		ovs_assert((error == 0) == (netdev->tc != NULL));
		VLOG_DBG("netdev_solaris_set_qos installed %s, %d", type,
		    error);
	}
exit:
	ovs_mutex_unlock(&netdev->mutex);
	return (error);
}

static int
netdev_solaris_get_queue(const struct netdev *netdev_,
    unsigned int queue_id, struct smap *details)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	int			error = 0;

	VLOG_DBG("netdev_solaris_get_queue device %s", netdev_name);

	ovs_mutex_lock(&netdev->mutex);
	error = tc_query_qdisc(netdev_);
	if (!error) {
		struct tc_queue *queue = tc_find_queue(netdev_, queue_id);
		error = (queue ?
		    netdev->tc->ops->class_get(netdev_, queue, details) :
		    ENOENT);
	}
	ovs_mutex_unlock(&netdev->mutex);
	VLOG_DBG("netdev_solaris_get_queue device %s done %d", netdev_name,
	    error);
	return (error);
}

static int
netdev_solaris_set_queue(struct netdev *netdev_,
    unsigned int queue_id, const struct smap *details)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	int			error = 0;

	VLOG_DBG("netdev_solaris_set_queue device %s", netdev_name);

	ovs_mutex_lock(&netdev->mutex);
	error = tc_query_qdisc(netdev_);
	if (!error) {
		error = (queue_id < netdev->tc->ops->n_queues &&
		    netdev->tc->ops->class_set ?
		    netdev->tc->ops->class_set(netdev_, queue_id, details) :
		    EINVAL);
	} else {
		VLOG_DBG("netdev_solaris_set_queue %s: no qdisc", netdev_name);
	}
	ovs_mutex_unlock(&netdev->mutex);
	return (error);
}

static int
netdev_solaris_delete_queue(struct netdev *netdev_,
    unsigned int queue_id)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	int			error = 0;

	VLOG_DBG("netdev_solaris_delete_queue device %s", netdev_name);

	ovs_mutex_lock(&netdev->mutex);
	error = tc_query_qdisc(netdev_);
	if (!error) {
		if (netdev->tc->ops->class_delete) {
			struct tc_queue *queue =
			    tc_find_queue(netdev_, queue_id);

			error = (queue
			    ? netdev->tc->ops->class_delete(netdev_, queue)
			    : ENOENT);
		} else {
			error = EINVAL;
		}
	}
	ovs_mutex_unlock(&netdev->mutex);
	return (error);
}

static int
netdev_solaris_get_queue_stats(const struct netdev *netdev_,
    unsigned int queue_id OVS_UNUSED,
    struct netdev_queue_stats *stats OVS_UNUSED)
{
	const char	*netdev_name = netdev_get_name(netdev_);
	int		error = 0;

	VLOG_DBG("netdev_solaris_set_queue_stats device %s", netdev_name);

	return (error);
}

struct netdev_solaris_queue_state {
	unsigned int	*queues;
	size_t		cur_queue;
	size_t		n_queues;
};

static int
netdev_solaris_queue_dump_start(const struct netdev *netdev_,
    void **statep)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	int			error = 0;

	VLOG_DBG("netdev_solaris_queue_dump_start device %s", netdev_name);

	ovs_mutex_lock(&netdev->mutex);
	error = tc_query_qdisc(netdev_);
	if (!error) {
		if (netdev->tc->ops->class_get) {
			struct netdev_solaris_queue_state *state;
			struct tc_queue *queue;
			size_t i;

			*statep = state = xmalloc(sizeof (*state));
			state->n_queues = hmap_count(&netdev->tc->queues);
			state->cur_queue = 0;
			state->queues =
			    xmalloc(state->n_queues * sizeof (*state->queues));

			i = 0;
			HMAP_FOR_EACH(queue, hmap_node, &netdev->tc->queues) {
				state->queues[i++] = queue->queue_id;
			}
		} else {
			error = EOPNOTSUPP;
		}
	} else {
		VLOG_DBG("netdev_solaris_queue_dump_start: no qdisc");
	}
	ovs_mutex_unlock(&netdev->mutex);

	return (error);
}

static int
netdev_solaris_queue_dump_next(const struct netdev *netdev_,
    void *state_, unsigned int *queue_idp, struct smap *details)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	int			error = EOF;
	struct netdev_solaris_queue_state *state = state_;

	if (!state) {
		VLOG_DBG("netdev_solaris_queue_dump_next %s: null state\n",
		    netdev_name);
		return (EOF);
	}

	VLOG_DBG("netdev_solaris_queue_dump_next device %s, %"PRIuSIZE
	    ", %"PRIuSIZE, netdev_name, state->cur_queue, state->n_queues);
	ovs_mutex_lock(&netdev->mutex);
	while (state->cur_queue < state->n_queues) {
		unsigned int queue_id = state->queues[state->cur_queue++];
		struct tc_queue *queue = tc_find_queue(netdev_, queue_id);

		if (queue) {
			*queue_idp = queue_id;
			if (!netdev->tc || !netdev->tc->ops ||
			    !netdev->tc->ops->class_get) {
				break;
			}
			error = netdev->tc->ops->class_get(netdev_, queue,
			    details);
			break;
		}
	}
	ovs_mutex_unlock(&netdev->mutex);
	return (error);
}

static int
netdev_solaris_queue_dump_done(const struct netdev *netdev_,
    void *state_)
{
	const char	*netdev_name = netdev_get_name(netdev_);
	struct netdev_solaris_queue_state *state = state_;

	VLOG_DBG("netdev_solaris_queue_dump_done device %s", netdev_name);
	if (state) {
		if (state->queues)
			free(state->queues);
		free(state);
	}
	return (0);
}

static int
netdev_solaris_dump_queue_stats(const struct netdev *netdev_,
    netdev_dump_queue_stats_cb *cb OVS_UNUSED, void *aux OVS_UNUSED)
{
	const char	*netdev_name = netdev_get_name(netdev_);
	int		error = 0;

	VLOG_DBG("netdev_solaris_queue_dump_stats device %s", netdev_name);

	return (error);
}

/*
 * If 'netdev' has an assigned IPv4 address, sets '*address' to that
 * address and '*netmask' to the associated netmask. Otherwise, returns
 * errno.
 */
static int
netdev_solaris_get_in4(const struct netdev *netdev_,
    struct in_addr *address, struct in_addr *netmask)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	struct lifreq		lifr;
	const struct sockaddr_in *sin;
	int			error = 0;

	VLOG_DBG("netdev_solaris_get_in4 device %s", netdev_name);

	ovs_mutex_lock(&netdev->mutex);
	if (netdev->cache_valid & VALID_IN4) {
		*address = netdev->in4;
		*netmask = netdev->netmask;
		goto exit;
	}

	error = netdev_solaris_plumb(netdev_, AF_INET);
	if (error != 0)
		goto exit;

	/*
	 * In the future, a RAD IP module might be a good provider
	 * of this information. For now, use the SIOCGLIFADDR.
	 */
	bzero(&lifr, sizeof (lifr));
	(void) strncpy(lifr.lifr_name, netdev_name, sizeof (lifr.lifr_name));
	sin = ALIGNED_CAST(struct sockaddr_in *, &lifr.lifr_addr);
	if (ioctl(sock4, SIOCGLIFADDR, &lifr) < 0) {
		error = errno;
		goto exit;
	}
	netdev->in4 = sin->sin_addr;

	if (ioctl(sock4, SIOCGLIFNETMASK, (caddr_t)&lifr) < 0) {
		error = errno;
		goto exit;
	}
	netdev->netmask = sin->sin_addr;
	netdev->cache_valid |= VALID_IN4;

	if (netdev->in4.s_addr != INADDR_ANY) {
		*address = netdev->in4;
		*netmask = netdev->netmask;
	} else {
		error = EADDRNOTAVAIL;
	}

exit:
	ovs_mutex_unlock(&netdev->mutex);
	return (error);
}

static int
netdev_solaris_set_in4(struct netdev *netdev_, struct in_addr address,
    struct in_addr netmask)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	struct lifreq		lifr;
	struct sockaddr_in	*sin;
	int			error = 0;

	VLOG_DBG("netdev_solaris_set_in4 device %s", netdev_name);

	ovs_mutex_lock(&netdev->mutex);

	error = netdev_solaris_plumb(netdev_, AF_INET);
	if (error != 0)
		goto exit;

	/*
	 * In the future, a RAD IP module might be a good provider
	 * of this information. For now, use the SIOCSLIFADDR.
	 */
	bzero(&lifr, sizeof (lifr));
	(void) strncpy(lifr.lifr_name, netdev_name, sizeof (lifr.lifr_name));
	sin = ALIGNED_CAST(struct sockaddr_in *, &lifr.lifr_addr);
	sin->sin_addr = address;
	sin->sin_family = AF_INET;
	if (ioctl(sock4, SIOCSLIFADDR, &lifr) < 0) {
		error = errno;
		goto exit;
	}
	if (address.s_addr == htonl(INADDR_ANY))
		goto done;

	sin->sin_addr = netmask;
	if (ioctl(sock4, SIOCSLIFNETMASK, (caddr_t)&lifr) < 0) {
		error = errno;
		goto done;
	}
	netdev->in4 = address;
	netdev->netmask = netmask;
	netdev->cache_valid |= VALID_IN4;

done:
	netdev_change_seq_changed(netdev_);
exit:
	ovs_mutex_unlock(&netdev->mutex);
	return (error);
}

/*
 * If 'netdev' has an assigned IPv6 address, sets '*address' to that
 * address. Otherwise, returns errno.
 */
static int
netdev_solaris_get_in6(const struct netdev *netdev_, struct in6_addr *address)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	struct lifreq		lifr;
	const struct sockaddr_in6 *sin6;
	int			error = 0;

	VLOG_DBG("netdev_solaris_get_in6 device %s", netdev_name);

	ovs_mutex_lock(&netdev->mutex);
	if (netdev->cache_valid & VALID_IN6) {
		if (!IN6_IS_ADDR_UNSPECIFIED(address))
			*address = netdev->in6;
		else
			error = EADDRNOTAVAIL;
		goto exit;
	}

	error = netdev_solaris_plumb(netdev_, AF_INET6);
	if (error != 0)
		goto exit;

	/*
	 * In the future, a RAD IP module might be a good provider
	 * of this information. For now, use the SIOCGLIFADDR.
	 */
	bzero(&lifr, sizeof (lifr));
	(void) strncpy(lifr.lifr_name, netdev_name, sizeof (lifr.lifr_name));
	if (ioctl(sock6, SIOCGLIFADDR, &lifr) < 0) {
		error = errno;
		goto exit;
	}
	sin6 = ALIGNED_CAST(struct sockaddr_in6 *, &lifr.lifr_addr);
	netdev->in6 = sin6->sin6_addr;
	netdev->cache_valid |= VALID_IN6;

	if (!IN6_IS_ADDR_UNSPECIFIED(address))
		*address = netdev->in6;
	else
		error = EADDRNOTAVAIL;

exit:
	ovs_mutex_unlock(&netdev->mutex);
	return (error);
}

#define	ROUNDUP_LONG(a) ((a) > 0 ? (1 + (((a) - 1) | (sizeof (long) - 1))) : \
    sizeof (long))
#define	RT_ADVANCE(x, n) ((x) += ROUNDUP_LONG(salen(n)))
#define	BUF_SIZE 2048

typedef struct rtmsg {
	struct rt_msghdr	m_rtm;
	char			m_space[BUF_SIZE];
} rtmsg_t;

static int
salen(const struct sockaddr *sa)
{
	switch (sa->sa_family) {
	case AF_INET:
		return (sizeof (struct sockaddr_in));
	case AF_LINK:
		return (sizeof (struct sockaddr_dl));
	case AF_INET6:
		return (sizeof (struct sockaddr_in6));
	default:
		return (sizeof (struct sockaddr));
	}
}

/*
 * Adds 'router' as a default IP gateway.
 */
static int
netdev_solaris_add_router(struct netdev *netdev_, struct in_addr router)
{
	const char		*netdev_name = netdev_get_name(netdev_);
	rtmsg_t			m_rtmsg;
	struct rt_msghdr	*rtm = &m_rtmsg.m_rtm;
	char			*cp = m_rtmsg.m_space;
	struct sockaddr_in	gateway;
	struct sockaddr_in	dest;
	struct sockaddr_in	mask;
	int			rtsock_fd;
	int			error = 0;
	int			l;

	VLOG_DBG("netdev_solaris_add_router %s", netdev_name);

	rtsock_fd = socket(PF_ROUTE, SOCK_RAW, 0);
	if (rtsock_fd == -1) {
		error = errno;
		VLOG_ERR("failed to create PF_ROUTE socket (%s)",
		    ovs_strerror(error));
		return (error);
	}

	memset(&gateway, 0, sizeof (gateway));
	gateway.sin_family = AF_INET;
	gateway.sin_addr = router;

	memset(&dest, 0, sizeof (dest));
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = htonl(INADDR_ANY);

	memset(&dest, 0, sizeof (mask));
	mask.sin_family = AF_INET;
	mask.sin_addr.s_addr = htonl(INADDR_ANY);

	(void) memset(&m_rtmsg, 0, sizeof (m_rtmsg));
	rtm->rtm_version = RTM_VERSION;
	rtm->rtm_type	 = RTM_ADD;
	rtm->rtm_flags	 = RTF_GATEWAY | RTF_STATIC | RTF_UP;
	rtm->rtm_addrs	 = RTA_GATEWAY | RTA_DST | RTA_NETMASK;

	l = ROUNDUP_LONG(sizeof (struct sockaddr_in));
	(void) memcpy(cp, &dest, l);
	cp += l;
	(void) memcpy(cp, &gateway, l);
	cp += l;
	(void) memcpy(cp, &mask, l);
	cp += l;

	rtm->rtm_msglen = l = cp - (char *)&m_rtmsg;
	if (write(rtsock_fd, (char *)&m_rtmsg, l) != l) {
		char buffer[INET_ADDRSTRLEN];
		(void) inet_ntop(AF_INET, &router, buffer, sizeof (buffer));
		error = errno;
		VLOG_ERR("failed to add router %s: %s", buffer,
		    ovs_strerror(error));
	}
	close(rtsock_fd);
	return (error);
}

/*
 * Looks up the next hop for 'host' in the host's routing table.  If
 * successful, stores the next hop gateway's address (0 if 'host' is on a
 * directly connected network) in '*next_hop' and a copy of the name of the
 * device to reach 'host' in '*netdev_name', and returns 0. The caller is
 * responsible for freeing '*netdev_name' (by calling free()).
 */
static int
netdev_solaris_get_next_hop(const struct in_addr *host,
    struct in_addr *next_hop, char **netdev_name)
{
	rtmsg_t			m_rtmsg;
	struct rt_msghdr	*rtm = &m_rtmsg.m_rtm;
	char			*cp = m_rtmsg.m_space;
	int			rtsock_fd;
	struct sockaddr_in	sin;
	struct sockaddr_dl	sdl;
	const pid_t		pid = getpid();
	static int		seq;
	boolean_t		gateway = B_FALSE;
	ssize_t			ssz;
	char			*ifname = NULL;
	int			saved_errno;
	int			error = 0;
	int			rlen;
	int			l;
	int			i;

	memset(&sin, 0, sizeof (sin));
	sin.sin_family = AF_INET;
	sin.sin_port = 0;
	sin.sin_addr = *host;

	memset(&sdl, 0, sizeof (sdl));
	sdl.sdl_family = AF_LINK;

	rtsock_fd = socket(PF_ROUTE, SOCK_RAW, 0);
	if (rtsock_fd == -1) {
		error = errno;
		VLOG_ERR("failed to create PF_ROUTE socket (%s)",
		    ovs_strerror(error));
		return (error);
	}

	(void) memset(&m_rtmsg, 0, sizeof (m_rtmsg));
	rtm->rtm_type = RTM_GET;
	rtm->rtm_flags = RTF_HOST|RTF_UP;
	rtm->rtm_version = RTM_VERSION;
	rtm->rtm_seq = ++seq;
	rtm->rtm_addrs = RTA_DST|RTA_IFP;

	l = ROUNDUP_LONG(sizeof (struct sockaddr_in));
	(void) memcpy(cp, &sin, l);
	cp += l;

	l = ROUNDUP_LONG(sizeof (struct sockaddr_dl));
	(void) memcpy(cp, &sdl, l);
	cp += l;

	rtm->rtm_msglen = l = cp - (char *)&m_rtmsg;
	if ((rlen = write(rtsock_fd, (char *)&m_rtmsg, l)) < l) {
		error = errno;
		VLOG_ERR("failed to get route: %s", ovs_strerror(error));
		close(rtsock_fd);
		return (errno);
	}

	memset(next_hop, 0, sizeof (*next_hop));
	*netdev_name = NULL;
	memset(&m_rtmsg, 0, sizeof (m_rtmsg));
	do {
		ssz = read(rtsock_fd, &m_rtmsg, sizeof (m_rtmsg));
	} while (ssz > 0 && (rtm->rtm_seq != seq || rtm->rtm_pid != pid));
	saved_errno = errno;
	close(rtsock_fd);
	if (ssz <= 0) {
		if (ssz < 0) {
			return (saved_errno);
		}
		return (EPIPE);
	}
	cp = (void *)&m_rtmsg.m_space;
	for (i = 1; i; i <<= 1) {
		if ((rtm->rtm_addrs & i) != 0) {
			const struct sockaddr *sa = (const void *)cp;

			if ((i == RTA_GATEWAY) && sa->sa_family == AF_INET) {
				const struct sockaddr_in * const sin =
				    ALIGNED_CAST(const struct sockaddr_in *,
				    sa);

				*next_hop = sin->sin_addr;
				gateway = B_TRUE;
			}
			if ((i == RTA_IFP) && sa->sa_family == AF_LINK) {
				const struct sockaddr_dl * const sdl =
				    ALIGNED_CAST(const struct sockaddr_dl *,
				    sa);

				ifname = xmemdup0(sdl->sdl_data,
				    sdl->sdl_nlen);
			}
			RT_ADVANCE(cp, sa);
		}
	}
	if (ifname == NULL) {
		return (ENXIO);
	}
	if (!gateway) {
		*next_hop = *host;
	}
	*netdev_name = ifname;
	VLOG_DBG("host " IP_FMT " next-hop " IP_FMT " if %s\n",
	    IP_ARGS(host->s_addr), IP_ARGS(next_hop->s_addr), *netdev_name);

	return (0);
}

static int
netdev_solaris_get_status(const struct netdev *netdev_,
    struct smap *smap OVS_UNUSED)
{
	const char	*netdev_name = netdev_get_name(netdev_);
	int		error = EOPNOTSUPP;

	VLOG_DBG("netdev_solaris_get_status %s", netdev_name);

	/*
	 * It looks like this is used to populate a column,
	 * OVSREC_INTERFACE_COL_STATUS in the OVSDB. It doesn't appear
	 * to be required though. If we wanted to return the driver name
	 * then we could return that using libdladm.
	 */
	return (error);
}

/*
 * Looks up the ARP table entry for 'ip' on 'netdev'.  If one exists and can be
 * successfully retrieved, it stores the corresponding MAC address in 'mac' and
 * returns 0.  Otherwise, it returns a positive errno value; in particular,
 * ENXIO indicates that there is not ARP table entry for 'ip' on 'netdev'.
 */
static int
netdev_solaris_arp_lookup(const struct netdev *netdev_,
    ovs_be32 ip OVS_UNUSED, uint8_t mac[ETH_ADDR_LEN] OVS_UNUSED)
{
	const char		*netdev_name = netdev_get_name(netdev_);
	int			error = 0;
	struct xarpreq		ar;
	struct sockaddr_in	*sin;

	VLOG_DBG("netdev_solaris_arp_lookup %s", netdev_name);

	bzero(&ar, sizeof (ar));
	sin = ALIGNED_CAST(struct sockaddr_in *, &ar.xarp_pa);
	sin->sin_addr.s_addr = ip;
	sin->sin_family = AF_INET;
	ar.xarp_ha.sdl_family = AF_LINK;

	if (ioctl(sock4, SIOCGXARP, &ar) < 0) {
		error = errno;
		goto out;
	}
	if (!(ar.xarp_flags & ATF_COM)) {
		errno = EOPNOTSUPP; /* XXX */
		goto out;
	}
	memcpy(mac, LLADDR(&ar.xarp_ha), ETH_ADDR_LEN);
out:
	return (error);
}

static int
lifr_to_nd_flags(int64_t lifrflags)
{
	enum netdev_flags nd_flags = 0;

	if (lifrflags & IFF_UP) {
		nd_flags |= NETDEV_UP;
	}
	if (lifrflags & IFF_PROMISC) {
		nd_flags |= NETDEV_PROMISC;
	}
	if (lifrflags & IFF_LOOPBACK) {
		nd_flags |= NETDEV_LOOPBACK;
	}
	return (nd_flags);
}

static int64_t
nd_to_lifr_flags(enum netdev_flags nd_flags)
{
	int64_t lifrflags = 0;

	if (nd_flags & NETDEV_UP) {
		lifrflags |= IFF_UP;
	}
	if (nd_flags & NETDEV_PROMISC) {
		lifrflags |= IFF_PROMISC;
	}
	if (nd_flags & NETDEV_LOOPBACK) {
		lifrflags |= IFF_LOOPBACK;
	}
	return (lifrflags);
}

/*
 * Retrieves the current set of flags on 'netdev' into '*old_flags'.  Then,
 * turns off the flags that are set to 1 in 'off' and turns on the flags
 * that are set to 1 in 'on'.  (No bit will be set to 1 in both 'off' and
 * 'on'; that is, off & on == 0.)
 */
static int
netdev_solaris_update_flags(struct netdev *netdev_, enum netdev_flags off,
    enum netdev_flags on, enum netdev_flags *old_flagsp)
{
	const char		*netdev_name = netdev_get_name(netdev_);
	struct lifreq		lifr;
	int64_t			old_lifr_flags;
	int64_t			new_lifr_flags;
	int			error = 0;

	VLOG_DBG("netdev_solaris_update_flags %s", netdev_name);

	bzero(&lifr, sizeof (lifr));
	(void) strncpy(lifr.lifr_name, netdev_name, sizeof (lifr.lifr_name));
	if (ioctl(sock4, SIOCGLIFFLAGS, (caddr_t)&lifr) < 0) {
		error = errno;
		goto exit;
	}
	old_lifr_flags = lifr.lifr_flags;
	*old_flagsp = lifr_to_nd_flags(old_lifr_flags);
	new_lifr_flags = (old_lifr_flags & ~nd_to_lifr_flags(off)) |
	    nd_to_lifr_flags(on);

	if (new_lifr_flags == old_lifr_flags)
		goto exit;

	lifr.lifr_flags = new_lifr_flags;
	if (ioctl(sock4, SIOCSLIFFLAGS, (caddr_t)&lifr) < 0) {
		error = errno;
		goto exit;
	}
	netdev_change_seq_changed(netdev_);

exit:
	return (error);
}

static int
netdev_internal_get_status(const struct netdev *netdev OVS_UNUSED,
    struct smap *smap)
{
	smap_add(smap, "driver_name", "openvswitch");
	return (0);
}

#define	NETDEV_SOLARIS_CLASS(NAME, CONSTRUCT, GET_STATS, SET_STATS,	\
    GET_FEATURES, GET_STATUS)						\
{									\
	NAME,								\
	netdev_solaris_init,						\
	netdev_solaris_run,						\
	netdev_solaris_wait,						\
	netdev_solaris_alloc,						\
	CONSTRUCT,							\
	netdev_solaris_destruct,					\
	netdev_solaris_dealloc,						\
	NULL,								\
	NULL,								\
	NULL,								\
	NULL,								\
	NULL,								\
	netdev_solaris_set_etheraddr,					\
	netdev_solaris_get_etheraddr,					\
	netdev_solaris_get_mtu,						\
	netdev_solaris_set_mtu,						\
	netdev_solaris_get_ifindex,					\
	NULL,								\
	NULL,								\
	NULL,								\
	GET_STATS,							\
	SET_STATS,							\
	GET_FEATURES,							\
	NULL,								\
	netdev_solaris_set_policing,					\
	netdev_solaris_get_qos_types,					\
	netdev_solaris_get_qos_capabilities,				\
	netdev_solaris_get_qos,						\
	netdev_solaris_set_qos,						\
	netdev_solaris_get_queue,					\
	netdev_solaris_set_queue,					\
	netdev_solaris_delete_queue,					\
	netdev_solaris_get_queue_stats,					\
	netdev_solaris_queue_dump_start,				\
	netdev_solaris_queue_dump_next,					\
	netdev_solaris_queue_dump_done,					\
	netdev_solaris_dump_queue_stats,				\
	netdev_solaris_get_in4,						\
	netdev_solaris_set_in4,						\
	netdev_solaris_get_in6,						\
	netdev_solaris_add_router,					\
	netdev_solaris_get_next_hop,					\
	GET_STATUS,							\
	netdev_solaris_arp_lookup,					\
	netdev_solaris_update_flags,					\
	netdev_solaris_configure_uplink,				\
	netdev_solaris_is_uplink,					\
	netdev_solaris_add_port_to_bridge_mapping,			\
	NULL,								\
	NULL,								\
	NULL,								\
	NULL,								\
	NULL,								\
	NULL,								\
	NULL								\
}

const struct netdev_class netdev_solaris_class =
    NETDEV_SOLARIS_CLASS(
	"system",
	netdev_solaris_construct,
	netdev_solaris_get_stats,
	NULL,				/* set_stats */
	netdev_solaris_get_features,
	netdev_solaris_get_status);

const struct netdev_class netdev_internal_class =
    NETDEV_SOLARIS_CLASS(
	"internal",
	netdev_solaris_construct,
	netdev_solaris_get_stats,
	NULL,				/* set_stats */
	NULL,				/* get_features */
	netdev_internal_get_status);

/* Solaris HTB traffic control class */
#define	HTB_N_QUEUES	0xf000

struct htb {
	struct tc	tc;
	unsigned int	max_rate;	/* In bytes/s. */
};

struct htb_class {
	struct tc_queue	tc_queue;
	unsigned int	min_rate;	/* In bytes/s */
	unsigned int	max_rate;	/* In bytes/s */
	unsigned int	burst;		/* In bytes/s -- unused */
	unsigned int	priority;	/* Lower value is higher priority */
};


/*
 * Create an HTB qdisc.
 *
 * Equivalent to "tc qdisc add dev <dev> root handle 1: htb default 1".
 */
static int
htb_setup_qdisc__(struct netdev *netdev)
{
	VLOG_DBG("htb_setup_qdisc__ device %s", netdev->name);
	tc_del_qdisc(netdev);

	return (0);
}

static struct htb *
htb_get__(const struct netdev *netdev_)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);

	VLOG_DBG("htb_get__ device %s", netdev_name);
	return (CONTAINER_OF(netdev->tc, struct htb, tc));
}

static void
htb_install__(struct netdev *netdev_, uint64_t max_rate)
{
	const char		*netdev_name = netdev_get_name(netdev_);
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	struct htb		*htb;

	VLOG_DBG("htb_install__ device %s", netdev_name);
	htb = xmalloc(sizeof (*htb));
	tc_init(&htb->tc, &tc_ops_htb);
	htb->max_rate = max_rate;

	netdev->tc = &htb->tc;
	VLOG_DBG("htb_install__ device %s TC configured ", netdev_name);
}

static int
htb_setup_class__(struct netdev *netdev, unsigned int handle OVS_UNUSED,
    unsigned int parent OVS_UNUSED,
    struct htb_class *class OVS_UNUSED)
{
	VLOG_DBG("htb_setup_class__ device %s", netdev->name);

	return (0);
}

static void
htb_parse_qdisc_details__(struct netdev *netdev_,
			const struct smap *details, struct htb_class *hc)
{
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	const char		*netdev_name = netdev_get_name(netdev_);
	const char		*max_rate_s;
	const char		*physname;
	char			buffer[DLADM_PROP_VAL_MAX];
	int			error = 0;

	VLOG_DBG("htb_parse_qdisc_details__ device %s", netdev_name);

	/*
	 * Initialize in case of early return.
	 */
	hc->max_rate = 0;
	hc->min_rate = 0;
	hc->burst = 0;
	hc->priority = 0;

	if (netdev_solaris_is_uplink(netdev_)) {
		physname = netdev_name;
	} else {
		error = solaris_get_dllower(netdev_name, buffer,
		    sizeof (buffer));
		if (error != 0)
			return;
		physname = buffer;
	}

	max_rate_s = smap_get(details, "max-rate");
	hc->max_rate = max_rate_s ? strtoull(max_rate_s, NULL, 10) / 8 : 0;
	if (!hc->max_rate) {
		enum netdev_features current;

		netdev_solaris_read_features(netdev, physname);
		current = !netdev->get_features_error ? netdev->current : 0;
		hc->max_rate = netdev_features_to_bps(current,
		    100 * 1000 * 1000) / 8;
	}
}

static int
htb_tc_install(struct netdev *netdev, const struct smap *details)
{
	int error;

	VLOG_DBG("htb_tc_install device %s", netdev->name);

	error = htb_setup_qdisc__(netdev);
	if (!error) {
		struct htb_class hc;

		htb_parse_qdisc_details__(netdev, details, &hc);
		error = htb_setup_class__(netdev, 0, 0, &hc);
		if (!error) {
			htb_install__(netdev, hc.max_rate);
		}
	}
	return (error);
}

static void
htb_tc_destroy(struct tc *tc)
{
	struct htb		*htb = CONTAINER_OF(tc, struct htb, tc);
	struct htb_class	*hc, *next;

	HMAP_FOR_EACH_SAFE(hc, next, tc_queue.hmap_node, &htb->tc.queues) {
		hmap_remove(&htb->tc.queues, &hc->tc_queue.hmap_node);
		free(hc);
	}
	tc_destroy(tc);
	free(htb);
}

static int
htb_qdisc_get(const struct netdev *netdev, struct smap *details)
{
	const struct htb *htb = htb_get__(netdev);

	VLOG_DBG("htb_qdisc_get device %s", netdev->name);
	smap_add_format(details, "max-rate", "%llu", 8ULL * htb->max_rate);
	return (0);
}

static int
htb_qdisc_set(struct netdev *netdev, const struct smap *details)
{
	struct htb_class	hc;
	int			error;

	VLOG_DBG("htb_qdisc_set device %s", netdev->name);
	htb_parse_qdisc_details__(netdev, details, &hc);
	/* Solaris: don't care about the handles */
	error = htb_setup_class__(netdev, 0, 0, &hc);
	if (!error) {
		htb_get__(netdev)->max_rate = hc.max_rate;
	}

	return (error);
}

static struct htb_class *
htb_class_cast__(const struct tc_queue *queue)
{
	return (CONTAINER_OF(queue, struct htb_class, tc_queue));
}

static int
htb_class_get(const struct netdev *netdev,
    const struct tc_queue *queue, struct smap *details)
{
	const struct htb_class *hc = htb_class_cast__(queue);

	VLOG_DBG("htb_class_get device %s", netdev->name);

	if (hc->max_rate > 0)
		smap_add_format(details, "max-rate", "%llu",
		    8ULL * hc->max_rate);

	VLOG_DBG("htb_class_get device done");
	return (0);
}

/* Solaris: currently, min-rate, burst and priority are not supported */
static int
htb_parse_class_details__(struct netdev *netdev,
    const struct smap *details, struct htb_class *hc)
{
	const struct htb	*htb = htb_get__(netdev);
	const char		*max_rate_s = smap_get(details, "max-rate");

	VLOG_DBG("htb_parse_class_details__ device %s", netdev->name);

	/* max-rate */
	hc->max_rate = (max_rate_s
	    ? strtoull(max_rate_s, NULL, 10) / 8
	    : htb->max_rate);
	VLOG_DBG("htb_parse_class_details__ device max_rate is %u",
	    hc->max_rate);

	return (0);
}

static void
htb_update_queue__(struct netdev *netdev, unsigned int queue_id,
    const struct htb_class *hc)
{
	struct htb		*htb = htb_get__(netdev);
	size_t			hash = hash_int(queue_id, 0);
	struct tc_queue		*queue;
	struct htb_class	*hcp;

	VLOG_DBG("htb_update_queue__ %s", netdev->name);

	queue = tc_find_queue__(netdev, queue_id, hash);
	if (queue) {
		hcp = htb_class_cast__(queue);
	} else {
		hcp = xmalloc(sizeof (*hcp));
		queue = &hcp->tc_queue;
		queue->queue_id = queue_id;
		queue->created = time_msec();
		hmap_insert(&htb->tc.queues, &queue->hmap_node, hash);
	}

	hcp->max_rate = hc->max_rate;
}

static int
htb_class_set(struct netdev *netdev, unsigned int queue_id,
    const struct smap *details)
{
	struct htb_class	hc;
	int			error;

	VLOG_DBG("htb_class_set %s", netdev->name);

	error = htb_parse_class_details__(netdev, details, &hc);
	if (error) {
		return (error);
	}

	error = htb_setup_class__(netdev, 0, 0, &hc);
	if (error) {
		return (error);
	}

	htb_update_queue__(netdev, queue_id, &hc);
	return (0);
}

static int
htb_class_delete(struct netdev *netdev, struct tc_queue *queue)
{
	struct htb_class	*hc = htb_class_cast__(queue);
	struct htb		*htb = htb_get__(netdev);
	int			error;

	VLOG_DBG("htb_class_delete %s", netdev->name);
	error = tc_delete_class(netdev, 0);
	if (!error) {
		hmap_remove(&htb->tc.queues, &hc->tc_queue.hmap_node);
		free(hc);
	}
	return (error);
}

/*
 * Used to get existing configuration for qdiscs in the kernel, not used in
 * Solaris.
 */
static int
htb_tc_load(struct netdev *netdev, struct ofpbuf *nlmsg OVS_UNUSED)
{
	VLOG_DBG("htb_tc_load %s", netdev->name);

	return (0);
}

static const struct tc_ops tc_ops_htb = {
	"htb",			/* linux_name */
	"linux-htb",		/* ovs_name */
	HTB_N_QUEUES,		/* n_queues */
	htb_tc_install,
	htb_tc_load,
	htb_tc_destroy,
	htb_qdisc_get,
	htb_qdisc_set,
	htb_class_get,
	htb_class_set,
	htb_class_delete,
	NULL,
	NULL
};

/*
 * The default traffic control class.
 *
 * This class represents the default, unnamed Linux qdisc.  It corresponds to
 * the "" (empty string) QoS type in the OVS database.
 */
static void
default_install__(struct netdev *netdev_)
{
	const char		*netdev_name = netdev_get_name(netdev_);
	struct netdev_solaris	*netdev = netdev_solaris_cast(netdev_);
	static const struct tc	tc = TC_INITIALIZER(&tc, &tc_ops_default);

	VLOG_DBG("default_install__ device %s", netdev_name);

	/*
	 * Nothing but a tc class implementation is allowed to write to a tc.
	 * This class never does that, so we can legitimately use a const tc
	 * object.
	 */
	netdev->tc = CONST_CAST(struct tc *, &tc);
}

static int
default_tc_install(struct netdev *netdev,
    const struct smap *details OVS_UNUSED)
{
	VLOG_DBG("default_tc_install device %s", netdev->name);
	default_install__(netdev);
	return (0);
}

static int
default_tc_load(struct netdev *netdev, struct ofpbuf *nlmsg OVS_UNUSED)
{
	VLOG_DBG("default_tc_load device %s", netdev->name);
	default_install__(netdev);
	return (0);
}

static const struct tc_ops tc_ops_default = {
	NULL,			/* linux_name */
	"",			/* ovs_name */
	0,			/* n_queues */
	default_tc_install,
	default_tc_load,
	NULL,			/* tc_destroy */
	NULL,			/* qdisc_get */
	NULL,			/* qdisc_set */
	NULL,			/* class_get */
	NULL,			/* class_set */
	NULL,			/* class_delete */
	NULL,			/* class_get_stats */
	NULL			/* class_dump_stats */
};
