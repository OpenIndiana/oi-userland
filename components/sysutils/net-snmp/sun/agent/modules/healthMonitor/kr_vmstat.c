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



#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <unistd.h>
#include <memory.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <kstat.h>

#include <sys/types.h>
#include <sys/time.h>
#include <sys/sysinfo.h>
#include <sys/vfs.h>
#include <sys/dnlc.h>
#include <sys/vmmeter.h>

static  kstat_ctl_t     *kc;            /* libkstat cookie */
static  int             ncpus;
static  kstat_t         **cpu_stat_list = NULL;
static  kstat_t         *sysinfo_ksp, *vminfo_ksp, *system_misc_ksp;
static  kstat_named_t   *deficit_knp, *lbolt_knp, *clk_intr_knp;

static  void    fail(int, char *, ...);
static  void    safe_zalloc(void **, int, int);

typedef struct {
        cpu_sysinfo_t   cpu_sysinfo;
        cpu_vminfo_t    cpu_vminfo;
        sysinfo_t       sysinfo;
        vminfo_t        vminfo;
        long            deficit;
} all_stat_t;

static	all_stat_t	s_new, s_old;

#define	denom(x) ((x) ? (x) : 1)
#define	DELTA(x) (s_new.x - s_old.x)

static  int     hz;
static  int     pagesize;
static  int     etime;

static	void	all_stat_init(void);
static	int	all_stat_load(void);
static	void	safe_kstat_read(kstat_ctl_t *, kstat_t *, void *);
static	kstat_t	*safe_kstat_lookup(kstat_ctl_t *, char *, int, char *);
static	void	*safe_kstat_data_lookup(kstat_t *, char *);

static int fr_time = 0;
/* Get CPU Process details from kstats- 
 * Number of processes in runqueue, 
 * waiting and swapqueue 
 */
int 
krgetprocdetail(int *runque, int *waiting, int *swapque)
{
	ulong_t updates;

	if(!fr_time) {
	/* Initialize a kstat control structure */
	if ((kc = kstat_open()) == NULL)
		fail(1, "kstat_open(): can't open /dev/kstat");
	all_stat_init();
	fr_time = 1;
	}

	/* update the kstat header chain or load all_stat structure */ 
	while (kstat_chain_update(kc) || all_stat_load()) {
		all_stat_init();
	}

	updates = denom(DELTA(sysinfo.updates));

#define ADJ(n)  ((adj <= 0) ? n : (adj >= n) ? 1 : n - adj)
#define adjprintf(fmt, n, val)  adj -= (n + 1) - printf(fmt, ADJ(n), val)

        *runque =  DELTA(sysinfo.runque) / updates;
        *waiting = DELTA(sysinfo.waiting) / updates;
        *swapque = DELTA(sysinfo.swpque) / updates;

	/*
	 * Close the kstat control structure and set it to null.
	 */
/*	kstat_close(kc);
	kc = (kstat_ctl_t *)NULL;*/

	return(0);

}

/* Get RAm details from kstats */
int 
krgetramdetail(int *handspread, int *scan)
{
	int i;
	int pages, handspreadpages;

	pagesize = sysconf(_SC_PAGESIZE);
        hz = sysconf(_SC_CLK_TCK);

	/* default max handspread is 64MB worth of pages */
	handspreadpages = (64 * 1048576)/sysconf(_SC_PAGESIZE);
	pages = sysconf(_SC_PHYS_PAGES);

	if(!fr_time) {
	if ((kc = kstat_open()) == NULL) {
		fail(1, "kstat_open(): can't open /dev/kstat");
	}

	/* Initialize the all_stat structure */
	all_stat_init();
	fr_time = 1;
	}

	if (handspreadpages > (pages/4)) {
		handspreadpages = (int)(pages/4);

	/* update the kstat header chain or load all_stat structure */ 
        while (kstat_chain_update(kc) || all_stat_load()) 	
		/* (void) printf("<<State change>>\n"); */
                all_stat_init();
	}

        etime = 0;
        for (i = 0; i < CPU_STATES; i++)
                etime += DELTA(cpu_sysinfo.cpu[i]);

        etime = denom(((etime / ncpus) + (hz >> 1)) / hz);

	*handspread = handspreadpages;
        *scan =  DELTA(cpu_vminfo.scan) / etime;

	/*
	 * Close the kstat control structure and set it to null.
	 */
/*	kstat_close(kc);
	kc = (kstat_ctl_t *)NULL;
*/
	return(0);
}

/* Get ncstat data */
int 
krgetncstatdetail(unsigned long *hits, unsigned long *misses)
{
        struct ncstats ncstats;

	if(!fr_time) {
	/* Initialize the all_stat structure */
	if ((kc = kstat_open()) == NULL) {
		fail(1, "kstat_open(): can't open /dev/kstat");
	}

	/* Initialize the all_stat structure */
	all_stat_init();
	fr_time =1 ;
	}

        if (all_stat_load() != 0)
                fail(1, "all_stat_load() failed");

        safe_kstat_read(kc, safe_kstat_lookup(kc, "unix", 0, "ncstats"), (void *) &ncstats);

	*hits = (unsigned long)ncstats.hits;
	*misses = (unsigned long)ncstats.misses;

	/*
	 * Close the kstat control structure and set it to null.
	 */
/*	kstat_close(kc);
	kc = (kstat_ctl_t *)NULL;
*/
	return(0);
}

/* Initialize the all_stat structure */
static void
all_stat_init(void)
{
	kstat_t *ksp;

	/*
	 * Global statistics
	 */

	sysinfo_ksp	= safe_kstat_lookup(kc, "unix", 0, "sysinfo");
        vminfo_ksp      = safe_kstat_lookup(kc, "unix", 0, "vminfo");
        system_misc_ksp = safe_kstat_lookup(kc, "unix", 0, "system_misc");

        safe_kstat_read(kc, system_misc_ksp, NULL);
        deficit_knp     = safe_kstat_data_lookup(system_misc_ksp, "deficit");
        lbolt_knp       = safe_kstat_data_lookup(system_misc_ksp, "lbolt");
        clk_intr_knp    = safe_kstat_data_lookup(system_misc_ksp, "clk_intr");

       /*
         * Per-CPU statistics
         */

        ncpus = 0;
        for (ksp = kc->kc_chain; ksp; ksp = ksp->ks_next)
                if (strncmp(ksp->ks_name, "cpu_stat", 8) == 0)
                        ncpus++;

        safe_zalloc((void **) &cpu_stat_list, ncpus * sizeof (kstat_t *), 1);

        ncpus = 0;
        for (ksp = kc->kc_chain; ksp; ksp = ksp->ks_next)
                if (strncmp(ksp->ks_name, "cpu_stat", 8) == 0 &&
                    kstat_read(kc, ksp, NULL) != -1)
                        cpu_stat_list[ncpus++] = ksp;

        if (ncpus == 0)
                fail(0, "can't find any cpu statistics");

	(void) memset(&s_new, 0, sizeof (all_stat_t));
}

/*
 * load statistics, summing across CPUs where needed
 */

static int
all_stat_load(void)
{
	int i, j;
	cpu_stat_t cs;
	uint *np, *tp;

	s_old = s_new;
	(void) memset(&s_new, 0, sizeof (all_stat_t));

	/*
	 * Global statistics
	 */

	safe_kstat_read(kc, sysinfo_ksp, (void *) &s_new.sysinfo);
        safe_kstat_read(kc, vminfo_ksp, (void *) &s_new.vminfo);
        safe_kstat_read(kc, system_misc_ksp, NULL);
        s_new.deficit = deficit_knp->value.l;

        /*
         * Per-CPU statistics.
         * For now, we just sum across all CPUs.  In the future,
         * we should add options to vmstat for per-CPU data.
         */

        for (i = 0; i < ncpus; i++) {
                if (kstat_read(kc, cpu_stat_list[i], (void *) &cs) == -1)
                        return (1);
                np = (uint *) &s_new.cpu_sysinfo;
                tp = (uint *) &cs.cpu_sysinfo;
                for (j = 0; j < sizeof (cpu_sysinfo_t); j += sizeof (uint_t))
                        *np++ += *tp++;
                np = (uint *) &s_new.cpu_vminfo;
                tp = (uint *) &cs.cpu_vminfo;
                for (j = 0; j < sizeof (cpu_vminfo_t); j += sizeof (uint_t))
                        *np++ += *tp++;
        }
	return (0);
}

static void
fail(int do_perror, char *message, ...)
{
	va_list args;
	int save_errno = errno;

	va_start(args, message);
	(void) vfprintf(stderr, message, args);
	va_end(args);
	if (do_perror)
		(void) fprintf(stderr, ": %s", strerror(save_errno));
	(void) fprintf(stderr, "\n");
	exit(2);
}

static void
safe_zalloc(void **ptr, int size, int free_first)
{
        if (free_first && *ptr != NULL)
                free(*ptr);
        if ((*ptr = (void *) malloc(size)) == NULL)
                fail(1, "malloc failed");
        (void) memset(*ptr, 0, size);
}


void
safe_kstat_read(kstat_ctl_t *kc, kstat_t *ksp, void *data)
{
	kid_t kstat_chain_id = kstat_read(kc, ksp, data);

	if (kstat_chain_id == -1)
		fail(1, "kstat_read(%x, '%s') failed", kc, ksp->ks_name);
}

kstat_t *
safe_kstat_lookup(kstat_ctl_t *kc, char *ks_module, int ks_instance,
	char *ks_name)
{
	kstat_t *ksp = kstat_lookup(kc, ks_module, ks_instance, ks_name);

	if (ksp == NULL)
		fail(0, "kstat_lookup('%s', %d, '%s') failed",
			ks_module == NULL ? "" : ks_module,
			ks_instance,
			ks_name == NULL ? "" : ks_name);
	return (ksp);
}

void *
safe_kstat_data_lookup(kstat_t *ksp, char *name)
{
	void *fp = kstat_data_lookup(ksp, name);

	if (fp == NULL)
		fail(0, "kstat_data_lookup('%s', '%s') failed",
			ksp->ks_name, name);
	return (fp);
}
