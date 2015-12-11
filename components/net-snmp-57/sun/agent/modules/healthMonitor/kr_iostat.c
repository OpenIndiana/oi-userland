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
#include <stropts.h>
#include <poll.h>

#include <sys/types.h>
#include <sys/time.h>
#include <sys/sysinfo.h>
#include <sys/stat.h>

kstat_ctl_t	*kc;		/* libkstat cookie */
static  int     ncpus = -1;
typedef struct cpuinfo {
        kstat_t         *cs_kstat;
        cpu_stat_t      cs_old;
        cpu_stat_t      cs_new;
} cpuinfo_t;

static  cpuinfo_t       *cpulist = NULL;

#define DELTA(i, x)     (cpulist[i].cs_new.x - cpulist[i].cs_old.x)

static	kstat_t		**cpu_stat_list = NULL;
static	cpu_stat_t	*cpu_stat_data = NULL;

#define	DISK_OLD		0x0001
#define	DISK_NEW		0x0002
#define	DISK_EXTENDED		0x0004
#define	DISK_ERRORS		0x0008
#define	DISK_EXTENDED_ERRORS	0x0010
#define	DISK_NORMAL	(DISK_OLD | DISK_NEW)

#define	DISK_IO_MASK	(DISK_OLD | DISK_NEW | DISK_EXTENDED)
#define	DISK_ERROR_MASK	(DISK_ERRORS | DISK_EXTENDED_ERRORS)
#define	PRINT_VERTICAL	(DISK_ERROR_MASK | DISK_EXTENDED)

#define	REPRINT 19

/*
 * Name and print priority of each supported ks_class.
 */
#define	IO_CLASS_DISK		0
#define	IO_CLASS_PARTITION	0
#define	IO_CLASS_TAPE		1
#define	IO_CLASS_NFS		2

struct io_class {
	char	*class_name;
	int	class_priority;
};


#undef printf
#undef putchar
/*ARGSUSED*/
int printf(const char *bar, ...) { return 1; }
/*ARGSUSED*/
int putchar(int bar){return 1;}

static int reentrant = 0;

/*
 * I've had some strange behavior with "refreshMode = async".
 */
#define REENTRANT_BEGIN() { \
		if (reentrant != 0) \
	    reentrant++; \
    }

#define REENTRANT_END() { \
	reentrant--; \
    }

static struct io_class io_class[] = {
	{ "disk",	IO_CLASS_DISK},
	{ "partition",	IO_CLASS_PARTITION},
	{ NULL,		0}
};

struct diskinfo {
	struct diskinfo *next;
	kstat_t *ks;
	kstat_io_t new_kios, old_kios;
	int	selected;
	int	class;
	char	*device_name;
	kstat_t	*disk_errs;	/* pointer to the disk's error kstats */
};

#define	DISK_GIGABYTE	1000000000.0

static void *dl = 0;	/* for device name lookup */
extern void *build_disk_list(void *);
extern char *lookup_ks_name(char *, void *);

#define	NULLDISK (struct diskinfo *)0
static	struct diskinfo zerodisk;
static	struct diskinfo *firstdisk = NULLDISK;
static	struct diskinfo *lastdisk = NULLDISK;
static	struct diskinfo *snip = NULLDISK;
static int refreshDiskdetail=0;
static int refreshDisksrv=0;

static	cpu_stat_t	old_cpu_stat, new_cpu_stat;

#define	DISK_DELTA(x) (disk->new_kios.x - disk->old_kios.x)

#define	CPU_DELTA(x) (new_cpu_stat.x - old_cpu_stat.x)


#define	PRINT_TTY_DATA(sys, time) \
				(void) printf(" %3.0f %4.0f",\
				(float)CPU_DELTA(sys.rawch) / time, \
				(float)CPU_DELTA(sys.outch) / time);

#define	PRINT_CPU_DATA(sys, pcnt) \
				(void) printf(" %2.0f %2.0f %2.0f %2.0f", \
			CPU_DELTA(sys.cpu[CPU_USER]) * pcnt, \
			CPU_DELTA(sys.cpu[CPU_KERNEL]) * pcnt, \
			CPU_DELTA(sys.cpu[CPU_WAIT]) * pcnt, \
			CPU_DELTA(sys.cpu[CPU_IDLE]) * pcnt);

#define	PRINT_CPU_HDR1	(void) printf("%12s", "cpu");
#define	PRINT_CPU_HDR2	(void) printf(" us sy wt id");
#define	PRINT_TTY_HDR1	(void) printf("%9s", "tty");
#define	PRINT_TTY_HDR2	(void) printf(" tin tout");
#define	PRINT_ERR_HDR	(void) printf(" ---- errors --- ");

static	char	*cmdname = "iostat";

static	int	do_disk = 0;
static	int	do_cpu = 0;
static	int	do_interval = 0;
static	int	do_partitions = 0;	/* collect per-partition stats */
static	int	do_partitions_only = 0;	/* collect per-partition stats only */
					/* no per-device stats for disks */
static	int	do_conversions = 0;	/* display disks as cXtYdZ */
static	int	do_megabytes = 0;	/* display data in MB/sec */
#define	DEFAULT_LIMIT	4
static	int	limit = 0;		/* limit for drive display */
static	int	ndrives = 0;

struct disk_selection {
	struct disk_selection *next;
	char ks_name[KSTAT_STRLEN];
};

static	struct disk_selection *disk_selections = (struct disk_selection *)NULL;

static void show_disk(struct diskinfo *disk, double *rps, double *wps, double *tps, double *krps, double *kwps, double *kps, double *avw, double *avr, double *w_pct, double *r_pct, double *wserv, double *rserv, double *serv);
static	void	cpu_stat_init(void);

static	int	cpu_stat_load(int);

static	void	fail(int, char *, ...);
static	void	safe_zalloc(void **, int, int);
static	void	init_disks(void);
static	void	select_disks(void);
static	int	diskinfo_load(void);
static	void 	init_disk_errors(void);
static	void	find_disk(kstat_t *);

/* static struct diskinfo *disk;  */
int first_time = 1;

void
initialize_everything()
{
    if ((kc = kstat_open()) == NULL)
	return;
    do_disk |= DISK_EXTENDED /* | DISK_OLD */;
    do_conversions = 1;
    do_cpu = 1;
    {
	/*
	 * Choose drives to be displayed.  Priority
	 * goes to (in order) drives supplied as arguments,
	 * then any other active drives that fit.
	 */
	struct disk_selection **dsp = &disk_selections;
	*dsp = (struct disk_selection *)NULL;
    }
    cpu_stat_init();
    init_disks();
#if 0
    for (disk = firstdisk; disk; disk->next) {
	number_of_disks++;
    }
#endif
    /* disk = firstdisk; */
    first_time = 0;
}

int update_kstat_chain(int cpu_save_old_flag)
{
  int ret;

  ret=kstat_chain_update(kc);
  if (ret == 0) { /* no change */
    cpu_stat_load(cpu_save_old_flag);
    diskinfo_load();
    return 0;
  } else if (ret > 0) { /* changed */
    cpu_stat_init();
    init_disks();
    if (cpu_stat_load(cpu_save_old_flag)) {
      return -1;
    };
    if (diskinfo_load()) {
      return -1;
    };
    return 0;
  } else {  /* error */
    return -1;
  }
}

/* Get Adaptive mutex summary and number of cpus for the system */
int
krgetsmtx(ulong *smtx, int *num_cpus) 
{
       int i, c, hz,  ticks;
       ulong mutex;
       double etime, percent;
       etime = 0;
       mutex = 0;

       if ((first_time) || (!kc))
           initialize_everything();

       while (update_kstat_chain(1) == -1);

/*       while (kstat_chain_update(kc) || cpu_stat_load(1)) {
           (void) cpu_stat_init();
       }
*/


       hz = sysconf(_SC_CLK_TCK);
       for (c = 0; c < ncpus; c++) {
                ticks = 0;
                for (i = 0; i < CPU_STATES; i++)
                        ticks += DELTA(c, cpu_sysinfo.cpu[i]);
                etime = (double)ticks / hz;
                if (etime == 0.0)
                        etime = 1.0;
                percent = 100.0 / etime / hz;
		mutex += (int) (DELTA(c, cpu_sysinfo.mutex_adenters) / etime);
	}
	*num_cpus = ncpus;
	*smtx = mutex;

        return 0;
}

int
krgetcpudetail (cpu_stat_t **cpus, int *num_cpus)
{
    REENTRANT_BEGIN();
    if ((first_time) || (!kc))
	initialize_everything();

   while (update_kstat_chain(0) == -1) {
   /*     DPRINTF("ERROR: kstat_chain_update \n");
     DFFLUSH(stdout);*/
   }

    *cpus = cpu_stat_data;
    *num_cpus = ncpus;
    REENTRANT_END();
    return 0;
}

/* returns 0 if more disks remain, 1 if the last disk, < 0 on error */
int
krgetdiskdetail(char *name, char *alias, double *rps, double *wps, double *tps, double *krps, double *kwps, double *kps, double *avw, double *avr)
{
        double w_pct, r_pct, wserv, rserv, serv;
	static struct diskinfo *disk = NULL;

	REENTRANT_BEGIN();


	if (disk==NULL) disk=firstdisk;
	if ((first_time) || (!kc)) {
	    initialize_everything();
	    disk=firstdisk;

	}

	if (refreshDiskdetail) {
	  disk=firstdisk;
	  refreshDiskdetail=0;
	}

	if (disk == firstdisk) {
            while (update_kstat_chain(0) == -1) {
                /* DPRINTF("ERROR: diskdetail - kstat_chain_update \n");
                DFFLUSH(stdout);*/
            }
	}
	
	if (disk) {
	    if (disk->selected) {
		show_disk(disk, rps, wps, tps, krps, kwps, kps, avw, avr, &w_pct, &r_pct, &wserv, &rserv, &serv);
		strcpy(name, disk->ks->ks_name);
		if (disk->device_name != NULL)
		    strcpy(alias, disk->device_name);
		else
		    strcpy(alias, disk->ks->ks_name);
	    }
	    else {
	    }
	    disk = disk->next;
	}
	REENTRANT_END();
	if (disk == NULL) {
	    disk = firstdisk;
	    return 1;
	}
	return(0);
}

/* returns 0 if more disks remain, 1 if the last disk, < 0 on error */
int
krgetdisksrv(char *name, char *alias, double *w_pct, double *r_pct, double *wserv, double *rserv, double *serv)
{
	static struct diskinfo *disk = NULL;
	double rps, wps, tps, krps, kwps, kps, avw, avr;



	if (disk==NULL) disk=firstdisk;

	if (refreshDisksrv) {
	  disk=firstdisk;
	  refreshDisksrv=0;
	}
        if (disk) {
            if (disk->selected) {
		show_disk(disk, &rps, &wps, &tps, &krps, &kwps, &kps, &avw, &avr, w_pct, r_pct, wserv, rserv, serv);
		strcpy(name, disk->ks->ks_name);
		if (disk->device_name != NULL)
		    strcpy(alias, disk->device_name);
		else
		    strcpy(alias, disk->ks->ks_name);
            }
            else {
	        /*ddlPrintf(DDL_ERROR, "krgetdisksrv - skipping %s\n", disk->device_name ? disk->device_name : disk->ks->ks_name);*/
            }
            disk = disk->next;
        }
        if (disk == NULL) {
            disk = firstdisk;
            return 1;
        }

	return(0);
}

static void
show_disk(struct diskinfo *disk, double *Rps, double *Wps, double *Tps, double *Krps, double *Kwps, double *Kps, double *Avw, double *Avr, double *W_pct, double *R_pct, double *Wserv, double *Rserv, double *Serv)
{
	double rps, wps, tps, krps, kwps, kps, avw, avr, w_pct, r_pct;
	double wserv, rserv, serv;
	double iosize;	/* kb/sec or MB/sec */
	double etime, hr_etime;

	hr_etime = (double)DISK_DELTA(wlastupdate);
	if (hr_etime == 0.0)
		hr_etime = (double)NANOSEC;
	etime = hr_etime / (double)NANOSEC;

	rps	= (double)DISK_DELTA(reads) / etime;
		/* reads per second */

	wps	= (double)DISK_DELTA(writes) / etime;
		/* writes per second */

	tps	= rps + wps;
		/* transactions per second */

	/*
	 * report throughput as either kb/sec or MB/sec
	 */
	if (!do_megabytes) {
		iosize = 1024.0;
	} else {
		iosize = 1048576.0;
	}
	krps	= (double)DISK_DELTA(nread) / etime / iosize;
		/* block reads per second */

	kwps	= (double)DISK_DELTA(nwritten) / etime / iosize;
		/* blocks written per second */

	kps	= krps + kwps;
		/* blocks transferred per second */

	avw	= (double)DISK_DELTA(wlentime) / hr_etime;
		/* average number of transactions waiting */

	avr	= (double)DISK_DELTA(rlentime) / hr_etime;
		/* average number of transactions running */

	wserv	= tps > 0 ? (avw / tps) * 1000.0 : 0.0;
		/* average wait service time in milliseconds */

	rserv	= tps > 0 ? (avr / tps) * 1000.0 : 0.0;
		/* average run service time in milliseconds */

	serv	= tps > 0 ? ((avw + avr) / tps) * 1000.0 : 0.0;
		/* average service time in milliseconds */

	w_pct	= (double)DISK_DELTA(wtime) / hr_etime * 100.0;
		/* % of time there is a transaction waiting for service */

	r_pct	= (double)DISK_DELTA(rtime) / hr_etime * 100.0;
		/* % of time there is a transaction running */

	if (do_interval) {
		rps	*= etime;
		wps	*= etime;
		tps	*= etime;
		krps	*= etime;
		kwps	*= etime;
		kps	*= etime;
	}

	*Rps = rps;
	*Wps = wps;
	*Tps = tps;
	*Krps = krps;
	*Kwps = kwps;
	*Kps = kps;
	*Avw = avw;
	*Avr = avr;
	*W_pct = w_pct;
	*R_pct = r_pct;
	*Wserv = wserv;
	*Rserv = rserv;
	*Serv = serv;
}

/*
 * Get list of cpu_stat KIDs for subsequent cpu_stat_load operations.
 */

static void
cpu_stat_init(void)
{
	kstat_t *ksp;
	int tmp_ncpus;
        int i;
        int nb_cpus;

	tmp_ncpus = 0;
	for (ksp = kc->kc_chain; ksp; ksp = ksp->ks_next) {
		if (strncmp(ksp->ks_name, "cpu_stat", 8) == 0) {
			tmp_ncpus++;
                        if (kstat_read(kc, ksp, NULL) == -1) {
                            /* ddlPrintf(DDL_ERROR, "cpu_stat_init - kstat_read() failed for cpu:%s\n", ksp->ks_name);*/
                             
                        }
                }
        }
                        
        safe_zalloc((void **) &cpulist, tmp_ncpus * sizeof (cpuinfo_t), 1);
	safe_zalloc((void **)&cpu_stat_list, tmp_ncpus * sizeof (kstat_t *), 1);
	safe_zalloc((void *)&cpu_stat_data, tmp_ncpus * sizeof (cpu_stat_t), 1);

	ncpus = 0; 
        nb_cpus = 0;
	for (ksp = kc->kc_chain; ksp; ksp = ksp->ks_next) {
		if (strncmp(ksp->ks_name, "cpu_stat", 8) == 0) {
		    if (kstat_read(kc, ksp, NULL) != -1) {
			cpu_stat_list[ncpus++] = ksp;
                    } else {
                        /* ddlPrintf(DDL_ERROR, "cpu_stat_init - kstat_read() failed for cpu:%s\n", ksp->ks_name); */
                    }
                }

                if (strcmp(ksp->ks_module, "cpu_stat") != 0)
                        continue;
                /*
                 * insertion sort by CPU id
                 */
                for (i = nb_cpus - 1; i >= 0; i--) {
                        if (cpulist[i].cs_kstat->ks_instance < ksp->ks_instance)
                                break;
                        cpulist[i + 1].cs_kstat = cpulist[i].cs_kstat;
                }
                cpulist[i + 1].cs_kstat = ksp;
                nb_cpus++;
        }


	(void) memset(&new_cpu_stat, 0, sizeof (cpu_stat_t));

        if ( ncpus != tmp_ncpus ) {
            /* ddlPrintf(DDL_ERROR, "cpu_stat_init - kstat_read() for some cpu failed,  Passed :ncpus=%d   Total :tmp_ncpus=%d\n", ncpus, tmp_ncpus); */
        }
}


static int
cpu_stat_load(int save_old_flag)
{
	int i, j;
	uint *np, *tp;

	if (save_old_flag)
	    old_cpu_stat = new_cpu_stat;
	(void) memset(&new_cpu_stat, 0, sizeof (cpu_stat_t));

	/* Sum across all cpus */
	for (i = 0; i < ncpus; i++) {
                cpulist[i].cs_old = cpulist[i].cs_new;
                if (kstat_read(kc, cpulist[i].cs_kstat,
                    (void *) &cpulist[i].cs_new) == -1)
                        return (1);

		if (kstat_read(kc, cpu_stat_list[i], (void *)&cpu_stat_data[i]) == -1) {
                    /* ddlPrintf(DDL_ERROR, "cpu_stat_load - kstat_read() failed for cpu:%s\n", cpu_stat_list[i]->ks_name); */
		    return (1);
                }
		np = (uint *)&new_cpu_stat.cpu_sysinfo;
		tp = (uint *)&(cpu_stat_data[i].cpu_sysinfo);
		for (j = 0; j < sizeof (cpu_sysinfo_t); j += sizeof (uint_t))
			*np++ += *tp++;
		np = (uint *)&new_cpu_stat.cpu_vminfo;
		tp = (uint *)&(cpu_stat_data[i].cpu_vminfo);
		for (j = 0; j < sizeof (cpu_vminfo_t); j += sizeof (uint_t))
			*np++ += *tp++;
	}
	return (0);
}

static void
fail(int do_perror, char *message, ...)
{
	va_list args;

	va_start(args, message);
	(void) fprintf(stderr, "%s: ", cmdname);
	(void) vfprintf(stderr, message, args);
	va_end(args);
	if (do_perror)
		(void) fprintf(stderr, ": %s", strerror(errno));
	(void) fprintf(stderr, "\n");
	exit(2);
}

static void
safe_zalloc(void **ptr, int size, int free_first)
{
	if (free_first && *ptr != NULL)
		free(*ptr);
	if ((*ptr = (void *)malloc(size)) == NULL)
		fail(1, "malloc failed");
	(void) memset(*ptr, 0, size);
}


/*
 * Sort based on ks_class, ks_module, ks_instance, ks_name
 */
static int
kscmp(struct diskinfo *ks1, struct diskinfo *ks2)
{
	int cmp;

	cmp = ks1->class - ks2->class;
	if (cmp != 0)
		return (cmp);

	cmp = strcmp(ks1->ks->ks_module, ks2->ks->ks_module);
	if (cmp != 0)
		return (cmp);
	cmp = ks1->ks->ks_instance - ks2->ks->ks_instance;
	if (cmp != 0)
		return (cmp);

	if (ks1->device_name && ks2->device_name)
		return (strcmp(ks1->device_name,  ks2->device_name));
	else
		return (strcmp(ks1->ks->ks_name, ks2->ks->ks_name));
}

static void
init_disks(void)
{
	struct diskinfo *disk, *prevdisk, *comp;
	kstat_t *ksp;
        static int first = 1;

	refreshDiskdetail=1;
	refreshDisksrv=1;

	if (do_conversions)
		dl = (void *)build_disk_list(dl);

        if(first) {
                zerodisk.next = NULLDISK;
                first = 0;
        }

	disk = &zerodisk;

	/*
	 * Patch the snip in the diskinfo list (see below)
	 */
	if (snip)
		lastdisk->next = snip;

	for (ksp = kc->kc_chain; ksp; ksp = ksp->ks_next) {
		int i;

		if (ksp->ks_type != KSTAT_TYPE_IO)
			continue;

		for (i = 0; io_class[i].class_name != NULL; i++) {
			if (strcmp(ksp->ks_class, io_class[i].class_name) == 0)
				break;
		}
		if (io_class[i].class_name == NULL)
			continue;

		if (do_partitions_only &&
			(strcmp(ksp->ks_class, "disk") == 0))
				continue;

		if (!do_partitions && !do_partitions_only &&
			(strcmp(ksp->ks_class, "partition") == 0))
				continue;
		if (!strcmp(ksp->ks_name, "fd0"))
		    continue;

		prevdisk = disk;
		if (disk->next)
			disk = disk->next;
		else {
			safe_zalloc((void **)&disk->next,
				sizeof (struct diskinfo), 0);
			disk = disk->next;
			disk->next = NULLDISK;
		}
		disk->ks = ksp;
		(void) memset((void *)&disk->new_kios, 0, sizeof (kstat_io_t));
		disk->new_kios.wlastupdate = disk->ks->ks_crtime;
		disk->new_kios.rlastupdate = disk->ks->ks_crtime;

		if (do_conversions && dl) {
			if (!strcmp(ksp->ks_class, "nfs") == 0)
				disk->device_name =
					lookup_ks_name(ksp->ks_name, dl);
		} else {
			disk->device_name = (char *)0;
		}

		disk->disk_errs = (kstat_t *)NULL;
		disk->class = io_class[i].class_priority;

		/*
		 * Insertion sort on (ks_class, ks_module, ks_instance, ks_name)
		 */
		comp = &zerodisk;
		while (kscmp(disk, comp->next) > 0)
			comp = comp->next;
		if (prevdisk != comp) {
			prevdisk->next = disk->next;
			disk->next = comp->next;
			comp->next = disk;
			disk = prevdisk;
		}
	}
	/*
	 * Put a snip in the linked list of diskinfos.  The idea:
	 * If there was a state change such that now there are fewer
	 * disks, we snip the list and retain the tail, rather than
	 * freeing it.  At the next state change, we clip the tail back on.
	 * This prevents a lot of malloc/free activity, and it's simpler.
	 */
	lastdisk = disk;
	snip = disk->next;
	disk->next = NULLDISK;

	firstdisk = zerodisk.next;
	select_disks();

	if (do_disk & DISK_ERROR_MASK)
		init_disk_errors();
}

static void
select_disks(void)
{
	struct diskinfo *disk;
	struct disk_selection *ds;

	ndrives = 0;
	for (disk = firstdisk; disk; disk = disk->next) {
		disk->selected = 0;
		for (ds = disk_selections; ds; ds = ds->next) {
			if (strcmp(disk->ks->ks_name, ds->ks_name) == 0) {
				disk->selected = 1;
				ndrives++;
				break;
			}
		}
	}
	for (disk = firstdisk; disk; disk = disk->next) {
		if (disk->selected)
			continue;
		if (limit && ndrives >= limit)
			break;
		disk->selected = 1;
		ndrives++;
	}
}

static int
diskinfo_load(void)
{
	struct diskinfo *disk;

	for (disk = firstdisk; disk; disk = disk->next) {
		if (disk->selected) {
			disk->old_kios = disk->new_kios;
			if (kstat_read(kc, disk->ks,
			    (void *)&disk->new_kios) == -1)
				return (1);
			if (disk->disk_errs) {
				if (kstat_read(kc, disk->disk_errs, NULL) == -1) {
					return (1);
				}
			}
		}
	}
	return (0);
}
static void
init_disk_errors()
{
	kstat_t *ksp;

	for (ksp = kc->kc_chain; ksp; ksp = ksp->ks_next) {
		if ((ksp->ks_type == KSTAT_TYPE_NAMED) &&
			(strncmp(ksp->ks_class, "device_error", 12) == 0)) {
				find_disk(ksp);
			}
	}
}
static void
find_disk(ksp)
kstat_t	*ksp;
{
	struct diskinfo *disk;
	char	kstat_name[KSTAT_STRLEN];
	char	*dname = kstat_name;
	char	*ename = ksp->ks_name;

	while (*ename != ',') {
		*dname = *ename;
		dname++;
		ename++;
	}
	*dname = '\0';

	for (disk = firstdisk; disk; disk = disk->next) {
		if (disk->selected) {
			if (strcmp(disk->ks->ks_name, kstat_name) == 0) {
				disk->disk_errs = ksp;
				return;
			}
		}
	}

}

