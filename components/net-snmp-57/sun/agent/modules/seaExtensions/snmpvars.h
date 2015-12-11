/*
 * Copyright (c) 2003, 2011, Oracle and/or its affiliates. All rights reserved.
 *
 * U.S. Government Rights - Commercial software. Government users are subject
 * to the Sun Microsystems, Inc. standard license agreement and applicable
 * provisions of the FAR and its supplements.
 *
 *
 * This distribution may include materials developed by third parties. Sun,
 * Sun Microsystems, the Sun logo and Solaris are trademarks or registered
 * trademarks of Sun Microsystems, Inc. in the U.S. and other countries.
 *
 */

#if !defined(lint) && !defined(NOID)
#pragma ident	"@(#)snmpvars.h	2.19	01/07/06 SMI"
#endif

/****************************************************************************
 *     Copyright (c) 1988  Epilogue Technology Corporation
 *     All rights reserved.
 *
 *     This is unpublished proprietary source code of Epilogue Technology
 *     Corporation.
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 ****************************************************************************/

/* $Header: /net/bigblock.east/files5/SMA_CVS/sun/agent/modules/seaExtensions/snmpvars.h,v 1.3 2003/08/12 21:14:54 rr144420 Exp $	*/
/*
 * $Log: snmpvars.h,v $
 * Revision 1.3  2003/08/12 21:14:54  rr144420
 * 4895376 - correct Sun copyright statements. Cannot use (c), and must use Copyright Copyright in makefiles
 *
 * Revision 1.2  2003/08/08 15:39:54  pcarroll
 * 4895376 - The copyright statement in the demo* codes do not look right
 *
 * Revision 1.1  2003/07/28 17:59:23  dporter
 * 4892877 - Need SMA Agent to implement sun extensions found in SEA sun.mib
 *
 * 
 *    Rev 2.0   31 Mar 1990 15:34:28
 * Initial revision.
 * 
 *    Rev 1.1   26 Aug 1989 16:50:34
 * Moved ipForwarding into the ip_stats structure.
 * 
 *    Rev 1.0   14 Nov 1988 10:27:16
 * Initial revision.
*/

#if (!defined(snmpvars_inc))
#define	snmpvars_inc

#if (!defined(asn1_inc))
#include <asn1.h>
#endif

/**********************************************************************
 *
 * Define the various SNMP management variables used in this system.
 *
 * This file should closely match snmpvars.c
 *
 **********************************************************************/

#define	SNMP_COMM_MAX	32
#define MAX_SYSDESCR	256
#define MAX_SYSCONTACT	256
#define MAX_SYSNAME	256
#define MAX_SYSLOCATION	256
#define MAX_SYSNAME	256
#define MAX_KERN_FILE	256
#define MAX_NEW_DEVICE  10

/* If you change the following definition, you also need to	*/
/* change the sscanf format in setup.c accordingly.		*/
#define	MAX_HOST_NAME_SZ	64

/* If you redefine MAX_TRAPS_TO the scanf in read_con.c needs to	*/
/* be changed accordingly.						*/
#define	MAX_TRAPS_TO	5
extern int	trap_2_cnt;		/* How many entries follow */
extern u_long	traplist[MAX_TRAPS_TO];	/* IP addresses where to send traps */

/* If you redefine MAX_MGR_SCANF the scanf in read_con.c needs to	*/
/* be changed accordingly.						*/
#define	MAX_MGR_SCANF	5
#define	MAX_MGR		32
extern int	mgr_cnt;		/* How many entries follow */
extern u_long	mgr_list[MAX_MGR];	/* IP addresses for valid managers */

#if 0
extern	int		if_number;		/* ifNumber		*/
#endif

extern	char		snmp_sysgrp_read_community[];
extern	char		snmp_sysgrp_write_community[];
extern	char		snmp_fullmib_read_community[];
extern	char		snmp_fullmib_write_community[];
extern	char		snmp_trap_community[];
extern	char		snmp_auth_traps;
extern	OIDC_T		snmp_product_id[];
extern	int		snmp_product_id_count;
extern	OBJ_ID_T	snmp_sysObjectID;
extern	unsigned char	snmp_local_ip_address[];
extern	char		snmp_sysDescr[];
extern	char		snmp_sysContact[];
extern	char		snmp_sysName[];
extern	char		snmp_sysLocation[];
extern	struct timeval	boot_at;
extern	char		kernel_file[];
extern	int		trap_sd;
extern	int		cache_lifetime;
extern	int		snmp_socket;	/* Socket used to send traps and */
					/* send/receive SNMP queries,	 */
					/* usually UDP port 161		 */

struct new_devicess {
   char name[32];
   int  type;
   long speed;
} new_devices[MAX_NEW_DEVICE];

int new_device_pointer;
 
#endif	/* snmpvars_inc */
