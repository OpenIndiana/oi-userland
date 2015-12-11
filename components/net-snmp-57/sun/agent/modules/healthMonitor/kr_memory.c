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


#if 0
#include <stdio.h>
#endif
#include <kstat.h>
#include <sys/types.h>
#include <sys/swap.h>
#include <vm/anon.h>
#include <unistd.h>
#include <string.h>

#define ONEMB 1048576

extern int first_time;
extern kstat_ctl_t	*kc;
extern void initialize_everything();

static ulong_t page_size = 0;

/*
 * Return value of named statistic for given kstat_named kstat.
 * Return 0 if named statistic is not in list.
 */
static u_longlong_t
kstat_named_value(kstat_t *ksp, char *name)
{
    kstat_named_t *knp;

    if (ksp == NULL)
	return (0);

    knp = kstat_data_lookup(ksp, name);
    if (knp != NULL) {
        switch (knp->data_type) {
        case KSTAT_DATA_UINT64:
               return (knp->value.ull);
        case KSTAT_DATA_UINT32:
        default:
               return (knp->value.ul);
        }
    } else {
	return (0);
    }
}

int
krgetmemusage (int *mem_avail, int *mem_inuse, int *mem_free)
{
    int         intfactor;

    if ((first_time) || (!kc))
	initialize_everything();

    if (page_size == 0)
	page_size = sysconf(_SC_PAGESIZE);

    /* do ops differently dependent on pagesize to avoid overflow
     * note that: pagesize & ONEMB will both be powers of 2 therefore
     * the bigger one will be exactly divisible by the smaller
     */
    if(page_size < ONEMB){
        intfactor = ONEMB/page_size;

/* The following line is commented out because the value returned is less 
than the actual number of pages in the machine. More research has got be 
done about what is the value that kstat returns 
        *mem_avail = kstat_named_value(ksp, "physmem") / intfactor; */

        *mem_avail = sysconf(_SC_PHYS_PAGES) / intfactor;
        *mem_free = sysconf(_SC_AVPHYS_PAGES) / intfactor;
        *mem_inuse = *mem_avail - *mem_free;
    }
    else{ /* page_size >= ONEMB */
        intfactor = page_size/ONEMB;
/*        *mem_avail = kstat_named_value(ksp, "physmem") * intfactor; */
        *mem_avail = sysconf(_SC_PHYS_PAGES) * intfactor;
        *mem_free = sysconf(_SC_AVPHYS_PAGES) * intfactor;
        *mem_inuse = *mem_avail - *mem_free;
    }
    return 0;
}


u_int convert_ticks_to_bytes(u_int input) {

        static float factor = -1;

        if (factor == -1)
                factor = (float)(sysconf(_SC_PAGESIZE))/1024;/* in KB */
        return (input*(u_int)factor);
}


int
krgetswapusage (int *swap_avail, int *swap_resv, int *swap_alloc, int *swap_used, int *swap_total)
{

        struct anoninfo ai;

        if (swapctl(SC_AINFO, &ai) == -1) {
                /* perror("Error in swapctl ..............."); */
                return (-1);
        }
	*swap_avail = convert_ticks_to_bytes(ai.ani_max - ai.ani_resv);
	*swap_resv  = convert_ticks_to_bytes(ai.ani_resv - ai.ani_max + ai.ani_free);
	*swap_alloc = convert_ticks_to_bytes(ai.ani_max - ai.ani_free);
	*swap_used  = convert_ticks_to_bytes(ai.ani_resv);
	*swap_total = (*swap_used) + (*swap_avail);
	return 0;
}

/*
 * returns information about the "kmem_cache" buffer of name
 * "cache_name".  If the last character is an asterisk, it
 * returns the sum of the statistics over all caches that
 * match.
 */
int
krgetkmemdetail (const char *cache_name, int *alloc, int *alloc_fail, int *buf_size, int *buf_avail, int *buf_total, int *buf_max)
{
    kstat_t *ksp;
    int length = 0;

    if ((first_time) || (!kc))
	initialize_everything();

    if (cache_name[strlen(cache_name) - 1] == '*')
	length = strlen(cache_name) - 1;
    else
	length = 256;

    *alloc = 0;
    *alloc_fail = 0;
    *buf_size = 0;
    *buf_avail = 0;
    *buf_total = 0;
    *buf_max = 0;

    for (ksp = kc->kc_chain; ksp != NULL; ksp = ksp->ks_next) {
	if (strcmp(ksp->ks_class, "kmem_cache") != 0)
	    continue;
	if (strncmp(ksp->ks_name, cache_name, length) != 0)
	    continue;
	if (kstat_read(kc, ksp, NULL) == -1)
	    return -1;
	*alloc += kstat_named_value(ksp, "alloc");
	*alloc_fail += kstat_named_value(ksp, "alloc_fail");
	*buf_size += kstat_named_value(ksp, "buf_size");
	*buf_avail += kstat_named_value(ksp, "buf_avail");
	*buf_total += kstat_named_value(ksp, "buf_total");
	*buf_max += kstat_named_value(ksp, "buf_max");
    }
    return 0;

}

