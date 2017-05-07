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
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/mnttab.h>
#include <sys/systeminfo.h>
#include <sys/dklabel.h>
#include <sys/dkio.h>

typedef struct nms {
	char	*dsk;
	int	dnum;
	char	*dty;
	char	*real;
	int	devtype;
	struct nms *next;
} nms_t;

typedef struct list_of_disks {
	char	*dtype;
	int	dnum;
	char	*dsk;
	char	*dpart[NDKMAP];
	struct list_of_disks *next;
} disk_list_t;

static nms_t *rummage_dev_dsk(void);
static void	do_snm(char *, char *);
static int	look_up_name(const char *, nms_t *);
static void	make_an_entry(char *, const char *, nms_t **, int);
static char	*trim(char *);
static void	rummage_path_to_inst(nms_t *);
static nms_t	*find_str(const char *, nms_t *);
static int	pline(char *, nms_t *);
static void	insert_dlist_ent(const char *, const int, const char *,
			int, disk_list_t **);
static void	mk_list_of_disks(nms_t *, disk_list_t **);
static int	str_is_digit(char *);

extern void	*build_disk_list(void *);
extern char	*lookup_ks_name(char *, void *);

#define	DISK		0
#define	TAPE		1

#define	MAX_TYPES	2


/*
 * Build a list of disks attached to the system. if a previous list is passed
 * in, delete that list before building the new list.
 */

void *
build_disk_list(void *v)
{
	nms_t	*list;
	nms_t	*t;
	disk_list_t *rv=NULL;
	disk_list_t *p;
	int	i;

	p = (disk_list_t *)v;
	if (p != (disk_list_t *)NULL) {
		disk_list_t *t;
		while (p) {
			(void) free(p->dtype);
			(void) free(p->dsk);
			for (i = 0; i < NDKMAP; i++)
				(void) free(p->dpart[i]);
			t = p;
			p = p->next;
			(void) free(t);
		}
	}
	/*
	 * Build the list of devices connected to the system.
	 */
	list = rummage_dev_dsk();
	rummage_path_to_inst(list);
	mk_list_of_disks(list, &rv);
	t = list;
	while (t) {
		nms_t	*f;
		(void) free(t->real);
		f = t;
		t = t->next;
		if (t != list) {
			(void) free(f);
		}
	}
	return (rv);
}


/*
 * Currently it isn't necessary to look below the cntndn level....
 */

static nms_t *
rummage_dev_dsk(void)
{
	nms_t	*list = (nms_t *)0;
	DIR		*dskp;
	int	i;

	for (i = 0; i < MAX_TYPES; i++) {
		switch (i) {

			case DISK:
				dskp = opendir("/dev/dsk");
				break;
			case TAPE:
				dskp = opendir("/dev/rmt");
				break;
			default:
				dskp = NULL;
				break;
		}

		if (dskp != NULL) {
			struct dirent  *bpt;
			while ((bpt = readdir(dskp)) != NULL) {
				struct stat	sbuf;
				char	dnmbuf[1025];
				char	snm[256];
				char	lnm[256];
				char	*npt;
				char	nmbuf[1025];

				if (bpt->d_name[0] == '.')
					continue;

				if (i == DISK) {
					(void) strcpy(lnm, bpt->d_name);
					do_snm(bpt->d_name, snm);
				} else {
					/*
					 * don't want all rewind/etc
					 * devices for a tape
					 */
					if (!str_is_digit(bpt->d_name))
						continue;
					(void) sprintf(snm, "rmt/%s",
						bpt->d_name);
					(void) sprintf(lnm, "rmt/%s",
						bpt->d_name);
				}
				if (look_up_name(snm, list) != 0)
					continue;

				if (i == DISK) {
					(void) sprintf(dnmbuf,
						"/dev/dsk/%s", bpt->d_name);
				} else {
					(void) sprintf(dnmbuf,
						"/dev/rmt/%s", bpt->d_name);
				}
				if (lstat(dnmbuf, &sbuf) != -1) {
					int cnt;
					if ((sbuf.st_mode & S_IFMT)
								== S_IFLNK) {

						nmbuf[0] = '\0';
						if ((cnt = readlink(dnmbuf, nmbuf, sizeof (nmbuf))) != 1) {
							nmbuf[cnt] = '\0';
							npt = nmbuf;
						} else
							npt = (char *)0;
					} else
						npt = lnm;
					if (npt)
						make_an_entry(npt, snm,
								&list, i);
				}
			}
			(void) closedir(dskp);
		}
	}
	return (list);
}


static int
look_up_name(const char *nm, nms_t *list)
{
	int	rv = 0;

	while (list != (nms_t *)NULL) {
		if (strcmp(list->dsk, nm) != 0)
			list = list->next;
		else {
			rv++;
			break;
		}
	}
	return (rv);
}


static void
do_snm(char *orig, char *shortnm)
{
	while (*orig != 's' && *orig != 'p')
		*shortnm++ = *orig++;
	*shortnm = '\0';
}


static void
make_an_entry(char *lname, const char *shortnm, nms_t **list, int devtype)
{
	nms_t	*entry;

	entry = (nms_t *)malloc(sizeof (nms_t));
	if (entry != (nms_t *)NULL) {
		int	len;
		char	*nlnm;

		nlnm = trim(lname);
		len = strlen(nlnm);
		len++;
		entry->real = (char *)malloc(len);
		if (entry->real) {
			(void) strcpy(entry->real, nlnm);
			len = strlen(shortnm);
			len++;
			entry->dsk = (char *)malloc(len);
			if (entry->dsk) {
				(void) strcpy(entry->dsk, shortnm);
				entry->dnum = -1;
				entry->dty = (char *)NULL;
				entry->next = (nms_t *)NULL;
				entry->devtype = devtype;
				if (*list != (nms_t *)NULL) {
					entry->next = *list;
					*list = entry;
				} else
					*list = entry;
			} else {
				(void) free(entry->real);
				(void) free(entry);
			}
		} else
			(void) free(entry);
	}
}


static char    *
trim(char *fnm)
{
	char	*ptr;
	char	*lname = "../../devices";

	while (*lname == *fnm) {
		lname++;
		fnm++;
	}
	if ((ptr = strrchr(fnm, (int)':')) != (char *)NULL)
		*ptr = '\0';
	return (fnm);
}


static void
rummage_path_to_inst(nms_t *list)
{
	FILE	*inpt;

	inpt = fopen("/etc/path_to_inst", "r");
	if (inpt) {
		char	ibuf[1024];

		while (fgets(ibuf, sizeof (ibuf), inpt) != (char *)NULL) {
			if (ibuf[0] != '#') {
				(void) pline(ibuf, list);
			}
		}
		(void) fclose(inpt);
	}
}


/*
 * Process an /etc/path_to_inst line. The line is of the format:
 * "/pathname/device@unit,instance" devicenumber We want to extract the
 * devicenumber and the device from this string if it is one of the ones in
 * /dev/dsk.
 */


static int
pline(char *ib, nms_t *list)
{
	char	*rpt;
	char	*bpt;
	nms_t	*entry;
	int	rv = 0;
	int	done;
	int	len;
	char	*v;
	/*
	 * Skip over any stuff at the beginning of the line before a leading
	 * '/' If we don't find a '/', the line is malformed and we just skip
	 * it.
	 */
	while (*ib) {
		if (*ib != '/')
			ib++;
		else
			break;
	}
	if (!(*ib))
		goto done;

	/*
	 * Find the trailing '"' in the line. If not found, we just
	 * skip the line.
	 */

	rpt = strchr(ib, (int)'""');
	if (rpt != NULL)
		rpt = strchr(rpt, (int)'""');

	/*
	 * Find a matching entry in the list of names from /dev/dsk.
	 * If no match, we're not interested.
	 */
	if (!rpt)
		goto done;

	*rpt = '\0';


	if ((entry = find_str(ib, list)) == (nms_t *)NULL)
		goto done;

	bpt = rpt;
	/*
	 * Extract the device number at the end of
	 * the line. We expect whitespace followed by
	 * the beginning of the currently numeric
	 * device id string;
	 */
	rpt++;
	done = 0;
	while (!done) {
		if (*rpt) {
			if (*rpt != '\n') {
				if (isspace((int)*rpt))
					rpt++;
				else
					done++;
			} else
				done++;
		} else
			done++;
	}
	/*
	 * Should now be at the beginning of the
	 * device number. Point entry->dn at the
	 * string.
	 */
	if (*rpt) {
		v = rpt;
		len = 0;
		while (v) {
			if (*v != '\n') {
				v++;
				len++;
			} else {
				*v = '\0';
				v = (char *)NULL;
			}
		}
		if (len) {
			entry->dnum = atoi(rpt);
			while (bpt > ib) {
				if (*bpt != '@')
					bpt--;
				else
					break;
			}
			if (bpt > ib) {
				*bpt-- = '\0';
				len = 0;
				while (bpt > ib) {
					if (*bpt != '/') {
						bpt--;
						len++;
					} else
						break;
				}
				if (bpt > ib) {
					bpt++;
					len++;
					entry->dty = (char *)malloc(len);
					if (entry->dty) {
						(void) strcpy(entry->dty, bpt);
						rv++;
					}
				}
			}
		}
	}
done:
	return (rv);
}



static nms_t *
find_str(const char *inbuf, nms_t *list)
{
	while (list) {
		if (strcmp(inbuf, list->real) != 0)
			list = list->next;
		else
			break;
	}
	return (list);
}



static void
mk_list_of_disks(nms_t *list, disk_list_t **hd)
{
	while (list) {
		insert_dlist_ent(list->dsk, list->dnum, list->dty,
					list->devtype, hd);
		list = list->next;
	}
}



/*
 * Determine if a name is already in the list of disks. If not, insert the
 * name in the list.
 */


static void
insert_dlist_ent(const char *nm, const int dn, const char *dty,
			int devtype, disk_list_t ** hd)
{
	disk_list_t *stuff;
	int	i, len;

	if (dty == NULL)
		return;

	stuff = *hd;
	while (stuff) {
		if (strcmp(nm, stuff->dsk) != 0)
			stuff = stuff->next;
		else
			break;
	}
	if (!stuff) {
		disk_list_t	*entry;
		int	mv;

		entry = (disk_list_t *)malloc(
				sizeof (disk_list_t));
		if (entry) {
			entry->dnum = dn;
			entry->dsk = (char *)nm;
			entry->dtype = (char *)dty;

			len = strlen(nm) + 4;
			for (i = 0; i < NDKMAP; i++) {
				if (devtype == DISK) {
					entry->dpart[i] = (char *)malloc(len);
					if (entry->dpart[i]) {
						(void) sprintf(entry->dpart[i],
							"%ss%d\0", nm, i);
					}
				} else
					entry->dpart[i] = NULL;
			}
			/*
			 * Figure out where to insert the name. The list is
			 * ostensibly in sorted order.
			 */
			if (*hd != (disk_list_t *)NULL) {
				disk_list_t *follw;
				stuff = *hd;

				/*
				 * Look through the list. While the strcmp
				 * value is less than the current value,
				 */
				while (stuff) {
					if ((mv = strcmp(entry->dtype,
						stuff->dtype)) < 0) {
							follw = stuff;
							stuff = stuff->next;
					} else
						break;
				}
				if (mv == 0) {
					while (stuff) {
						if (strcmp(entry->dtype,
							stuff->dtype) != 0)
								break;
						if (dn > stuff->dnum) {
							follw = stuff;
							stuff = stuff->next;
						} else
							break;
					}
				}
				/*
				 * We should now be ready to insert an
				 * entry...
				 */
				if (mv >= 0) {
					if (stuff == *hd) {
						entry->next = stuff;
						*hd = entry;
					} else {
						entry->next = follw->next;
						follw->next = entry;
					}
				} else {
					/*
					 * insert at the end of the
					 * list
					 */
					follw->next = entry;
					entry->next = (disk_list_t *)NULL;
				}
			} else {
				*hd = entry;
				entry->next = (disk_list_t *)NULL;
			}
		}
	}
}



char *
lookup_ks_name(char *dev_nm, void *val)
{
	char	*rv = (char *)0;
	int	dv;
	char	*device;
	int	len;
	char	cmpbuf[1024];
	struct	list_of_disks *list;
	char	nmbuf[1024];
	char	*tmpnm;
	char	*nm;
	int	partition;

	tmpnm = nm = nmbuf;
	while ((*dev_nm) && (*dev_nm != ',')) {
		*tmpnm++ = *dev_nm++;
	}
	*tmpnm = '\0';

	if (*dev_nm == ',') {
		dev_nm++;
		partition = (int)(*dev_nm - 'a');
		if ((partition < 0) || (partition > NDKMAP))
			partition = -1;
	} else
		partition = -1;

	list = (disk_list_t *)val;
	device = nm;
	len = 0;
	while (*nm) {
		if (isalpha((int)*nm)) {
			nm++;
			len++;
		} else
			break;
	}
	(void) strncpy(cmpbuf, device, len);
	cmpbuf[len] = '\0';

	if (*nm) {
		int mv;

		dv = atoi(nm);
		while (list) {
			if ((mv = strcmp(cmpbuf, list->dtype)) < 0)
				list = list->next;
			else
				break;
		}
		if (mv == 0) {
			while (list) {
				if (list->dnum < dv)
					list = list->next;
				else
					break;
			}
			if(list) {
				if (list->dnum == dv) {
					if ((partition != -1) &&
						(list->dpart[partition] != NULL))
							rv = list->dpart[partition];
					else
						rv = list->dsk;
				}
			}
		}
	}
	return (rv);
}



static int
str_is_digit(char *str)
{
	int i;
	int j = 0;

	for (i = 0; i < (int)strlen(str); i++) {
		if (isdigit(str[i])) j++;
	}

	if (j == strlen(str))
		return (1);
	else
		return (0);
}

