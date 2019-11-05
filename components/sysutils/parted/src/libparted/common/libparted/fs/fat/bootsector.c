/*
    libparted
    Copyright (C) 1998, 1999, 2000, 2002, 2004, 2007 Free Software Foundation, Inc.

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
#include "fat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

/* Reads in the boot sector (superblock), and does a minimum of sanity
 * checking.  The goals are:
 *	- to detect fat file systems, even if they are damaged [i.e. not
 * return an error / throw an exception]
 *	- to fail detection if there's not enough information for
 * fat_boot_sector_probe_type() to work (or possibly crash on a divide-by-zero)
 */
int
fat_boot_sector_read (FatBootSector* bs, const PedGeometry *geom)
{
	PED_ASSERT (bs != NULL, return 0);
	PED_ASSERT (geom != NULL, return 0);

	if (!ped_geometry_read (geom, bs, 0, 1))
		return 0;

	if (PED_LE16_TO_CPU (bs->boot_sign) != 0xAA55) {
		ped_exception_throw (PED_EXCEPTION_ERROR, PED_EXCEPTION_CANCEL,
			_("File system has an invalid signature for a FAT "
			  "file system."));
		return 0;
	}

	if (!bs->system_id[0]) {
		ped_exception_throw (PED_EXCEPTION_ERROR, PED_EXCEPTION_CANCEL,
			_("File system has an invalid signature for a FAT "
			  "file system."));
		return 0;
	}

	if (!bs->sector_size
            || PED_LE16_TO_CPU (bs->sector_size) % PED_SECTOR_SIZE_DEFAULT) {
		ped_exception_throw (PED_EXCEPTION_ERROR, PED_EXCEPTION_CANCEL,
			_("File system has an invalid sector size for a FAT "
			  "file system."));
		return 0;
	}

	if (!bs->cluster_size) {
		ped_exception_throw (PED_EXCEPTION_ERROR, PED_EXCEPTION_CANCEL,
			_("File system has an invalid cluster size for a FAT "
			  "file system."));
		return 0;
	}

	if (!bs->reserved) {
		ped_exception_throw (PED_EXCEPTION_ERROR, PED_EXCEPTION_CANCEL,
			_("File system has an invalid number of reserved "
			  "sectors for a FAT file system."));
		return 0;
	}

	if (bs->fats < 1 || bs->fats > 4) {
		ped_exception_throw (PED_EXCEPTION_ERROR, PED_EXCEPTION_CANCEL,
			_("File system has an invalid number of FATs."));
		return 0;
	}

	return 1;
}

/*
    Don't trust the FAT12, FAT16 or FAT32 label string.
 */
FatType
fat_boot_sector_probe_type (const FatBootSector* bs, const PedGeometry* geom)
{
	PedSector	logical_sector_size;
	PedSector	first_cluster_sector;
	FatCluster	cluster_count;

	if (!PED_LE16_TO_CPU (bs->dir_entries))
		return FAT_TYPE_FAT32;

	logical_sector_size = PED_LE16_TO_CPU (bs->sector_size) / 512;

	first_cluster_sector
		= PED_LE16_TO_CPU (bs->reserved) * logical_sector_size
		  + 2 * PED_LE16_TO_CPU (bs->fat_length) * logical_sector_size
		  + PED_LE16_TO_CPU (bs->dir_entries)
			/ (512 / sizeof (FatDirEntry));
	cluster_count = (geom->length - first_cluster_sector)
			/ bs->cluster_size / logical_sector_size;
	if (cluster_count > MAX_FAT12_CLUSTERS)
		return FAT_TYPE_FAT16;
	else
		return FAT_TYPE_FAT12;
}

/* Analyses the boot sector, and sticks appropriate numbers in
   fs->type_specific.

   Note: you need to subtract (2 * cluster_sectors) off cluster offset,
   because the first cluster is number 2.  (0 and 1 are not real clusters,
   and referencing them is a bug)
 */
int
fat_boot_sector_analyse (FatBootSector* bs, PedFileSystem* fs)
{
	FatSpecific*		fs_info = FAT_SPECIFIC (fs);
	int			fat_entry_size;

	PED_ASSERT (bs != NULL, return 0);
	
	if (PED_LE16_TO_CPU (bs->sector_size) != 512) {
		if (ped_exception_throw (
			PED_EXCEPTION_BUG,
			PED_EXCEPTION_IGNORE_CANCEL,
			_("This file system has a logical sector size of %d.  "
			"GNU Parted is known not to work properly with sector "
			"sizes other than 512 bytes."),
			(int) PED_LE16_TO_CPU (bs->sector_size))
				!= PED_EXCEPTION_IGNORE)
			return 0;
	}

	fs_info->logical_sector_size = PED_LE16_TO_CPU (bs->sector_size) / 512;

	fs_info->sectors_per_track = PED_LE16_TO_CPU (bs->secs_track);
	fs_info->heads = PED_LE16_TO_CPU (bs->heads);
	if (fs_info->sectors_per_track < 1 || fs_info->sectors_per_track > 63
	    || fs_info->heads < 1 || fs_info->heads > 255) {
		PedCHSGeometry* bios_geom = &fs->geom->dev->bios_geom;
		int cyl_count = 0;

		if (fs_info->heads > 0 && fs_info->sectors_per_track > 0)
			cyl_count = fs->geom->dev->length / fs_info->heads
					/ fs_info->sectors_per_track;

		switch (ped_exception_throw (
			PED_EXCEPTION_ERROR,
			PED_EXCEPTION_FIX + PED_EXCEPTION_IGNORE
			+ PED_EXCEPTION_CANCEL,
			_("The file system's CHS geometry is (%d, %d, %d), "
			  "which is invalid.  The partition table's CHS "
			  "geometry is (%d, %d, %d).  If you select Ignore, "
			  "the file system's CHS geometry will be left "
			  "unchanged.  If you select Fix, the file system's "
			  "CHS geometry will be set to match the partition "
			  "table's CHS geometry."),
			 cyl_count, fs_info->heads, fs_info->sectors_per_track,
			 bios_geom->cylinders, bios_geom->heads,
			 bios_geom->sectors)) {

		case PED_EXCEPTION_FIX:
			fs_info->sectors_per_track = bios_geom->sectors;
			fs_info->heads = bios_geom->heads;
			bs->secs_track
				= PED_CPU_TO_LE16 (fs_info->sectors_per_track);
			bs->heads = PED_CPU_TO_LE16 (fs_info->heads);
			if (!fat_boot_sector_write (bs, fs))
				return 0;
			break;

		case PED_EXCEPTION_CANCEL:
			return 0;

		case PED_EXCEPTION_IGNORE:
			break;

                default:
                        break;
		}
	}

	if (bs->sectors)
		fs_info->sector_count = PED_LE16_TO_CPU (bs->sectors)
						* fs_info->logical_sector_size;
	else
		fs_info->sector_count = PED_LE32_TO_CPU (bs->sector_count)
						* fs_info->logical_sector_size;

	fs_info->fat_table_count = bs->fats;
	fs_info->root_dir_entry_count = PED_LE16_TO_CPU (bs->dir_entries);
	fs_info->fat_offset = PED_LE16_TO_CPU (bs->reserved)
					* fs_info->logical_sector_size;
	fs_info->cluster_sectors = bs->cluster_size
				   * fs_info->logical_sector_size;
	fs_info->cluster_size = fs_info->cluster_sectors * 512;

	if (fs_info->logical_sector_size == 0) {
		ped_exception_throw (PED_EXCEPTION_ERROR, PED_EXCEPTION_CANCEL,
			_("FAT boot sector says logical sector size is 0.  "
			  "This is weird. "));
		return 0;
	}
	if (fs_info->fat_table_count == 0) {
		ped_exception_throw (PED_EXCEPTION_ERROR, PED_EXCEPTION_CANCEL,
			_("FAT boot sector says there are no FAT tables.  This "
			  "is weird. "));
		return 0;
	}
	if (fs_info->cluster_sectors == 0) {
		ped_exception_throw (PED_EXCEPTION_ERROR, PED_EXCEPTION_CANCEL,
			_("FAT boot sector says clusters are 0 sectors.  This "
			  "is weird. "));
		return 0;
	}

	fs_info->fat_type = fat_boot_sector_probe_type (bs, fs->geom);
	if (fs_info->fat_type == FAT_TYPE_FAT12) {
		ped_exception_throw (
			PED_EXCEPTION_NO_FEATURE,
			PED_EXCEPTION_CANCEL,
			_("File system is FAT12, which is unsupported."));
		return 0;
	}
	if (fs_info->fat_type == FAT_TYPE_FAT16) {
		fs_info->fat_sectors = PED_LE16_TO_CPU (bs->fat_length)
				       * fs_info->logical_sector_size;
		fs_info->serial_number
			= PED_LE32_TO_CPU (bs->u.fat16.serial_number);
		fs_info->root_cluster = 0;
		fs_info->root_dir_offset
			= fs_info->fat_offset
			  + fs_info->fat_sectors * fs_info->fat_table_count;
		fs_info->root_dir_sector_count
			= fs_info->root_dir_entry_count * sizeof (FatDirEntry)
			  / (512 * fs_info->logical_sector_size);
		fs_info->cluster_offset
			= fs_info->root_dir_offset
			  + fs_info->root_dir_sector_count;
	}
	if (fs_info->fat_type == FAT_TYPE_FAT32) {
		fs_info->fat_sectors = PED_LE32_TO_CPU (bs->u.fat32.fat_length)
					* fs_info->logical_sector_size;
		fs_info->serial_number
			= PED_LE32_TO_CPU (bs->u.fat32.serial_number);
		fs_info->info_sector_offset
		    = PED_LE16_TO_CPU (fs_info->boot_sector.u.fat32.info_sector)
			  * fs_info->logical_sector_size;
		fs_info->boot_sector_backup_offset
		  = PED_LE16_TO_CPU (fs_info->boot_sector.u.fat32.backup_sector)
			  * fs_info->logical_sector_size;
		fs_info->root_cluster
			= PED_LE32_TO_CPU (bs->u.fat32.root_dir_cluster);
		fs_info->root_dir_offset = 0;
		fs_info->root_dir_sector_count = 0;
		fs_info->cluster_offset
			= fs_info->fat_offset
			  + fs_info->fat_sectors * fs_info->fat_table_count;
	}

	fs_info->cluster_count
		= (fs_info->sector_count - fs_info->cluster_offset)
		  / fs_info->cluster_sectors;

	fat_entry_size = fat_table_entry_size (fs_info->fat_type);
	if (fs_info->cluster_count + 2
			> fs_info->fat_sectors * 512 / fat_entry_size)
		fs_info->cluster_count
			= fs_info->fat_sectors * 512 / fat_entry_size - 2;

	fs_info->dir_entries_per_cluster
		= fs_info->cluster_size / sizeof (FatDirEntry);
	return 1;
}

#ifndef DISCOVER_ONLY
int
fat_boot_sector_set_boot_code (FatBootSector* bs)
{
	PED_ASSERT (bs != NULL, return 0);

	memset (bs, 0, 512);
	memcpy (bs->boot_jump, FAT_BOOT_JUMP, 3);
	memcpy (bs->u.fat32.boot_code, FAT_BOOT_CODE, FAT_BOOT_CODE_LENGTH);
	return 1;
}

int
fat_boot_sector_generate (FatBootSector* bs, const PedFileSystem* fs)
{
	FatSpecific*	fs_info = FAT_SPECIFIC (fs);

	PED_ASSERT (bs != NULL, return 0);

	memcpy (bs->system_id, "MSWIN4.1", 8);
	bs->sector_size = PED_CPU_TO_LE16 (fs_info->logical_sector_size * 512);
	bs->cluster_size = fs_info->cluster_sectors
				/ fs_info->logical_sector_size;
	bs->reserved = PED_CPU_TO_LE16 (fs_info->fat_offset
					/ fs_info->logical_sector_size);
	bs->fats = fs_info->fat_table_count;

	bs->dir_entries = (fs_info->fat_type == FAT_TYPE_FAT16)
			  ? PED_CPU_TO_LE16 (fs_info->root_dir_entry_count)
			  : 0;

	if (fs_info->sector_count / fs_info->logical_sector_size > 0xffff
		|| fs_info->fat_type == FAT_TYPE_FAT32) {
		bs->sectors = 0;
		bs->sector_count = PED_CPU_TO_LE32 (fs_info->sector_count
						/ fs_info->logical_sector_size);
	} else {
		bs->sectors = PED_CPU_TO_LE16 (fs_info->sector_count
					       / fs_info->logical_sector_size);
		bs->sector_count = 0;
	}

	bs->media = 0xf8;

	bs->secs_track = PED_CPU_TO_LE16 (fs_info->sectors_per_track);
	bs->heads = PED_CPU_TO_LE16 (fs_info->heads);
	bs->hidden = PED_CPU_TO_LE32 (fs->geom->start);

	if (fs_info->fat_type == FAT_TYPE_FAT32) {
		bs->fat_length = 0;
		bs->u.fat32.fat_length = PED_CPU_TO_LE32 (fs_info->fat_sectors
						/ fs_info->logical_sector_size);
		bs->u.fat32.flags = 0;	/* FIXME: what the hell are these? */
		bs->u.fat32.version = 0;  /* must be 0, for Win98 bootstrap */
		bs->u.fat32.root_dir_cluster
			= PED_CPU_TO_LE32 (fs_info->root_cluster);
		bs->u.fat32.info_sector
			= PED_CPU_TO_LE16 (fs_info->info_sector_offset
					   / fs_info->logical_sector_size);
		bs->u.fat32.backup_sector
			= PED_CPU_TO_LE16 (fs_info->boot_sector_backup_offset
					   / fs_info->logical_sector_size);

		bs->u.fat32.drive_num = 0x80;	/* _ALWAYS_ 0x80.  silly DOS */

		memset (bs->u.fat32.empty_1, 0, 12);

		bs->u.fat32.ext_signature = 0x29;
		bs->u.fat32.serial_number
			= PED_CPU_TO_LE32 (fs_info->serial_number);
		memcpy (bs->u.fat32.volume_name, "NO NAME    ", 11);
		memcpy (bs->u.fat32.fat_name, "FAT32   ", 8);
	} else {
		bs->fat_length
			= PED_CPU_TO_LE16 (fs_info->fat_sectors
					   / fs_info->logical_sector_size);

		bs->u.fat16.drive_num = 0x80;	/* _ALWAYS_ 0x80.  silly DOS */

		bs->u.fat16.ext_signature = 0x29;
		bs->u.fat16.serial_number
			= PED_CPU_TO_LE32 (fs_info->serial_number);
		memcpy (bs->u.fat16.volume_name, "NO NAME    ", 11);
		memcpy (bs->u.fat16.fat_name, "FAT16   ", 8);
	}

	bs->boot_sign = PED_CPU_TO_LE16 (0xaa55);

	return 1;
}

int
fat_boot_sector_write (const FatBootSector* bs, PedFileSystem* fs)
{
	FatSpecific*	fs_info = FAT_SPECIFIC (fs);

	PED_ASSERT (bs != NULL, return 0);

	if (!ped_geometry_write (fs->geom, bs, 0, 1))
		return 0;
	if (fs_info->fat_type == FAT_TYPE_FAT32) {
		if (!ped_geometry_write (fs->geom, bs,
					 fs_info->boot_sector_backup_offset, 1))
			return 0;
	}
	return ped_geometry_sync (fs->geom);
}

int
fat_info_sector_read (FatInfoSector* is, const PedFileSystem* fs)
{
	FatSpecific*	fs_info = FAT_SPECIFIC (fs);
	int		status;

	PED_ASSERT (is != NULL, return 0);
	
	if (!ped_geometry_read (fs->geom, is, fs_info->info_sector_offset, 1))
		return 0;

	if (PED_LE32_TO_CPU (is->signature_2) != FAT32_INFO_MAGIC2) {
		status = ped_exception_throw (PED_EXCEPTION_WARNING,
				PED_EXCEPTION_IGNORE_CANCEL,
				_("The information sector has the wrong "
				"signature (%x).  Select cancel for now, "
				"and send in a bug report.  If you're "
				"desperate, it's probably safe to ignore."),
				PED_LE32_TO_CPU (is->signature_2));
		if (status == PED_EXCEPTION_CANCEL) return 0;
	}
	return 1;
}

int
fat_info_sector_generate (FatInfoSector* is, const PedFileSystem* fs)
{
	FatSpecific*	fs_info = FAT_SPECIFIC (fs);

	PED_ASSERT (is != NULL, return 0);
	
	fat_table_count_stats (fs_info->fat);

	memset (is, 0, 512);

	is->signature_1 = PED_CPU_TO_LE32 (FAT32_INFO_MAGIC1);
	is->signature_2 = PED_CPU_TO_LE32 (FAT32_INFO_MAGIC2);
	is->free_clusters = PED_CPU_TO_LE32 (fs_info->fat->free_cluster_count);
	is->next_cluster = PED_CPU_TO_LE32 (fs_info->fat->last_alloc);
	is->signature_3 = PED_CPU_TO_LE16 (FAT32_INFO_MAGIC3);

	return 1;
}

int
fat_info_sector_write (const FatInfoSector* is, PedFileSystem *fs)
{
	FatSpecific*	fs_info = FAT_SPECIFIC (fs);

	PED_ASSERT (is != NULL, return 0);
	
	if (!ped_geometry_write (fs->geom, is, fs_info->info_sector_offset, 1))
		return 0;
	return ped_geometry_sync (fs->geom);
}
#endif /* !DISCOVER_ONLY */

