/*
 * Copyright (c) 2010, 2011, Oracle and/or its affiliates. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * OFED Solaris wrapper
 */
#if defined(__SVR4) && defined(__sun)

#pragma ident	"@(#)solaris_set_nodedesc.c	1.2	11/01/25 SMI"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/queue.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <getopt.h>
#include <libdevinfo.h>
#include <sys/utsname.h>

#include <infiniband/verbs.h>
#include <infiniband/arch.h>

#include <sys/ib/adapters/tavor/tavor_ioctl.h>
#include <sys/ib/adapters/hermon/hermon_ioctl.h>

/*
 * Local defines for HCA driver IOCTLs, used while
 * building on build system without the change in
 * header files.
 */
#ifdef	HERMON_NODEDESC_UPDATE_STR
#define	HERMON_NODEDESC_UPDATE_STRING		0x00000001
#endif
#ifndef	HERMON_NODEDESC_UPDATE_HCA_STRING
#define	HERMON_NODEDESC_UPDATE_HCA_STRING	0x00000002
#undef	HERMON_NODEDESC_UPDATE_HCA_MAP
#endif
#ifndef HERMON_IOCTL_GET_NODEDESC
#define	HERMON_IOCTL_GET_NODEDESC	(('t' << 8) | 0x31)
#endif

#ifdef	TAVOR_NODEDESC_UPDATE_STR
#define	TAVOR_NODEDESC_UPDATE_STRING		0x00000001
#endif
#ifndef	TAVOR_NODEDESC_UPDATE_HCA_STRING
#define	TAVOR_NODEDESC_UPDATE_HCA_STRING	0x00000002
#undef	TAVOR_NODEDESC_UPDATE_HCA_MAP
#endif
#ifndef TAVOR_IOCTL_GET_NODEDESC
#define	TAVOR_IOCTL_GET_NODEDESC	(('t' << 8) | 0x31)
#endif

#define	NODEDESC_UPDATE_STRING		0x00000001
#define	NODEDESC_UPDATE_HCA_STRING	0x00000002
#define	NODEDESC_READ			0x80000000

#include "ibdiag_common.h"

static char *devpath_prefix = "/devices";
static char *devpath_suffix = ":devctl";
static char *ib_hca_driver_list[] = {
	"tavor", "hermon", NULL
};
static di_node_t	di_rootnode;
char *argv0 = "solaris_set_nodedesc";

#define	MAX_HCAS	32
static struct nodedesc_read_info_s {
	boolean_t	info_valid;
	uint64_t	guid;
	char		nd_string[64];
	boolean_t	ofuv_name_valid;
	char		ofuv_name[64];
} nd_read_info_arr[MAX_HCAS];
int	nd_read_info_cnt;

static void
print_read_info()
{
	int	j;

	for (j = 0; j < nd_read_info_cnt; j++) {
		if (nd_read_info_arr[j].info_valid == B_FALSE ||
		    nd_read_info_arr[j].ofuv_name_valid == B_FALSE)
			continue;
		printf("%s: %-16s\n",
		    nd_read_info_arr[j].ofuv_name,
		    nd_read_info_arr[j].nd_string);
	}
}

static void
update_read_info_hwnames()
{
	struct ibv_device **dev_list;
	int num_devices, i;
	uint64_t	dev_guid;
	char		*dev_name;
	size_t		dev_name_len;

	dev_list = ibv_get_device_list(&num_devices);
	if (!dev_list) {
		fprintf(stderr, "No IB devices found\n");
		return;
	}

	for (i = 0; i < num_devices; ++i) {
		int	j;

		dev_guid = (uint64_t)ntohll(ibv_get_device_guid(dev_list[i]));
		dev_name = (char *)ibv_get_device_name(dev_list[i]);
		dev_name_len = strlen(dev_name) + 1;
		for (j = 0; j < nd_read_info_cnt; j++) {
			if (nd_read_info_arr[j].info_valid == B_TRUE &&
			    nd_read_info_arr[j].guid == dev_guid) {
				memcpy(nd_read_info_arr[j].ofuv_name,
				    dev_name, dev_name_len);
				nd_read_info_arr[j].ofuv_name_valid = B_TRUE;
				break;
			}
		}
	}

	ibv_free_device_list(dev_list);
}

static void
add_read_info_arr(char *nd_str, uint64_t guid)
{
	size_t	nd_len;

	nd_len = strlen(nd_str) + 1;
	nd_read_info_arr[nd_read_info_cnt].info_valid = B_TRUE;
	nd_read_info_arr[nd_read_info_cnt].guid = guid;
	memcpy(nd_read_info_arr[nd_read_info_cnt].nd_string, nd_str, nd_len);
	nd_read_info_cnt++;

}

static void
do_driver_read_ioctl(char *drivername)
{
	di_node_t	hcanode, childnode;
	char		*devpath;
	char		*access_devname;
	int		devlength, devfd, rc = -1;
	uint64_t	*hca_guid;

	if ((hcanode = di_drv_first_node(drivername, di_rootnode))
	    == DI_NODE_NIL) {
		return;
	}

	while (hcanode != DI_NODE_NIL) {
		childnode = di_child_node(hcanode);
		while (childnode != DI_NODE_NIL) {
			if (di_prop_lookup_int64(DDI_DEV_T_ANY,
			    childnode, "hca-guid",
			    (int64_t **)&hca_guid) != 1) {
				childnode = di_sibling_node(childnode);
				continue;
			} else {
				break;
			}
		}
		if (childnode == DI_NODE_NIL) {
			hcanode = di_drv_next_node(hcanode);
			continue;
		}

		devpath = di_devfs_path(hcanode);
		devlength = strlen(devpath_prefix) + strlen(devpath) +
		    strlen(devpath_suffix) + 2;
		access_devname = malloc(devlength);
		(void) snprintf(access_devname, devlength, "%s%s%s",
		    devpath_prefix, devpath, devpath_suffix);
		if ((devfd = open(access_devname, O_RDONLY)) < 0) {
			IBERROR("open device file %s failed", access_devname);
			free(access_devname);
			hcanode = di_drv_next_node(hcanode);
			continue;
		}
		if (strcmp(drivername, "tavor") == 0) {
			tavor_nodedesc_ioctl_t		nodedesc_ioctl;

			if ((rc = ioctl(devfd, TAVOR_IOCTL_GET_NODEDESC,
			    (void *)&nodedesc_ioctl)) != 0) {
				IBERROR("tavor ioctl failure");
				free(access_devname);
				close(devfd);
				hcanode = di_drv_next_node(hcanode);
				continue;
			}
			add_read_info_arr((char *)nodedesc_ioctl.node_desc_str,
			    *hca_guid);
		} else if (strcmp(drivername, "hermon") == 0) {
			hermon_nodedesc_ioctl_t		nodedesc_ioctl;

			if ((rc = ioctl(devfd, HERMON_IOCTL_GET_NODEDESC,
			    (void *)&nodedesc_ioctl)) != 0) {
				IBERROR("hermon ioctl failure");
				free(access_devname);
				close(devfd);
				hcanode = di_drv_next_node(hcanode);
				continue;
			}
			add_read_info_arr((char *)nodedesc_ioctl.node_desc_str,
			    *hca_guid);
		}

		free(access_devname);
		close(devfd);
		hcanode = di_drv_next_node(hcanode);
	}

}

static int
do_driver_update_ioctl(char *drivername, char *node_desc, char *hca_desc,
    uint64_t inp_hca_guid, uint32_t update_flag)
{
	di_node_t	hcanode, childnode;
	char		*devpath;
	char		*access_devname;
	int		devlength, devfd, rc = -1;
	uint64_t	*hca_guid;
	char		*desc_str = (node_desc ? node_desc : hca_desc);

	if ((hcanode = di_drv_first_node(drivername, di_rootnode))
	    == DI_NODE_NIL) {
		return (-1);
	}

	while (hca_desc && hcanode != DI_NODE_NIL) {
		childnode = di_child_node(hcanode);
		while (childnode != DI_NODE_NIL) {
			if (di_prop_lookup_int64(DDI_DEV_T_ANY,
			    childnode, "hca-guid",
			    (int64_t **)&hca_guid) != 1) {
				childnode = di_sibling_node(childnode);
				continue;
			} else {
				break;
			}
		}
		if (*hca_guid == inp_hca_guid)
			break;
		hcanode = di_drv_next_node(hcanode);
	}

	if ((hca_desc && childnode == DI_NODE_NIL) ||
	    hcanode == DI_NODE_NIL) {
		IBERROR("matching GUID not found");
		return (-1);
	}

	devpath = di_devfs_path(hcanode);
	devlength = strlen(devpath_prefix) + strlen(devpath) +
	    strlen(devpath_suffix) + 2;
	access_devname = malloc(devlength);
	(void) snprintf(access_devname, devlength, "%s%s%s",
	    devpath_prefix, devpath, devpath_suffix);
	if ((devfd = open(access_devname, O_RDONLY)) < 0) {
		IBERROR("open device file %s failed", access_devname);
		free(access_devname);
		return (rc);
	}
	if (strcmp(drivername, "tavor") == 0) {
		tavor_nodedesc_ioctl_t		nodedesc_ioctl;

		strncpy(nodedesc_ioctl.node_desc_str, desc_str, 64);
		if (update_flag & NODEDESC_UPDATE_STRING)
			nodedesc_ioctl.node_desc_update_flag =
			    TAVOR_NODEDESC_UPDATE_STRING;
		else if (update_flag & NODEDESC_UPDATE_HCA_STRING)
			nodedesc_ioctl.node_desc_update_flag =
			    TAVOR_NODEDESC_UPDATE_HCA_STRING;
		else {
			IBERROR("Invalid option");
			exit(-1);
		}
		if ((rc = ioctl(devfd, TAVOR_IOCTL_SET_NODEDESC,
		    (void *)&nodedesc_ioctl)) != 0) {
			IBERROR("tavor ioctl failure");
		}
	} else if (strcmp(drivername, "hermon") == 0) {
		hermon_nodedesc_ioctl_t		nodedesc_ioctl;

		strncpy(nodedesc_ioctl.node_desc_str, desc_str, 64);
		if (update_flag & NODEDESC_UPDATE_STRING)
			nodedesc_ioctl.node_desc_update_flag =
			    HERMON_NODEDESC_UPDATE_STRING;
		else if (update_flag & NODEDESC_UPDATE_HCA_STRING)
			nodedesc_ioctl.node_desc_update_flag =
			    HERMON_NODEDESC_UPDATE_HCA_STRING;
		else {
			IBERROR("Invalid option");
			exit(-1);
		}
		if ((rc = ioctl(devfd, HERMON_IOCTL_SET_NODEDESC,
		    (void *)&nodedesc_ioctl)) != 0) {
			IBERROR("hermon ioctl failure");
		}
	}

	free(access_devname);
	close(devfd);
	return (rc);
}

static void
read_nodedesc()
{
	int	i;

	if ((di_rootnode = di_init("/", DINFOCPYALL | DINFOFORCE))
	    == DI_NODE_NIL) {
		IBERROR("read_nodedesc di_init failure");
		return;
	}
	for (i = 0; ib_hca_driver_list[i]; i++)
		do_driver_read_ioctl(ib_hca_driver_list[i]);
	di_fini(di_rootnode);
}

static int
update_nodedesc(char *cmn_nodedesc, char *hca_nodedesc, uint64_t guid,
    uint32_t update_flag)
{
	int	i, rc = 0;

	if ((di_rootnode = di_init("/", DINFOCPYALL | DINFOFORCE))
	    == DI_NODE_NIL) {
		IBERROR("di_init failure");
		return (-1);
	}
	for (i = 0; ib_hca_driver_list[i]; i++) {
		rc = do_driver_update_ioctl(ib_hca_driver_list[i],
		    cmn_nodedesc, hca_nodedesc, guid,
		    update_flag);
		if (!rc)
			break;
	}
	if (rc)
		IBERROR("Updated failed for all HCA drivers");

	di_fini(di_rootnode);
	return (rc);
}

static void
usage(void)
{
	char *basename;

	if (!(basename = strrchr(argv0, '/')))
		basename = argv0;
	else
		basename++;

	fprintf(stderr, "Usage: %s \n", basename);
	fprintf(stderr, "\t\t %s [-N(ode_Descriptor) CmnString]\n",
	    basename);
	fprintf(stderr, "\t\t %s [-H(CA_Description) HCAString "
	    "-G(UID) HCA_GUID]\n", basename);
	fprintf(stderr, "\t\t %s [-H(CA_Description) HCAString "
	    "-G(UID) HCA_GUID -N(ode_Descriptor) CmnString]\n",
	    basename);
	fprintf(stderr, "\t\t %s [-v]\n", basename);
}

/*
 * Return the Node descriptor string by concatinating
 * many substrings. The first substring is "optarg" and
 * the index of the last sub-string is "optind".
 *
 * For common nodedescription, add a space at the end,
 * if there is none.
 */
static char *
nodedesc_substr_cat(char **argv, int argc, boolean_t space_at_end)
{
	int	i, start_opt, end_opt;
	char	*nodedesc_str;

	/* Get the index for first sub-string. */
	for (start_opt = 0, i = optind; i; i--) {
		if (argv[i] == NULL)
			continue;

		if (strcmp(argv[i], optarg) == 0) {
			start_opt = i;
			break;
		}
	}
	if (start_opt == 0)
		return (NULL);

	/* Get the index for last sub-string */
	for (end_opt = 0, i = optind; i <= argc; i++) {
		if (i == argc || argv[i][0] == '-') {
			end_opt = i - 1;
			break;
		}
	}
	if (end_opt == 0)
		return (NULL);

	nodedesc_str = malloc(64);
	strncpy(nodedesc_str, optarg, 64);
	start_opt++;

	/*
	 * strcat a space string and then strcat the
	 * next sub-string.
	 */
	for (i = start_opt; i <= end_opt; i++) {
		strncat(nodedesc_str, " ", 64);
		strncat(nodedesc_str, argv[i], 64);
	}

	/*
	 * Add a space at the end, if the caller has set
	 * space_at_end and the nodedesc string doesn't
	 * contain a space at the end.
	 */
	if (space_at_end == B_TRUE &&
	    nodedesc_str[strlen(nodedesc_str)] != ' ')
		strncat(nodedesc_str, " ", 64);
	return (nodedesc_str);
}

int
main(int argc, char **argv)
{
	int		rc;
	char		*nodedesc = NULL, *hcadesc = NULL;
	uint32_t	update_flag = 0;
	struct utsname	uts_name;
	uint64_t	hca_guid;
	boolean_t	guid_inited = B_FALSE;
	extern int ibdebug;

	static char const str_opts[] = "N:H:G:vd";
	static const struct option long_opts[] = {
		{ "Node_Descriptor", 1, 0, 'N'},
		{ "HCA_Description", 1, 0, 'H'},
		{ "GUID", 1, 0, 'G'},
		{ "verbose", 0, 0, 'v'},
		{ "debug", 0, 0, 'd'},
		{ }
	};

	argv0 = argv[0];
	while (1) {
		int ch = getopt_long(argc, argv, str_opts,
		    long_opts, NULL);
		if (ch == -1)
			break;
		switch (ch) {
		case 'N':
			nodedesc = nodedesc_substr_cat(argv, argc, B_TRUE);
			if (!nodedesc) {
				usage();
				rc = -1;
				goto free_and_ret;
			}
			update_flag |= NODEDESC_UPDATE_STRING;
			break;
		case 'H':
			hcadesc = nodedesc_substr_cat(argv, argc, B_FALSE);
			if (!hcadesc) {
				usage();
				rc = -1;
				goto free_and_ret;
			}
			update_flag |= NODEDESC_UPDATE_HCA_STRING;
			break;
		case 'G':
			guid_inited = B_TRUE;
			hca_guid = (uint64_t)strtoull(optarg, 0, 0);
			break;
		case 'v' :
			update_flag |= NODEDESC_READ;
			break;
		case 'd':
			ibdebug++;
			break;
		default:
			usage();
			rc = -1;
			goto free_and_ret;
		}
	}

	if (update_flag & NODEDESC_READ) {
		if (nodedesc || hcadesc || guid_inited == B_TRUE) {
			usage();
			rc = -1;
			goto free_and_ret;
		}

		read_nodedesc();
		update_read_info_hwnames();
		print_read_info();
		return (0);
	}

	if (hcadesc && guid_inited == B_FALSE) {
		IBERROR("No GUID specified for HCA Node descriptor");
		usage();
		rc = -1;
		goto free_and_ret;
	}

	if (nodedesc) {
		rc = update_nodedesc(nodedesc, NULL, 0,
		    NODEDESC_UPDATE_STRING);
		if (rc) {
			IBERROR("write common node descriptor "
			    "failed");
			rc = -1;
			goto free_and_ret;
		}
	}

	if (hcadesc) {
		rc = update_nodedesc(NULL, hcadesc, hca_guid,
		    NODEDESC_UPDATE_HCA_STRING);
		if (rc) {
			IBERROR("update_hca_noddesc failed");
			rc = -1;
			goto free_and_ret;
		}
		return (0);
	}


	if (nodedesc == NULL) {
		if (uname(&uts_name) < 0) {
			IBERROR("Node descriptor unspecified"
			    "& uts_name failed");
			rc = -1;
			goto free_and_ret;
		}
	}

	rc = update_nodedesc((char *)uts_name.nodename, NULL,
	    0, NODEDESC_UPDATE_STRING);

free_and_ret:
	if (nodedesc)
		free(nodedesc);
	if (hcadesc)
		free(hcadesc);

	return (rc);
}

#endif
