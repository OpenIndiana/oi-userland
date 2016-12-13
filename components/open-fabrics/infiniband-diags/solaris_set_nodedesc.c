/*
 * Copyright (c) 2010, 2016, Oracle and/or its affiliates. All rights reserved.
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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <getopt.h>
#include <sys/utsname.h>

#include <infiniband/verbs.h>
#include <infiniband/arch.h>
#include <infiniband/umad.h>
#include "ibdiag_common.h"
#include <sys/ib/clients/of/sol_uverbs/sol_uverbs_ioctl.h>

#define	NODEDESC_READ			0x80000000


char *argv0 = "solaris_set_nodedesc";

static struct nodedesc_read_info_s {
	boolean_t	info_valid;
	uint64_t	guid;
	char		nd_string[64];
	boolean_t	ofuv_name_valid;
	char		ofuv_name[64];
} nd_read_info_arr[MAX_HCAS];
int	nd_read_info_cnt = 0;

static int
read_nodedesc_ioctl(struct ibv_context *context,
    sol_uverbs_nodedesc_t *nodedesc);
static int
write_nodedesc_ioctl(struct ibv_context *context,
    sol_uverbs_nodedesc_t *nodedesc);

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
update_read_info_hwnames(struct ibv_device **dev_list, int num_devices)
{
	int		i;
	uint64_t	dev_guid;
	char		*dev_name;
	size_t		dev_name_len;

	for (i = 0; dev_list[i] != 0 && i < num_devices; ++i) {
		int	j;

		dev_guid = (uint64_t)ntohll(
		    ibv_get_device_guid(dev_list[i]));
		dev_name = (char *)ibv_get_device_name(dev_list[i]);
		dev_name_len = strlen(dev_name) + 1;
		for (j = 0; j < nd_read_info_cnt; j++) {
			if (nd_read_info_arr[j].info_valid == B_TRUE &&
			    nd_read_info_arr[j].guid == dev_guid) {
				memcpy(nd_read_info_arr[j].ofuv_name,
				    dev_name, dev_name_len);
				nd_read_info_arr[j].ofuv_name_valid =
				    B_TRUE;
				break;
			}
		}
	}
}

static void
add_read_info_arr(char *nd_str, uint64_t guid)
{
	size_t	nd_len;

	nd_len = strlen(nd_str) + 1;
	nd_read_info_arr[nd_read_info_cnt].info_valid = B_TRUE;
	nd_read_info_arr[nd_read_info_cnt].guid = guid;
	memcpy(nd_read_info_arr[nd_read_info_cnt].nd_string,
	    nd_str, nd_len);
	nd_read_info_cnt++;

}

static void
do_driver_read_ioctl(struct ibv_device *device)
{
	int			rc;
	uint64_t		hca_guid;
	struct ibv_context	*context;
	sol_uverbs_nodedesc_t	*nodedescp;

	/* Get the context for the device */
	context = ibv_open_device(device);
	if (!context) {
		IBEXIT("Unable to open the device.\n");
		/* NOTREACHED */
	}

	if (context->device != device) {
		IBEXIT("Device not set.\n");
		/* NOTREACHED */
	}

	/* Allocate the memory for node descriptor */
	nodedescp = (sol_uverbs_nodedesc_t *)malloc(
	    sizeof (sol_uverbs_nodedesc_t));
	if (nodedescp == NULL) {
		IBEXIT("Memory allocation failed.\n");
		/* NOTREACHED */
	}

	nodedescp->uverbs_solaris_abi_version =
	    IB_USER_VERBS_SOLARIS_ABI_VERSION;

	/* Get the guid for the device */
	hca_guid = (uint64_t)ntohll(ibv_get_device_guid(device));
	if (!hca_guid) {
		IBEXIT("ibv_get_device_guid failed.\n");
		/* NOTREACHED */
	}

	/* Read node descriptor */
	rc = read_nodedesc_ioctl(context, nodedescp);
	if (rc != 0) {
		IBEXIT("Failed to read node descriptor.\n");
		/* NOTREACHED */
	}

	add_read_info_arr((char *)nodedescp->node_desc_str,
	    hca_guid);

read_nodedesc_exit_1:
	/* release the allocated memory */
	free(nodedescp);
read_nodedesc_exit_2:
	/* Close the device */
	ibv_close_device(context);
}

static int
do_driver_update_ioctl(struct ibv_device *device, char *node_desc,
    char *hca_desc, uint32_t update_flag)
{
	int			rc;
	struct ibv_context	*context;
	sol_uverbs_nodedesc_t	*nodedescp;
	char			*desc_str;

	desc_str = (node_desc ? node_desc : hca_desc);

	/* Get context for the device */
	context = ibv_open_device(device);
	if (!context) {
		IBEXIT("Unable to open the device.\n");
		/* NOTREACHED */
	}

	if (context->device != device) {
		IBEXIT("Device not set.\n");
		/* NOTREACHED */
	}

	/* Allocate the memory for node descriptor */
	nodedescp = (sol_uverbs_nodedesc_t *)malloc(
	    sizeof (sol_uverbs_nodedesc_t));
	if (nodedescp == NULL) {
		IBEXIT("Memory allocation failed.\n");
		/* NOTREACHED */
	}

	strncpy(nodedescp->node_desc_str, desc_str, UVERBS_NODEDESC_MAX);
	nodedescp->node_desc_str[UVERBS_NODEDESC_MAX - 1] = '\0';
	nodedescp->node_desc_update_flag = update_flag;
	nodedescp->uverbs_solaris_abi_version =
	    IB_USER_VERBS_SOLARIS_ABI_VERSION;

	rc = write_nodedesc_ioctl(context, nodedescp);
	if (rc != 0)
		IBEXIT("Failed to set node descriptor.\n");

	free(nodedescp);

write_nodedesc_exit:
	ibv_close_device(context);
	return (rc);
}

static void
read_nodedesc(struct ibv_device **device_list, int num_devices)
{
	int i;

	for (i = 0; device_list[i] != 0 && i < num_devices; i++)
		do_driver_read_ioctl(device_list[i]);
}

static int
update_nodedesc(struct ibv_device **device_list, int num_devices,
    char *cmn_nodedesc, char *hca_nodedesc, uint64_t guid,
    uint32_t update_flag)
{
	int		i, rc = -1;
	uint64_t	dev_guid;
	boolean_t	matched = B_FALSE;

	if (cmn_nodedesc && hca_nodedesc == NULL) {
		for (i = 0; i < num_devices; i++) {
			rc = do_driver_update_ioctl(device_list[i],
			    cmn_nodedesc, hca_nodedesc, update_flag);
			if (rc != 0)
				continue;
			else
				break;
		}

		if (rc != 0 && i == num_devices)
			IBEXIT("Failed to set the node descriptor.\n");

		return (rc);
	}

	if (hca_nodedesc && guid) {
		for (i = 0; i < num_devices; i++) {
			dev_guid = (uint64_t)ntohll(ibv_get_device_guid(
			    device_list[i]));
			if (!dev_guid) {
				continue;
			}
			if (dev_guid == guid) {
				matched = B_TRUE;
				rc = do_driver_update_ioctl(device_list[i],
				    cmn_nodedesc, hca_nodedesc, update_flag);
				break;
			} else {
				continue;
			}
		}

		if (matched == B_FALSE) {
			IBEXIT("No guid matched.\n");
			/* NOTREACHED */
		}

		if (rc != 0) {
			IBEXIT("Failed to set the node descriptor.\n");
			/* NOTREACHED */
		}
	}

	return (rc);
}

static int
read_nodedesc_ioctl(struct ibv_context *context,
    sol_uverbs_nodedesc_t *nodedesc)
{

	int	ret;

	/*
	 * Use ioctl call to sol_uverbs module.
	 */
	if (!context || !nodedesc) {
		return (-1);
	}

	ret = ioctl(context->cmd_fd, UVERBS_IOCTL_GET_NODEDESC, nodedesc);
	if (ret != 0) {
		if (ret == EINVAL)
			IBEXIT("ABI version check failed.\n");
		else
			IBEXIT("UVERBS_IOCTL_GET_NODEDESC ioctl failed.\n");

		/* NOTREACHED */
	}

	return (0);
}

static int
write_nodedesc_ioctl(struct ibv_context *context,
    sol_uverbs_nodedesc_t *nodedesc)
{
	int	ret;

	/*
	 * Use ioctl call to sol_uverbs module.
	 */
	if (!context || !nodedesc)
		return (-1);

	ret = ioctl(context->cmd_fd, UVERBS_IOCTL_SET_NODEDESC, nodedesc);
	if (ret != 0) {
		if (ret == EINVAL)
			IBEXIT("ABI version check failed.\n");
		else
			IBEXIT("UVERBS_IOCTL_SET_NODEDESC ioctl failed.\n");

		/* NOTREACHED */
	}

	return (0);
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
 * Name		: nodedesc_substr_cat
 *
 * Function	:
 * 	This fuction returns the node descriptor string
 * 	extracted from the command line arguments.
 *
 * Inputs	:
 * 	Parameters
 * 	----------
 * 	argv, argc  - Command line arguments to main()
 * 	space_at_end- Indicates if a space should be
 * 		added at the end of returned string
 *	Externs
 *	-------
 *	optarg - string after option (-N / -H)
 *	optind - 1 based index to argv array for the
 *		string after option name
 *	See getopt_long(3C) for more information.
 *
 * Return	:
 * 	Node description string. The memory allocated
 * 	for the returned node descriptor string should
 * 	be freed by the caller.
 *
 * Notes	:
 * 	The node descriptor string can contain multiple
 * 	sub-strings, for example
 * 		-N s1 s2 s3
 * 	This function concatenates these sub-strings with
 * 	a space between the substring. An additional space
 * 	is added at the end, if "space_at_end" parameter
 * 	is TRUE.
 *
 * 	This function always returns a string of length
 * 	less than UVERBS_NODEDESC_MAX.
 */

static char *
nodedesc_substr_cat(char **argv, int argc, boolean_t space_at_end)
{
	int	i, start_opt, end_opt;
	char	*nodedesc_str;

	/*
	 * Set start_opt to the 0 based index to the starting
	 * string after the option. As optind is 1 based,
	 * decrement 1.
	 */
	start_opt = optind - 1;

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
	/* copy the first string after the option. */
	strncpy(nodedesc_str, optarg, UVERBS_NODEDESC_MAX);
	nodedesc_str[UVERBS_NODEDESC_MAX - 1] = '\0';
	start_opt++;

	/*
	 * concatenate subsequent strings after the option
	 * (if any). Add a space between the strings.
	 */
	for (i = start_opt; i <= end_opt; i++) {
		/*
		 * Check if concatenated string would go out of
		 * bounds, if so skip the rest of the strings.
		 */
		if ((strlen(nodedesc_str) + strlen(argv[i]) + 1)
		    >= UVERBS_NODEDESC_MAX) {
			break;
		}
		/* concatenate a space and the next string. */
		strncat(nodedesc_str, " ", UVERBS_NODEDESC_MAX - 1);
		strncat(nodedesc_str, argv[i],
		    UVERBS_NODEDESC_MAX - strlen(nodedesc_str));
	}

	/*
	 * Add a space at the end, if the caller has set
	 * space_at_end and the nodedesc string doesn't
	 * contain a space at the end.
	 */
	if (space_at_end == B_TRUE &&
	    nodedesc_str[strlen(nodedesc_str)] != ' ') {
		/*
		 * If the return string has already reached the
		 * maximum length, just overwrite the last char
		 * in the string with space.
		 *
		 * else strcat a space at the end.
		 */
		if (strlen(nodedesc_str) == (UVERBS_NODEDESC_MAX - 1))
			nodedesc_str[UVERBS_NODEDESC_MAX - 2] = ' ';
		else
			strncat(nodedesc_str, " ", UVERBS_NODEDESC_MAX - 2);
	}

	return (nodedesc_str);
}

int
main(int argc, char **argv)
{
	int			rc;
	char			*nodedesc = NULL;
	char			*hcadesc = NULL;
	uint32_t		update_flag = 0;
	struct utsname		uts_name;
	uint64_t		hca_guid;
	boolean_t		guid_inited = B_FALSE;
	extern int 		ibdebug;
	char			nodename[64];
	struct ibv_device	**device_list = NULL;
	int			num_devices = 0;

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
				goto free_and_ret_2;
			}
			update_flag |= UVERBS_NODEDESC_UPDATE_STRING;
			break;
		case 'H':
			hcadesc = nodedesc_substr_cat(argv, argc, B_FALSE);
			if (!hcadesc) {
				usage();
				rc = -1;
				goto free_and_ret_2;
			}
			update_flag |= UVERBS_NODEDESC_UPDATE_HCA_STRING;
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
			goto free_and_ret_2;
		}
	}

	if (update_flag & NODEDESC_READ) {
		if (nodedesc || hcadesc || guid_inited == B_TRUE) {
			usage();
			rc = -1;
			goto free_and_ret_2;
		}

		device_list = ibv_get_device_list(&num_devices);
		if (!device_list) {
			IBEXIT("ibv_get_device_list failed.\n");
			/* NOTREACHED */
		}

		read_nodedesc(device_list, num_devices);
		update_read_info_hwnames(device_list, num_devices);
		print_read_info();
		rc = 0;
		goto free_and_ret_1;
	}

	if (hcadesc && guid_inited == B_FALSE) {
		IBEXIT("No GUID specified for HCA Node descriptor");
		/* NOTREACHED */
	}

	device_list = ibv_get_device_list(&num_devices);
	if (!device_list) {
		IBEXIT("ibv_get_device_list failed.\n");
		/* NOTREACHED */
	}

	if (nodedesc) {
		rc = update_nodedesc(device_list, num_devices,
		    nodedesc, NULL, 0, UVERBS_NODEDESC_UPDATE_STRING);
		if (rc) {
			IBEXIT("write common node descriptor "
			    "failed");
			/* NOTREACHED */
		}
	}

	if (hcadesc) {
		rc = update_nodedesc(device_list, num_devices,
		    NULL, hcadesc, hca_guid,
		    UVERBS_NODEDESC_UPDATE_HCA_STRING);
		if (rc) {
			IBEXIT("update_hca_noddesc failed");
			/* NOTREACHED */
		}
		rc = 0;
		goto free_and_ret_1;
	}


	if (nodedesc == NULL) {
		if (uname(&uts_name) < 0) {
			IBEXIT("Node descriptor unspecified"
			    "& uts_name failed");
			/* NOTREACHED */
		}

		/*
		 * The common nodedesc string can have max
		 * UVERBS_NODEDESC_MAX chars. From the nodename,
		 * UVERBS_NODEDESC_MAX - 2 can be accommodated.
		 * A space is appended at the end, just like
		 * common node specified using the "-N" option.
		 */

		(void) strncpy(nodename, uts_name.nodename,
		    UVERBS_NODEDESC_MAX - 2);
		nodename[UVERBS_NODEDESC_MAX - 1] = '\0';
		if (nodename[strlen(nodename)] != ' ') {
			if (strlen(nodename) == UVERBS_NODEDESC_MAX - 1)
				nodename[UVERBS_NODEDESC_MAX - 2] = ' ';
			else
				(void) strncat(nodename, " ",
				    UVERBS_NODEDESC_MAX - 2);
		}

		rc = update_nodedesc(device_list, num_devices,
		    nodename, NULL, 0,
		    UVERBS_NODEDESC_UPDATE_STRING);
		if (rc) {
			IBEXIT("write common node descriptor failed");
			/* NOTREACHED */
		}
	}

free_and_ret_1:
	ibv_free_device_list(device_list);

free_and_ret_2:
	if (nodedesc)
		free(nodedesc);
	if (hcadesc)
		free(hcadesc);

	return (rc);
}

#endif
