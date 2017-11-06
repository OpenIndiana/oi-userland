/*
    libparted - a library for manipulating disk partitions
    Copyright (C) 1999, 2000, 2001, 2007 Free Software Foundation, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <config.h>
#include "configmake.h"

#include <parted/parted.h>
#include <parted/debug.h>

#ifdef linux
#  include <parted/linux.h>
#elif defined(__BEOS__)
#  include <parted/beos.h>
#elif defined(__sun)
#  include <parted/solaris.h>
#else
#  include <parted/gnu.h>
#endif

#if ENABLE_NLS
#  include <locale.h>
#  include <libintl.h>
#  define _(String) dgettext (PACKAGE, String)
#else
#  define _(String) (String)
#endif /* ENABLE_NLS */

const PedArchitecture* ped_architecture;

/* ped_malloc() debugging.  Stick the address and size of memory blocks that
 * weren't ped_free()d in here, and an exception will be thrown when it is
 * allocated.  That way, you can find out what, exactly, the allocated thing
 * is, and where it is created.
 */
typedef struct
{
    void*	pointer;
    size_t	size;
} pointer_size_type;

/* IMHO, none of the DEBUG-related code below is useful, and the
   ped_malloc memset code is actually quite harmful: it masked at
   least two nasty bugs that were fixed in June of 2007.  */
#undef DEBUG
#ifdef DEBUG
static pointer_size_type dodgy_malloc_list[] = {
 {0,		0},
 {0,		0},
 {0,		0},
 {0,		0},
 {0,		0},
 {0,		0},
 {0,		0},
 {0,		0},
 {0,		0},
 {0,		0}
};

static int	dodgy_memory_active[100];
#endif /* DEBUG */

int
ped_set_architecture (const PedArchitecture* arch)
{
	PED_ASSERT (ped_device_get_next (NULL) == NULL, return 0);

	ped_architecture = arch;
	return 1;
}

extern void ped_disk_aix_init ();
extern void ped_disk_bsd_init ();
extern void ped_disk_dvh_init ();
extern void ped_disk_gpt_init ();
extern void ped_disk_loop_init ();
extern void ped_disk_mac_init ();
extern void ped_disk_msdos_init ();
extern void ped_disk_pc98_init ();
extern void ped_disk_sun_init ();
extern void ped_disk_amiga_init ();
extern void ped_disk_dasd_init ();

static void
init_disk_types ()
{
	ped_disk_loop_init ();	/* must be last in the probe list */

#if defined(__s390__) || defined(__s390x__)
	ped_disk_dasd_init();
#endif

	ped_disk_sun_init ();
#ifdef ENABLE_PC98
	ped_disk_pc98_init ();
#endif
	ped_disk_msdos_init ();
	ped_disk_mac_init ();
	ped_disk_gpt_init ();
	ped_disk_dvh_init ();
	ped_disk_bsd_init ();
	ped_disk_amiga_init ();
	ped_disk_aix_init ();
}

#ifdef ENABLE_FS
extern void ped_file_system_amiga_init (void);
extern void ped_file_system_xfs_init (void);
extern void ped_file_system_ufs_init (void);
extern void ped_file_system_reiserfs_init (void);
extern void ped_file_system_ntfs_init (void);
extern void ped_file_system_linux_swap_init (void);
extern void ped_file_system_jfs_init (void);
extern void ped_file_system_hfs_init (void);
extern void ped_file_system_fat_init (void);
extern void ped_file_system_ext2_init (void);
extern void ped_file_system_solaris_x86_init (void);

static void
init_file_system_types ()
{
	ped_file_system_amiga_init ();
	ped_file_system_xfs_init ();
	ped_file_system_ufs_init ();
	ped_file_system_reiserfs_init ();
	ped_file_system_ntfs_init ();
	ped_file_system_linux_swap_init ();
	ped_file_system_jfs_init ();
	ped_file_system_hfs_init ();
	ped_file_system_fat_init ();
	ped_file_system_ext2_init ();
	ped_file_system_solaris_x86_init ();
}
#endif /* ENABLE_FS */

extern void ped_disk_aix_done ();
extern void ped_disk_bsd_done ();
extern void ped_disk_dvh_done ();
extern void ped_disk_gpt_done ();
extern void ped_disk_loop_done ();
extern void ped_disk_mac_done ();
extern void ped_disk_msdos_done ();
extern void ped_disk_pc98_done ();
extern void ped_disk_sun_done ();
extern void ped_disk_amiga_done ();
extern void ped_disk_dasd_done ();

static void
done_disk_types ()
{
#if defined(__s390__) || (__s390x__)
	ped_disk_dasd_done ();
#endif
	ped_disk_sun_done ();
#ifdef ENABLE_PC98
	ped_disk_pc98_done ();
#endif
	ped_disk_msdos_done ();
	ped_disk_mac_done ();
	ped_disk_loop_done ();
	ped_disk_gpt_done ();
	ped_disk_dvh_done ();
	ped_disk_bsd_done ();
	ped_disk_amiga_done ();
	ped_disk_aix_done ();
}

static void _init() __attribute__ ((constructor));

static void
_init()
{
#ifdef ENABLE_NLS
	bindtextdomain (PACKAGE, LOCALEDIR);
#endif

	init_disk_types ();

#ifdef ENABLE_FS
	init_file_system_types ();
#endif

	/* FIXME: a better way of doing this? */
#ifdef linux
	ped_set_architecture (&ped_linux_arch);
#elif defined(__BEOS__)
	ped_set_architecture (&ped_beos_arch);
#elif defined (__sun)
	ped_set_architecture (&ped_solaris_arch);
#else
	ped_set_architecture (&ped_gnu_arch);
#endif

#ifdef DEBUG
	memset (dodgy_memory_active, 0, sizeof (dodgy_memory_active));
#endif
}

#ifdef ENABLE_FS
extern void ped_file_system_ext2_done (void);
extern void ped_file_system_fat_done (void);
extern void ped_file_system_hfs_done (void);
extern void ped_file_system_jfs_done (void);
extern void ped_file_system_linux_swap_done (void);
extern void ped_file_system_ntfs_done (void);
extern void ped_file_system_reiserfs_done (void);
extern void ped_file_system_ufs_done (void);
extern void ped_file_system_xfs_done (void);
extern void ped_file_system_amiga_done (void);

static void
done_file_system_types ()
{
	ped_file_system_ext2_done ();
	ped_file_system_fat_done ();
	ped_file_system_hfs_done ();
	ped_file_system_jfs_done ();
	ped_file_system_linux_swap_done ();
	ped_file_system_ntfs_done ();
	ped_file_system_reiserfs_done ();
	ped_file_system_ufs_done ();
	ped_file_system_xfs_done ();
	ped_file_system_amiga_done ();
}
#endif /* ENABLE_FS */

static void _done() __attribute__ ((destructor));

static void
_done()
{
	ped_device_free_all ();

	done_disk_types ();

#ifdef ENABLE_FS
	done_file_system_types ();
#endif
}

const char*
ped_get_version ()
{
	return VERSION;
}

#ifdef DEBUG
static void
_check_dodgy_pointer (const void* ptr, size_t size, int is_malloc)
{
	int		i;

	for (i=0; dodgy_malloc_list[i].pointer; i++) {
		if (dodgy_malloc_list[i].pointer != ptr)
 			continue;
		if (is_malloc && dodgy_malloc_list[i].size != size)
			continue;
		if (!is_malloc && !dodgy_memory_active[i])
			continue;


		if (is_malloc) {
			ped_exception_throw (
				PED_EXCEPTION_INFORMATION,
				PED_EXCEPTION_OK,
				"Dodgy malloc(%x) == %p occurred (active==%d)",
				size, ptr, dodgy_memory_active[i]);
			dodgy_memory_active[i]++;
		} else {
			ped_exception_throw (
				PED_EXCEPTION_INFORMATION,
				PED_EXCEPTION_OK,
				"Dodgy free(%p) occurred (active==%d)",
				ptr, dodgy_memory_active[i]);
			dodgy_memory_active[i]--;
		}

		return;
	}
}
#endif /* DEBUG */

void*
ped_malloc (size_t size)
{
	void*		mem;

	mem = (void*) malloc (size);
	if (!mem) {
		ped_exception_throw (PED_EXCEPTION_FATAL, PED_EXCEPTION_CANCEL,
				     _("Out of memory."));
		return NULL;
	}

#ifdef DEBUG
	memset (mem, 0xff, size);
	_check_dodgy_pointer (mem, size, 1);
#endif

	return mem;
}

int
ped_realloc (void** old, size_t size)
{
	void*		mem;

	mem = (void*) realloc (*old, size);
	if (!mem) {
		ped_exception_throw (PED_EXCEPTION_FATAL, PED_EXCEPTION_CANCEL,
				     _("Out of memory."));
		return 0;
	}
	*old = mem;
	return 1;
}


void* ped_calloc (size_t size)
{
        void* buf = ped_malloc (size);

        memset (buf, 0, size);

        return buf;
}


void
ped_free (void* ptr)
{
#ifdef DEBUG
	_check_dodgy_pointer (ptr, 0, 0);
#endif

	free (ptr);
}
