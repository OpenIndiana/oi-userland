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



/*
 * nfsstat: Network File System statistics for client RPC
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <kvm.h>
#include <kstat.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/t_lock.h>
#include <sys/tiuser.h>
#include <sys/statvfs.h>
#include <sys/mntent.h>
#include <sys/mnttab.h>
#include <sys/sysmacros.h>
#include <sys/mkdev.h>
#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/auth.h>
#include <rpc/clnt.h>
#include <nfs/nfs.h>
#include <nfs/nfs_clnt.h>

static kstat_ctl_t *kc = NULL;		/* libkstat cookie */
static kstat_t *rpc_clts_client_kstat;
static kstat_t *rpc_cots_client_kstat;

static void getstats(void);
static void setup();
static void clear_setup_data();
static  void    fail(int, char *, ...);

static kid_t safe_kstat_read(kstat_ctl_t *, kstat_t *, void *);

#define	MAX_COLUMNS	80

static int field_width = 0;
static int ncolumns;

int cflag = 0;		/* client stats */
int rflag = 0;		/* rpc stats */
int zflag = 0;		/* zero stats after printing */

static void stat_width(kstat_t *);

static void
getstats(void)
{

	if (rpc_clts_client_kstat != NULL) {
		safe_kstat_read(kc, rpc_clts_client_kstat, NULL);
		stat_width(rpc_clts_client_kstat);
	}
	if (rpc_cots_client_kstat != NULL) {
		safe_kstat_read(kc, rpc_cots_client_kstat, NULL);
		stat_width(rpc_cots_client_kstat);
	}
}



static void
clear_setup_data()
{
	/*
	 * Verify and close the kstat control structure 
	 */
	if (kc)
		kstat_close(kc);

	/*
	 * Set all the related variables to null
	 */
	kc = (kstat_ctl_t *)NULL;
	rpc_clts_client_kstat = (kstat_t *)NULL;
	rpc_cots_client_kstat = (kstat_t *)NULL;
}

	
static void
setup()
{
	/* Initialize kstat control structures */
	if ((kc = kstat_open()) == NULL)
		fail(1, "kstat_open(): can't open /dev/kstat");

	/* Find a kstat by name */
	rpc_clts_client_kstat = kstat_lookup(kc, "unix", 0, "rpc_clts_client");
	rpc_cots_client_kstat = kstat_lookup(kc, "unix", 0, "rpc_cots_client");
}

static void
stat_width(kstat_t *req)
{
	int i, nreq, len;
	char fixlen[128];
	kstat_named_t *knp;

	knp = KSTAT_NAMED_PTR(req);
	nreq = req->ks_ndata;

	for (i = 0; i < nreq; i++) {
		len = strlen(knp[i].name) + 1;
		if (field_width < len)
			field_width = len;
		(void) sprintf(fixlen, "%lu", knp[i].value.ul);
		len = strlen(fixlen) + 1;
		if (field_width < len)
			field_width = len;
	}
}

/*
 * Get Client RPC data
 *   This function is called by Health Monitoring Module
 */
krgetclientrpcdetail(double *calls, int *badcalls, int *retrans, int *badxids, int *timeouts, int *newcreds, int *badverfs, int *timers, int *nomem, int *cantsend) 
{
        int i, j, nreq;
        char fixlen[128];
	char buf[1024];
        kstat_named_t *knp;
	cflag++;
	rflag++;

        buf[0]= '\0';

	setup();

	getstats();

	ncolumns = (MAX_COLUMNS - 1) / field_width;

	/* Kstat lookup client rpc info */
	if (rpc_clts_client_kstat != NULL) {

		knp = KSTAT_NAMED_PTR(rpc_clts_client_kstat);
        	nreq = rpc_clts_client_kstat->ks_ndata;

        	for (i = 0; i < nreq; i += ncolumns) {
               	 	/* Don't print heading */
               	 	/*
               		for (j = i; j < MIN(i + ncolumns, nreq); j++) {
             	           printf("%-*s", field_width, knp[j].name);
               	 	}
                	printf("\n");
                	*/
                	for (j = i; j < MIN(i + ncolumns, nreq); j++) {
#if (defined SOLARIS2_5 || defined SOLARIS2_6)
                        	(void) sprintf(fixlen, "%lu ", knp[j].value.ul);
#else
                                (void) sprintf(fixlen, "%llu ", knp[j].value.ui64);
#endif

                        	strcat(buf, fixlen);
                	}
        	}

	}
	*calls = atof(strtok(buf, " "));
	*badcalls = atoi (strtok(NULL, " "));
	*retrans = atoi (strtok(NULL, " "));
	*badxids = atoi (strtok(NULL, " "));
	*timeouts = atoi (strtok(NULL, " "));
	*newcreds = atoi (strtok(NULL, " "));
	*badverfs = atoi (strtok(NULL, " "));
	*timers = atoi (strtok(NULL, " "));
	*nomem = atoi (strtok(NULL, " "));
	*cantsend = atoi (strtok(NULL, " "));

	/*
	 * The following function closes the kstat control structure
	 *  and sets the related variables to NULL.
	 */
	clear_setup_data();

	return (0);
}

#define	MIN(a, b)	((a) < (b) ? (a) : (b))

static void
fail(int do_perror, char *message, ...)
{
	va_list args;

	va_start(args, message);
	fprintf(stderr, "nfsstat: ");
	vfprintf(stderr, message, args);
	va_end(args);
	if (do_perror)
		fprintf(stderr, ": %s", strerror(errno));
	fprintf(stderr, "\n");
	exit(1);
}

kid_t
safe_kstat_read(kstat_ctl_t *kc, kstat_t *ksp, void *data)
{
	kid_t kstat_chain_id = kstat_read(kc, ksp, data);

	if (kstat_chain_id == -1)
		fail(1, "kstat_read(%x, '%s') failed", kc, ksp->ks_name);
	return (kstat_chain_id);
}


