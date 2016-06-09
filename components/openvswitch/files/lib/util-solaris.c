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

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <alloca.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <strings.h>
#include <stropts.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <inet/ip.h>
#include <inet/ip6.h>
#include <arpa/inet.h>
#include <sys/sockio.h>
#include <libdlpi.h>
#include <libdladm.h>
#include <libdllink.h>
#include <zone.h>
#include <net/if_types.h>
#include <inet/arp.h>
#include <sys/socket.h>
#include <netdb.h>
#include <rad/radclient.h>
#include <rad/client/1/dlmgr.h>

#undef	IP_VERSION
#include "netlink-protocol.h"
#include "netlink.h"
#include "flow.h"
#include "packets.h"
#include "util-solaris.h"
#include "util.h"
#include "dpif-solaris.h"

static rc_conn_t *rad_conn = NULL;
static boolean_t b_true = B_TRUE;

typedef struct {
	uint_t		ifsp_ppa;	/* Physical Point of Attachment */
	uint_t		ifsp_lun;	/* Logical Unit number */
	boolean_t	ifsp_lunvalid;	/* TRUE if lun is valid */
	char		ifsp_devnm[LIFNAMSIZ]; /* only the device name */
} ifspec_t;

static int
extract_uint(const char *valstr, uint_t *val)
{
	char		*ep;
	unsigned long	ul;

	errno = 0;
	ul = strtoul(valstr, &ep, 10);
	if (errno != 0 || *ep != '\0' || ul > UINT_MAX)
		return (-1);
	*val = (uint_t)ul;
	return (0);
}

/*
 * Given a token with a logical unit spec, return the logical unit converted
 * to a uint_t.
 *
 * Returns: 0 for success, nonzero if an error occurred. errno is set if
 * necessary.
 */
static int
getlun(const char *bp, size_t bpsize, uint_t *lun)
{
	const char	*ep = &bp[bpsize - 1];
	const char	*tp;

	/* Lun must be all digits */
	for (tp = ep; tp > bp && isdigit(*tp); tp--)
		/* Null body */;

	if (tp == ep || tp != bp || extract_uint(bp + 1, lun) != 0) {
		errno = EINVAL;
		return (-1);
	}
	return (0);
}

/*
 * Given a single token ending with a ppa spec, return the ppa spec converted
 * to a uint_t.
 *
 * Returns: 0 for success, nonzero if an error occurred. errno is set if
 * necessary.
 */
static int
getppa(const char *bp, size_t bpsize, uint_t *ppa)
{
	const char	*ep = &bp[bpsize - 1];
	const char	*tp;

	for (tp = ep; tp >= bp && isdigit(*tp); tp--)
		/* Null body */;

	/*
	 * If the device name does not end with a digit or the device
	 * name is a sequence of numbers or a PPA contains a leading
	 * zero, return error.
	 */
	if (tp == ep || tp < bp || ((ep - tp) > 1 && *(tp + 1) == '0'))
		goto fail;

	if (extract_uint(tp + 1, ppa) != 0)
		goto fail;

	/* max value of PPA is 4294967294, which is (UINT_MAX - 1) */
	if (*ppa > UINT_MAX - 1)
		goto fail;
	return (0);
fail:
	errno = EINVAL;
	return (-1);
}

/*
 * Given a `linkname' of the form drv(ppa), parse it into `driver' and `ppa'.
 * If the `dsize' for the `driver' is not atleast MAXLINKNAMELEN then part of
 * the driver name will be copied to `driver'.
 *
 * This function also validates driver name and PPA and therefore callers can
 * call this function with `driver' and `ppa' set to NULL, to just verify the
 * linkname.
 */
boolean_t
dlparse_drvppa(const char *linknamep, char *driver, uint_t dsize, uint_t *ppa)
{
	char	*tp;
	char    linkname[MAXLINKNAMELEN];
	size_t	len;
	uint_t	lppa;

	if (linknamep == NULL || linknamep[0] == '\0')
		goto fail;

	len = strlcpy(linkname, linknamep, MAXLINKNAMELEN);
	if (len >= MAXLINKNAMELEN)
		goto fail;

	/* Get PPA */
	if (getppa(linkname, len, &lppa) != 0)
		return (_B_FALSE);

	/* strip the ppa off of the linkname, if present */
	for (tp = &linkname[len - 1]; tp >= linkname && isdigit(*tp); tp--)
		*tp = '\0';

	/*
	 * Now check for the validity of the device name. The legal characters
	 * in a device name are: alphanumeric (a-z,  A-Z,  0-9), underscore
	 * ('_'), hyphen ('-'), and period ('.'). The first character
	 * of the device name cannot be a digit and should be an alphabetic
	 * character.
	 */
	if (!isalpha(linkname[0]))
		goto fail;
	for (tp = linkname + 1; *tp != '\0'; tp++) {
		if (!isalnum(*tp) && *tp != '_' && *tp != '-' && *tp != '.')
			goto fail;
	}

	if (driver != NULL)
		(void) strlcpy(driver, linkname, dsize);

	if (ppa != NULL)
		*ppa = lppa;

	return (_B_TRUE);
fail:
	errno = EINVAL;
	return (_B_FALSE);
}

/*
 * Given an IP interface name, which is either a
 *	- datalink name (which is driver name plus PPA), for e.g. bge0 or
 *	- datalink name plus a logical interface identifier (delimited by ':'),
 *		for e.g. bge0:34
 * the following function validates its form and decomposes the contents into
 * ifspec_t.
 *
 * Returns _B_TRUE for success, otherwise _B_FALSE is returned.
 */
static boolean_t
ifparse_ifspec(const char *ifname, ifspec_t *ifsp)
{
	char	*lp;
	char	ifnamecp[LIFNAMSIZ];

	if (ifname == NULL || ifname[0] == '\0' ||
	    strlcpy(ifnamecp, ifname, LIFNAMSIZ) >= LIFNAMSIZ) {
		errno = EINVAL;
		return (_B_FALSE);
	}

	ifsp->ifsp_lunvalid = _B_FALSE;

	/* Any logical units? */
	lp = strchr(ifnamecp, ':');
	if (lp != NULL) {
		if (getlun(lp, strlen(lp), &ifsp->ifsp_lun) != 0)
			return (_B_FALSE);
		*lp = '\0';
		ifsp->ifsp_lunvalid = _B_TRUE;
	}

	return (dlparse_drvppa(ifnamecp, ifsp->ifsp_devnm,
	    sizeof (ifsp->ifsp_devnm), &ifsp->ifsp_ppa));
}

/*
 * Issues the ioctl SIOCSLIFNAME to kernel.
 */
static int
slifname(const char *ifname, uint64_t flags, int fd)
{
	struct lifreq	lifr;
	int		status = 0;
	ifspec_t	ifsp;
	boolean_t	valid_if;

	bzero(&lifr, sizeof (lifr));

	/* We should have already validated the interface name. */
	valid_if = ifparse_ifspec(ifname, &ifsp);
	ovs_assert(valid_if);

	lifr.lifr_ppa = ifsp.ifsp_ppa;
	lifr.lifr_flags = flags;
	(void) strlcpy(lifr.lifr_name, ifname, sizeof (lifr.lifr_name));
	if (ioctl(fd, SIOCSLIFNAME, &lifr) == -1) {
		status = errno;
	}

	return (status);
}

/*
 * Wrapper for sending a non-transparent I_STR ioctl().
 * Returns: Result from ioctl().
 */
static int
strioctl(int s, int cmd, char *buf, uint_t buflen)
{
	struct strioctl ioc;

	(void) memset(&ioc, 0, sizeof (ioc));
	ioc.ic_cmd = cmd;
	ioc.ic_timout = 0;
	ioc.ic_len = buflen;
	ioc.ic_dp = buf;

	return (ioctl(s, I_STR, (char *)&ioc));
}

/*
 * Issues the ioctl SIOCSLIFNAME to kernel on the given ARP stream fd.
 */
static int
slifname_arp(const char *ifname, uint64_t flags, int fd)
{
	struct lifreq	lifr;
	ifspec_t	ifsp;

	bzero(&lifr, sizeof (lifr));
	(void) ifparse_ifspec(ifname, &ifsp);
	lifr.lifr_ppa = ifsp.ifsp_ppa;
	lifr.lifr_flags = flags;
	(void) strlcpy(lifr.lifr_name, ifname, sizeof (lifr.lifr_name));
	/*
	 * Tell ARP the name and unit number for this interface.
	 * Note that arp has no support for transparent ioctls.
	 */
	if (strioctl(fd, SIOCSLIFNAME, (char *)&lifr,
	    sizeof (lifr)) == -1) {
		return (errno);
	}
	return (0);
}

/*
 * Open "/dev/udp{,6}" for use as a multiplexor to PLINK the interface stream
 * under. We use "/dev/udp" instead of "/dev/ip" since STREAMS will not let
 * you PLINK a driver under itself, and "/dev/ip" is typically the driver at
 * the bottom of the stream for tunneling interfaces.
 */
static int
open_arp_on_udp(const char *udp_dev_name, int *fd)
{
	int err;

	if ((*fd = open(udp_dev_name, O_RDWR)) == -1)
		return (errno);
	/*
	 * Pop off all undesired modules (note that the user may have
	 * configured autopush to add modules above udp), and push the
	 * arp module onto the resulting stream. This is used to make
	 * IP+ARP be able to atomically track the muxid for the I_PLINKed
	 * STREAMS, thus it isn't related to ARP running the ARP protocol.
	 */
	while (ioctl(*fd, I_POP, 0) != -1)
		;
	if (errno == EINVAL && ioctl(*fd, I_PUSH, ARP_MOD_NAME) != -1)
		return (0);

	err = errno;
	(void) close(*fd);
	return (err);
}

static char *
solaris_proto2str(uint8_t protocol)
{
	if (protocol == IPPROTO_TCP)
		return ("tcp");
	if (protocol == IPPROTO_UDP)
		return ("udp");
	if (protocol == IPPROTO_SCTP)
		return ("sctp");
	if (protocol == IPPROTO_ICMPV6)
		return ("icmpv6");
	if (protocol == IPPROTO_ICMP)
		return ("icmp");
	else
		return ("");
}

static uint8_t
solaris_str2proto(const char *protostr)
{
	if (strcasecmp(protostr, "tcp") == 0)
		return (IPPROTO_TCP);
	else if (strcasecmp(protostr, "udp") == 0)
		return (IPPROTO_UDP);
	else if (strcasecmp(protostr, "sctp") == 0)
		return (IPPROTO_SCTP);
	else if (strcasecmp(protostr, "icmpv6") == 0)
		return (IPPROTO_ICMPV6);
	else if (strcasecmp(protostr, "icmp") == 0)
		return (IPPROTO_ICMP);
	return (0);
}

/*
 * Returns the flags value for the logical interface in `lifname'
 * in the buffer pointed to by `flags'.
 */
static int
solaris_get_flags(int sock, const char *lifname, uint64_t *flags)
{
	struct lifreq	lifr;

	bzero(&lifr, sizeof (lifr));
	(void) strlcpy(lifr.lifr_name, lifname, sizeof (lifr.lifr_name));

	if (ioctl(sock, SIOCGLIFFLAGS, (caddr_t)&lifr) < 0)
		return (errno);
	*flags = lifr.lifr_flags;

	return (0);
}

/*
 * For a given interface name, checks if IP interface exists.
 */
int
solaris_if_enabled(int sock, const char *ifname, uint64_t *flags)
{
	struct lifreq	lifr;
	int		error = 0;

	bzero(&lifr, sizeof (lifr));
	(void) strlcpy(lifr.lifr_name, ifname, sizeof (lifr.lifr_name));
	if (ioctl(sock, SIOCGLIFFLAGS, (caddr_t)&lifr) != 0)
		error = errno;

	if (error == 0 && flags != NULL)
		*flags = lifr.lifr_flags;

	return (error);
}

int
solaris_unplumb_if(int sock, const char *ifname, sa_family_t af)
{
	int		ip_muxid;
	int		arp_muxid;
	int		mux_fd = -1;
	int		muxid_fd = -1;
	char		*udp_dev_name;
	uint64_t	ifflags = 0;
	boolean_t	changed_arp_muxid = B_FALSE;
	struct lifreq	lifr;
	int		ret = 0;
	boolean_t	v6 = (af == AF_INET6);

	/*
	 * We used /dev/udp or udp6 to set up the mux. So we have to use
	 * the same now for PUNLINK also.
	 */
	udp_dev_name = (v6 ?  UDP6_DEV_NAME : UDP_DEV_NAME);
	if ((muxid_fd = open(udp_dev_name, O_RDWR)) == -1) {
		ret = errno;
		goto done;
	}
	ret = open_arp_on_udp(udp_dev_name, &mux_fd);
	if (ret != 0)
		goto done;

	bzero(&lifr, sizeof (lifr));
	(void) strlcpy(lifr.lifr_name, ifname, sizeof (lifr.lifr_name));
	if (ioctl(muxid_fd, SIOCGLIFMUXID, (caddr_t)&lifr) < 0) {
		ret = errno;
		goto done;
	}
	arp_muxid = lifr.lifr_arp_muxid;
	ip_muxid = lifr.lifr_ip_muxid;

	ret = solaris_get_flags(sock, ifname, &ifflags);
	if (ret != 0)
		goto done;
	/*
	 * We don't have a good way of knowing whether the arp stream is
	 * plumbed. We can't rely on IFF_NOARP because someone could
	 * have turned it off later using "ifconfig xxx -arp".
	 */
	if (arp_muxid != 0) {
		if (ioctl(mux_fd, I_PUNLINK, arp_muxid) < 0) {
			if ((errno == EINVAL) &&
			    (ifflags & (IFF_NOARP | IFF_IPV6))) {
				/*
				 * Some plumbing utilities set the muxid to
				 * -1 or some invalid value to signify that
				 * there is no arp stream. Set the muxid to 0
				 * before trying to unplumb the IP stream.
				 * IP does not allow the IP stream to be
				 * unplumbed if it sees a non-null arp muxid,
				 * for consistency of IP-ARP streams.
				 */
				lifr.lifr_arp_muxid = 0;
				(void) ioctl(muxid_fd, SIOCSLIFMUXID,
				    (caddr_t)&lifr);
				changed_arp_muxid = B_TRUE;
			}
		}
	}

	if (ioctl(mux_fd, I_PUNLINK, ip_muxid) < 0) {
		if (changed_arp_muxid) {
			/*
			 * Some error occurred, and we need to restore
			 * everything back to what it was.
			 */
			ret = errno;
			lifr.lifr_arp_muxid = arp_muxid;
			lifr.lifr_ip_muxid = ip_muxid;
			(void) ioctl(muxid_fd, SIOCSLIFMUXID, (caddr_t)&lifr);
		}
	}
done:
	if (muxid_fd != -1)
		(void) close(muxid_fd);
	if (mux_fd != -1)
		(void) close(mux_fd);

	return (ret);
}

/*
 * Plumbs the interface `ifname'.
 */
int
solaris_plumb_if(int sock, const char *ifname, sa_family_t af)
{
	int		ip_muxid;
	int		mux_fd = -1, ip_fd, arp_fd;
	char		*udp_dev_name;
	dlpi_handle_t	dh_arp = NULL, dh_ip = NULL;
	uint64_t	ifflags;
	uint_t		dlpi_flags;
	int		status = 0;
	const char	*linkname;
	int		ret;

	if (solaris_if_enabled(sock, ifname, NULL) == 0) {
		status = EEXIST;
		goto done;
	}

	dlpi_flags = DLPI_NOATTACH;
	linkname = ifname;

	/*
	 * We use DLPI_NOATTACH because the ip module will do the attach
	 * itself for DLPI style-2 devices.
	 */
	ret = dlpi_open(linkname, &dh_ip, dlpi_flags);
	if (ret != DLPI_SUCCESS) {
		ret = (ret == DL_SYSERR) ? errno : EOPNOTSUPP;
		goto done;
	}

	ip_fd = dlpi_fd(dh_ip);
	if (ioctl(ip_fd, I_PUSH, IP_MOD_NAME) == -1) {
		status = errno;
		goto done;
	}

	if (af == AF_INET) {
		ifflags = IFF_IPV4;
	} else {
		ifflags = IFF_IPV6;
		ifflags |= IFF_NOLINKLOCAL;
	}

	status = slifname(ifname, ifflags, ip_fd);
	if (status != 0)
		goto done;

	/* Get the full set of existing flags for this stream */
	status = solaris_get_flags(sock, ifname, &ifflags);
	if (status != 0)
		goto done;

	udp_dev_name = (af == AF_INET6 ? UDP6_DEV_NAME : UDP_DEV_NAME);
	status = open_arp_on_udp(udp_dev_name, &mux_fd);
	if (status != 0)
		goto done;

	/* Check if arp is not needed */
	if (ifflags & (IFF_NOARP|IFF_IPV6)) {
		/*
		 * PLINK the interface stream so that the application can exit
		 * without tearing down the stream.
		 */
		if ((ip_muxid = ioctl(mux_fd, I_PLINK, ip_fd)) == -1)
			status = errno;
		goto done;
	}

	/*
	 * This interface does use ARP, so set up a separate stream
	 * from the interface to ARP.
	 *
	 * We use DLPI_NOATTACH because the arp module will do the attach
	 * itself for DLPI style-2 devices.
	 */
	ret = dlpi_open(linkname, &dh_arp, dlpi_flags);
	if (ret != DLPI_SUCCESS) {
		ret = (ret == DL_SYSERR) ? errno : EOPNOTSUPP;
		goto done;
	}

	arp_fd = dlpi_fd(dh_arp);
	if (ioctl(arp_fd, I_PUSH, ARP_MOD_NAME) == -1) {
		status = errno;
		goto done;
	}
	status = slifname_arp(ifname, ifflags, arp_fd);
	if (status != 0)
		goto done;
	/*
	 * PLINK the IP and ARP streams so that we can exit
	 * without tearing down the stream.
	 */
	if ((ip_muxid = ioctl(mux_fd, I_PLINK, ip_fd)) == -1) {
		status = errno;
		goto done;
	}

	if (ioctl(mux_fd, I_PLINK, arp_fd) < 0) {
		status = errno;
		(void) ioctl(mux_fd, I_PUNLINK, ip_muxid);
	}

done:
	dlpi_close(dh_ip);
	if (dh_arp != NULL)
		dlpi_close(dh_arp);
	if (mux_fd != -1)
		(void) close(mux_fd);

	return (status);
}

int
solaris_init_rad()
{
	rc_uri_t *rc_uri;

	if (rad_conn == NULL) {
		if ((rc_uri = rc_alloc_uri("unix://", RCS_UNIX)) == NULL)
			return (ENODEV); /* Not sure what to return */

		rad_conn = rc_connect_uri(rc_uri, NULL);
		rc_free_uri(rc_uri);
		if (rad_conn == NULL)
			return (ENODEV); /* Not sure what to return */
		}
		return (0);
}

static rc_err_t
test_dlclass(const char *key, dlmgr_DLValue_t *dlval, void *arg)
{
	if (strcmp(key, "class") == 0)
		(void) strlcpy((char *)arg, dlval->ddlv_sval, DLADM_STRSIZE);
	dlmgr_DLValue_free(dlval);
	return (RCE_OK);
}

static rc_err_t
test_dllower(const char *key, dlmgr_DLValue_t *dlval, void *arg)
{
	/* TODO(gmoodalb): seems like we need physname/devname here */
	if (strcmp(key, "over") == 0) {
		(void) strlcpy((char *)arg, dlval->ddlv_slist[0],
		    DLADM_STRSIZE);
	}
	dlmgr_DLValue_free(dlval);
	return (RCE_OK);
}

static int
solaris_get_dlinfo(const char *netdev_name, char *info_val, size_t info_len,
    rc_err_t (*test_cb)(const char *, dlmgr_DLValue_t *, void *))
{
	dlmgr__rad_dict_string_DLValue_t *linkinfo = NULL;
	dlmgr_DatalinkError_t	*derrp = NULL;
	rc_instance_t		*link = NULL;
	rc_err_t		status;
	char			propstr[DLADM_STRSIZE];
	int			error = 0;

	status = dlmgr_Datalink__rad_lookup(rad_conn, B_TRUE, &link, 1,
	    "name", netdev_name);
	if (status != RCE_OK) {
		error = ENODEV;
		goto out;
	}

	status = dlmgr_Datalink_getInfo(link, NULL, 0, &linkinfo, &derrp);
	if (status != RCE_OK) {
		if (status == RCE_SERVER_OBJECT) {
			dpif_log(derrp->dde_err,
			    "failed Datalink_getInfo(%s): %s",
			    netdev_name, derrp->dde_errmsg);
		}
		error = ENOTSUP;
		goto out;
	}

	propstr[0] = '\0';
	status = dlmgr__rad_dict_string_DLValue_map(linkinfo, test_cb,
	    propstr);
	if (status != RCE_OK) {
		error = EINVAL;
		goto out;
	}

	memcpy(info_val, propstr, info_len);
out:
	dlmgr__rad_dict_string_DLValue_free(linkinfo);
	dlmgr_DatalinkError_free(derrp);
	rc_instance_rele(link);
	return (error);
}

int
solaris_get_devname(const char *netdev_name, char *name_val, size_t name_len)
{
	dlmgr__rad_dict_string_DLValue_t *linkinfo = NULL;
	dlmgr_DLValue_t		*dlval = NULL;
	dlmgr_DatalinkError_t	*derrp = NULL;
	rc_instance_t		*link = NULL;
	rc_err_t		status;
	int			error = 0;

	status = dlmgr_Physical__rad_lookup(rad_conn, B_TRUE, &link, 1,
	    "name", netdev_name);
	if (status != RCE_OK) {
		error = ENODEV;
		goto out;
	}

	status = dlmgr_Physical_getInfo(link, NULL, 0, &linkinfo, &derrp);
	if (status != RCE_OK) {
		if (status == RCE_SERVER_OBJECT) {
			dpif_log(derrp->dde_err,
			    "failed Physical_getInfo(%s): %s",
			    netdev_name, derrp->dde_errmsg);
		}
		error = ENODEV;
		goto out;
	}

	status = dlmgr__rad_dict_string_DLValue_get(linkinfo, "device",
	    &dlval);
	if (status != RCE_OK) {
		error = ENODEV;
		goto out;
	}

	memcpy(name_val, dlval->ddlv_sval, name_len);
out:
	dlmgr_DLValue_free(dlval);
	dlmgr_DatalinkError_free(derrp);
	dlmgr__rad_dict_string_DLValue_free(linkinfo);
	rc_instance_rele(link);
	return (error);
}

int
solaris_get_dlclass(const char *netdev_name, char *class_val, size_t class_len)
{
	return (solaris_get_dlinfo(netdev_name, class_val, class_len,
	    test_dlclass));
}

int
solaris_get_dllower(const char *netdev_name, char *lower_val, size_t lower_len)
{
	return (solaris_get_dlinfo(netdev_name, lower_val, lower_len,
	    test_dllower));
}

int
solaris_get_dlprop(const char *netdev_name, const char *prop_name,
    const char *field_name, char *prop_value, size_t prop_len)
{
	dlmgr_DLDict_t		**dlist = NULL;
	dlmgr_DLValue_t		*dlval = NULL;
	dlmgr_DatalinkError_t   *derrp = NULL;
	rc_instance_t		*link = NULL;
	rc_err_t		status;
	const char		*props[1];
	const char		*fields[1];
	int			ndlist = 0;
	int			error = 0, i = 0;
	char			buf[DLADM_STRSIZE];

	status = dlmgr_Datalink__rad_lookup(rad_conn, B_TRUE, &link, 1,
	    "name", netdev_name);
	if (status != RCE_OK) {
		error = ENODEV;
		goto out;
	}

	props[0] = prop_name;
	fields[0] = field_name;
	status = dlmgr_Datalink_getProperties(link, props, 1, fields, 1,
	    &dlist, &ndlist, &derrp);
	if (status != RCE_OK) {
		if (status == RCE_SERVER_OBJECT) {
			dpif_log(derrp->dde_err,
			    "failed Datalink_getProperties(%s, %s): %s",
			    netdev_name, prop_name, derrp->dde_errmsg);
		}
		error = ENOTSUP;
		goto out;
	}
	status = dlmgr__rad_dict_string_DLValue_get((*dlist)->ddld_map,
	    field_name, &dlval);
	if (status != RCE_OK) {
		error = EINVAL;
		goto out;
	}
	switch (dlval->ddlv_type) {
	case DDLVT_STRING:
		if (dlval->ddlv_sval == NULL) {
			error = EINVAL;
			goto out;
		}
		memcpy(prop_value, dlval->ddlv_sval, prop_len);
		break;
	case DDLVT_STRINGS:
		if (dlval->ddlv_slist_count == 0) {
			error = EINVAL;
			goto out;
		}
		for (i = 0; i < dlval->ddlv_slist_count; i++) {
			(void) snprintf(buf, sizeof (buf), "%s%s",
			    (i != 0 ? "," : ""), dlval->ddlv_slist[i]);
		}
		memcpy(prop_value, buf, prop_len);
		break;
	case DDLVT_ULONG:
		if (dlval->ddlv_ulval == NULL) {
			error = EINVAL;
			goto out;
		}
		(void) snprintf(buf, sizeof (buf), "%llu", *dlval->ddlv_ulval);
		memcpy(prop_value, buf, prop_len);
		break;
	case DDLVT_BOOLEAN:
		if (dlval->ddlv_bval == NULL) {
			error = EINVAL;
			goto out;
		}
		(void) snprintf(buf, sizeof (buf), "%d", *dlval->ddlv_bval);
		memcpy(prop_value, buf, prop_len);
		break;
	case DDLVT_BOOLEANS:
	case DDLVT_LONG:
	case DDLVT_LONGS:
	case DDLVT_ULONGS:
	case DDLVT_DICTIONARY:
	case DDLVT_DICTIONARYS:
	default:
		ovs_assert(0);
		break;
	}
out:
	dlmgr_DLValue_free(dlval);
	dlmgr_DatalinkError_free(derrp);
	dlmgr_DLDict_array_free(dlist, ndlist);
	rc_instance_rele(link);
	return (error);
}

static int
solaris_set_dlprop(const char *netdev_name, const char *propname, void *arg,
    dlmgr_DLValueType_t vtype, boolean_t temp)
{
	dlmgr__rad_dict_string_DLValue_t *sprop_dict = NULL;
	dlmgr_DLValue_t			*old_val = NULL;
	dlmgr_DLValue_t			new_val;
	rc_instance_t			*link = NULL;
	rc_err_t			status;
	dlmgr_DatalinkError_t   	*derrp = NULL;
	int				error = 0;

	status = dlmgr_Datalink__rad_lookup(rad_conn, B_TRUE, &link, 1,
	    "name", netdev_name);
	if (status != RCE_OK) {
		error = ENODEV;
		goto out;
	}

	sprop_dict = dlmgr__rad_dict_string_DLValue_create(link);
	if (sprop_dict == NULL) {
		status = ENOMEM;
		goto out;
	}

	bzero(&new_val, sizeof (new_val));
	new_val.ddlv_type = vtype;
	switch (vtype) {
	case DDLVT_BOOLEAN:
		new_val.ddlv_bval = arg;
		status = dlmgr__rad_dict_string_DLValue_put(
		    sprop_dict, propname, &new_val, &old_val);
		if (status != RCE_OK) {
			error = EINVAL;
			goto out;
		}
		dlmgr_DLValue_free(old_val);
		break;
	case DDLVT_ULONG:
		new_val.ddlv_ulval = arg;
		status = dlmgr__rad_dict_string_DLValue_put(
		    sprop_dict, propname, &new_val, &old_val);
		if (status != RCE_OK) {
			error = EINVAL;
			goto out;
		}
		dlmgr_DLValue_free(old_val);
		break;
	case DDLVT_STRING:
		new_val.ddlv_sval = arg;
		status = dlmgr__rad_dict_string_DLValue_put(
		    sprop_dict, propname, &new_val, &old_val);
		if (status != RCE_OK) {
			error = EINVAL;
			goto out;
		}
		dlmgr_DLValue_free(old_val);
		break;
	case DDLVT_LONG:
	case DDLVT_LONGS:
	case DDLVT_ULONGS:
	case DDLVT_STRINGS:
	case DDLVT_BOOLEANS:
	case DDLVT_DICTIONARY:
	case DDLVT_DICTIONARYS:
	default:
		ovs_assert(0);
		break;
	}

	if (temp) {
		bzero(&new_val, sizeof (new_val));
		old_val = NULL;
		new_val.ddlv_type = DDLVT_BOOLEAN;
		new_val.ddlv_bval = &b_true;
		status = dlmgr__rad_dict_string_DLValue_put(
		    sprop_dict, "temporary", &new_val, &old_val);
		if (status != RCE_OK) {
			error = EINVAL;
			goto out;
		}
		dlmgr_DLValue_free(old_val);
	}

	status = dlmgr_Datalink_setProperties(link, sprop_dict, &derrp);
	if (status != RCE_OK) {
		if (status == RCE_SERVER_OBJECT) {
			dpif_log(derrp->dde_err,
			    "failed Datalink_setPropertiess(%s, %s): %s",
			    netdev_name, propname, derrp->dde_errmsg);
		}
		error = ENOTSUP;
	}
out:
	dlmgr_DatalinkError_free(derrp);
	dlmgr__rad_dict_string_DLValue_free(sprop_dict);
	rc_instance_rele(link);
	return (error);
}

int
solaris_set_dlprop_boolean(const char *netdev_name, const char *propname,
    void *arg, boolean_t temp)
{
	return (solaris_set_dlprop(netdev_name, propname, arg, DDLVT_BOOLEAN,
	    temp));
}

int
solaris_set_dlprop_ulong(const char *netdev_name, const char *propname,
    void *arg, boolean_t temp)
{
	return (solaris_set_dlprop(netdev_name, propname, arg, DDLVT_ULONG,
	    temp));
}

int
solaris_set_dlprop_string(const char *netdev_name, const char *propname,
    void *arg, boolean_t temp)
{
	return (solaris_set_dlprop(netdev_name, propname, arg, DDLVT_STRING,
	    temp));
}

int
solaris_create_vnic(const char *linkname, const char *vnicname)
{
	dlmgr__rad_dict_string_DLValue_t *prop = NULL;
	dlmgr_DatalinkError_t		*derrp = NULL;
	dlmgr_DLValue_t			*old_val = NULL;
	dlmgr_DLValue_t			name_val;
	rc_instance_t			*linkmgr = NULL;
	rc_instance_t			*vnic = NULL;
	rc_err_t			status;

	status = dlmgr_DatalinkManager__rad_lookup(rad_conn, B_TRUE,
	    &linkmgr, 0);
	if (status != RCE_OK)
		goto out;

	prop = dlmgr__rad_dict_string_DLValue_create(linkmgr);
	if (prop == NULL)
		goto out;

	bzero(&name_val, sizeof (name_val));
	name_val.ddlv_type = DDLVT_STRING;
	/* linkname is 'const char *' and ddlv_sval is 'char *' */
	name_val.ddlv_sval = strdupa(linkname);
	status = dlmgr__rad_dict_string_DLValue_put(prop, "lower-link",
	    &name_val, &old_val);
	if (status != RCE_OK)
		goto out;
	dlmgr_DLValue_free(old_val);
	old_val = NULL;

	status = dlmgr_DatalinkManager_createVNIC(linkmgr, vnicname, prop,
	    &vnic, &derrp);
	if (status == RCE_SERVER_OBJECT) {
		dpif_log(derrp->dde_err,
		    "failed DatalinkManager_createVNIC(%s): %s",
		    vnicname, derrp->dde_errmsg);
	}
	rc_instance_rele(vnic);
	dlmgr_DatalinkError_free(derrp);
out:
	dlmgr__rad_dict_string_DLValue_free(prop);
	rc_instance_rele(linkmgr);
	return ((status != RCE_OK) ? ENOTSUP : 0);
}

int
solaris_modify_vnic(const char *linkname, const char *vnicname)
{
	dlmgr__rad_dict_string_DLValue_t *sprop_dict = NULL;
	dlmgr_DLValue_t			*old_val = NULL;
	dlmgr_DLValue_t			new_val;
	rc_instance_t			*link = NULL;
	rc_err_t			status;
	dlmgr_DatalinkError_t   	*derrp = NULL;
	int				error = 0;

	status = dlmgr_Datalink__rad_lookup(rad_conn, B_TRUE, &link, 1,
	    "name", vnicname);
	if (status != RCE_OK) {
		error = ENODEV;
		goto out;
	}

	sprop_dict = dlmgr__rad_dict_string_DLValue_create(link);
	if (sprop_dict == NULL) {
		status = ENOMEM;
		goto out;
	}

	bzero(&new_val, sizeof (new_val));
	new_val.ddlv_type = DDLVT_STRING;
	new_val.ddlv_sval = strdupa(linkname);
	status = dlmgr__rad_dict_string_DLValue_put(
	    sprop_dict, "lower-link", &new_val, &old_val);
	if (status != RCE_OK) {
		error = EINVAL;
		goto out;
	}
	dlmgr_DLValue_free(old_val);

	status = dlmgr_Datalink_setProperties(link, sprop_dict, &derrp);
	if (status != RCE_OK) {
		if (status == RCE_SERVER_OBJECT) {
			dpif_log(derrp->dde_err,
			    "failed Datalink_setPropertiess(%s, lower-link): "
			    " %s", vnicname, derrp->dde_errmsg);
		}
		error = ENOTSUP;
	}
out:
	dlmgr_DatalinkError_free(derrp);
	dlmgr__rad_dict_string_DLValue_free(sprop_dict);
	rc_instance_rele(link);
	return (error);
}

int
solaris_delete_vnic(const char *vnicname)
{
	dlmgr_DatalinkError_t		*derrp = NULL;
	rc_instance_t			*linkmgr = NULL;
	rc_err_t			status;
	int				err = 0;

	status = dlmgr_DatalinkManager__rad_lookup(rad_conn, B_TRUE,
	    &linkmgr, 0);
	if (status != RCE_OK)
		return (EINVAL);

	status = dlmgr_DatalinkManager_deleteVNIC(linkmgr, vnicname, NULL,
	    &derrp);
	if (status != RCE_OK) {
		err = -1;
		if (status == RCE_SERVER_OBJECT) {
			err = derrp->dde_err;
			dpif_log(err,
			    "failed DatalinkManager_deleteVNIC(%s): %s",
			    vnicname, derrp->dde_errmsg);
		}
	}
	dlmgr_DatalinkError_free(derrp);

	rc_instance_rele(linkmgr);
	return (err);
}

int
solaris_create_etherstub(const char *name)
{
	dlmgr_DatalinkError_t		*derrp = NULL;
	rc_instance_t			*linkmgr = NULL;
	rc_instance_t			*etherstub = NULL;
	rc_err_t			status;

	status = dlmgr_DatalinkManager__rad_lookup(rad_conn, B_TRUE,
	    &linkmgr, 0);
	if (status != RCE_OK)
		return (ENOTSUP);

	status = dlmgr_DatalinkManager_createEtherstub(linkmgr, name, NULL,
	    &etherstub, &derrp);
	if (status == RCE_SERVER_OBJECT) {
		dpif_log(derrp->dde_err,
		    "failed DatalinkManager_createEtherstub(%s): %s",
		    name, derrp->dde_errmsg);
	}
	rc_instance_rele(etherstub);
	dlmgr_DatalinkError_free(derrp);
	rc_instance_rele(linkmgr);

	return ((status != RCE_OK) ? ENOTSUP : 0);
}

int
solaris_delete_etherstub(const char *name)
{
	dlmgr_DatalinkError_t		*derrp = NULL;
	rc_instance_t			*linkmgr = NULL;
	rc_err_t			status;

	status = dlmgr_DatalinkManager__rad_lookup(rad_conn, B_TRUE,
	    &linkmgr, 0);
	if (status != RCE_OK)
		return (ENOTSUP);

	status = dlmgr_DatalinkManager_deleteEtherstub(linkmgr, name, NULL,
	    &derrp);
	if (status == RCE_SERVER_OBJECT) {
		dpif_log(derrp->dde_err,
		    "failed DatalinkManager_deleteEtherstub(%s): %s",
		    name, derrp->dde_errmsg);
	}
	dlmgr_DatalinkError_free(derrp);
	rc_instance_rele(linkmgr);

	return ((status != RCE_OK) ? ENOTSUP : 0);
}

static int
flow_str2mac(const char *str, uchar_t *f, size_t maclen)
{
	uchar_t		*addr = NULL;
	int		len, err = 0;

	if ((addr = _link_aton(str, &len)) == NULL)
		return ((len == -1) ? EINVAL : ENOMEM);

	if (len != maclen) {
		err = EINVAL;
		goto done;
	}

	bcopy(addr, f, maclen);
done:
	free(addr);
	return (err);
}

static int
flow_str2addr(const char *str, in6_addr_t *f, int *afp)
{
	struct in_addr	v4addr;
	struct in6_addr	v6addr;
	int		af;

	if (inet_pton(AF_INET, str, &v4addr.s_addr) == 1) {
		af = AF_INET;
	} else if (inet_pton(AF_INET6, str, v6addr.s6_addr) == 1) {
		af = AF_INET6;
	} else {
		return (EINVAL);
	}

	if (af == AF_INET) {
		IN6_INADDR_TO_V4MAPPED(&v4addr, f);
	} else {
		*f = v6addr;
	}
	*afp = af;
	return (0);
}

static int
solaris_flowinfo2linkname(dlmgr__rad_dict_string_DLValue_t *flowinfo,
    char *linkname, size_t size)
{
	dlmgr__rad_dict_string_DLValue_t *fdict;
	dlmgr_DLValue_t		*flist = NULL, *dlval = NULL;
	rc_err_t		status;
	int			err = 0;

	status = dlmgr__rad_dict_string_DLValue_get(flowinfo, "filters",
	    &flist);
	if (status != RCE_OK)
		return (EINVAL);

	fdict = flist->ddlv_dlist[0]->ddld_map;

	status = dlmgr__rad_dict_string_DLValue_get(fdict,
	    "linkname", &dlval);
	if (status != RCE_OK) {
		err = EINVAL;
		goto out;
	}
	(void) strlcpy(linkname, dlval->ddlv_sval, size);
	dlmgr_DLValue_free(dlval);
out:
	dlmgr_DLValue_free(flist);
	return (err);
}

static void
flow_mac2str(uint8_t *f, uint8_t *m, char *buf, char *rbuf, size_t buf_len,
    size_t rbuf_len)
{
	char *str = NULL;
	char *pstr = NULL;

	buf[0] = '\0';
	rbuf[0] = '\0';

	if (!eth_addr_is_zero(f) || !eth_addr_is_zero(m)) {
		str = _link_ntoa(f, NULL, ETHERADDRL, IFT_ETHER);
		if (str != NULL) {
			pstr = _link_ntoa(m, NULL, ETHERADDRL, IFT_ETHER);
			if (pstr != NULL) {
				(void) snprintf(buf, buf_len, "%s", str);
				(void) snprintf(rbuf, rbuf_len, "%s", pstr);
				free(pstr);
			}
			free(str);
		}
	}
}

static void
flow_addr2str(struct in6_addr *f6, struct in6_addr *m6, uint32_t f4,
    uint32_t m4, char *buf, char *rbuf, size_t buf_len, size_t rbuf_len)
{
	struct in_addr ipaddr;
	char abuf[INET6_ADDRSTRLEN], mbuf[INET6_ADDRSTRLEN];

	buf[0] = '\0';
	rbuf[0] = '\0';
	if ((f6 != NULL) && (m6 != NULL) &&
	    (!ipv6_addr_equals(f6, &in6addr_any) ||
	    !ipv6_addr_equals(m6, &in6addr_any))) {
		(void) inet_ntop(AF_INET6, f6, abuf, INET6_ADDRSTRLEN);
		(void) inet_ntop(AF_INET6, m6, mbuf, INET6_ADDRSTRLEN);
		(void) snprintf(buf, buf_len, "%s", abuf);
		(void) snprintf(rbuf, rbuf_len, "%s", mbuf);
	} else if (f4 != 0 || m4 != 0) {
		ipaddr.s_addr = f4;
		(void) strlcpy(abuf, inet_ntoa(ipaddr), sizeof (abuf));
		ipaddr.s_addr = m4;
		(void) strlcpy(mbuf, inet_ntoa(ipaddr), sizeof (mbuf));
		(void) snprintf(buf, buf_len, "%s", abuf);
		(void) snprintf(rbuf, rbuf_len, "%s", mbuf);
	}
}

#define	FP_NAME_VAL_DELIM		'@'
#define	FP_MULTI_ACTION_DELIM		'#'
#define	FP_ACTION_NAME_VALUE_DELIM	'-'
#define	FP_ACTION_MULTI_VAL_DELIM	'^'
#define	FP_MULTI_ACTION_DELIM_STR	"#"

static int
flow_ofports2propstr(char *str, size_t strsize, uint32_t *ofports,
    int nofports)
{
	char	buf[DLADM_STRSIZE];
	int	i;

	if (nofports == 0) {
		(void) snprintf(buf, sizeof (buf), "%soutports%cdrop",
		    strlen(str) == 0 ? "" : FP_MULTI_ACTION_DELIM_STR,
		    FP_NAME_VAL_DELIM);

		if (strlcat(str, buf, strsize) >= strsize)
			return (EINVAL);

		return (0);
	}

	for (i = 0; i < nofports; i++) {
		(void) snprintf(buf, sizeof (buf), "%soutports%c%u",
		    (i == 0) && strlen(str) == 0 ? "" :
		    FP_MULTI_ACTION_DELIM_STR, FP_NAME_VAL_DELIM, ofports[i]);

		if (strlcat(str, buf, strsize) >= strsize)
			return (EINVAL);
	}
	return (0);
}

static int
dlmgr_DLValue_putstring(dlmgr__rad_dict_string_DLValue_t *ddvp,
    const char *key, char *buf, char *dstr, size_t dstrlen)
{
	dlmgr_DLValue_t  *old_val = NULL;
	dlmgr_DLValue_t  new_val;
	rc_err_t status;

	if (strlen(key) != 0) {
		bzero(&new_val, sizeof (new_val));
		new_val.ddlv_type = DDLVT_STRING;
		new_val.ddlv_sval = buf;
		if ((status = dlmgr__rad_dict_string_DLValue_put(ddvp, key,
		    &new_val, &old_val)) != RCE_OK) {
			return (EINVAL);
		}
		snprintf(dstr, dstrlen, "%s,%s=%s", dstr, key, buf);
		dlmgr_DLValue_free(old_val);
	}
	return (0);
}

static int
dlmgr_DLValue_fm_putstring(dlmgr__rad_dict_string_DLValue_t *ddvp,
    dlmgr__rad_dict_string_DLValue_t *ddmp, const char *key,
    char *buf, char *rbuf, char *dstr, size_t dstrlen)
{
	dlmgr_DLValue_t  *old_val = NULL;
	dlmgr_DLValue_t  new_val;
	rc_err_t status;

	if (strlen(buf) != 0) {
		bzero(&new_val, sizeof (new_val));
		new_val.ddlv_type = DDLVT_STRING;
		new_val.ddlv_sval = buf;
		if ((status = dlmgr__rad_dict_string_DLValue_put(ddvp, key,
		    &new_val, &old_val)) != RCE_OK) {
			return (EINVAL);
		}
		dlmgr_DLValue_free(old_val);
		old_val = NULL;
		new_val.ddlv_sval = rbuf;
		if ((status = dlmgr__rad_dict_string_DLValue_put(ddmp, key,
		    &new_val, &old_val)) != RCE_OK) {
			return (EINVAL);
		}
		dlmgr_DLValue_free(old_val);

		snprintf(dstr, dstrlen, "%s,%s=%s/%s", dstr, key, buf, rbuf);
	}
	return (0);
}

static int
dlmgr_DLValue_putboolean(dlmgr__rad_dict_string_DLValue_t *ddvp,
    const char *key, boolean_t val, char *dstr, size_t dstrlen)
{
	dlmgr_DLValue_t  *old_val = NULL;
	dlmgr_DLValue_t  new_val;
	rc_err_t status;

	bzero(&new_val, sizeof (new_val));
	new_val.ddlv_type = DDLVT_BOOLEAN;
	new_val.ddlv_bval = &val;
	if ((status = dlmgr__rad_dict_string_DLValue_put(ddvp, key, &new_val,
	    &old_val)) != RCE_OK) {
		return (EINVAL);
	}
	snprintf(dstr, dstrlen, "%s,%s=%s", dstr, key,
	    val ? "true" : "false");
	dlmgr_DLValue_free(old_val);
	return (0);
}

static int
dlmgr_DLValue_putulong(dlmgr__rad_dict_string_DLValue_t *ddvp, const char *key,
    uint64_t val, char *dstr, size_t dstrlen)
{
	dlmgr_DLValue_t  *old_val = NULL;
	dlmgr_DLValue_t  new_val;
	unsigned long long ulval = val;
	rc_err_t status;

	bzero(&new_val, sizeof (new_val));
	new_val.ddlv_type = DDLVT_ULONG;
	new_val.ddlv_ulval = &ulval;
	if ((status = dlmgr__rad_dict_string_DLValue_put(ddvp, key, &new_val,
	    &old_val)) != RCE_OK) {
		return (EINVAL);
	}
	snprintf(dstr, dstrlen, "%s,%s=%"PRIu64, dstr, key, val);
	dlmgr_DLValue_free(old_val);
	return (0);
}

static int
dlmgr_DLValue_fm_putulong(dlmgr__rad_dict_string_DLValue_t *ddvp,
    dlmgr__rad_dict_string_DLValue_t *ddmp, const char *key,
    uint64_t f, uint64_t m, char *dstr, size_t dstrlen)
{
	dlmgr_DLValue_t  *old_val = NULL;
	dlmgr_DLValue_t  new_val;
	unsigned long long f_ulval = f;
	unsigned long long m_ulval = m;
	rc_err_t status;

	bzero(&new_val, sizeof (new_val));
	new_val.ddlv_type = DDLVT_ULONG;
	new_val.ddlv_ulval = &f_ulval;
	if ((status = dlmgr__rad_dict_string_DLValue_put(ddvp, key, &new_val,
	    &old_val)) != RCE_OK) {
		return (EINVAL);
	}
	dlmgr_DLValue_free(old_val);
	old_val = NULL;
	new_val.ddlv_ulval = &m_ulval;
	if ((status = dlmgr__rad_dict_string_DLValue_put(ddmp, key, &new_val,
	    &old_val)) != RCE_OK) {
		return (EINVAL);
	}
	dlmgr_DLValue_free(old_val);
	snprintf(dstr, dstrlen, "%s,%s=%"PRIu64"/%"PRIu64, dstr, key, f, m);
	return (0);
}

static int
solaris_flow_to_DLVal(struct flow *f, struct flow *m,
    dlmgr__rad_dict_string_DLValue_t *ddvp,
    dlmgr__rad_dict_string_DLValue_t *ddmp)
{
	char		buf[DLADM_STRSIZE], rbuf[DLADM_STRSIZE];
	char		dstr[DLADM_STRSIZE];
	int		err = 0;
	boolean_t	is_arp = (ntohs(f->dl_type) == 0x806);

	dstr[0] = '\0';
	if (f->dl_type != htons(FLOW_DL_TYPE_NONE)) {
		err = dlmgr_DLValue_fm_putulong(ddvp, ddmp, "sap",
		    ntohs(f->dl_type), ntohs(m->dl_type), dstr, sizeof (dstr));
		if (err != 0)
			goto out;
	}

	if (is_arp) {
		if (f->nw_proto != 0 || m->nw_proto != 0) {
			err = dlmgr_DLValue_fm_putulong(ddvp, ddmp, "arp-op",
			    f->nw_proto, m->nw_proto, dstr, sizeof (dstr));
			if (err != 0)
				goto out;
		}

		flow_mac2str(f->arp_sha, m->arp_sha, buf, rbuf, sizeof (buf),
		    sizeof (rbuf));
		if (strlen(buf) != 0) {
			err = dlmgr_DLValue_fm_putstring(ddvp, ddmp,
			    "arp-sender", buf, rbuf, dstr, sizeof (dstr));
			if (err != 0)
				goto out;
		}

		flow_mac2str(f->arp_tha, m->arp_tha, buf, rbuf, sizeof (buf),
		    sizeof (rbuf));
		if (strlen(buf) != 0) {
			err = dlmgr_DLValue_fm_putstring(ddvp, ddmp,
			    "arp-target", buf, rbuf, dstr, sizeof (dstr));
			if (err != 0)
				goto out;
		}

		flow_addr2str(NULL, NULL, f->nw_src, m->nw_src, buf, rbuf,
		    sizeof (buf), sizeof (rbuf));
		if (strlen(buf) != 0) {
			err = dlmgr_DLValue_fm_putstring(ddvp, ddmp, "arp-sip",
			    buf, rbuf, dstr, sizeof (dstr));
			if (err != 0)
				goto out;
		}

		flow_addr2str(NULL, NULL, f->nw_dst, m->nw_dst, buf, rbuf,
		    sizeof (buf), sizeof (rbuf));
		if (strlen(buf) != 0) {
			err = dlmgr_DLValue_fm_putstring(ddvp, ddmp, "arp-tip",
			    buf, rbuf,  dstr, sizeof (dstr));
			if (err != 0)
				goto out;
		}
	} else {
		if (f->nw_proto != 0 || m->nw_proto != 0) {
			err = dlmgr_DLValue_fm_putulong(ddvp, ddmp, "transport",
			    f->nw_proto, m->nw_proto, dstr, sizeof (dstr));
			if (err != 0)
				goto out;
		}

		flow_addr2str(&f->ipv6_src, &m->ipv6_src, f->nw_src, m->nw_src,
		    buf, rbuf, sizeof (buf), sizeof (rbuf));
		if (strlen(buf) != 0) {
			err = dlmgr_DLValue_fm_putstring(ddvp, ddmp, "local-ip",
			    buf, rbuf, dstr, sizeof (dstr));
			if (err != 0)
				goto out;
		}

		flow_addr2str(&f->ipv6_dst, &m->ipv6_dst, f->nw_dst, m->nw_dst,
		    buf, rbuf, sizeof (buf), sizeof (rbuf));
		if (strlen(buf) != 0) {
			err = dlmgr_DLValue_fm_putstring(ddvp, ddmp,
			    "remote-ip", buf, rbuf, dstr, sizeof (dstr));
			if (err != 0)
				goto out;
		}

		if (f->tcp_flags != 0 || m->tcp_flags != 0) {
			err = dlmgr_DLValue_fm_putulong(ddvp, ddmp,
			    "tcp-flags", (uint8_t)(ntohs(f->tcp_flags)),
			    (uint8_t)(ntohs(m->tcp_flags)), dstr,
			    sizeof (dstr));
			if (err != 0)
				goto out;
		}

		if (f->nw_proto != IPPROTO_ICMP &&
		    f->nw_proto != IPPROTO_ICMPV6) {
			if (f->tp_src != 0 || m->tp_src != 0) {
				err = dlmgr_DLValue_fm_putulong(ddvp, ddmp,
				    "local-port", ntohs(f->tp_src),
				    ntohs(m->tp_src), dstr, sizeof (dstr));
				if (err != 0)
					goto out;
			}

			if (f->tp_dst != 0 || m->tp_dst != 0) {
				err = dlmgr_DLValue_fm_putulong(ddvp, ddmp,
				    "remote-port", ntohs(f->tp_dst),
				    ntohs(m->tp_dst), dstr, sizeof (dstr));
				if (err != 0)
					goto out;
			}
		} else {
			if (f->tp_src != 0 || m->tp_src != 0) {
				err = dlmgr_DLValue_fm_putulong(ddvp, ddmp,
				    "icmp-type", ntohs(f->tp_src),
				    ntohs(m->tp_src), dstr, sizeof (dstr));
				if (err != 0)
					goto out;
			}
			if (f->tp_dst != 0 || m->tp_dst != 0) {
				err = dlmgr_DLValue_fm_putulong(ddvp, ddmp,
				    "icmp-code", ntohs(f->tp_dst),
				    ntohs(m->tp_dst), dstr, sizeof (dstr));
				if (err != 0)
					goto out;
			}

			flow_mac2str(f->arp_sha, m->arp_sha, buf, rbuf,
			    sizeof (buf), sizeof (rbuf));
			if (strlen(buf) != 0) {
				err = dlmgr_DLValue_fm_putstring(ddvp, ddmp,
				    "nd-sll", buf, rbuf,
				    dstr, sizeof (dstr));
				if (err != 0)
					goto out;
			}

			flow_mac2str(f->arp_tha, m->arp_tha, buf, rbuf,
			    sizeof (buf), sizeof (rbuf));
			if (strlen(buf) != 0) {
				err = dlmgr_DLValue_fm_putstring(ddvp, ddmp,
				    "nd-tll", buf, rbuf,
				    dstr, sizeof (dstr));
				if (err != 0)
					goto out;
			}

			flow_addr2str(&f->nd_target, &m->nd_target, 0, 0,
			    buf, rbuf, sizeof (buf), sizeof (rbuf));
			if (strlen(buf) != 0) {
				err = dlmgr_DLValue_fm_putstring(ddvp, ddmp,
				    "nd-target", buf, rbuf,
				    dstr, sizeof (dstr));
				if (err != 0)
					goto out;
			}
		}
	}


	flow_mac2str(f->dl_src, m->dl_src, buf, rbuf, sizeof (buf),
	    sizeof (rbuf));
	if (strlen(buf) != 0) {
		err = dlmgr_DLValue_fm_putstring(ddvp, ddmp, "src-mac", buf,
		    rbuf, dstr, sizeof (dstr));
		if (err != 0)
			goto out;
	}

	flow_mac2str(f->dl_dst, m->dl_dst, buf, rbuf, sizeof (buf),
	    sizeof (rbuf));
	if (strlen(buf) != 0) {
		err = dlmgr_DLValue_fm_putstring(ddvp, ddmp, "dst-mac", buf,
		    rbuf, dstr, sizeof (dstr));
		if (err != 0)
			goto out;
	}

	if (f->in_port.odp_port != ODPP_NONE) {
		err = dlmgr_DLValue_putulong(ddvp, "srcport",
		    f->in_port.odp_port, dstr, sizeof (dstr));
		if (err != 0)
			goto out;
	}

	if ((f->vlan_tci != 0) || (m->vlan_tci != htons(0xffff))) {
		err = dlmgr_DLValue_fm_putulong(ddvp, ddmp,
		    "vlan-tci", ntohs(f->vlan_tci),
		    ntohs(m->vlan_tci), dstr, sizeof (dstr));
		if (err != 0)
			goto out;
	}

	if (f->nw_tos != 0 || m->nw_tos != 0) {
		err = dlmgr_DLValue_fm_putulong(ddvp, ddmp,
		    "dsfield", f->nw_tos, m->nw_tos, dstr, sizeof (dstr));
		if (err != 0)
			goto out;
	}

	if (f->nw_ttl != 0 || m->nw_ttl != 0) {
		err = dlmgr_DLValue_fm_putulong(ddvp, ddmp,
		    "ttl", f->nw_ttl, m->nw_ttl, dstr, sizeof (dstr));
		if (err != 0)
			goto out;
	}

out:
	dpif_log(err, "solaris_flow_to_DLVal FLOWATTR: %s", dstr);
	return (err);
}

static int
solaris_maxbw_action_to_DLVal(dlmgr__rad_dict_string_DLValue_t *prop,
    void *cookie, uint32_t ofports[], int nofports, uint32_t queueid,
    char *dstr, size_t dstrlen)
{
	struct smap details;
	const char *max_rate = NULL;
	uint64_t maxbw;
	char *endp = NULL;
	int err = EINVAL;

	smap_init(&details);
	if (queueid == UINT32_MAX || nofports != 1)
		goto done;

	if ((err = dpif_solaris_get_priority_details(cookie, ofports[0],
	    queueid, &details)) != 0) {
		goto done;
	}
	/* min-rate and priority not currently used */
	max_rate = smap_get(&details, "max-rate");
	if (max_rate == NULL)
		goto done;

	errno = 0;
	maxbw = strtoull(max_rate, &endp, 10);
	if (errno != 0 || *endp != '\0')
		goto done;

	err = dlmgr_DLValue_putulong(prop, "max-bw", maxbw, dstr, dstrlen);

done:
	smap_destroy(&details);
	return (err);
}

static int
solaris_setether_action_to_str(char *str, size_t strsize,
    const struct ovs_key_ethernet *ek)
{
	char *sstr = NULL, *dstr = NULL;
	char buf[DLADM_STRSIZE];
	int err = 0;

	sstr = _link_ntoa(ek->eth_src, NULL, ETHERADDRL, IFT_ETHER);
	dstr = _link_ntoa(ek->eth_dst, NULL, ETHERADDRL, IFT_ETHER);
	if (sstr != NULL && dstr != NULL) {
		(void) snprintf(buf, sizeof (buf),
		    "%ssetether%cether_src%c%s%cether_dst%c%s",
		    (strlen(str) == 0) ? "" : FP_MULTI_ACTION_DELIM_STR,
		    FP_NAME_VAL_DELIM, FP_ACTION_NAME_VALUE_DELIM, sstr,
		    FP_ACTION_MULTI_VAL_DELIM, FP_ACTION_NAME_VALUE_DELIM,
		    dstr);
		if (strlcat(str, buf, strsize) >= strsize)
			err = EINVAL;
	}
	free(sstr);
	free(dstr);
	if (sstr == NULL || dstr == NULL)
		err = ENOMEM;
	return (err);
}

static int
solaris_setipv4_action_to_str(char *str, size_t strsize,
    const struct ovs_key_ipv4 *ipv4)
{
	struct in_addr ipaddr;
	char *cp;
	char buf[DLADM_STRSIZE];
	int err = 0;

	ipaddr.s_addr = ipv4->ipv4_src;
	cp = inet_ntoa(ipaddr);
	(void) snprintf(buf, sizeof (buf), "%sset-ipv4%cdst%c%s%c",
	    (strlen(str) == 0) ? "" : FP_MULTI_ACTION_DELIM_STR,
	    FP_NAME_VAL_DELIM, FP_ACTION_NAME_VALUE_DELIM, cp,
	    FP_ACTION_MULTI_VAL_DELIM);

	ipaddr.s_addr = ipv4->ipv4_dst;
	cp = inet_ntoa(ipaddr);
	(void) snprintf(buf, sizeof (buf),
	    "%sdst%c%s%cprotocol%c%s%ctos%c0x%x%choplimit%c%d",
	    buf, FP_ACTION_NAME_VALUE_DELIM, cp, FP_ACTION_MULTI_VAL_DELIM,
	    FP_ACTION_NAME_VALUE_DELIM, solaris_proto2str(ipv4->ipv4_proto),
	    FP_ACTION_MULTI_VAL_DELIM, FP_ACTION_NAME_VALUE_DELIM,
	    ipv4->ipv4_tos, FP_ACTION_MULTI_VAL_DELIM,
	    FP_ACTION_NAME_VALUE_DELIM, ipv4->ipv4_ttl);
	if (strlcat(str, buf, strsize) >= strsize)
		err = EINVAL;

	return (err);
}

static int
solaris_setipv6_action_to_str(char *str, size_t strsize,
    const struct ovs_key_ipv6 *ipv6)
{
	char abuf[INET6_ADDRSTRLEN];
	char buf[DLADM_STRSIZE];
	int err = 0;

	(void) inet_ntop(AF_INET6, ipv6->ipv6_src, abuf, INET6_ADDRSTRLEN);
	(void) snprintf(buf, sizeof (buf),
	    "%sset-ipv6%csrc%c%s%c", (strlen(str) == 0) ? "" :
	    FP_MULTI_ACTION_DELIM_STR, FP_NAME_VAL_DELIM,
	    FP_ACTION_NAME_VALUE_DELIM, abuf, FP_ACTION_MULTI_VAL_DELIM);

	(void) inet_ntop(AF_INET6, ipv6->ipv6_dst, abuf, INET6_ADDRSTRLEN);
	(void) snprintf(buf, sizeof (buf),
	    "%sdst%c%s%clabel%c0x%x%cprotocol%c%s%ctos%c0x%x%choplimit%c%d",
	    buf, FP_ACTION_NAME_VALUE_DELIM, abuf, FP_ACTION_MULTI_VAL_DELIM,
	    FP_ACTION_NAME_VALUE_DELIM, ipv6->ipv6_label,
	    FP_ACTION_MULTI_VAL_DELIM, FP_ACTION_NAME_VALUE_DELIM,
	    solaris_proto2str(ipv6->ipv6_proto), FP_ACTION_MULTI_VAL_DELIM,
	    FP_ACTION_NAME_VALUE_DELIM, ipv6->ipv6_tclass,
	    FP_ACTION_MULTI_VAL_DELIM, FP_ACTION_NAME_VALUE_DELIM,
	    ipv6->ipv6_hlimit);
	if (strlcat(str, buf, strsize) >= strsize)
		err = EINVAL;

	return (err);
}

static int
solaris_settransport_action_to_str(char *str, size_t strsize, const char *key,
    uint16_t src, uint16_t dst)
{
	char buf[DLADM_STRSIZE];
	int err = 0;

	(void) snprintf(buf, sizeof (buf),
	    "%s%s%csport%c%d%cdport%c%d", (strlen(str) == 0) ? "" :
	    FP_MULTI_ACTION_DELIM_STR, key, FP_NAME_VAL_DELIM,
	    FP_ACTION_NAME_VALUE_DELIM, src, FP_ACTION_MULTI_VAL_DELIM,
	    FP_ACTION_NAME_VALUE_DELIM, dst);
	if (strlcat(str, buf, strsize) >= strsize)
		err = EINVAL;

	return (err);
}

static int
solaris_settnl_action_to_str(char *str, size_t strsize,
    const struct flow_tnl *tnl)
{
	struct in_addr ipaddr;
	char *cp;
	char buf[DLADM_STRSIZE];
	int err = 0;

	ipaddr.s_addr = tnl->ip_src;
	cp = inet_ntoa(ipaddr);
	(void) snprintf(buf, sizeof (buf), "%sset-tunnel%csrc%c%s%c",
	    (strlen(str) == 0) ? "" : FP_MULTI_ACTION_DELIM_STR,
	    FP_NAME_VAL_DELIM, FP_ACTION_NAME_VALUE_DELIM, cp,
	    FP_ACTION_MULTI_VAL_DELIM);

	ipaddr.s_addr = tnl->ip_dst;
	cp = inet_ntoa(ipaddr);
	(void) snprintf(buf, sizeof (buf),
	    "%sdst%c%s%ctun_id%c0x%"PRIx64"%ctos%c0x%x%choplimit%c%d",
	    buf, FP_ACTION_NAME_VALUE_DELIM, cp, FP_ACTION_MULTI_VAL_DELIM,
	    FP_ACTION_NAME_VALUE_DELIM, ntohll(tnl->tun_id),
	    FP_ACTION_MULTI_VAL_DELIM, FP_ACTION_NAME_VALUE_DELIM,
	    tnl->ip_tos, FP_ACTION_MULTI_VAL_DELIM, FP_ACTION_NAME_VALUE_DELIM,
	    tnl->ip_ttl);
	if (strlcat(str, buf, strsize) >= strsize)
		err = EINVAL;

	return (err);
}

static int
solaris_nlattr_to_DLVal(void *cookie,
    const struct nlattr *actions_nlattr, size_t actions_len,
    dlmgr__rad_dict_string_DLValue_t *prop)
{
	const struct nlattr *a;
	unsigned int left;
	char buf[DLADM_STRSIZE];
	char str[DLADM_STRSIZE];
	char dstr[DLADM_STRSIZE];
	int err = 0, nofports = 0;
	uint32_t ofports[MAC_OF_MAXPORT];
	enum ovs_action_attr type = -1, lasttype;
	uint_t queueid = UINT32_MAX;

	dstr[0] = '\0';
	str[0] = '\0';
	err = dlmgr_DLValue_putboolean(prop, "temporary", B_TRUE, dstr,
	    sizeof (dstr));
	if (err != 0)
		goto out;

	/* if actions_len == 0, then the action is drop */
	if (actions_len == 0) {
		err = flow_ofports2propstr(str, sizeof (str), ofports, 0);
		goto out;
	}

	NL_ATTR_FOR_EACH_UNSAFE(a, left, actions_nlattr, actions_len) {
		lasttype = type;
		type = nl_attr_type(a);
		if ((type != OVS_ACTION_ATTR_OUTPUT) ||
		    (lasttype != OVS_ACTION_ATTR_OUTPUT)) {
			if (lasttype == OVS_ACTION_ATTR_OUTPUT) {
				dpif_log(0, "solaris_nlattr_to_DLVal outports "
				    "total %d ports", nofports);
				err = flow_ofports2propstr(str, sizeof (str),
				    ofports, nofports);
				if (err != 0)
					goto out;
				(void) solaris_maxbw_action_to_DLVal(prop,
				    cookie, ofports, nofports, queueid, dstr,
				    sizeof (dstr));
			}
			nofports = 0;
		}

		switch ((enum ovs_action_attr) type) {
		/* These only make sense in the context of a datapath. */
		case OVS_ACTION_ATTR_OUTPUT:
			if (nofports + 1 > MAC_OF_MAXPORT) {
				err = ENOBUFS;
				break;
			}
			dpif_log(0, "solaris_nlattr_to_DLVal %d ports: %u",
			    nofports+1, nl_attr_get_u32(a));
			ofports[nofports++] = u32_to_odp(nl_attr_get_u32(a));
			break;
		case OVS_ACTION_ATTR_USERSPACE: {
			const struct nlattr *userdata;
			size_t userdata_len;
			union user_action_cookie cookie;

			userdata = nl_attr_find_nested(a,
			    OVS_USERSPACE_ATTR_USERDATA);
			userdata_len = nl_attr_get_size(userdata);
			memcpy(&cookie, nl_attr_get(userdata), userdata_len);
			if (userdata_len < sizeof (cookie.type) ||
			    userdata_len > sizeof (cookie)) {
				err = EINVAL;
				dpif_log(err,
				    "unexpected action size %"PRIuSIZE,
				    userdata_len);
				break;
			}
			if (userdata_len != MAX(8, sizeof (cookie.slow_path)) ||
			    cookie.type != USER_ACTION_COOKIE_SLOW_PATH) {
				err = EOPNOTSUPP;
				dpif_log(err,
				    "userspace action size %"PRIuSIZE" "
				    "type unsupported %d", userdata_len,
				    cookie.type);
				break;
			}
			if (cookie.slow_path.reason != SLOW_CONTROLLER)
				break;

			(void) snprintf(buf, sizeof (buf), "%scontroller%c%u",
			    (strlen(str) == 0) ? "" : FP_MULTI_ACTION_DELIM_STR,
			    FP_NAME_VAL_DELIM, PORT_PF_PACKET_UPLINK);

			if (strlcat(str, buf, sizeof (str)) >= sizeof (str)) {
				err = EINVAL;
				break;
			}
			break;
		}
		case OVS_ACTION_ATTR_SET: {
			const struct nlattr *aset = nl_attr_get(a);

			switch (nl_attr_type(aset)) {
			case OVS_KEY_ATTR_PRIORITY:
				queueid = nl_attr_get_u32(aset);
				break;

			case OVS_KEY_ATTR_ETHERNET: {
				const struct ovs_key_ethernet *ek;

				ek = nl_attr_get_unspec(aset,
				    sizeof (struct ovs_key_ethernet));
				err = solaris_setether_action_to_str(str,
				    sizeof (str), ek);
				break;
			}
			case OVS_KEY_ATTR_IPV4: {
				const struct ovs_key_ipv4 *eip4;

				eip4 = nl_attr_get_unspec(aset,
				    sizeof (struct ovs_key_ipv4));
				err = solaris_setipv4_action_to_str(str,
				    sizeof (str), eip4);
				break;
			}
			case OVS_KEY_ATTR_IPV6: {
				const struct ovs_key_ipv6 *eip6;

				eip6 = nl_attr_get_unspec(aset,
				    sizeof (struct ovs_key_ipv6));
				err = solaris_setipv6_action_to_str(str,
				    sizeof (str), eip6);
				break;
			}
			case OVS_KEY_ATTR_TCP: {
				const struct ovs_key_tcp *etcp;
				etcp = nl_attr_get_unspec(aset,
				    sizeof (struct ovs_key_tcp));
				err = solaris_settransport_action_to_str(
				    str, sizeof (str), "set-tcp", etcp->tcp_src,
				    etcp->tcp_dst);
				break;
			}
			case OVS_KEY_ATTR_UDP: {
				const struct ovs_key_udp *eudp;
				eudp = nl_attr_get_unspec(aset,
				    sizeof (struct ovs_key_udp));
				err = solaris_settransport_action_to_str(
				    str, sizeof (str), "set-udp", eudp->udp_src,
				    eudp->udp_dst);
				break;
			}
			case OVS_KEY_ATTR_SCTP: {
				const struct ovs_key_sctp *esctp;
				esctp = nl_attr_get_unspec(aset,
				    sizeof (struct ovs_key_sctp));
				err = solaris_settransport_action_to_str(str,
				    sizeof (str), "set-sctp", esctp->sctp_src,
				    esctp->sctp_dst);
				break;
			}
			case OVS_KEY_ATTR_TUNNEL: {
				struct flow_tnl tnl;
				enum odp_key_fitness fitness;

				memset(&tnl, 0, sizeof (tnl));
				fitness = odp_tun_key_from_attr(aset, &tnl);
				ovs_assert(fitness != ODP_FIT_ERROR);
				err = solaris_settnl_action_to_str(
				    str, sizeof (str), &tnl);
				break;
			}
			default:
				err = EOPNOTSUPP;
				dpif_log(err, "solaris_nlattr_to_DLVal set "
				    "%d not supported",
				    nl_attr_type(nl_attr_get(a)));
			}
			break;
		}
		case OVS_ACTION_ATTR_PUSH_VLAN: {
			const struct ovs_action_push_vlan *vlan;

			vlan = nl_attr_get_unspec(a,
			    sizeof (struct ovs_action_push_vlan));

			(void) snprintf(buf, sizeof (buf), "%svlan-tag%c%u",
			    (strlen(str) == 0) ? "" : FP_MULTI_ACTION_DELIM_STR,
			    FP_NAME_VAL_DELIM, ntohs(vlan->vlan_tci));

			if (strlcat(str, buf, sizeof (str)) >= sizeof (str)) {
				err = EINVAL;
				break;
			}
			break;
		}
		case OVS_ACTION_ATTR_POP_VLAN:
			(void) snprintf(buf, sizeof (buf), "%svlan-strip%c%s",
			    (strlen(str) == 0) ? "" : FP_MULTI_ACTION_DELIM_STR,
			    FP_NAME_VAL_DELIM, "on");

			if (strlcat(str, buf, sizeof (str)) >= sizeof (str)) {
				err = EINVAL;
				break;
			}
			break;
		case OVS_ACTION_ATTR_RECIRC:
		case OVS_ACTION_ATTR_HASH:
		case OVS_ACTION_ATTR_PUSH_MPLS:
		case OVS_ACTION_ATTR_POP_MPLS:
		case OVS_ACTION_ATTR_SAMPLE:
			/* TBD */
			err = EOPNOTSUPP;
			dpif_log(err, "solaris_nlattr_to_DLVal type %d "
			    "not supported", type);
		case OVS_ACTION_ATTR_UNSPEC:
		case __OVS_ACTION_ATTR_MAX:
			OVS_NOT_REACHED();
		}
		if (err != 0)
			goto out;
	}
	if (type == OVS_ACTION_ATTR_OUTPUT) {
		dpif_log(0, "solaris_nlattr_to_DLVal outports total %d ports",
		    nofports);
		err = flow_ofports2propstr(str, sizeof (str),
		    ofports, nofports);
		if (err != 0)
			goto out;
		(void) solaris_maxbw_action_to_DLVal(prop, cookie, ofports,
		    nofports, queueid, dstr, sizeof (dstr));
	}

	err = dlmgr_DLValue_putstring(prop, "ofaction", str, dstr,
	    sizeof (dstr));
out:

	if (err == 0)
		dpif_log(err, "solaris_nlattr_to_DLVal %s", dstr);

	return (err);
}

int
solaris_add_flow(void *cookie, const char *linkname,
    const char *flowname, struct flow *f, struct flow *m,
    const struct nlattr *actions_nlattr, size_t actions_len)
{
	dlmgr_DLDict_t dff, dfm, *dffp, *dfmp;
	dlmgr__rad_dict_string_DLValue_t *prop = NULL;
	rc_instance_t *link = NULL, *flow = NULL;
	dlmgr_DatalinkError_t *derrp = NULL;
	int err = 0;
	rc_err_t status;

	bzero(&dff, sizeof (dff));
	bzero(&dfm, sizeof (dfm));
	dffp = &dff;
	dfmp = &dfm;
	status = dlmgr_Datalink__rad_lookup(rad_conn, B_TRUE, &link, 1,
	    "name", linkname);
	if (status != RCE_OK) {
		err = ENODEV;
		goto out;
	}

	dff.ddld_map = dlmgr__rad_dict_string_DLValue_create(link);
	if (dff.ddld_map == NULL) {
		err = ENOMEM;
		goto out;
	}

	dfm.ddld_map = dlmgr__rad_dict_string_DLValue_create(link);
	if (dfm.ddld_map == NULL) {
		err = ENOMEM;
		goto out;
	}

	prop = dlmgr__rad_dict_string_DLValue_create(link);
	if (prop == NULL) {
		err = ENOMEM;
		goto out;
	}

	err = solaris_flow_to_DLVal(f, m, dff.ddld_map, dfm.ddld_map);
	if (err != 0)
		goto out;

	err = solaris_nlattr_to_DLVal(cookie, actions_nlattr,
	    actions_len, prop);
	if (err != 0)
		goto out;

	status = dlmgr_Datalink_addFlow(link, flowname, &dffp, 1, &dfmp, 1,
	    prop, &flow, &derrp);
	if (status != RCE_OK) {
		err = -1;
		if (status == RCE_SERVER_OBJECT) {
			err = derrp->dde_err;
			dpif_log(err,
			    "failed Datalink_addFlow(%s, %s): %s",
			    flowname, linkname, derrp->dde_errmsg);
		}
	}
	rc_instance_rele(flow);
	dlmgr_DatalinkError_free(derrp);

out:
	dlmgr__rad_dict_string_DLValue_free(dfm.ddld_map);
	dlmgr__rad_dict_string_DLValue_free(dff.ddld_map);
	dlmgr__rad_dict_string_DLValue_free(prop);
	rc_instance_rele(link);
	return (err);
}

int
solaris_modify_flow(void *cookie, const char *flowname,
    const struct nlattr *actions_nlattr, size_t actions_len)
{
	rc_instance_t *flow = NULL;
	dlmgr__rad_dict_string_DLValue_t *prop = NULL;
	dlmgr_DatalinkError_t *derrp = NULL;
	rc_err_t status;
	int err;

	dpif_log(0, "solaris_modify_flow(%s)", flowname);
	status = dlmgr_Flow__rad_lookup(rad_conn, B_TRUE, &flow, 1,
	    "name", flowname);
	if (status != RCE_OK) {
		err = ENODEV;
		goto out;
	}

	prop = dlmgr__rad_dict_string_DLValue_create(flow);
	if (prop == NULL) {
		err = ENOMEM;
		goto out;
	}

	err = solaris_nlattr_to_DLVal(cookie, actions_nlattr,
	    actions_len, prop);
	if (err != 0)
		goto out;

	status = dlmgr_Flow_setProperties(flow, prop, &derrp);
	if (status != RCE_OK) {
		err = -1;
		if (status == RCE_SERVER_OBJECT) {
			err = derrp->dde_err;
			dpif_log(err,
			    "failed Flow_setProperties(%s): %s",
			    flowname, derrp->dde_errmsg);
		}
	}

	dlmgr_DatalinkError_free(derrp);

out:
	dlmgr__rad_dict_string_DLValue_free(prop);
	rc_instance_rele(flow);
	return (err);
}

int
solaris_remove_flow(const char *linkname, const char *flowname)
{
	dlmgr__rad_dict_string_DLValue_t *prop = NULL;
	dlmgr_DatalinkError_t		*derrp = NULL;
	dlmgr_DLValue_t			*old_val = NULL;
	dlmgr_DLValue_t			val;
	rc_instance_t			*link = NULL;
	rc_err_t			status;
	int				error = 0;

	status = dlmgr_Datalink__rad_lookup(rad_conn, B_TRUE, &link, 1,
	    "name", linkname);
	if (status != RCE_OK) {
		error = ENODEV;
		goto out;
	}

	prop = dlmgr__rad_dict_string_DLValue_create(link);
	if (prop == NULL) {
		error = EINVAL;
		goto out;
	}

	bzero(&val, sizeof (val));
	val.ddlv_type = DDLVT_BOOLEAN;
	val.ddlv_bval = &b_true;
	status = dlmgr__rad_dict_string_DLValue_put(prop, "temporary",
	    &val, &old_val);
	if (status != RCE_OK) {
		error = EINVAL;
		goto out;
	}
	dlmgr_DLValue_free(old_val);

	status = dlmgr_Datalink_removeFlow(link, flowname, prop, &derrp);
	if (status != RCE_OK) {
		error = -1;
		if (status == RCE_SERVER_OBJECT) {
			error = derrp->dde_err;
			dpif_log(error, "failed Datalink_removeFlow(%s): %s",
			    flowname, derrp->dde_errmsg);
		}
	}
	dlmgr_DatalinkError_free(derrp);
out:
	dlmgr__rad_dict_string_DLValue_free(prop);
	rc_instance_rele(link);
	return (error);
}

static rc_err_t
solaris_flowinfo2flowmap(const char *key, dlmgr_DLValue_t *val, void *arg)
{
	struct flow *f = arg;
	in6_addr_t fa;
	struct in_addr v4;
	int af, err = 0;

	if (strcmp(key, "dst-mac") == 0) {
		err = flow_str2mac(val->ddlv_sval, f->dl_dst, 6);
	} else if (strcmp(key, "src-mac") == 0) {
		err = flow_str2mac(val->ddlv_sval, f->dl_src, 6);
	} else if (strcmp(key, "local-ip") == 0 ||
	    strcmp(key, "remote-ip") == 0 || strcmp(key, "arp-sip") == 0 ||
	    strcmp(key, "arp-tip") == 0) {
		err = flow_str2addr(val->ddlv_sval, &fa, &af);
		if (err != 0)
			goto out;
		if (af == AF_INET) {
			IN6_V4MAPPED_TO_INADDR(&fa, &v4);
			if (strcmp(key, "local-ip") == 0 ||
			    strcmp(key, "arp-sip") == 0) {
				f->nw_src = v4.s_addr;
			} else {
				f->nw_dst = v4.s_addr;
			}
		} else {
			if (strcmp(key, "local-ip") == 0) {
				bcopy(&fa, &f->ipv6_src, sizeof (f->ipv6_src));
			} else if (strcmp(key, "remote-ip") == 0) {
				bcopy(&fa, &f->ipv6_dst, sizeof (f->ipv6_dst));
			} else {
				err = EINVAL;
			}
		}
	} else if (strcmp(key, "transport") == 0) {
		f->nw_proto = (uint8_t)*val->ddlv_ulval;
	} else if (strcmp(key, "local-port") == 0) {
		f->tp_src = htons((uint16_t)*val->ddlv_ulval);
	} else if (strcmp(key, "remote-port") == 0) {
		f->tp_dst = htons((uint16_t)*val->ddlv_ulval);
	} else if (strcmp(key, "dsfield") == 0) {
		f->nw_tos = (uint8_t)*val->ddlv_ulval;
	} else if (strcmp(key, "srcport") == 0) {
		f->in_port.odp_port = (odp_port_t)*val->ddlv_ulval;
	} else if (strcmp(key, "arp-target") == 0 ||
	    strcmp(key, "nd-tll") == 0) {
		err = flow_str2mac(val->ddlv_sval, f->arp_tha, 6);
	} else if (strcmp(key, "arp-sender") == 0 ||
	    strcmp(key, "nd-sll") == 0) {
		err = flow_str2mac(val->ddlv_sval, f->arp_sha, 6);
	} else if (strcmp(key, "arp-op") == 0) {
		f->nw_proto = (uint8_t)*val->ddlv_ulval;
	} else if (strcmp(key, "sap") == 0) {
		f->dl_type = htons((uint16_t)*val->ddlv_ulval);
	} else if (strcmp(key, "ttl") == 0) {
		f->nw_ttl = (uint8_t)*val->ddlv_ulval;
	} else if (strcmp(key, "vlan-tci") == 0) {
		f->vlan_tci = htons((uint16_t)*val->ddlv_ulval);
	} else if (strcmp(key, "icmp-type") == 0) {
		f->tp_src = htons((uint16_t)*val->ddlv_ulval);
	} else if (strcmp(key, "icmp-code") == 0) {
		f->tp_dst = htons((uint16_t)*val->ddlv_ulval);
	} else if (strcmp(key, "nd-target") == 0) {
		err = flow_str2addr(val->ddlv_sval, &fa, &af);
		if (err != 0)
			goto out;
		bcopy(&fa, &f->nd_target, sizeof (f->nd_target));
	} else if (strcmp(key, "tcp-flags") == 0) {
		f->tcp_flags = htons((uint16_t)*val->ddlv_ulval);
	}

out:
	if (err != 0)
		dpif_log(err, "solaris_flowinfo2flowmap %s failed", key);
	dlmgr_DLValue_free(val);
	return (err == 0 ? RCE_OK : -1);
}

static int
solaris_flowinfo2flow(dlmgr__rad_dict_string_DLValue_t *flowinfo,
    struct flow *f, struct flow *m)
{
	dlmgr__rad_dict_string_DLValue_t *fdict, *mdict;
	dlmgr_DLValue_t  *flist = NULL, *mlist = NULL;
	rc_err_t status;

	bzero(f, sizeof (*f));
	bzero(m, sizeof (*m));

	status = dlmgr__rad_dict_string_DLValue_get(flowinfo, "filters",
	    &flist);
	if (status != RCE_OK)
		return (EINVAL);

	fdict = flist->ddlv_dlist[0]->ddld_map;

	status = dlmgr__rad_dict_string_DLValue_map(fdict,
	    solaris_flowinfo2flowmap, f);
	dlmgr_DLValue_free(flist);
	if (status != RCE_OK)
		return (EINVAL);

	status = dlmgr__rad_dict_string_DLValue_get(flowinfo, "masks", &mlist);
	if (status != RCE_OK)
		return (EINVAL);

	mdict = mlist->ddlv_dlist[0]->ddld_map;

	status = dlmgr__rad_dict_string_DLValue_map(mdict,
	    solaris_flowinfo2flowmap, m);
	dlmgr_DLValue_free(mlist);
	if (status != RCE_OK)
		return (EINVAL);
	return (0);
}

int
solaris_get_flowattr(const char *flowname, struct flow *f, struct flow *m)
{
	dlmgr__rad_dict_string_DLValue_t *flowinfo = NULL;
	dlmgr_DatalinkError_t	*derrp = NULL;
	rc_instance_t		*flow = NULL;
	rc_err_t		status;
	int			err = 0;

	status = dlmgr_Flow__rad_lookup(rad_conn, B_TRUE, &flow, 1,
	    "name", flowname);
	if (status != RCE_OK) {
		return (ENODEV);
	}

	status = dlmgr_Flow_getInfo(flow, NULL, 0, &flowinfo, &derrp);
	if (status != RCE_OK) {
		err = -1;
		if (status == RCE_SERVER_OBJECT) {
			err = derrp->dde_err;
			/*
			 * XXX For now, log DDLSTATUS_NOT_FOUND as debug until
			 * we can determine how to handle the RAD caching
			 * issue.
			 */
			dpif_log(err == DDLSTATUS_NOT_FOUND ? 0 : err,
			    "failed Flow_getInfo(%s): %s",
			    flowname, derrp->dde_errmsg);
		}
	}

	dlmgr_DatalinkError_free(derrp);
	rc_instance_rele(flow);

	if (err == 0) {
		err = solaris_flowinfo2flow(flowinfo, f, m);
		dlmgr__rad_dict_string_DLValue_free(flowinfo);
	}

	return (err);
}

static int
flow_propval2action_outports_drop(char **propvals, int nval OVS_UNUSED,
    struct ofpbuf *action)
{
	char *endp = NULL;
	int64_t n;

	if (strcmp(propvals[0], "drop") == 0)
		return (0);

	errno = 0;
	n = strtoull(propvals[0], &endp, 10);
	if ((errno != 0) || *endp != '\0')
		return (EINVAL);

	nl_msg_put_u32(action, OVS_ACTION_ATTR_OUTPUT, (uint32_t)n);
	return (0);
}

static int
flow_propval2action_setpri(char **propvals OVS_UNUSED, int nval OVS_UNUSED,
    struct ofpbuf *action OVS_UNUSED)
{
	/* TBD */
	return (0);
}

void
slowpath_to_actions(enum slow_path_reason reason, struct ofpbuf *buf)
{
	union user_action_cookie cookie;

	cookie.type = USER_ACTION_COOKIE_SLOW_PATH;
	cookie.slow_path.unused = 0;
	cookie.slow_path.reason = reason;

	odp_put_userspace_action(0, &cookie, sizeof (cookie.slow_path), buf);
}

static int
flow_propval2action_controller(char **propvals OVS_UNUSED, int nval OVS_UNUSED,
    struct ofpbuf *action)
{
	slowpath_to_actions(SLOW_CONTROLLER, action);
	return (0);
}

static int
flow_propval2action_pushvlan(char **propvals, int nval OVS_UNUSED,
    struct ofpbuf *action)
{
	char *endp = NULL;
	int64_t n;
	struct ovs_action_push_vlan push;
	int tpid = ETH_TYPE_VLAN;

	errno = 0;
	n = strtoull(propvals[0], &endp, 10);
	if ((errno != 0) || *endp != '\0' || n > 0xffff)
		return (EINVAL);

	push.vlan_tpid = htons(tpid);
	push.vlan_tci = htons((uint16_t)n);
	nl_msg_put_unspec(action, OVS_ACTION_ATTR_PUSH_VLAN,
	    &push, sizeof (push));
	return (0);
}

static int
flow_propval2action_popvlan(char **propvals OVS_UNUSED, int nval OVS_UNUSED,
    struct ofpbuf *action)
{
	nl_msg_put_flag(action, OVS_ACTION_ATTR_POP_VLAN);
	return (0);
}

static int
flow_propval2action_setether(char **propvals, int nval, struct ofpbuf *action)
{
	char pval[DLADM_PROP_VAL_MAX];
	struct ovs_key_ethernet eth_key;
	uchar_t *etheraddr;
	int etheraddrlen;
	boolean_t src_set, dst_set;
	char *sep;
	size_t start_ofs;
	uint_t i;
	int err = 0;

	/*
	 * The property value is in the format of "ether_src-xxx"
	 * "ether_dst-xxx"
	 */
	bzero(&eth_key, sizeof (eth_key));
	src_set = dst_set = B_FALSE;

	for (i = 0; i < nval; i++) {
		(void) strlcpy(pval, propvals[i], sizeof (pval));
		if ((sep = strchr(pval, FP_ACTION_NAME_VALUE_DELIM)) == NULL) {
			err = EINVAL;
			goto out;
		}
		*sep = '\0';
		sep++;
		if ((etheraddr = _link_aton(sep, &etheraddrlen)) == NULL) {
			err = (etheraddrlen == -1) ? EINVAL : ENOMEM;
			goto out;
		}
		/* Only ethernet address is supported */
		if (etheraddrlen != ETHERADDRL) {
			err = EINVAL;
			free(etheraddr);
			goto out;
		}
		if (strcmp(pval, "ether_src") == 0) {
			if (src_set) {
				err = EINVAL;
			} else {
				bcopy(etheraddr, &eth_key.eth_src, ETHERADDRL);
				src_set = _B_TRUE;
			}
		} else if (strcmp(pval, "ether_dst") == 0) {
			if (dst_set) {
				err = EINVAL;
			} else {
				bcopy(etheraddr, &eth_key.eth_dst, ETHERADDRL);
				dst_set = _B_TRUE;
			}
		} else {
			err = EINVAL;
		}
		free(etheraddr);
		if (err != 0)
			goto out;
	}
	if (!src_set || !dst_set) {
		err = EINVAL;
		goto out;
	}

	start_ofs = nl_msg_start_nested(action, OVS_ACTION_ATTR_SET);
	nl_msg_put_unspec(action, OVS_KEY_ATTR_ETHERNET, &eth_key,
	    sizeof (eth_key));
	nl_msg_end_nested(action, start_ofs);
out:
	return (err);
}

static int
flow_propval2action_setipv4(char **propvals, int nval, struct ofpbuf *action)
{
	struct ovs_key_ipv4 ipv4;
	char pval[DLADM_PROP_VAL_MAX];
	char *sep, *endp;
	uint_t i, value;
	uint8_t protocol;
	size_t start_ofs;
	int err = EINVAL;
	boolean_t tos_set = B_FALSE;

	/*
	 * The property value is in the format of "src:xxx" "dst:xxx"
	 * "protocol:xxx" "tos:xxx" "hoplimit:xxx"
	 */
	bzero(&ipv4, sizeof (ipv4));
	for (i = 0; i < nval; i++) {
		(void) strlcpy(pval, propvals[i], sizeof (pval));
		if ((sep = strchr(pval, FP_ACTION_NAME_VALUE_DELIM)) == NULL) {
			err = EINVAL;
			goto out;
		}
		*sep = '\0';
		sep++;
		if (strcmp(pval, "src") == 0) {
			if (ipv4.ipv4_src != 0)
				goto out;
			if (inet_pton(AF_INET, sep, &ipv4.ipv4_src) != 1)
				goto out;
		} else if (strcmp(pval, "dst") == 0) {
			if (ipv4.ipv4_dst != 0)
				goto out;
			if (inet_pton(AF_INET, sep, &ipv4.ipv4_dst) != 1)
				goto out;
		} else if (strcmp(pval, "protocol") == 0) {
			if (ipv4.ipv4_proto != 0)
				goto out;
			protocol = solaris_str2proto(sep);
			if (protocol == 0)
				goto out;
			ipv4.ipv4_proto = protocol;
		} else if (strcmp(pval, "tos") == 0) {
			if (tos_set)
				goto out;
			errno = 0;
			endp = NULL;
			value = strtoul(sep, &endp, 16);
			if (errno != 0 || value > 0xff || *endp != '\0')
				goto out;
			tos_set = B_TRUE;
			ipv4.ipv4_tos = value;
		} else if (strcmp(pval, "hoplimit") == 0) {
			if (ipv4.ipv4_ttl != 0)
				goto out;
			errno = 0;
			endp = NULL;
			value = strtoul(sep, &endp, 10);
			if (errno != 0 || value == 0 || value > 0xff ||
			    *endp != '\0')
				goto out;
			ipv4.ipv4_ttl = value;
		}
	}
	start_ofs = nl_msg_start_nested(action, OVS_ACTION_ATTR_SET);
	nl_msg_put_unspec(action, OVS_KEY_ATTR_IPV4, &ipv4, sizeof (ipv4));
	nl_msg_end_nested(action, start_ofs);
	err = 0;
out:
	return (err);
}

static int
flow_propval2action_setipv6(char **propvals, int nval, struct ofpbuf *action)
{
	struct ovs_key_ipv6 ipv6;
	char pval[DLADM_PROP_VAL_MAX];
	char *sep, *endp;
	uint_t i, value;
	uint8_t protocol;
	struct in6_addr in6;
	size_t start_ofs;
	int err = EINVAL;
	boolean_t tos_set = B_FALSE;

	/*
	 * The property value is in the format of "src:xxx" "dst:xxx"
	 * "label:0xxxxx" "protocol:xxx" "tos:xxx" "hoplimit:xxx"
	 */
	bzero(&ipv6, sizeof (ipv6));
	for (i = 0; i < nval; i++) {
		(void) strlcpy(pval, propvals[i], sizeof (pval));
		if ((sep = strchr(pval, FP_ACTION_NAME_VALUE_DELIM)) == NULL)
			goto out;
		*sep = '\0';
		sep++;
		if (strcmp(pval, "src") == 0) {
			bcopy(&ipv6.ipv6_src, &in6.s6_addr,
			    sizeof (struct in6_addr));
			if (!IN6_IS_ADDR_UNSPECIFIED(&in6))
				goto out;
			if (inet_pton(AF_INET6, sep, ipv6.ipv6_src) != 1)
				goto out;
		} else if (strcmp(pval, "dst") == 0) {
			bcopy(&ipv6.ipv6_dst, &in6.s6_addr,
			    sizeof (struct in6_addr));
			if (!IN6_IS_ADDR_UNSPECIFIED(&in6))
				goto out;
			if (inet_pton(AF_INET6, sep, ipv6.ipv6_dst) != 1)
				goto out;
		} else if (strcmp(pval, "protocol") == 0) {
			if (ipv6.ipv6_proto != 0)
				goto out;
			protocol = solaris_str2proto(sep);
			if (protocol == 0)
				goto out;
			ipv6.ipv6_proto = protocol;
		} else if (strcmp(pval, "tos") == 0) {
			if (tos_set)
				goto out;
			errno = 0;
			endp = NULL;
			value = strtoul(sep, &endp, 16);
			if (errno != 0 || value > 0xff || *endp != '\0')
				goto out;
			tos_set = B_TRUE;
			ipv6.ipv6_tclass = value;
		} else if (strcmp(pval, "ttl") == 0) {
			if (ipv6.ipv6_hlimit != 0)
				goto out;
			errno = 0;
			endp = NULL;
			value = strtoul(sep, &endp, 10);
			if (errno != 0 || value == 0 || value > 0xff ||
			    *endp != '\0') {
				goto out;
			}
			ipv6.ipv6_hlimit = value;
		} else if (strcmp(pval, "label") == 0) {
			if (ipv6.ipv6_label != 0)
				goto out;
			errno = 0;
			endp = NULL;
			value = strtoul(sep, &endp, 16);
			if (errno != 0 || value == 0 || value > 0xff ||
			    *endp != '\0') {
				goto out;
			}
			ipv6.ipv6_label = value;
		}
	}
	start_ofs = nl_msg_start_nested(action, OVS_ACTION_ATTR_SET);
	nl_msg_put_unspec(action, OVS_KEY_ATTR_IPV6, &ipv6, sizeof (ipv6));
	nl_msg_end_nested(action, start_ofs);
	err = 0;
out:
	return (err);
}

static int
flow_propval2action_settransport(char **propvals, int nval,
    uint16_t *sportp, uint16_t *dportp)
{
	char pval[DLADM_PROP_VAL_MAX];
	char *sep, *endp;
	uint_t i, value;
	int err = EINVAL;
	uint16_t sport = 0, dport = 0;

	/* The property value is in the format of "sport-xxx" "dport-xxx" */
	for (i = 0; i < nval; i++) {
		(void) strlcpy(pval, propvals[i], sizeof (pval));
		if ((sep = strchr(pval, FP_ACTION_NAME_VALUE_DELIM)) == NULL)
			goto out;
		*sep = '\0';
		sep++;
		if (strcmp(pval, "sport") == 0) {
			if (sport != 0)
				goto out;
			errno = 0;
			endp = NULL;
			value = strtoul(sep, &endp, 10);
			if (errno != 0 || value == 0 || value > 0xffff ||
			    *endp != '\0') {
				goto out;
			}
			sport = value;
		} else if (strcmp(pval, "dport") == 0) {
			if (dport != 0)
				return (DLADM_STATUS_DUPLICATE_ARG);
			errno = 0;
			endp = NULL;
			value = strtoul(sep, &endp, 10);
			if (errno != 0 || value == 0 || value > 0xffff ||
			    *endp != '\0') {
				goto out;
			}
			dport = value;
		}
	}
	err = 0;
out:
	*sportp = sport;
	*dportp = dport;
	return (err);
}

static int
flow_propval2action_settcp(char **propvals, int nval, struct ofpbuf *action)
{
	struct ovs_key_tcp tcp;
	size_t start_ofs;
	int err;

	err = flow_propval2action_settransport(propvals, nval, &tcp.tcp_src,
	    &tcp.tcp_dst);
	if (err != 0)
		return (err);

	start_ofs = nl_msg_start_nested(action, OVS_ACTION_ATTR_SET);
	nl_msg_put_unspec(action, OVS_KEY_ATTR_TCP, &tcp, sizeof (tcp));
	nl_msg_end_nested(action, start_ofs);
	return (0);
}

static int
flow_propval2action_setudp(char **propvals, int nval, struct ofpbuf *action)
{
	struct ovs_key_udp udp;
	size_t start_ofs;
	int err;

	err = flow_propval2action_settransport(propvals, nval, &udp.udp_src,
	    &udp.udp_dst);
	if (err != 0)
		return (err);

	start_ofs = nl_msg_start_nested(action, OVS_ACTION_ATTR_SET);
	nl_msg_put_unspec(action, OVS_KEY_ATTR_UDP, &udp, sizeof (udp));
	nl_msg_end_nested(action, start_ofs);
	return (0);
}

static int
flow_propval2action_setsctp(char **propvals, int nval, struct ofpbuf *action)
{
	struct ovs_key_sctp sctp;
	size_t start_ofs;
	int err;

	err = flow_propval2action_settransport(propvals, nval, &sctp.sctp_src,
	    &sctp.sctp_dst);
	if (err != 0)
		return (err);

	start_ofs = nl_msg_start_nested(action, OVS_ACTION_ATTR_SET);
	nl_msg_put_unspec(action, OVS_KEY_ATTR_SCTP, &sctp, sizeof (sctp));
	nl_msg_end_nested(action, start_ofs);
	return (0);
}

static int
set_addr(char *pval, uint32_t *addrp)
{
	struct addrinfo		hints;
	struct addrinfo		*ai;
	struct addrinfo		*next_ai;
	void			*ptr;

	(void) memset(&hints, 0, sizeof (hints));
	hints.ai_family = AF_UNSPEC;
	if (getaddrinfo(pval, NULL, &hints, &ai) != 0)
		return (EINVAL);

	/* Check if hostname resolves to multiple addresses */
	for (next_ai = ai->ai_next; next_ai != NULL;
	    next_ai = next_ai->ai_next) {
		if (next_ai->ai_addrlen != ai->ai_addrlen ||
		    bcmp(next_ai->ai_addr, ai->ai_addr,
		    ai->ai_addrlen) != 0) {
			/* maps to more than one address */
			freeaddrinfo(ai);
			return (EINVAL);
		}
	}
	if (ai->ai_family != AF_INET) {
		freeaddrinfo(ai);
		return (EINVAL);
	}

	ptr = ((uint8_t *)ai->ai_addr) +
	    offsetof(struct sockaddr_in, sin_addr);
	memcpy(addrp, ptr, sizeof (struct in_addr));
	freeaddrinfo(ai);
	return (0);
}

static int
flow_propval2action_settnl(char **propvals, int nval, struct ofpbuf *action)
{
	char pval[DLADM_PROP_VAL_MAX];
	char *sep, *endp;
	uint_t i, value;
	struct flow_tnl tnl;
	size_t start_ofs, tun_key_ofs;
	boolean_t id_set, src_set, dst_set, tos_set, ttl_set;
	int err = 0;

	id_set = src_set = dst_set = tos_set = ttl_set = B_FALSE;

	/*
	 * The property value is in the format of "src:xxx" "dst:xxx"
	 * "tun_id:0x%x" "tos:0x%x" "hoplimit:xxx"
	 */
	bzero(&tnl, sizeof (struct flow_tnl));
	tnl.ip_tos = 0xff;
	for (i = 0; i < nval; i++) {
		(void) strlcpy(pval, propvals[i], sizeof (pval));
		if ((sep = strchr(pval, FP_ACTION_NAME_VALUE_DELIM)) == NULL)
			return (EINVAL);
		*sep = '\0';
		sep++;
		if (strcmp(pval, "tun_id") == 0) {
			if (id_set)
				return (EINVAL);
			errno = 0;
			endp = NULL;
			value = strtoull(sep, &endp, 16);
			if (errno != 0 || *endp != '\0')
				return (EINVAL);
			tnl.tun_id = value;
			id_set = B_TRUE;
		} else if (strcmp(pval, "src") == 0) {
			if (src_set)
				return (EINVAL);
			err = set_addr(sep, &tnl.ip_src);
			if (err != 0)
				return (err);
			src_set = B_TRUE;
		} else if (strcmp(pval, "dst") == 0) {
			if (dst_set)
				return (EINVAL);
			err = set_addr(sep, &tnl.ip_dst);
			if (err != 0)
				return (err);
			dst_set = B_TRUE;
		} else if (strcmp(pval, "tos") == 0) {
			if (tos_set)
				return (EINVAL);
			errno = 0;
			endp = NULL;
			value = strtoul(sep, &endp, 16);
			if (errno != 0 || value > 0xff || *endp != '\0')
				return (EINVAL);
			tnl.ip_tos = value;
			tos_set = B_TRUE;
		} else if (strcmp(pval, "hoplimit") == 0) {
			if (ttl_set)
				return (EINVAL);
			errno = 0;
			endp = NULL;
			value = strtoul(sep, &endp, 10);
			if (errno != 0 || value == 0 || value > 0xff ||
			    *endp != '\0') {
				return (EINVAL);
			}
			tnl.ip_ttl = value;
			ttl_set = B_TRUE;
		}
	}

	start_ofs = nl_msg_start_nested(action, OVS_ACTION_ATTR_SET);
	tun_key_ofs = nl_msg_start_nested(action, OVS_KEY_ATTR_TUNNEL);
	nl_msg_put_be64(action, OVS_TUNNEL_KEY_ATTR_ID,
	    ntohll((uint64_t)tnl.tun_id));
	nl_msg_put_be32(action, OVS_TUNNEL_KEY_ATTR_IPV4_SRC, tnl.ip_src);
	nl_msg_put_be32(action, OVS_TUNNEL_KEY_ATTR_IPV4_DST, tnl.ip_dst);
	nl_msg_put_u8(action, OVS_TUNNEL_KEY_ATTR_TOS, tnl.ip_tos);
	nl_msg_put_u8(action, OVS_TUNNEL_KEY_ATTR_TTL, tnl.ip_ttl);
	nl_msg_put_flag(action, OVS_TUNNEL_KEY_ATTR_DONT_FRAGMENT);
	nl_msg_end_nested(action, tun_key_ofs);
	nl_msg_end_nested(action, start_ofs);
	return (0);
}

static int
flow_propstr2vals(char *key, char *val, char ***propvalsp, int *valcntp)
{
	char **propvals = *propvalsp, *curr;
	int i, j, len;
	char c;

	dpif_log(0, "flow_propstr2vals key %s val %s", key, val);
	len = strlen(val);
	for (i = 0, j = 0, curr = val; i < len; i++) {
		if ((c = val[i]) != FP_ACTION_MULTI_VAL_DELIM && i != len -1)
			continue;

		if (c == FP_ACTION_MULTI_VAL_DELIM)
			val[i] = '\0';

		if (strlcpy(propvals[j++], curr, DLADM_PROP_VAL_MAX) >=
		    DLADM_PROP_VAL_MAX) {
			dpif_log(EINVAL, "flow_propstr2vals key %s %dth string "
			    "too long %s", key, j - 1, curr);
			return (EINVAL);
		}
		curr = val + i + 1;
	}

	*valcntp = j;
	for (i = 0; i < j; i++)
		dpif_log(0, "flow_propstr2vals key %s %dth: %s", key, i+1,
		    propvals[i]);
	return (0);
}

static int
flow_propval2action_ofaction(char *propval, struct ofpbuf *action)
{
	char ofaction_str[DLADM_STRSIZE];
	char **pvals, *buf = NULL;
	size_t len;
	char *curr, *key, c;
	boolean_t match;
	int nval, err = 0, i;

	buf = malloc((sizeof (char *) +
	    DLADM_PROP_VAL_MAX) * DLADM_MAX_PROP_VALCNT);

	pvals = (char **)(void *)buf;
	for (i = 0; i < DLADM_MAX_PROP_VALCNT; i++) {
		pvals[i] = buf + sizeof (char *) * DLADM_MAX_PROP_VALCNT +
		    i * DLADM_PROP_VAL_MAX;
	}

	if (strlcpy(ofaction_str, propval, sizeof (ofaction_str)) >=
	    sizeof (ofaction_str)) {
		err = EINVAL;
		goto done;
	}

	len = strlen(ofaction_str);
	curr = ofaction_str;
	key = NULL;
	for (i = 0; i < len; i++) {
		c = ofaction_str[i];

		match = (c == FP_NAME_VAL_DELIM || c == FP_MULTI_ACTION_DELIM);
		if (!match && i != len - 1)
			continue;
		if (match) {
			ofaction_str[i] = '\0';
			if (*curr == '\0') {
				err = EINVAL;
				goto done;
			}
		}
		if (c == FP_NAME_VAL_DELIM) {
			key = curr;
			curr = ofaction_str + i + 1;
			continue;
		}

		if (key == NULL) {
			err = EINVAL;
			goto done;
		}

		err = flow_propstr2vals(key, curr, &pvals, &nval);
		if (err != 0)
			goto done;

		if (strcmp(key, "outports") == 0)
			err = flow_propval2action_outports_drop(pvals, nval,
			    action);
		else if (strcmp(key, "max-bw") == 0)
			err = flow_propval2action_setpri(pvals, nval, action);
		else if (strcmp(key, "controller") == 0)
			err = flow_propval2action_controller(pvals, nval,
			    action);
		else if (strcmp(key, "vlan-tag") == 0)
			err = flow_propval2action_pushvlan(pvals, nval, action);
		else if (strcmp(key, "vlan-strip") == 0)
			err = flow_propval2action_popvlan(pvals, nval, action);
		else if (strcmp(key, "set-ether") == 0)
			err = flow_propval2action_setether(pvals, nval, action);
		else if (strcmp(key, "set-ipv4") == 0)
			err = flow_propval2action_setipv4(pvals, nval, action);
		else if (strcmp(key, "set-ipv6") == 0)
			err = flow_propval2action_setipv6(pvals, nval, action);
		else if (strcmp(key, "set-tcp") == 0)
			err = flow_propval2action_settcp(pvals, nval, action);
		else if (strcmp(key, "set-udp") == 0)
			err = flow_propval2action_setudp(pvals, nval, action);
		else if (strcmp(key, "set-sctp") == 0)
			err = flow_propval2action_setsctp(pvals, nval, action);
		else if (strcmp(key, "set-tunnel") == 0)
			err = flow_propval2action_settnl(pvals, nval, action);
		else
			err = EINVAL;

		if (err != 0)
			goto done;

		key = NULL;
		curr = ofaction_str + i + 1;
	}
done:
	free(buf);
	return (err);
}

/* valcnt must be 1 */
static rc_err_t
solaris_flowinfo2actionmap(const char *key, dlmgr_DLValue_t *val,
    void *arg)
{
	struct ofpbuf *action = arg;
	char propval[DLADM_STRSIZE];
	int valcnt, err = 0;

	switch (val->ddlv_type) {
	case DDLVT_STRING:
		if (val->ddlv_sval == NULL)
			goto out;
		if (strlen(val->ddlv_sval) == 0)
			goto out;
		valcnt = 1;
		if (strlcpy(propval, val->ddlv_sval, DLADM_STRSIZE) >=
		    DLADM_STRSIZE)
			goto out;
		break;
	case DDLVT_STRINGS:
		if (val->ddlv_slist_count == 0)
			goto out;
		valcnt = val->ddlv_slist_count;
		if (valcnt != 1 || strlen(val->ddlv_slist[0]) == 0)
			goto out;
		if (strlcpy(propval, val->ddlv_slist[0], DLADM_STRSIZE) >=
		    DLADM_STRSIZE)
			goto out;
		break;
	case DDLVT_ULONG:
		if (val->ddlv_ulval == NULL || *val->ddlv_ulval == 0)
			goto out;
		valcnt = 1;
		(void) snprintf(propval, DLADM_STRSIZE, "%llu",
		    *val->ddlv_ulval);
		break;
	case DDLVT_BOOLEAN:
	case DDLVT_BOOLEANS:
	case DDLVT_LONG:
	case DDLVT_LONGS:
	case DDLVT_ULONGS:
	case DDLVT_DICTIONARY:
	case DDLVT_DICTIONARYS:
	default:
		goto out;
	}
	dpif_log(0, "solaris_flowinfo2actionmap %s:%d %s", key, valcnt,
	    propval);

	if (strcmp(key, "ofaction") == 0)
		err = flow_propval2action_ofaction(propval, action);

out:
	dlmgr_DLValue_free(val);
	return (err == 0 ? RCE_OK : -1);
}

static int
solaris_flowinfo2action(dlmgr__rad_dict_string_DLValue_t *flowinfo,
    struct ofpbuf *action)
{
	dlmgr__rad_dict_string_DLValue_t *fdict;
	dlmgr_DLValue_t  *flist = NULL;
	rc_err_t status;
	int err = 0;

	status = dlmgr__rad_dict_string_DLValue_get(flowinfo, "properties",
	    &flist);
	if (status != RCE_OK) {
		dpif_log(EINVAL, "solaris_flowinfo2action get properties failed"
		    " %d", status);
		return (EINVAL);
	}

	fdict = flist->ddlv_dval;
	status = dlmgr__rad_dict_string_DLValue_map(fdict,
	    solaris_flowinfo2actionmap, action);
	if (status != RCE_OK) {
		err = EINVAL;
		dpif_log(EINVAL, "solaris_flowinfo2action get walk actionmap "
		    "failed %d", status);
	}

	dlmgr_DLValue_free(flist);
	return (err);
}

int
solaris_get_flowaction(const char *flowname, struct ofpbuf *action)
{
	dlmgr__rad_dict_string_DLValue_t *flowinfo = NULL;
	dlmgr_DatalinkError_t	*derrp = NULL;
	rc_instance_t		*flow = NULL;
	rc_err_t		status;
	int			err = 0;

	status = dlmgr_Flow__rad_lookup(rad_conn, B_TRUE, &flow, 1,
	    "name", flowname);
	if (status != RCE_OK) {
		return (ENODEV);
	}

	status = dlmgr_Flow_getInfo(flow, NULL, 0, &flowinfo, &derrp);
	if (status != RCE_OK) {
		err = -1;
		if (status == RCE_SERVER_OBJECT) {
			err = derrp->dde_err;
			/*
			 * XXX For now, log DDLSTATUS_NOT_FOUND as debug until
			 * we can determine how to handle the RAD caching
			 * issue.
			 */
			dpif_log(err == DDLSTATUS_NOT_FOUND ? 0 : err,
			    "failed Flow_getInfo(%s): %s",
			    flowname, derrp->dde_errmsg);
		}
	}

	dlmgr_DatalinkError_free(derrp);
	rc_instance_rele(flow);

	if (err == 0) {
		err = solaris_flowinfo2action(flowinfo, action);
		dlmgr__rad_dict_string_DLValue_free(flowinfo);
	}

	return (err);
}

static int
i_solaris_get_flowstats(rc_instance_t *flow, uint64_t *npackets,
    uint64_t *nbytes, uint64_t *lastused)
{
	dlmgr__rad_dict_string_DLValue_t *flowstat = NULL;
	dlmgr_DLValue_t		*dlval = NULL;
	dlmgr_DatalinkError_t	*derrp = NULL;
	rc_err_t		status;
	int			err = 0;

	status = dlmgr_Flow_getStatistics(flow, NULL, 0, &flowstat, &derrp);
	if (status != RCE_OK) {
		err = -1;
		if (status == RCE_SERVER_OBJECT) {
			err = derrp->dde_err;
			dpif_log(err, "failed Flow_getStatistics(): %s",
			    derrp->dde_errmsg);
		}
		goto out;
	}

#if _TBD_
	uint16_t tcp_flags; /* bitmaps of tcp_flags */
#endif
	status = dlmgr__rad_dict_string_DLValue_get(flowstat, "ipackets",
	    &dlval);
	if (status != RCE_OK) {
		err = EINVAL;
		goto out;
	}
	*npackets = *dlval->ddlv_ulval;
	dlmgr_DLValue_free(dlval);

	status = dlmgr__rad_dict_string_DLValue_get(flowstat, "opackets",
	    &dlval);
	if (status != RCE_OK) {
		err = EINVAL;
		goto out;
	}
	*npackets += *dlval->ddlv_ulval;
	dlmgr_DLValue_free(dlval);

	status = dlmgr__rad_dict_string_DLValue_get(flowstat, "ibytes",
	    &dlval);
	if (status != RCE_OK) {
		err = EINVAL;
		goto out;
	}
	*nbytes = *dlval->ddlv_ulval;
	dlmgr_DLValue_free(dlval);

	status = dlmgr__rad_dict_string_DLValue_get(flowstat, "obytes",
	    &dlval);
	if (status != RCE_OK) {
		err = EINVAL;
		goto out;
	}
	*nbytes += *dlval->ddlv_ulval;
	dlmgr_DLValue_free(dlval);

	status = dlmgr__rad_dict_string_DLValue_get(flowstat, "lastused",
	    &dlval);
	if (status != RCE_OK) {
		err = EINVAL;
		goto out;
	}
	*lastused = *dlval->ddlv_ulval;
	dlmgr_DLValue_free(dlval);
out:
	dlmgr__rad_dict_string_DLValue_free(flowstat);
	dlmgr_DatalinkError_free(derrp);
	return (err);
}

int
solaris_get_flowstats(const char *flowname, uint64_t *npackets,
    uint64_t *nbytes, uint64_t *lastused)
{
	rc_err_t status;
	rc_instance_t *flow = NULL;
	int err;

	status = dlmgr_Flow__rad_lookup(rad_conn, B_TRUE, &flow, 1,
	    "name", flowname);
	if (status != RCE_OK) {
		err = ENODEV;
		goto out;
	}

	err = i_solaris_get_flowstats(flow, npackets, nbytes, lastused);
out:
	rc_instance_rele(flow);
	return (err);
}

boolean_t
kstat_handle_init(kstat2_handle_t *khandlep)
{
	kstat2_status_t	stat;

	stat = kstat2_open(khandlep, NULL);
	return (stat != KSTAT2_S_OK ? B_FALSE: B_TRUE);
}

boolean_t
kstat_handle_update(kstat2_handle_t khandle)
{
	kstat2_status_t	stat;

	stat = kstat2_update(khandle);
	return (stat != KSTAT2_S_OK ? B_FALSE: B_TRUE);
}

void
kstat_handle_close(kstat2_handle_t *khandlep)
{
	kstat2_close(khandlep);
}

uint64_t
get_nvvt_int(kstat2_map_t map, char *name)
{
	kstat2_status_t stat;
	kstat2_nv_t val;

	stat = kstat2_map_get(map, name, &val);
	if (stat != KSTAT2_S_OK) {
		(void) printf("can't get value: %s\n",
		    kstat2_status_string(stat));
		return (0);
	}

	if (val->type != KSTAT2_NVVT_INT) {
		(void) printf("%s is not KSTAT2_NVVT_INT type\n", name);
		return (0);
	}

	return (val->kstat2_integer);
}

void
solaris_port_walk(void *arg, void (*fn)(void *, const char *, char *,
    odp_port_t))
{
	adr_name_t	**anamearr = NULL;
	int		anamecnt = 0, i;
	rc_err_t	rerr;

	rerr = dlmgr_Datalink__rad_list(rad_conn, B_FALSE, NS_GLOB, &anamearr,
	    &anamecnt, 0);
	if (rerr != RCE_OK)
		return;

	if (anamecnt == 0) {
		free(anamearr);
		return;
	}

	for (i = 0; i < anamecnt; i++) {
		dlmgr_DLDict_t		**dlist = NULL;
		dlmgr_DLValue_t		*dlval = NULL;
		const char		*props[1];
		const char		*fields[1];
		int			ndlist = 0;
		rc_instance_t		*rip = NULL;
		dlmgr_DatalinkError_t	*derrp = NULL;
		rc_err_t 		rerr;

		rerr = rc_lookup(rad_conn, anamearr[i], NULL, B_FALSE, &rip);
		if (rerr != RCE_OK)
			continue;

		props[0] = "ofport";
		fields[0] = "current";
		rerr = dlmgr_Datalink_getProperties(rip, props, 1, fields, 1,
		    &dlist, &ndlist, &derrp);
		rc_instance_rele(rip);
		if (rerr != RCE_OK) {
			if (rerr == RCE_SERVER_OBJECT) {
				dpif_log(derrp->dde_err,
				    "failed Datalink_getProperties(%s, %s): %s",
				    adr_name_key(anamearr[i], "name"),
				    props[0], derrp->dde_errmsg);
			}
			dlmgr_DatalinkError_free(derrp);
			continue;
		}
		rerr = dlmgr__rad_dict_string_DLValue_get((*dlist)->ddld_map,
		    "current", &dlval);
		if (rerr != RCE_OK || dlval->ddlv_sval == NULL) {
			dlmgr_DatalinkError_free(derrp);
			dlmgr_DLValue_free(dlval);
			dlmgr_DLDict_array_free(dlist, ndlist);
			continue;
		}

		if (dlval->ddlv_sval != NULL && dlval->ddlv_sval[0] != '\0') {
			fn(arg, adr_name_key(anamearr[i], "name"),
			    "system", atoi(dlval->ddlv_sval));
		}
		dlmgr_DatalinkError_free(derrp);
		dlmgr_DLValue_free(dlval);
		dlmgr_DLDict_array_free(dlist, ndlist);
	}

	for (i = 0; i < anamecnt; i++)
		adr_name_rele(anamearr[i]);
	free(anamearr);
}

uint64_t
solaris_flow_walk(void *arg, struct ofpbuf *action, boolean_t no_default,
    void (*fn)(void *, const char *, boolean_t, struct flow *, struct flow *,
    struct ofpbuf *, uint64_t, uint64_t, uint64_t))
{
	adr_name_t	**anamearr = NULL;
	int		anamecnt = 0, i;
	rc_err_t	rerr;
	int		err = 0;
	uint64_t	n_flows = 0;

	rerr = dlmgr_Flow__rad_list(rad_conn, B_FALSE, NS_GLOB, &anamearr,
	    &anamecnt, 0);
	if (rerr != RCE_OK)
		return (0);

	if (anamecnt == 0) {
		free(anamearr);
		return (0);
	}

	for (i = 0; i < anamecnt; i++) {
		dlmgr__rad_dict_string_DLValue_t *flowinfo;
		char			linkname[MAXLINKNAMELEN];
		rc_instance_t		*rip = NULL;
		dlmgr_DLDict_t		**dlist;
		dlmgr_DLValue_t		*dlval;
		const char		*props[1];
		const char		*fields[1];
		struct flow		f, m;
		int			ndlist = 0;
		uint64_t		npackets, nbytes, lastused;
		boolean_t		is_default;
		dlmgr_DatalinkError_t	*derrp = NULL;

		flowinfo = NULL;
		dlist = NULL;
		dlval = NULL;
		is_default = B_FALSE;
		if (strstr(adr_name_key(anamearr[i], "name"), "defflow") !=
		    NULL) {
			if (no_default)
				continue;
			else
				is_default = B_TRUE;
		} else if (strstr(adr_name_key(anamearr[i], "name"),
		    "sys.of") == NULL) {
			continue;
		}

		rerr = rc_lookup(rad_conn, anamearr[i], NULL, B_FALSE, &rip);
		if (rerr != RCE_OK)
			continue;

		if ((err = i_solaris_get_flowstats(rip, &npackets, &nbytes,
		    &lastused)) != 0) {
			dpif_log(err, "solaris_flow_walk get_flowstats "
			    "failed for %s: %d", adr_name_key(anamearr[i],
			    "name"), err);
			rc_instance_rele(rip);
			goto done;
		}

		rerr = dlmgr_Flow_getInfo(rip, NULL, 0, &flowinfo, &derrp);
		rc_instance_rele(rip);
		if (rerr != RCE_OK) {
			err = -1;
			if (rerr == RCE_SERVER_OBJECT) {
				err = derrp->dde_err;
				/*
				 * XXX For now, log DDLSTATUS_NOT_FOUND as
				 * debug until we can determine how to handle
				 * the RAD caching issue.
				 */
				dpif_log(err == DDLSTATUS_NOT_FOUND ? 0 : err,
				    "failed Flow_getInfo(%s): %s",
				    adr_name_key(anamearr[i], "name"),
				    derrp->dde_errmsg);
			}
			dlmgr_DatalinkError_free(derrp);
			goto done;
		}

		/* See whether this flow is created over of enabled link */
		err = solaris_flowinfo2linkname(flowinfo, linkname,
		    MAXLINKNAMELEN);
		if (err != 0) {
			goto done;
		}

		rerr = dlmgr_Datalink__rad_lookup(rad_conn, B_TRUE, &rip,
		    1, "name", linkname);
		if (rerr != RCE_OK) {
			goto done;
		}

		props[0] = "openvswitch";
		fields[0] = "current";
		rerr = dlmgr_Datalink_getProperties(rip, props, 1, fields, 1,
		    &dlist, &ndlist, &derrp);
		rc_instance_rele(rip);
		if (rerr != RCE_OK) {
			err = -1;
			if (rerr == RCE_SERVER_OBJECT) {
				err = derrp->dde_err;
				dpif_log(err,
				    "failed Datalink_getProperties(%s, %s): %s",
				    linkname, props[0], derrp->dde_errmsg);
			}
			dlmgr_DatalinkError_free(derrp);
			goto done;
		}
		rerr = dlmgr__rad_dict_string_DLValue_get((*dlist)->ddld_map,
		    "current", &dlval);
		if (rerr != RCE_OK)
			goto done;

		if (!dlval->ddlv_bval)
			goto done;

		err = solaris_flowinfo2flow(flowinfo, &f, &m);
		if (err != 0) {
			dpif_log(err, "solaris_flow_walk flowinfo2flow "
			    "failed for %s: %d", adr_name_key(anamearr[i],
			    "name"), err);
			goto done;
		}

		if (action != NULL) {
			err = solaris_flowinfo2action(flowinfo, action);
			if (err != 0) {
				dpif_log(err, "solaris_flow_walk "
				    "flowinfo2action failed for %s: %d",
				    adr_name_key(anamearr[i], "name"), err);
				goto done;
			}
		}

		if (fn != NULL) {
			fn(arg, adr_name_key(anamearr[i], "name"), is_default,
			    &f, &m, action, npackets, nbytes, lastused);
		}
		n_flows++;
done:
		dlmgr__rad_dict_string_DLValue_free(flowinfo);
		dlmgr_DLValue_free(dlval);
		dlmgr_DLDict_array_free(dlist, ndlist);
	}

	for (i = 0; i < anamecnt; i++)
		adr_name_rele(anamearr[i]);
	free(anamearr);

	return (n_flows);
}

int
solaris_dladm_status2error(dladm_status_t status)
{
	int error;

	if (status == DLADM_STATUS_NOMEM) {
		error = ENOMEM;
	} else if (status == DLADM_STATUS_DENIED) {
		error = EPERM;
	} else if (status == DLADM_STATUS_OK) {
		error = 0;
	} else if (status == DLADM_STATUS_IOERR) {
		error = EIO;
	} else {
		error = EINVAL;
	}
	return (error);
}

boolean_t
solaris_is_uplink_class(const char *class)
{
	return (strcmp("phys", class) == 0 ||
	    strcmp("aggr", class) == 0 ||
	    strcmp("etherstub", class) == 0 ||
	    strcmp("vxlan", class) == 0 ||
	    strcmp("veth", class) == 0 ||
	    strcmp("simnet", class) == 0);
}

/*
 * This is a copy of dlparse_zonelinkname() function in libinetutil. libinetutil
 * is not a public interface, therefore we make a copy here.
 *
 * Given a linkname that can be specified using a zonename prefix retrieve
 * the optional linkname and/or zone ID value. If no zonename prefix was
 * specified we set the optional linkname and set optional zone ID return
 * value to ALL_ZONES.
 */
boolean_t
solaris_dlparse_zonelinkname(const char *name, char *link_name,
    zoneid_t *zoneidp)
{
	char buffer[MAXLINKNAMESPECIFIER];
	char *search = "/";
	char *zonetoken;
	char *linktoken;
	char *last;
	size_t namelen;

	if (link_name != NULL)
		link_name[0] = '\0';
	if (zoneidp != NULL)
		*zoneidp = ALL_ZONES;

	if ((namelen = strlcpy(buffer, name, sizeof (buffer))) >=
	    sizeof (buffer))
		return (_B_FALSE);

	if ((zonetoken = strtok_r(buffer, search, &last)) == NULL)
		return (_B_FALSE);

	/* If there are no other strings, return given name as linkname */
	if ((linktoken = strtok_r(NULL, search, &last)) == NULL) {
		if (namelen >= MAXLINKNAMELEN)
			return (_B_FALSE);
		if (link_name != NULL)
			(void) strlcpy(link_name, name, MAXLINKNAMELEN);
		return (_B_TRUE);
	}

	/* First token is the zonename. Check zone and link lengths */
	if (strlen(zonetoken) >= ZONENAME_MAX || strlen(linktoken) >=
	    MAXLINKNAMELEN)
		return (_B_FALSE);
	/*
	 * If there are more '/' separated strings in the input
	 * name  then we return failure. We only support a single
	 * zone prefix or a devnet directory (f.e. net/bge0).
	 */
	if (strtok_r(NULL, search, &last) != NULL)
		return (_B_FALSE);

	if (link_name != NULL)
		(void) strlcpy(link_name, linktoken, MAXLINKNAMELEN);
	if (zoneidp != NULL) {
		if ((*zoneidp = getzoneidbyname(zonetoken)) < MIN_ZONEID)
			return (_B_FALSE);
	}

	return (_B_TRUE);
}

/*
 * Sets *n_cores to the total number of cores on this system, or 0 if the
 * number cannot be determined.
 */
void
solaris_parse_cpuinfo(long int *n_cores)
{
	kstat2_handle_t	handle;
	kstat2_status_t	stat;
	kstat2_map_t	map;
	kstat2_nv_t	val;
	char		kuri[1024];
	int		coreid;
	int		lcoreid = -1;
	int		i;

	*n_cores = 0;

	stat = kstat2_open(&handle, NULL);
	if (stat != KSTAT2_S_OK) {
		dpif_log(1, "solaris_parse_cpuinfo kstat2_open failed (%s). "
		    "Core count may be inaccurate.",
		    kstat2_status_string(stat));
		return;
	}

	for (i = 0; ; i++) {
		(void) snprintf(kuri, sizeof (kuri),
		    "kstat:/system/cpu/%d/info", i);
		stat = kstat2_lookup_map(handle, kuri, &map);
		if (stat == KSTAT2_S_OK) {
			stat = kstat2_map_get(map, "core_id", &val);
			if (stat != KSTAT2_S_OK) {
				dpif_log(1, "solaris_parse_cpuinfo"
				    "kstat2_map_get failed (%s). "
				    "Core count may be inaccurate.",
				    kstat2_status_string(stat));
				*n_cores = 0;
				break;
			}

			if (val->type != KSTAT2_NVVT_INT) {
				dpif_log(1, "solaris_parse_cpuinfo "
				    "kstat2 value error. "
				    "Core count may be inaccurate.");
				*n_cores = 0;
				break;
			}

			coreid = val->kstat2_integer;
			if (coreid != lcoreid) {
				(*n_cores)++;
				lcoreid = coreid;
			}
		} else if (stat == KSTAT2_S_NOT_FOUND) {
			/* no more cores */
			break;
		} else {
			dpif_log(1, "solaris_parse_cpuinfo kstat2_lookup_map "
			    "failed (%s). Core count may be inaccurate.",
			    kstat2_status_string(stat));
			*n_cores = 0;
			break;
		}
	}

	kstat2_close(&handle);
}
