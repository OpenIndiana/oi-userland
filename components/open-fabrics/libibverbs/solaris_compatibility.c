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
#if HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

/*
 * OFED Solaris wrapper
 */
#if defined(__SVR4) && defined(__sun)

#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/processor.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/param.h>
#include <sys/ib/adapters/hermon/hermon_ioctl.h>
#include <sys/ib/adapters/tavor/tavor_ioctl.h>

#include <alloca.h>
#include "../include/infiniband/arch.h"
#include "../include/infiniband/verbs.h"
#include <errno.h>
#include <pthread.h>
#include <kstat.h>

/*
 * The followings will be removed when sol_uverbs_ioctl.h and sol_umad_ioctl.h
 * are delivered through ON.
 */

#define	UVERBS_IOCTL		('v' << 8)

#define	IB_USER_VERBS_SOLARIS_ABI_VERSION	1

typedef enum {
	UVERBS_IOCTL_GET_HCA_INFO	= UVERBS_IOCTL | 0x01
} uverbs_ioctl_enum_t;

typedef struct sol_uverbs_hca_info_s {
	char		uverbs_hca_psid_string[MAXNAMELEN];
	char		uverbs_hca_ibdev_name[MAXNAMELEN];
	char		uverbs_hca_driver_name[MAXNAMELEN];
	uint32_t	uverbs_hca_driver_instance;
	uint32_t	uverbs_hca_vendorid;
	uint16_t	uverbs_hca_deviceid;
	uint8_t		uverbs_hca_devidx;
	uint8_t		uverbs_hca_pad1[5];
} sol_uverbs_hca_info_t;

typedef struct sol_uverbs_info_s {
	int32_t			uverbs_abi_version;
	int32_t			uverbs_solaris_abi_version;
	int16_t			uverbs_hca_cnt;
	int8_t			uverbs_pad1[6];    /* Padding for alignment */
	sol_uverbs_hca_info_t	uverbs_hca_info[];
} sol_uverbs_info_t;

#define	UMAD_IOCTL		('m' << 8)

#define	IB_USER_MAD_SOLARIS_ABI_VERSION	1

typedef enum {
	IB_USER_MAD_GET_PORT_INFO	= UMAD_IOCTL | 0x01
} umad_ioctl_enum_t;

typedef struct sol_umad_ioctl_port_info_s {
	char		umad_port_ibdev_name[MAXNAMELEN];
	uint32_t	umad_port_num;
	uint16_t	umad_port_idx;
	uint8_t		umad_port_pad1[2];
} sol_umad_ioctl_port_info_t;

typedef struct sol_umad_ioctl_info_s {
	int32_t				umad_abi_version;
	int32_t				umad_solaris_abi_version;
	int16_t				umad_port_cnt;
	int8_t				umad_pad1[6];    /* alignment padding */
	sol_umad_ioctl_port_info_t	umad_port_info[];
} sol_umad_ioctl_info_t;

/* end of sol_uverbs_ioctl.h and sol_umad_ioctl.h contents */

/*
 * duplicate ABI definitions for HCAs as the HCA abi headers are not
 * installed in proto.
 */ 
#define	MTHCA_UVERBS_ABI_VERSION	1 /* mthca-abi.h */
#define	MLX4_UVERBS_MAX_ABI_VERSION	3 /* mlx4-abi.h */
#define	RDMA_USER_CM_MIN_ABI_VERSION	3 /* rdma_cma_abi.h */
#define	RDMA_USER_CM_MAX_ABI_VERSION	4 /* rdma_cma_abi.h */

#define	MLX4	0
#define	MTHCA	1
#define	MAX_HCAS				16
#define	MAX_HCA_PORTS				16
#define	HW_DRIVER_MAX_NAME_LEN			20
#define	UVERBS_KERNEL_SYSFS_NAME_BASE		"uverbs"
#define	UMAD_KERNEL_SYSFS_NAME_BASE		"umad"
#define	IB_HCA_DEVPATH_PREFIX			"/dev/infiniband/hca"
#define	IB_OFS_DEVPATH_PREFIX			"/dev/infiniband/ofs"
#define	CONNECTX_NAME				"mlx4_"
#define	INFINIHOST_NAME				"mthca"

#define	MELLANOX_VENDOR_ID			0x15b3
#define	PCI_DEVICE_ID_MELLANOX_TAVOR		0x5a44
#define	PCI_DEVICE_ID_MELLANOX_ARBEL		0x6282
#define	PCI_DEVICE_ID_MELLANOX_ARBEL_COMPAT	0x6278
#define	PCI_DEVICE_ID_MELLANOX_HERMON_SDR	0x6340
#define	PCI_DEVICE_ID_MELLANOX_HERMON_DDR	0x634a
#define	PCI_DEVICE_ID_MELLANOX_HERMON_QDR	0x6354
#define	PCI_DEVICE_ID_MELLANOX_HERMON_DDR_PCIE2	0x6732
#define	PCI_DEVICE_ID_MELLANOX_HERMON_QDR_PCIE2	0x673c
#define	INFINIHOST_DEVICE_ID_2			0x5a45
#define	INFINIHOST_DEVICE_ID_4			0x6279

/*
 * sol_uverbs_drv_status is the status of what libibverbs knows
 * about the status of sol_uverbs driver.
 */
#define	SOL_UVERBS_DRV_STATUS_UNKNOWN	0x0
#define	SOL_UVERBS_DRV_STATUS_LOADED	0x1
#define	SOL_UVERBS_DRV_STATUS_UNLOADED	0x02

static kstat_ctl_t	*kc = NULL;	/* libkstat cookie */
static int sol_uverbs_drv_status = SOL_UVERBS_DRV_STATUS_UNKNOWN;
static int sol_uverbs_minor_dev = -1;

/*
 * check_path() prefixs
 */
typedef enum cp_prefix_e {
	CP_SOL_UVERBS		= 1,
	CP_DEVICE		= 2,
	CP_D			= 3,
	CP_GIDS			= 4,
	CP_PKEYS		= 5,
	CP_MTHCA		= 6,
	CP_MLX4			= 7,
	CP_PORTS		= 8,
	CP_UMAD			= 9,
	CP_SLASH		= 10,
	CP_SYS			= 11,
	CP_CLASS		= 12,
	CP_INFINIBAND_VERBS	= 13,
	CP_INFINIBAND		= 14,
	CP_INFINIBAND_MAD	= 15,
	CP_MISC			= 16,
	CP_RDMA_CM		= 17
} cp_prefix_t;

/*
 * Some temporary cache code, until things are cleaned up as part of DR
 * work. This will speed up the sysfs emulation.
 */
typedef struct ibdev_cache_info_s {
	uint_t		ibd_valid;
	uint_t		ibd_hw_rev;
	char		ibd_node_guid_str[20];
	char		ibd_sys_image_guid[20];
	char		ibd_fw_ver[16];
	char		ibd_name[8];
	int		ibd_boardid_index;
} ibdev_cache_info_t;

/* tavor and hermon - hence 2 */
static ibdev_cache_info_t ibdev_cache[2][MAX_HCAS];

typedef struct uverbs_cache_info_s {
	uint_t		uvc_valid;
	uint_t		uvc_ibdev_abi_version;
	uint_t		uvc_vendor_id;
	uint_t		uvc_device_id;
	int		uvc_hca_instance;
	char		uvc_ibdev_name[8];
	char		uvc_ibdev_hca_path[MAXPATHLEN];
} uverbs_cache_info_t;
static uverbs_cache_info_t	uverbs_dev_cache[MAX_HCAS];
static int			uverbs_abi_version = -1;

typedef struct umad_cache_info_s {
	uint_t		umc_valid;
	int		umc_port;
	char		umc_ib_dev[16];
} umad_cache_info_t;
static umad_cache_info_t	umad_dev_cache[MAX_HCAS * MAX_HCA_PORTS];
static int			umad_abi_version = -1;

/*
 * Structure to hold the part number  & PSID for an HCA card
 * This is a sub-set of the file :
 * /ws/onnv-clone/usr/src/cmd/fwflash/plugins/hdrs/MELLANOX.h
 */
typedef struct mlx_mdr_s {
	char *mlx_pn;
	char *mlx_psid;
} mlx_mdr_t;

/*
 * Magic decoder ring for matching HCA hardware/firmware.
 * Part Number / PSID / String ID
 */
mlx_mdr_t mlx_mdr[] = {
	/* For failure case, use unknown as "board-id" */
	{ "unknown",		"unknown"	},

	/* Part No		PSID		*/
	{ "375-3605-01",	"SUN0160000001" },
	{ "375-3382-01",	"SUN0030000001" },
	{ "375-3481-01",	"SUN0040000001" },
	{ "375-3418-01",	"SUN0040000001" },
	{ "375-3259-01",	"SUN0010000001" },
	{ "375-3259-03",	"SUN0010000001" },
	{ "X1289A-Z",		"SUN0010010001" },
	{ "375-3548-01",	"SUN0060000001" },
	{ "375-3549-01",	"SUN0070000001" },
	{ "375-3549-01",	"SUN0070130001" },
	{ "375-3481-01",	"SUN0050000001" },
	{ "375-3439-01",	"SUN0051000001" },
	{ "375-3260-03",	"SUN0020000001" },
	{ "375-3605-01",	"SUN0160000002" },
	{ "375-3697-01",	"SUN0160000002" },
	{ "375-3606-01",	"SUN0150000001" },
	{ "375-3606-02",	"SUN0150000009" },
	{ "375-3606-03",	"SUN0150000009" },
	{ "375-3606-02",	"SUN0170000009" },
	{ "375-3696-01",	"SUN0170000009" },
	{ "375-3551-05",	"SUN0080000001" },
	{ "MHEA28-XS",		"MT_0250000001" },
	{ "MHEA28-XSC",		"MT_0390110001" },
	{ "MHEA28-XT",		"MT_0150000001" },
	{ "MHEA28-XTC",		"MT_0370110001" },
	{ "MHGA28-XT",		"MT_0150000002" },
	{ "MHGA28-XTC",		"MT_0370110002" },
	{ "MHGA28-XTC",		"MT_0370130002" },
	{ "MHGA28-XS",		"MT_0250000002" },
	{ "MHGA28-XSC",		"MT_0390110002" },
	{ "MHGA28-XSC",		"MT_0390130002" },
	{ "MHEL-CF128",		"MT_0190000001" },
	{ "MHEL-CF128-T",	"MT_00A0000001" },
	{ "MTLP25208-CF128T",	"MT_00A0000001" },
	{ "MHEL-CF128-TC",	"MT_00A0010001" },
	{ "MHEL-CF128-TC",	"MT_0140010001" },
	{ "MHEL-CF128-SC",	"MT_0190010001" },
	{ "MHEA28-1TC",		"MT_02F0110001" },
	{ "MHEA28-1SC",		"MT_0330110001" },
	{ "MHGA28-1T",		"MT_0200000001" },
	{ "MHGA28-1TC",		"MT_02F0110002" },
	{ "MHGA28-1SC",		"MT_0330110002" },
	{ "MHGA28-1S",		"MT_0430000001" },
	{ "MHEL-CF256-T",	"MT_00B0000001" },
	{ "MTLP25208-CF256T",	"MT_00B0000001" },
	{ "MHEL-CF256-TC",	"MT_00B0010001" },
	{ "MHEA28-2TC",		"MT_0300110001" },
	{ "MHEA28-2SC",		"MT_0340110001" },
	{ "MHGA28-2T",		"MT_0210000001" },
	{ "MHGA28-2TC",		"MT_0300110002" },
	{ "MHGA28-2SC",		"MT_0340110002" },
	{ "MHEL-CF512-T",	"MT_00C0000001" },
	{ "MTLP25208-CF512T",	"MT_00C0000001" },
	{ "MHGA28-5T",		"MT_0220000001" },
	{ "MHES14-XSC",		"MT_0410110001" },
	{ "MHES14-XT",		"MT_01F0000001" },
	{ "MHES14-XTC",		"MT_03F0110001" },
	{ "MHES18-XS",		"MT_0260000001" },
	{ "MHES18-XS",		"MT_0260010001" },
	{ "MHES18-XSC",		"MT_03D0110001" },
	{ "MHES18-XSC",		"MT_03D0120001" },
	{ "MHES18-XSC",		"MT_03D0130001" },
	{ "MHES18-XT",		"MT_0230000002" },
	{ "MHES18-XT",		"MT_0230010002" },
	{ "MHES18-XTC",		"MT_03B0110001" },
	{ "MHES18-XTC",		"MT_03B0120001" },
	{ "MHES18-XTC",		"MT_03B0140001" },
	{ "MHGS18-XS",		"MT_0260000002" },
	{ "MHGS18-XSC",		"MT_03D0110002" },
	{ "MHGS18-XSC",		"MT_03D0120002" },
	{ "MHGS18-XSC",		"MT_03D0130002" },
	{ "MHGS18-XT",		"MT_0230000001" },
	{ "MHGS18-XTC",		"MT_03B0110002" },
	{ "MHGS18-XTC",		"MT_03B0120002" },
	{ "MHGS18-XTC",		"MT_03B0140002" },
	{ "MHXL-CF128",		"MT_0180000001" },
	{ "MHXL-CF128-T",	"MT_0030000001" },
	{ "MTLP23108-CF128T",	"MT_0030000001" },
	{ "MHET2X-1SC",		"MT_0280110001" },
	{ "MHET2X-1SC",		"MT_0280120001" },
	{ "MHET2X-1TC",		"MT_0270110001" },
	{ "MHET2X-1TC",		"MT_0270120001" },
	{ "MHXL-CF256-T",	"MT_0040000001" },
	{ "MHET2X-2SC",		"MT_02D0110001" },
	{ "MHET2X-2SC",		"MT_02D0120001" },
	{ "MHET2X-2TC",		"MT_02B0110001" },
	{ "MHET2X-2TC",		"MT_02B0120001" },
	{ "MHX-CE128-T",	"MT_0000000001" },
	{ "MTPB23108-CE128",	"MT_0000000001" },
	{ "MHX-CE256-T",	"MT_0010000001" },
	{ "MTPB23108-CE256",	"MT_0010000001" },
	{ "MHX-CE512-T",	"MT_0050000001" },
	{ "MTPB23108-CE512",	"MT_0050000001" },
	{ "MHEH28-XSC",		"MT_04C0110001" },
	{ "MHEH28-XSC",		"MT_04C0130005" },
	{ "MHEH28-XTC",		"MT_04A0110001" },
	{ "MHEH28-XTC",		"MT_04A0130005" },
	{ "MHGH28-XSC",		"MT_04C0110002" },
	{ "MHGH28-XSC",		"MT_04C0120002" },
	{ "MHGH28-XSC",		"MT_04C0140005" },
	{ "MHGH28-XTC",		"MT_04A0110002" },
	{ "MHGH28-XTC",		"MT_04A0120002" },
	{ "MHGH28-XTC",		"MT_04A0140005" },
	{ "MHGH29-XSC",		"MT_0A60110002" },
	{ "MHGH29-XSC",		"MT_0A60120005" },
	{ "MHGH29-XTC",		"MT_0A50110002" },
	{ "MHGH29-XTC",		"MT_0A50120005" },
	{ "MHJH29-XTC",		"MT_04E0110003" },
	{ "MHJH29-XSC",		"MT_0500120005" },
	{ "MHQH29-XTC",		"MT_04E0120005" },
	{ "MHQH19-XTC",		"MT_0C40110009" },
	{ "MHQH29-XTC",		"MT_0BB0110003" },
	{ "MHQH29-XTC",		"MT_0BB0120003" },
	{ "MHEH28B-XSR",	"MT_0D10110001" },
	{ "MHEH28B-XTR",	"MT_0D20110001" },
	{ "MHGH28B-XSR",	"MT_0D10110002" },
	{ "MHGH28B-XTR",	"MT_0D20110002" },
	{ "MHGH18B-XTR",	"MT_0D30110002" },
	{ "MNEH28B-XSR",	"MT_0D40110004" },
	{ "MNEH28B-XTR",	"MT_0D50110004" },
	{ "MNEH29B-XSR",	"MT_0D40110010" },
	{ "MNEH29B-XTR",	"MT_0D50110010" },
	{ "MHGH29B-XSR",	"MT_0D10110008" },
	{ "MHGH29B-XTR",	"MT_0D20110008" },
	{ "MHJH29B-XSR",	"MT_0D10110009" },
	{ "MHJH29B-XSR",	"MT_0D10120009" },
	{ "MHJH29B-XTR",	"MT_0D20110009" },
	{ "MHJH29B-XTR",	"MT_0D20120009" },
	{ "MHGH19B-XSR",	"MT_0D60110008" },
	{ "MHGH19B-XTR",	"MT_0D30110008" },
	{ "MHJH19B-XTR",	"MT_0D30110009" },
	{ "MHQH29B-XSR",	"MT_0D70110009" },
	{ "MHQH29B-XTR",	"MT_0D80110009" },
	{ "MHQH29B-XTR",	"MT_0D80120009" },
	{ "MHQH29B-XTR",	"MT_0D80130009" },
	{ "MHQH29B-XTR",	"MT_0E30110009" },
	{ "MHRH29B-XSR",	"MT_0D70110008" },
	{ "MHRH29B-XTR",	"MT_0D80110008" },
	{ "MHQH19B-XTR",	"MT_0D90110009" },
	{ "MHRH19B-XSR",	"MT_0E40110009" },
	{ "MHRH19B-XTR",	"MT_0D90110008" },
	{ "MNPH28C-XSR",	"MT_0DA0110004" },
	{ "MNPH28C-XTR",	"MT_0DB0110004" },
	{ "MNPH29C-XSR",	"MT_0DA0110010" },
	{ "MNPH29C-XTR",	"MT_0DB0110010" },
	{ "MNPH29C-XTR",	"MT_0DB0120010" },
	{ "MNPH29C-XTR",	"MT_0DB0130010" },
	{ "MNZH29-XSR",		"MT_0DC0110009" },
	{ "MNZH29-XTR",		"MT_0DD0110009" },
	{ "MNZH29-XTR",		"MT_0DD0120009" },
	{ "MHQH19B-XNR",	"MT_0DF0110009" },
	{ "MHQH19B-XNR",	"MT_0DF0120009" },
	{ "MNQH19-XTR",		"MT_0D80110017" },
	{ "MNQH19C-XTR",	"MT_0E20110017" },
	{ "MHZH29B-XSR",	"MT_0E80110009" },
	{ "MHZH29B-XTR",	"MT_0E90110009" },
	{ "MHZH29B-XTR",	"MT_0E90110009" },
	{ "MHQA19-XTR",		"MT_0EA0110009" },
	{ "MHRA19-XTR",		"MT_0EB0110008" },
	{ "MHQH29C-XTR",	"MT_0EF0110009" },
	{ "MHQH29C-XSR",	"MT_0F00110009" },
	{ "MHRH29C-XTR",	"MT_0F10110008" },
	{ "MHRH29C-XSR",	"MT_0F20110008" },
	{ "MHPH29D-XTR",	"MT_0F30110010" },
	{ "MHPH29D-XSR",	"MT_0F40110010" },
	{ "MNPA19-XTR",		"MT_0F60110010" },
	{ "MNPA19-XSR",		"MT_0F70110010" },

	/* Ethernet cards */
	{ "MNEH28B-XTR",	"MT_0D50110004" },
	{ "MNEH29B-XSR",	"MT_0D40110010" },
	{ "MNEH29B-XTR",	"MT_0D50110010" },
	{ "MNPH28C-XSR",	"MT_0DA0110004" },
	{ "MNPH28C-XTR",	"MT_0DB0110004" },
	{ "MNPH29C-XSR",	"MT_0DA0110010" },
	{ "MNPH29C-XTR",	"MT_0DB0110010" },
	{ "X6275 M2 10GbE",	"X6275M2_10G"   }
};

/* Get mlx_mdr[] array size */
#define	MLX_SZ_MLX_MDR		sizeof (mlx_mdr)
#define	MLX_SZ_MLX_MDR_STRUCT	sizeof (mlx_mdr[0])
#define	MLX_MAX_ID		(MLX_SZ_MLX_MDR / MLX_SZ_MLX_MDR_STRUCT)

pthread_once_t		oneTimeInit = PTHREAD_ONCE_INIT;
static int 		umad_cache_cnt = 0;
static int 		ibdev_cache_cnt = 0;
static int 		uverbs_cache_cnt = 0;
static boolean_t	initialized = B_FALSE;
static boolean_t	umad_cache_initialized = B_FALSE;
static boolean_t	ibdev_cache_initialized = B_FALSE;
static boolean_t	uverbs_cache_initialized = B_FALSE;
static pthread_mutex_t	umad_cache_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t	ibdev_cache_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t	uverbs_cache_mutex = PTHREAD_MUTEX_INITIALIZER;

void __attribute__((constructor))solaris_init(void);
void __attribute__((destructor))solaris_fini(void);

void
solaris_init(void)
{
	while ((kc = kstat_open()) == NULL) {
		if (errno == EAGAIN)
			(void) poll(NULL, 0, 200);
		else
			fprintf(stderr, "cannot open /dev/kstat: %s\n",
			    strerror(errno));
	}
}

void
solaris_fini(void)
{
	(void) kstat_close(kc);
}

static int
umad_cache_add(uint_t dev_num, int port, char *ibdev)
{
	if ((dev_num >= (MAX_HCAS  * MAX_HCA_PORTS)) ||
	    (umad_cache_cnt >= (MAX_HCAS  * MAX_HCA_PORTS))) {
		fprintf(stderr, "dev %d: exceeds umad cache size\n", dev_num);
		return (1);
	}

	umad_dev_cache[dev_num].umc_port = port;
	strcpy(umad_dev_cache[dev_num].umc_ib_dev, ibdev);
	umad_dev_cache[dev_num].umc_valid = 1;
	umad_cache_cnt++;
	return (0);
}

static int
ibdev_cache_add(uint_t dev_num, ibdev_cache_info_t *info_p)
{
	if ((dev_num >= MAX_HCAS) || (ibdev_cache_cnt >= (MAX_HCAS * 2))) {
		fprintf(stderr, "dev %d: exceeds hca cache size\n", dev_num);
		return (1);
	}

	if (!(strncmp(info_p->ibd_name, "mlx4", 4))) {
		memcpy(&(ibdev_cache[MLX4][dev_num]), info_p,
		    sizeof (ibdev_cache_info_t));
		ibdev_cache[MLX4][dev_num].ibd_valid = 1;
	} else {
		memcpy(&(ibdev_cache[MTHCA][dev_num]), info_p,
		    sizeof (ibdev_cache_info_t));
		ibdev_cache[MTHCA][dev_num].ibd_valid = 1;
	}

	ibdev_cache_cnt++;
	return (0);
}

static int
uverbs_cache_add(uint_t dev_num, uverbs_cache_info_t *info_p)
{
	if ((dev_num >= MAX_HCAS) || (uverbs_cache_cnt >= MAX_HCAS)) {
		fprintf(stderr, "dev %d: exceeds uverbs cache size\n", dev_num);
		return (1);
	}

	memcpy(&(uverbs_dev_cache[dev_num]), info_p,
	    sizeof (uverbs_cache_info_t));

	uverbs_dev_cache[dev_num].uvc_valid = 1;
	uverbs_cache_cnt++;
	return (0);
}

static int
ibdev_cache_init()
{
	ibdev_cache_info_t	info;
	struct ibv_device	**root_dev_list, **dev_list = NULL;
	struct ibv_context	*ctx = NULL;
	struct ibv_device_attr	device_attr;
	int			i, num_dev, dev_num, ret = 1;
	uint64_t		guid;
	const char		*p, *ibdev;


	root_dev_list = dev_list = ibv_get_device_list(&num_dev);
	if (!dev_list) {
		fprintf(stderr, "No HCA devices found");
		goto error_exit1;
	}

	for (i = 0; i < num_dev; i++, dev_list++) {

		if (!(ctx = ibv_open_device(*dev_list))) {
			fprintf(stderr, "failed to open device %p\n",
			    *dev_list);
			goto error_exit2;
		}

		if (ibv_query_device(ctx, &device_attr)) {
			fprintf(stderr, "failed to query device %p\n", ctx);
			goto error_exit3;
		}

		guid = ntohll(device_attr.node_guid);
		sprintf(info.ibd_node_guid_str, "%04x:%04x:%04x:%04x",
		    (unsigned)(guid >> 48) & 0xffff,
		    (unsigned)(guid >> 32) & 0xffff,
		    (unsigned)(guid >> 16) & 0xffff,
		    (unsigned)(guid >>  0) & 0xffff);

		guid = ntohll(device_attr.sys_image_guid);
		sprintf(info.ibd_sys_image_guid, "%04x:%04x:%04x:%04x",
		    (unsigned)(guid >> 48) & 0xffff,
		    (unsigned)(guid >> 32) & 0xffff,
		    (unsigned)(guid >> 16) & 0xffff,
		    (unsigned)(guid >>  0) & 0xffff);

		(void) strcpy(info.ibd_fw_ver, device_attr.fw_ver);
		info.ibd_hw_rev = device_attr.hw_ver;

		ibdev = ibv_get_device_name(*dev_list);
		p = ibdev + (strlen(ibdev)-1);
		dev_num = atoi(p);
		(void) strcpy(info.ibd_name, ibdev);

		info.ibd_boardid_index = -1;

		if (ibdev_cache_add(dev_num, &info)) {
			fprintf(stderr, "failed to add dev %d to ibdev cache\n",
			    dev_num);
			goto error_exit3;
		}
	}

	ret = 0;

	/* clean up and Return */
error_exit3:
	if (ctx)
		ibv_close_device(ctx);
error_exit2:
	if (root_dev_list)
		ibv_free_device_list(root_dev_list);
error_exit1:
	return (ret);
}

static int
uverbs_cache_init()
{
	uverbs_cache_info_t	info;
	int			dev_num, fd, i, bufsize, hca_cnt;
	char			uverbs_devpath[MAXPATHLEN];
	sol_uverbs_info_t	*uverbs_infop;
	sol_uverbs_hca_info_t	*hca_infop;
	char *buf;

	snprintf(uverbs_devpath, MAXPATHLEN, "%s/%s%d",
	    IB_OFS_DEVPATH_PREFIX, UVERBS_KERNEL_SYSFS_NAME_BASE,
		    sol_uverbs_minor_dev);

	/*
	 * using the first sol_uverbs minor node that can be opened to get
	 * all the HCA information
	 */
	if ((fd = open(uverbs_devpath, O_RDWR)) < 0) {
		fprintf(stderr, "sol_uverbs failed to open: %s\n",
		    strerror(errno));
		goto error_exit1;
	}
	
	bufsize = sizeof(sol_uverbs_info_t) + sizeof(sol_uverbs_hca_info_t) *
	    MAX_HCAS;
 
	buf = malloc(bufsize);
	memset(buf, 0, bufsize);
	uverbs_infop = (sol_uverbs_info_t *)buf;
	uverbs_infop->uverbs_hca_cnt = MAX_HCAS;

	if (ioctl(fd, UVERBS_IOCTL_GET_HCA_INFO, uverbs_infop) != 0) {
		fprintf(stderr, "sol_uverbs ioctl failed: %s\n",
		    strerror(errno));
		
		goto error_exit2;
	}

	if (uverbs_infop->uverbs_solaris_abi_version !=
	    IB_USER_VERBS_SOLARIS_ABI_VERSION) {
		fprintf(stderr, "sol_uverbs solaris_abi_version !="
		    "IB_USER_VERBS_SOLARIS_ABI_VERSION : %d\n",
		    uverbs_infop->uverbs_solaris_abi_version);
		goto error_exit2;
	}

	hca_cnt = uverbs_infop->uverbs_hca_cnt;	/* hca count returned */
	hca_infop = uverbs_infop->uverbs_hca_info;

	if (uverbs_abi_version == -1)
		uverbs_abi_version = uverbs_infop->uverbs_abi_version;

	for (i = 0; i < hca_cnt; i++, hca_infop++) {
		info.uvc_vendor_id = hca_infop->uverbs_hca_vendorid;
		info.uvc_device_id = hca_infop->uverbs_hca_deviceid;
		info.uvc_hca_instance =
		    hca_infop->uverbs_hca_driver_instance;

		snprintf(info.uvc_ibdev_hca_path, sizeof (info.uvc_ibdev_hca_path),
		    "%s/%s%d", IB_HCA_DEVPATH_PREFIX,
		    hca_infop->uverbs_hca_driver_name,
		    hca_infop->uverbs_hca_driver_instance);

		if (! strncmp(hca_infop->uverbs_hca_ibdev_name, "mlx4_", 5))
			info.uvc_ibdev_abi_version =
			    MLX4_UVERBS_MAX_ABI_VERSION;
		else
			info.uvc_ibdev_abi_version = MTHCA_UVERBS_ABI_VERSION;

		strcpy(info.uvc_ibdev_name, hca_infop->uverbs_hca_ibdev_name);

		dev_num = hca_infop->uverbs_hca_devidx;
		if (uverbs_cache_add(dev_num, &info)) {
			fprintf(stderr, "failed to add dev %d to uverbs "
			    "cache\n", dev_num);
			goto error_exit2;
		}
	}

	free(buf);
	close(fd);
	return (1);

error_exit2:
	free(buf);
	close(fd);

error_exit1:
	return(0);
}

static int
umad_cache_init()
{
	int				i, fd, minor;
	int				save_errno = 0;
	int				port_cnt, bufsize;
	char				umad_devpath[MAXPATHLEN], *buf;
	sol_umad_ioctl_info_t		*umad_infop;
	sol_umad_ioctl_port_info_t	*port_infop;

	for (minor = 0; minor < MAX_HCAS * MAX_HCA_PORTS; minor++) {
		snprintf(umad_devpath, MAXPATHLEN, "%s/%s%d",
		    IB_OFS_DEVPATH_PREFIX, UMAD_KERNEL_SYSFS_NAME_BASE,
		    minor);

		if ((fd = open(umad_devpath, O_RDWR)) > 0)
			break;

		if ((! save_errno) && (errno != ENOENT))
			save_errno = errno;
	}

	if ((minor == MAX_HCAS * MAX_HCA_PORTS) && (fd < 0)) {
		if (! save_errno)
			save_errno = errno;
		fprintf(stderr, "failed to open sol_umad: %s\n",
		    strerror(save_errno));
		return (0);
	}

	bufsize = sizeof(sol_umad_ioctl_info_t) +
	    (sizeof(sol_umad_ioctl_port_info_t) * MAX_HCAS * MAX_HCA_PORTS);
 
	buf = malloc(bufsize);
	memset(buf, 0, bufsize);
	umad_infop = (sol_umad_ioctl_info_t *)buf;
	umad_infop->umad_port_cnt = MAX_HCAS * MAX_HCA_PORTS;

	if (ioctl(fd, IB_USER_MAD_GET_PORT_INFO, umad_infop) != 0) {
		fprintf(stderr, "sol_umad ioctl failed: %s\n",
		    strerror(errno));
		
		goto error_exit;
	}

	if (umad_infop->umad_solaris_abi_version !=
	    IB_USER_MAD_SOLARIS_ABI_VERSION) {
		fprintf(stderr, "sol_umad solaris_abi_version !="
		    "IB_USER_MAD_SOLARIS_ABI_VERSION : %d\n",
		    umad_infop->umad_solaris_abi_version);
		goto error_exit;
	}

	/*
	 * set port_cnt to the number of total ports for all HCAs returned
	 */
	port_cnt = umad_infop->umad_port_cnt;
	port_infop = umad_infop->umad_port_info;

	if (umad_abi_version == -1)
		umad_abi_version = umad_infop->umad_abi_version;

	for (i = 0; i < port_cnt; i++, port_infop++) {
		if (umad_cache_add(port_infop->umad_port_idx,
		    port_infop->umad_port_num,
		    port_infop->umad_port_ibdev_name)) {
			fprintf(stderr, "failed to add dev %d to umad cache",
			    port_infop->umad_port_idx);
			goto error_exit;
		}
	}

	free(buf);
	close(fd);
	return (1);

error_exit:
	free(buf);
	close(fd);
	return (0);
}

void
initialize(void)
{
	int		fd, minor;
	char		uverbs_devpath[MAXPATHLEN];

	/*
	 * find the first sol_uverbs minor node that can be opened successfully
	 * and set sol_uverbs_mino_dev to that minor no.
	 */
	for (minor = 0; minor < MAX_HCAS; minor++) {
		snprintf(uverbs_devpath, MAXPATHLEN, "%s/%s%d",
		    IB_OFS_DEVPATH_PREFIX, UVERBS_KERNEL_SYSFS_NAME_BASE,
		    minor);

		if ((fd = open(uverbs_devpath, O_RDWR)) < 0) {
			continue;
		} else {
			sol_uverbs_drv_status = SOL_UVERBS_DRV_STATUS_LOADED;
			sol_uverbs_minor_dev = minor;
			close(fd);
			break;
		}
	}

	/*
	 * All minor nodes failed to open, so set sol_uverbs_drv_status to
	 * SOL_UVERBS_DRV_STATUS_UNLOADED to reflect that
	 */
	if (minor == MAX_HCAS && sol_uverbs_minor_dev == -1) {
		sol_uverbs_drv_status = SOL_UVERBS_DRV_STATUS_UNLOADED;
		return;
	}

	memset(&uverbs_dev_cache, 0, (sizeof (uverbs_cache_info_t) * MAX_HCAS));
	memset(&ibdev_cache, 0, (sizeof (ibdev_cache_info_t) * MAX_HCAS * 2));
	memset(&umad_dev_cache, 0,
	    (sizeof (umad_cache_info_t) * MAX_HCAS * MAX_HCA_PORTS));

	initialized = B_TRUE;
}

/*
 * Some sysfs emulation software
 */


/*
 * Check whether a path starts with prefix, and if it does, remove it
 * from the string. The prefix can also contain one %d scan argument.
 */
static int
check_path(char *path, cp_prefix_t prefix, unsigned int *arg)
{
	int	ret, pos = 0;

	switch (prefix) {
		case CP_SOL_UVERBS:
			ret = sscanf(path, "uverbs%d%n/", arg,
			    &pos);
			break;
		case CP_DEVICE:
			ret = sscanf(path, "device%n/", &pos);
			break;
		case CP_D:
			ret = sscanf(path, "%d%n/", arg, &pos);
			break;
		case CP_GIDS:
			ret = sscanf(path, "gids%n/", &pos);
			break;
		case CP_PKEYS:
			ret = sscanf(path, "pkeys%n/", &pos);
			break;
		case CP_MTHCA:
			ret = sscanf(path, "mthca%d%n/", arg, &pos);
			break;
		case CP_MLX4:
			ret = sscanf(path, "mlx4_%d%n/", arg, &pos);
			break;
		case CP_PORTS:
			ret = sscanf(path, "ports%n/", &pos);
			break;
		case CP_UMAD:
			ret = sscanf(path, "umad%d%n/", arg, &pos);
			break;
		case CP_SLASH:
			ret = sscanf(path, "%n/", &pos);
			break;
		case CP_SYS:
			ret = sscanf(path, "sys%n/", &pos);
			break;
		case CP_CLASS:
			ret = sscanf(path, "class%n/", &pos);
			break;
		case CP_INFINIBAND_VERBS:
			ret = sscanf(path, "infiniband_verbs%n/", &pos);
			break;
		case CP_INFINIBAND:
			ret = sscanf(path, "infiniband%n/", &pos);
			break;
		case CP_INFINIBAND_MAD:
			ret = sscanf(path, "infiniband_mad%n/", &pos);
			break;
		case CP_MISC:
			ret = sscanf(path, "misc%n/", &pos);
			break;
		case CP_RDMA_CM:
			ret = sscanf(path, "rdma_cm%n/", &pos);
			break;
		default:
			/* Unkown prefix */
			return (0);
	}

	if (path[pos] == '/') {
		/* Some requests have several consecutive slashes. */
		while (path[pos] == '/')
			pos ++;

		memmove(path, &path[pos], strlen(path)-pos+1);
		return (1);
	}

	return (0);
}

static ibdev_cache_info_t *
get_device_info(const char *devname)
{
	ibdev_cache_info_t 	*info;
	const char		*p = devname;
	int			dev_num;

	if (pthread_mutex_lock(&ibdev_cache_mutex) != 0) {
		fprintf(stderr, "failed: to acquire ibdev_cache_mutex %s\n",
		    strerror(errno));
		return (NULL);
	}

	if (!ibdev_cache_initialized) {
		if (ibdev_cache_init()) {
			(void) pthread_mutex_unlock(&ibdev_cache_mutex);
			fprintf(stderr, "failed to init ibdev_cache\n");
			return (NULL);
		} else {
			ibdev_cache_initialized = B_TRUE;
		}
	}
	(void) pthread_mutex_unlock(&ibdev_cache_mutex);

	p = p+(strlen(p)-1);
	dev_num = atoi(p);

	if (dev_num >= MAX_HCAS) {
		fprintf(stderr, "Invalid device %s\n", devname);
		return (NULL);
	}

	if (strncmp(devname, "mlx4", 4) == 0) {
		if (ibdev_cache[MLX4][dev_num].ibd_valid)
			info = &(ibdev_cache[MLX4][dev_num]);
		else
			info = NULL;
	} else {
		if (ibdev_cache[MTHCA][dev_num].ibd_valid)
			info = &(ibdev_cache[MTHCA][dev_num]);
		else
			info = NULL;
	}

	return (info);
}

/*
 * Get the IB user verbs port info attributes for the specified device/port.
 * If the address of a gid pointer is passed for "gid_table", the memory
 * will be allocated and the ports gid table and returned as well. The caller
 * must free this memory on successful completion.  If the address of a
 * pkey pointer is passed for "pkey_table", the memory will be allocated
 * and the ports pkey table returned as well.  The caller must free this
 * memory on successful completion.
 */
static int
get_port_info(const char *devname, uint8_t port_num,
    struct ibv_port_attr *port_attr, union ibv_gid **gid_table,
    uint16_t **pkey_table)
{
	struct ibv_device 	**root_dev_list, **dev_list = NULL;
	struct ibv_context 	*ctx = NULL;
	union ibv_gid 		*gids = NULL;
	uint16_t		*pkeys = NULL;
	int 			i, num_dev, rv, ret = 1;

	root_dev_list = dev_list = ibv_get_device_list(&num_dev);
	if (!dev_list) {
		fprintf(stderr, "No HCA devices found\n");
		goto error_exit1;
	}

	for (i = 0; i < num_dev; i++, dev_list++) {
		if (strcmp(ibv_get_device_name(*dev_list), devname) == 0) {
			break;
		}
	}

	if (i == num_dev) {
		fprintf(stderr, "failed to find %s\n", devname);
		goto error_exit2;
	}

	if (!(ctx = ibv_open_device(*dev_list))) {
		fprintf(stderr, "failed to open device %p\n", *dev_list);
		goto error_exit2;
	}

	if (ibv_query_port(ctx, port_num, port_attr)) {
		fprintf(stderr, "failed to query dev %p, port %d\n",
		    ctx, port_num);
		goto error_exit3;
	}

	if (gid_table) {
		*gid_table = NULL;
		gids = malloc(sizeof (union ibv_gid) * port_attr->gid_tbl_len);
		if (!gids)
			goto error_exit3;
		/*
		 * set high bit of port_num, and try get all gids in one go.
		 */
		port_num |= 0x80;
		rv = ibv_query_gid(ctx, port_num, port_attr->gid_tbl_len, gids);

		if (rv != 0) {
			/*
			 * Quering all gids didn't work try one at a time.
			 */
			port_num &= 0x7f;

			for (i = 0; i < port_attr->gid_tbl_len; i++) {
				if (ibv_query_gid(ctx, port_num, i, &gids[i]))
					goto error_exit4;
			}
		}
		*gid_table = gids;
		gids = NULL;
	}

	if (pkey_table) {
		*pkey_table = NULL;
		pkeys = malloc(sizeof (uint16_t) * port_attr->pkey_tbl_len);
		if (!pkeys)
			goto error_exit4;

		port_num |= 0x80;

		rv = ibv_query_pkey(ctx, port_num, port_attr->pkey_tbl_len,
		    pkeys);

		if (rv != 0) {
			/*
			 * Quering all gids didn't work try one at a time.
			 */
			port_num &= 0x7f;

			for (i = 0; i < port_attr->pkey_tbl_len; i++) {
				if (ibv_query_pkey(ctx, port_num, i, &pkeys[i]))
					goto error_exit5;
			}
		}
		*pkey_table = pkeys;
		pkeys = NULL;
	}

	ret = 0;

	/*
	 * clean up and Return
	 */
error_exit5:
	if (pkeys)
		free(pkeys);
error_exit4:
	if (gids)
		free(gids);
error_exit3:
	if (ctx)
		ibv_close_device(ctx);
error_exit2:
	if (root_dev_list)
		ibv_free_device_list(root_dev_list);
error_exit1:
	return (ret);
}

/*
 * In Solaris environments, the underlying hardware driver is opened to
 * perform the memory mapping operations of kernel allocated memory
 * into the users address space.
 */
int
ibv_open_mmap_driver(char *dev_name)
{
	int			fd;
#ifndef _LP64
	int			tmpfd;
#endif
	int			uverbs_indx;

	/*
	 * Map the user verbs device (uverbs) to the associated 
	 * hca device. 
	 */
	uverbs_indx = strtol(dev_name + strlen(UVERBS_KERNEL_SYSFS_NAME_BASE),
	    NULL, 0);
	if (uverbs_indx >= MAX_HCAS) {
		fprintf(stderr, "Invalid device %s\n", dev_name);
		goto err_dev;
	}

	if (!uverbs_dev_cache[uverbs_indx].uvc_valid) {
		fprintf(stderr, "Invalid Device %s\n", dev_name);
		goto err_dev;
	}

	fd = open(uverbs_dev_cache[uverbs_indx].uvc_ibdev_hca_path, O_RDWR);
	if (fd < 0) {
		goto err_dev;
	}

#ifndef _LP64
	/*
	 * libc can't handle fd's greater than 255,  in order to
	 * ensure that these values remain available make fd > 255.
	 * Note: not needed for LP64
	 */
	tmpfd = fcntl(fd, F_DUPFD, 256);
	if (tmpfd >=  0) {
		(void) close(fd);
		fd = tmpfd;
	}
#endif  /* _LP64 */

	if (fcntl(fd, F_SETFD, FD_CLOEXEC) < 0) {
		fprintf(stderr, "FD_CLOEXEC failed: %s\n", strerror(errno));
		goto err_close;
	}
	return (fd);

err_close:
	close(fd);
err_dev:
	return (-1);
}

static int
infiniband_verbs(char *path, char *buf, size_t size)
{
	unsigned int		device_num;
	int 			len = -1;
	uverbs_cache_info_t	*info_p;

	if (pthread_mutex_lock(&uverbs_cache_mutex) != 0) {
		fprintf(stderr, "failed: to acquire uverbs_cache_mutex %s\n",
		    strerror(errno));
		goto exit;
	}

	if (!uverbs_cache_initialized) {
		if (uverbs_cache_init())
			uverbs_cache_initialized = B_TRUE;
		else
			goto exit;
	}
	(void) pthread_mutex_unlock(&uverbs_cache_mutex);

	if (check_path(path, CP_SOL_UVERBS, &device_num)) {

		if (device_num >= MAX_HCAS) {
			fprintf(stderr, "Invalid path%s\n", path);
			goto exit;
		}

		if (!uverbs_dev_cache[device_num].uvc_valid) {
			goto exit;
		}

		info_p = &uverbs_dev_cache[device_num];

		if (check_path(path, CP_DEVICE, NULL)) {
			/*
			 * Under Linux, this is a link to the PCI device entry
			 * in /sys/devices/pci...../....
			 */
			if (strcmp(path, "vendor") == 0) {
				len = 1 + sprintf(buf, "0x%x",
				    info_p->uvc_vendor_id);
			} else if (strcmp(path, "device") == 0) {
				len = 1 + sprintf(buf, "0x%x",
				    info_p->uvc_device_id);
			}
		} else if (strcmp(path, "ibdev") == 0) {
			len = 1 + sprintf(buf, "%s",
			    info_p->uvc_ibdev_name);
		} else if (strcmp(path, "abi_version") == 0) {
			len = 1 + sprintf(buf, "%d",
			    info_p->uvc_ibdev_abi_version);
		}
	} else if (strcmp(path, "abi_version") == 0) {

		if (uverbs_abi_version == -1) {
			fprintf(stderr, "UVerbs ABI Version invalid\n");

			goto exit;
		}

		len = 1 + sprintf(buf, "%d", uverbs_abi_version); 
	} else {
		fprintf(stderr, "Unsupported read: %s\n", path);
	}
exit:
	return (len);
}

static int
infiniband_ports(char *path, char *buf, size_t size, char *dev_name)
{
	int 			len = -1;
	unsigned int		port_num;
	unsigned int		gid_num;
	union ibv_gid		*gids;
	uint64_t		subnet_prefix;
	uint64_t		interface_id;
	uint16_t		*pkeys;
	unsigned int		pkey_num;
	struct ibv_port_attr	port_attr;
	float			rate;

	if (!(check_path(path, CP_D, &port_num)))
		goto exit;

	if (check_path(path, CP_GIDS, NULL)) {
		if (get_port_info(dev_name, port_num, &port_attr, &gids, NULL))
				goto exit;

		gid_num = atoi(path);

		if (gid_num <  port_attr.gid_tbl_len) {

			subnet_prefix =
			    htonll(gids[gid_num].global.subnet_prefix);
			interface_id =
			    htonll(gids[gid_num].global.interface_id);
			len = 1 + sprintf(buf,
			    "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x",
			    (unsigned)(subnet_prefix >>  48) & 0xffff,
			    (unsigned)(subnet_prefix >>  32) & 0xffff,
			    (unsigned)(subnet_prefix >>  16) & 0xffff,
			    (unsigned)(subnet_prefix >>   0) & 0xffff,
			    (unsigned)(interface_id  >>  48) & 0xffff,
			    (unsigned)(interface_id  >>  32) & 0xffff,
			    (unsigned)(interface_id  >>  16) & 0xffff,
			    (unsigned)(interface_id  >>   0) & 0xffff);
		}
		if (gids)
			free(gids);

	} else if (check_path(path, CP_PKEYS, NULL)) {
		if (get_port_info(dev_name, port_num, &port_attr, NULL, &pkeys))
				goto exit;

		pkey_num = atoi(path);
		if (pkey_num <  port_attr.pkey_tbl_len)
			len = 1 + sprintf(buf, "0x%04x", pkeys[pkey_num]);

		if (pkeys)
			free(pkeys);
	} else {

		if (get_port_info(dev_name, port_num, &port_attr, NULL, NULL))
				goto exit;

		if (strcmp(path, "lid_mask_count") == 0) {
			len = 1 + sprintf(buf, "%d", port_attr.lmc);
		} else if (strcmp(path, "sm_lid") == 0) {
			len = 1 + sprintf(buf, "0x%x", port_attr.sm_lid);
		} else if (strcmp(path, "sm_sl") == 0) {
			len = 1 + sprintf(buf, "%d", port_attr.sm_sl);
		} else if (strcmp(path, "lid") == 0) {
			len = 1 + sprintf(buf, "0x%x", port_attr.lid);
		} else if (strcmp(path, "state") == 0) {
			switch (port_attr.state) {
				case IBV_PORT_NOP:
					len = 1 + sprintf(buf, "%d: NOP",
					    port_attr.state);
					break;
				case IBV_PORT_DOWN:
					len = 1 + sprintf(buf, "%d: DOWN",
					    port_attr.state);
					break;
				case IBV_PORT_INIT:
					len = 1 + sprintf(buf, "%d: INIT",
					    port_attr.state);
					break;
				case IBV_PORT_ARMED:
					len = 1 + sprintf(buf, "%d: ARMED",
					    port_attr.state);
					break;
				case IBV_PORT_ACTIVE:
					len = 1 + sprintf(buf, "%d: ACTIVE",
					    port_attr.state);
					break;
				case IBV_PORT_ACTIVE_DEFER:
					len = 1 + sprintf(buf,
					    "%d: ACTIVE_DEFER",
					    port_attr.state);
					break;
				default:
					len = 1 + sprintf(buf, "%d: INVALID",
					    port_attr.state);
					break;
			}
		} else if (strcmp(path, "phys_state") == 0) {
			switch (port_attr.phys_state) {
				case 1:
					len = 1 + sprintf(buf, "%d: Sleep",
					    port_attr.phys_state);
					break;
				case 2:
					len = 1 + sprintf(buf, "%d: Polling",
					    port_attr.phys_state);
					break;
				case 3:
					len = 1 + sprintf(buf, "%d: Disabled",
					    port_attr.phys_state);
					break;
				case 4:
					len = 1 + sprintf(buf,
					    "%d: PortConfigurationTraining",
					    port_attr.phys_state);
					break;
				case 5:
					len = 1 + sprintf(buf, "%d: LinkUp",
					    port_attr.phys_state);
					break;
				case 6:
					len = 1 + sprintf(buf,
					    "%d: LinkErrorRecovery",
					    port_attr.phys_state);
					break;
				case 7:
					len = 1 + sprintf(buf,
					    "%d: Phy Test",
					    port_attr.phys_state);
					break;
				default:
					len = 1 + sprintf(buf, "%d: <unknown>",
					    port_attr.phys_state);
					break;
			}
		} else if (strcmp(path, "rate") == 0) {
			/* rate = speed * width */
			switch (port_attr.active_speed) {
			case 1:
				rate = 2.5;
				break;
			case 2:
				rate = 5;
				break;
			case 4:
				rate = 10;
				break;
			default:
				rate = 0;
			}
			switch (port_attr.active_width) {
			case 1:
				break;
			case 2:
				rate = 4 * rate;
				break;
			case 4:
				rate = 8 * rate;
				break;
			case 8:
				rate = 12 * rate;
				break;
			default:
				rate = 0;
			}
			len = 1 + sprintf(buf, "%f", rate);
		} else if (strcmp(path, "cap_mask") == 0) {
			len = 1 + sprintf(buf, "0x%08x",
			    port_attr.port_cap_flags);
		}
	}
exit:
	return (len);
}


/*
 * This function passes the HW Part number string obtained from driver
 * IOCTL. The memory for "hca_hwpn" argument has to be passed by the
 * caller and has to be at least 64 bytes in size.
 */
static int
get_hca_hwpn_str(char *ibd_name, int fd, char *hca_hwpn)
{
	hermon_flash_init_ioctl_t	hermon_flash_info;
	tavor_flash_init_ioctl_t	tavor_flash_info;
	int				rc;

	if (strncmp(ibd_name, "mthca", 5) == 0) {
		if ((rc = ioctl(fd, TAVOR_IOCTL_FLASH_INIT,
		    &tavor_flash_info)) != 0)
			return (rc);
		strncpy(hca_hwpn, tavor_flash_info.tf_hwpn, 64);
	} else {
		if ((rc = ioctl(fd, HERMON_IOCTL_FLASH_INIT,
		    &hermon_flash_info)) != 0)
			return (rc);
		strncpy(hca_hwpn, hermon_flash_info.af_hwpn, 64);
	}
	return (0);
}

static void
init_boardid_index(ibdev_cache_info_t *ibd_info)
{
	int	i;
	int	fd;
	char	hca_hwpn[64];
	char	*hwpnp;


	if (pthread_mutex_lock(&uverbs_cache_mutex) != 0) {
		fprintf(stderr, "failed: to acquire "
		    "uverbs_cache_mutex %s\n",
		    strerror(errno));
		goto boardid_err;
	}
	if (!uverbs_cache_initialized) {
		uverbs_cache_init();
		uverbs_cache_initialized = B_TRUE;
	}
	(void) pthread_mutex_unlock(&uverbs_cache_mutex);

	for (i = 0; i < MAX_HCAS; i++) {
		if (uverbs_dev_cache[i].uvc_valid &&
		    strcmp(uverbs_dev_cache[i].uvc_ibdev_name,
		    ibd_info->ibd_name) == 0) {
			break;
		}
	}

	if (i == MAX_HCAS) {
		fprintf(stderr, "failed to find uverbs_dev for %s\n",
		    ibd_info->ibd_name);
		goto boardid_err;
	}

	fd = open(uverbs_dev_cache[i].uvc_ibdev_hca_path, O_RDWR);
	if (fd < 0) {
		goto boardid_err;
	}

	if (get_hca_hwpn_str(ibd_info->ibd_name, fd, hca_hwpn)) {
		close(fd);
		goto boardid_err;
	}
	close(fd);
	if ((hwpnp = strchr(hca_hwpn, ' ')) != NULL)
		*hwpnp = '\0';

	/*
	 * Find part number, set the boardid_index,
	 * Skip index 0, as it is for failure "unknown"
	 * case.
	 */
	for (i = 1; i < MLX_MAX_ID; i++) {
		if (strcmp((const char *)hca_hwpn,
		    mlx_mdr[i].mlx_pn) == 0) {

			/* Set boardid_index */
			ibd_info->ibd_boardid_index = i;
			return;
		}
	}

boardid_err:
	/* Failure case, default to "unknown" */
	ibd_info->ibd_boardid_index = 0;
}

static int
infiniband(char *path, char *buf, size_t size)
{
	int			len = -1;
	unsigned int		device_num;
	char			dev_name[10];
	ibdev_cache_info_t	*info;

	memset(dev_name, 0, 10);

	if (check_path(path, CP_MTHCA, &device_num)) {
		sprintf(dev_name, "mthca%d", device_num);
	} else if (check_path(path, CP_MLX4, &device_num)) {
		sprintf(dev_name, "mlx4_%d", device_num);
	} else {
		goto exit;
	}

	if (check_path(path, CP_PORTS, NULL)) {
		len = infiniband_ports(path, buf, size, dev_name);
	} else if (strcmp(path, "node_type") == 0) {
		len = 1 + sprintf(buf, "%d", IBV_NODE_CA);
	} else {
		if (!(info = get_device_info(dev_name)))
			goto exit;

		if (strcmp(path, "node_guid") == 0) {
			len = 1 + sprintf(buf, "%s", info->ibd_node_guid_str);
		} else if (strcmp(path, "sys_image_guid") == 0) {
			len = 1 + sprintf(buf, "%s", info->ibd_sys_image_guid);
		} else if (strcmp(path, "fw_ver") == 0) {
			len = 1 + sprintf(buf, "%s", info->ibd_fw_ver);
		} else if (strcmp(path, "hw_rev") == 0) {
			len = 1 + sprintf(buf, "%d", info->ibd_hw_rev);
		} else if (strcmp(path, "hca_type") == 0) {
			if (!(strncmp(info->ibd_name, "mlx4", 4)))
				len = 1 + sprintf(buf, "%d", 0);
			else
				len = 1 + sprintf(buf, "unavailable");
		} else if (strcmp(path, "board_id") == 0) {
			if (info->ibd_boardid_index == -1)
				init_boardid_index(info);

			len = 1 + sprintf(buf, "%s",
			    mlx_mdr[info->ibd_boardid_index].mlx_psid);
		}
	}
exit:
	return (len);
}

static int
infiniband_mad(char *path, char *buf, size_t size)
{
	int		len = -1;
	unsigned int	dev_num;

	if (pthread_mutex_lock(&umad_cache_mutex) != 0) {
		fprintf(stderr, "failed: to acquire umad_cache_mutex %s\n",
		    strerror(errno));
		goto exit;
	}
	if (!umad_cache_initialized) {
		if (umad_cache_init())
			umad_cache_initialized = B_TRUE;
		else
			goto exit;
	}
	(void) pthread_mutex_unlock(&umad_cache_mutex);

	if (check_path(path, CP_UMAD, &dev_num)) {
		if (dev_num >= MAX_HCAS * MAX_HCA_PORTS) {
			fprintf(stderr, "Invalid Path: %s\n", path);
			goto exit;
		}
		if (!umad_dev_cache[dev_num].umc_valid) {
			goto exit;
		}
		if (strcmp(path, "ibdev") == 0) {
			len = strlcpy(buf, umad_dev_cache[dev_num].umc_ib_dev,
			    size) + 1;
		} else if (strcmp(path, "port") == 0) {
			len = 1 + sprintf(buf, "%d",
			    umad_dev_cache[dev_num].umc_port);
		}
	} else if (strcmp(path, "abi_version") == 0) {
		if (umad_abi_version == -1) {
			fprintf(stderr, "UMAD ABI Version invalid\n");
			goto exit;
		}
		len =
		    1 + sprintf(buf, "%d", umad_abi_version);
	}
exit:
	return (len);
}

/*
 * Return -1 on error, or the length of the data (buf) on success.
 */
int
sol_read_sysfs_file(char *path, char *buf, size_t size)
{
	int 			len = -1;

	if (!initialized) {
		if (pthread_once(&oneTimeInit, initialize)) {
			fprintf(stderr, "failed to initialize: %s\n",
			    strerror(errno));
			goto exit;
		}
		if (!initialized)
			/*
			 * There was a problem in initialize()
			 */
			goto exit;
	}

	if (!check_path(path, CP_SLASH, NULL))
		goto exit;

	if (!check_path(path, CP_SYS, NULL))
		goto exit;

	if (!check_path(path, CP_CLASS, NULL))
		goto exit;

	if (check_path(path, CP_INFINIBAND_VERBS, NULL)) {
		len = infiniband_verbs(path, buf, size);
	} else if (check_path(path, CP_INFINIBAND, NULL)) {
		len = infiniband(path, buf, size);
	} else if (check_path(path, CP_INFINIBAND_MAD, NULL)) {
		len = infiniband_mad(path, buf, size);
	} else if (check_path(path, CP_MISC, NULL)) {
		if (check_path(path, CP_RDMA_CM, NULL)) {
			if (strcmp(path, "abi_version") == 0) {
				len = 1 + sprintf(buf, "%d",
				    RDMA_USER_CM_MAX_ABI_VERSION);
			}
		}
	}
exit:
	return (len);
}


int
sol_get_cpu_info(sol_cpu_info_t *info)
{
	kstat_t		*ksp;
	kstat_named_t	*knp;

	/*
	 * We should check all CPUS, and make sure they
	 * are all the same or return an array of structs.
	 */
	ksp = kstat_lookup(kc, "cpu_info", 0, NULL);
	if (ksp == NULL)
		return (-1);

	if (kstat_read(kc, ksp, NULL) == -1)
		return (-1);

	knp = (kstat_named_t *)kstat_data_lookup(ksp, "brand");
	if (knp == NULL)
		return (-1);

	(void) strlcpy(info->cpu_name, knp->value.str.addr.ptr,
	    knp->value.str.len);

	knp = (kstat_named_t *)kstat_data_lookup(ksp, "clock_MHz");
	if (knp == NULL)
		return -1;

	info->cpu_mhz = knp->value.ui64;	
	info->cpu_num = sysconf(_SC_NPROCESSORS_ONLN);
	return (0);
}
#endif
