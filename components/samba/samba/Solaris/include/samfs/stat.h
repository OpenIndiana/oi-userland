/*
 * stat.h - SAM-FS file information definitions.
 *
 * Defines the SAM-FS file information structure and functions.
 * The POSIX stat structure and associated macros are used to allow
 * the sam_stat structure to be used on various client machine
 * architectures.
 *
 */

/*
 *    SAM-QFS_notice_begin
 *
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at pkg/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at pkg/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
 *
 *    SAM-QFS_notice_end
 */

#ifndef	SAM_STAT_H
#define	SAM_STAT_H


#ifdef linux
#include <sam/linux_types.h>	/* u_longlong_t */
#endif /* linux */

#ifdef  __cplusplus
extern "C" {
#endif

#define	MAX_ARCHIVE		4
#define	SAM_MIN_SEGMENT_SIZE	(1024*1024) /* Minimum segment size in bytes */

/*
 * If sam/stat.h and sys/stat.h are needed in the same module, then
 * sys/stat.h must be included before sam/stat.h.
 * The following is provided to avoid compilation errors:
 */
#if defined(_SYS_STAT_H) || defined(_LINUX_STAT_H) || defined(_BITS_STAT_H)
#undef st_atime
#undef st_mtime
#undef st_ctime
#undef S_ISBLK
#undef S_ISCHR
#undef S_ISDIR
#undef S_ISFIFO
#undef S_ISGID
#undef S_ISREG
#undef S_ISUID
#undef S_ISLNK
#undef S_ISSOCK

#ifdef	linux
#undef S_IRWXU
#undef S_IRUSR
#undef S_IWUSR
#undef S_IXUSR
#undef S_IRWXG
#undef S_IRGRP
#undef S_IWGRP
#undef S_IXGRP
#undef S_IRWXO
#undef S_IROTH
#undef S_IWOTH
#undef S_IXOTH
#endif	/* linux */

#endif /* defined(_SYS_STAT_H) */

/*
 *	NOTE that in order to pass the following structures from a 64-bit
 *	kernel to a 32-bit application, we need to conditionally define the
 *	positions of the 32-bit time and the pad differently for SPARC and X86.
 */

/*
 * Begin: 32-bit align copyin() structs for amd64 only due to 32-bit x86 ABI
 */
#if _LONG_LONG_ALIGNMENT == 8 && _LONG_LONG_ALIGNMENT_32 == 4
#pragma pack(4)
#endif

#if defined(__sparcv9) || defined(__amd64) || defined(linux)

/*
 * For each archive copy
 */
struct sam_copy_s {
	/* Location of archive file */
	u_longlong_t 	position;
	/* Time archive copy created */
	time_t		creation_time;
	/* Location of copy in archive file - in units of 512 bytes */
	uint_t		offset;
	ushort_t	flags;
	/* Number of VSNs the archive used */
	short		n_vsns;
	/* Media type */
	char		media[4];
	/* VSN */
	char		vsn[32];
};

/*
 * POSIX stat structure.
 */
struct sam_stat {
	uint_t		st_mode;	/* File mode */
	uint_t		st_ino;		/* File serial number */
#ifdef  sun
	/* ID of the device containing the file */
	dev_t		st_dev;
#endif  /* sun */
#ifdef  linux
	/* ID of the device containing the file */
	ushort_t	st_dev;
#endif  /* linux */
	uint_t		st_nlink;	/* Number of links */
	uint_t		st_uid;		/* User ID of the file's owner */
	uint_t		st_gid;		/* Group ID of the file's owner */
	u_longlong_t 	st_size;	/* The file size in bytes */
	time_t 		st_atime;	/* Time of last access */
	time_t 		st_mtime;	/* Time of last data modification */
	time_t 		st_ctime;	/* Time of last file status change */

	/* SAM-FS information. */
	time_t 		attribute_time;	/* Time attributes last changed */
	time_t 		creation_time;	/* Time inode created */
	time_t 		residence_time;	/* Time file changed residence */
	struct 		sam_copy_s copy[MAX_ARCHIVE];
	uint_t		old_attr;	/* File attr, backwards compatible */
	uchar_t		cs_algo;	/* Checksum algorithm indicator */
	uchar_t		flags;		/* Flags:  staging, stage err, etc. */
	uchar_t		stripe_width;	/* Stripe Width set by setfa -s or -h */
	uchar_t		stripe_group;	/* Stripe Group set by setfa -g or -o */
	uint_t 		gen;		/* File generation number */
	uint_t 		partial_size;	/* Partial size in kilobytes */
#ifdef	sun
	/* ID of device if S_IFBLK or S_IFCHR */
	dev_t		rdev;
#endif 	/* sun */
#ifdef linux
	/* ID of device if S_IFBLK or S_IFCHR */
	ushort_t	rdev;
#endif 	/* linux */
	/* Block count in units of 512 byte blocks */
	u_longlong_t 	st_blocks;
	/* Segment size in megabytes (SS_SEGMENT_A) */
	uint_t 		segment_size;
	/* Number of this segment */
	/* 0 - SS_SEGMENT_F, 1 .. n - SS_SEGMENT_S */
	uint_t 		segment_number;
	/* Number of segments to stage ahead */
	uint_t 		stage_ahead;
	/* admin ID; inherited from dir */
	uint_t 		admin_id;
	/* Allocate ahead size set by setfa -A */
	uint_t 		allocahead;
	/*
	 * Object stripe depth in kilobytes.
	 * If this field is used only for OSD support then it should be removed
	 * once it is determined that removing it is safe.  Update the man page
	 * for sam_stat(3) when this is done.
	 */
	uint_t		obj_depth;
	/* 128 bit checksum */
	u_longlong_t 	cs_val[2];
	/* WORM retention period start and duration. */
	time_t		rperiod_start_time;
	uint_t		rperiod_duration;
	projid_t	projid;
	u_longlong_t	attr;		/* File attributes */
};

#else   /* __sparcv9 || __amd64 || linux */
/*
 * For each archive copy.
 */
struct sam_copy_s {
	/* Location of archive file */
	u_longlong_t 	position;
#if 	defined(__i386)
	/* Time archive copy created */
	time_t		creation_time;
	ulong_t		pad0;
#else
	ulong_t		pad0;
	/* Time archive copy created */
	time_t		creation_time;
#endif	/* __i386 */
	/* Location of copy in archive file - in units of 512 bytes */
	ulong_t		offset;
	ushort_t 	flags;
	short		n_vsns;		/* Number of VSNs the archive used */
	char		media[4];	/* Media type */
	char		vsn[32];	/* VSN */
};

/*
 * POSIX stat structure.
 */
struct sam_stat {
	/* File mode */
	ulong_t		st_mode;
	/* File serial number */
	ulong_t		st_ino;
	/* ID of the device containing the file */
	dev_t		st_dev;
	long		pad1;
	ulong_t		st_nlink;	/* Number of links */
	ulong_t		st_uid;		/* User ID of the file's owner */
	ulong_t		st_gid;		/* Group ID of the file's owner */
	u_longlong_t 	st_size;	/* The file size in bytes */
#if 	defined(__i386)
	time_t		st_atime;	/* Time of last access */
	ulong_t		pad2;
	time_t		st_mtime;	/* Time of last data modification */
	ulong_t		pad3;
	time_t		st_ctime;	/* Time of last file status change */
	ulong_t		pad4;

	/* SAM-FS information. */
	time_t		attribute_time;	/* Time attributes last changed */
	ulong_t		pad5;
	time_t		creation_time;	/* Time inode created */
	ulong_t		pad6;
	time_t		residence_time;	/* Time file changed residence */
	ulong_t		pad7;
#else	/* __i386 */
	ulong_t		pad2;
	time_t		st_atime;	/* Time of last access */
	ulong_t		pad3;
	time_t		st_mtime;	/* Time of last data modification */
	ulong_t		pad4;
	time_t		st_ctime;	/* Time of last file status change */

	/* SAM-FS information. */
	ulong_t		pad5;
	time_t		attribute_time;	/* Time attributes last changed */
	ulong_t		pad6;
	time_t		creation_time;	/* Time inode created */
	ulong_t		pad7;
	time_t		residence_time;	/* Time file changed residence */
#endif	/* __i386 */
	struct		sam_copy_s copy[MAX_ARCHIVE];
	uint_t		old_attr;	/* File attr, backwards compatible */
	uchar_t 	cs_algo;	/* Checksum algorithm indicator */
	uchar_t		flags;		/* Flags:  staging, stage err, etc. */
	uchar_t		stripe_width;	/* Stripe Width set by setfa -s or -h */
	uchar_t		stripe_group;	/* Stripe Group set by setfa -g or -o */
	ulong_t		gen;		/* File generation number */
	ulong_t		partial_size;	/* Partial size in kilobytes */
	dev_t		rdev;		/* ID of device if S_IFBLK or S_IFCHR */
	ulong_t		pad8;
	/* Block count in units of 512 byte blocks */
	u_longlong_t 	st_blocks;
	/* Segment size in megabytes (SS_SEGMENT_A) */
	ulong_t 	segment_size;
	/* Number of this segment */
	/* 0 - SS_SEGMENT_F, 1 .. n - SS_SEGMENT_S */
	ulong_t 	segment_number;
	/* Number of segments to stage ahead */
	uint_t 		stage_ahead;
	/* admin ID; inherited from dir */
	ulong_t 	admin_id;
	/* Allocate ahead size set by setfa -A */
	ulong_t 	allocahead;
	ulong_t 	obj_depth;	/* Object stripe depth in kilobytes */
	/* 128 bit checksum */
	u_longlong_t 	cs_val[2];
	/* WORM retention period start and duration. */
#if	defined(__i386)
	time_t		rperiod_start_time;
	ulong_t		pad10;
#else	/* __i386 */
	ulong_t		pad10;
	time_t		rperiod_start_time;
#endif	/* __i386 */
	ulong_t		rperiod_duration;
	ulong_t		projid;
	u_longlong_t	attr;		/* File attributes */
};

#endif   /* __sparcv9 || __amd64 || linux */


#define	SAM_SECTION_SIZE(n) (sizeof (struct sam_section) * n)

struct sam_section {	/* For each archive copy volume section */
	/* VSN */
	char		vsn[32];
	/* Section length of file on this volume */
	u_longlong_t 	length;
	/* Position of archive file for this section */
	u_longlong_t 	position;
	/* Location of copy section in archive file */
	u_longlong_t 	offset;
};

/*
 * End: 32-bit align copyin() structs for amd64 only due to 32-bit x86 ABI
 */
#if _LONG_LONG_ALIGNMENT == 8 && _LONG_LONG_ALIGNMENT_32 == 4
#pragma pack()
#endif

/*
 * POSIX symbols.
 */

#define	S_IRWXU 	00700		/* read, write, execute: owner */
#define	S_IRUSR 	00400		/* read permission: owner */
#define	S_IWUSR 	00200		/* write permission: owner */
#define	S_IXUSR 	00100		/* execute permission: owner */
#define	S_IRWXG 	00070		/* read, write, execute: group */
#define	S_IRGRP 	00040		/* read permission: group */
#define	S_IWGRP 	00020		/* write permission: group */
#define	S_IXGRP 	00010		/* execute permission: group */
#define	S_IRWXO 	00007		/* read, write, execute: other */
#define	S_IROTH 	00004		/* read permission: other */

#define	S_IWOTH 	00002		/* write permission: other */
#define	S_IXOTH 	00001		/* execute permission: other */

#define	S_ISBLK(mode)  	(((mode)&0xf000) == 0x6000)
#define	S_ISCHR(mode)  	(((mode)&0xf000) == 0x2000)
#define	S_ISDIR(mode)  	(((mode)&0xf000) == 0x4000)
#define	S_ISFIFO(mode) 	(((mode)&0xf000) == 0x1000)
#define	S_ISGID(mode)  	((mode)&0x400)  /* set group id on execution */
#define	S_ISREG(mode)  	(((mode)&0xf000) == 0x8000)
#define	S_ISUID(mode)  	((mode)&0x800)  /* set user id on execution */
#define	S_ISLNK(mode)  	(((mode)&0xf000) == 0xa000)
#define	S_ISSOCK(mode) 	(((mode)&0xf000) == 0xc000)

/*
 * SAMFS attributes mapped into sam_stat but not in inode (ino_status_t).
 */
#define	SS_SAMFS	0x00000800	/* SAM-FS file */
#define	SS_ARCHIVE_R 	0x00002000	/* Re-archive */
#define	SS_ARCHIVED  	0x00010000	/* File has at least one archive copy */
#define	SS_DATA_V	0x00040000 	/* File requires data verification */
#define	SS_AIO		0x00080000 	/* AIO Char Device file */
#define	SS_ARCHIVE_A 	0x08000000	/* Archive immediate */

/*
 * SAMFS attributes from the inode.
 */
#define	SS_REMEDIA   	0x00000001	/* Removable media file */
#define	SS_RELEASE_A 	0x00000002	/* Release after archive */
#define	SS_RELEASE_N 	0x00000004	/* Release never (nodrop) */
#define	SS_STAGE_N   	0x00000008	/* Stage never (direct) */
#define	SS_DAMAGED   	0x00000010	/* File is damaged - */
					/* not online and no copy */
#define	SS_RELEASE_P 	0x00000020	/* Release partial (bof_online) */
#define	SS_ARCHIVE_N 	0x00000040	/* Archive never (noarch) */
#define	SS_STAGE_A	0x00000080	/* Stage associative (stageall) */

#define	SS_CSVAL	0x00000100	/* Valid checksum exists in inode */
#define	SS_CSUSE	0x00000200	/* Checksum will be used upon stage */
#define	SS_CSGEN	0x00000400	/* Checksum will be generated upon - */
					/* archive */
/*	SS_SAMFS	0x00000800	used by sam_stat() - see above */

#define	SS_ARCHDONE  	0x00001000	/* File has all required -  */
					/* archiving done */
/*	SS_ARCHIVE_R    0x00002000    	used by sam_stat() - see above */
#define	SS_PARTIAL   	0x00004000	/* Partial extents are online */
#define	SS_OFFLINE   	0x00008000	/* File is offline */

/*	SS_ARCHIVED   	0x00010000  	used by sam_stat() - see above */
#define	SS_SEGMENT_A 	0x00020000	/* Segment attribute */
/*	SS_DATA_V    	0x00040000   	used by sam_stat() - see above */
/*	SS_AIO		0x00080000	used by sam_stat() - see above */

#define	SS_ARCHIVE_C 	0x00100000	/* Archive concurrent */
#define	SS_DIRECTIO  	0x00200000	/* Directio */
#define	SS_ARCHIVE_I 	0x00400000	/* Archive inconsistent copies */
#define	SS_WORM		0x00800000	/* Read only attribute (worm_attr) */

#define	SS_READONLY  	0x01000000	/* Read only file enabled (worm_set) */
#define	SS_SEGMENT_S 	0x02000000	/* This is a segment of a - */
					/* segmented file */
#define	SS_SEGMENT_F 	0x04000000	/* Stage/archive file in segments */
/*	SS_ARCHIVE_A    0x08000000	used by sam_stat() - see above */

#define	SS_SETFA_S   	0x10000000	/* Stripe Width set by setfa -s */
#define	SS_SETFA_H   	0x10000000	/* Stripe Width set by setfa -h */
#define	SS_SETFA_G   	0x20000000	/* Stripe Group set by setfa -g */
#define	SS_SETFA_O   	0x20000000	/* Stripe Group set by setfa -o */
#define	SS_DFACL	0x40000000	/* Default access control list - */
					/* present */
#define	SS_ACL		0x80000000	/* Access control list present */

#define	SS_OBJECT_FS   	0x000100000000	/* Object file system "mb" */

#define	SS_ISSAMFS(attr)	(((attr)&SS_SAMFS) != 0)
#define	SS_ISREMEDIA(attr)   	(((attr)&SS_REMEDIA) != 0)
#define	SS_ISARCHIVED(attr)  	(((attr)&SS_ARCHIVED) != 0)
#define	SS_ISARCHDONE(attr)  	(((attr)&SS_ARCHDONE) != 0)
#define	SS_ISDAMAGED(attr)   	(((attr)&SS_DAMAGED) != 0)
#define	SS_ISOFFLINE(attr)   	(((attr)&SS_OFFLINE) != 0)
#define	SS_ISPARTIAL(attr)   	(((attr)&SS_PARTIAL) != 0)
#define	SS_ISARCHIVE_C(attr) 	(((attr)&SS_ARCHIVE_C) != 0)
#define	SS_ISARCHIVE_I(attr) 	(((attr)&SS_ARCHIVE_I) != 0)
#define	SS_ISARCHIVE_N(attr) 	(((attr)&SS_ARCHIVE_N) != 0)
#define	SS_ISARCHIVE_A(attr) 	(((attr)&SS_ARCHIVE_A) != 0)
#define	SS_ISARCHIVE_R(attr) 	(((attr)&SS_ARCHIVE_R) != 0)
#define	SS_ISRELEASE_A(attr) 	(((attr)&SS_RELEASE_A) != 0)
#define	SS_ISRELEASE_N(attr) 	(((attr)&SS_RELEASE_N) != 0)
#define	SS_ISRELEASE_P(attr) 	(((attr)&SS_RELEASE_P) != 0)
#define	SS_ISSTAGE_A(attr)   	(((attr)&SS_STAGE_A) != 0)
#define	SS_ISSTAGE_N(attr)   	(((attr)&SS_STAGE_N) != 0)
#define	SS_ISSEGMENT_A(attr) 	(((attr)&SS_SEGMENT_A) != 0)
#define	SS_ISSEGMENT_S(attr) 	(((attr)&SS_SEGMENT_S) != 0)
#define	SS_ISSEGMENT_F(attr) 	(((attr)&SS_SEGMENT_F) != 0)
#define	SS_ISCSGEN(attr)	(((attr)&SS_CSGEN) != 0)
#define	SS_ISCSUSE(attr)	(((attr)&SS_CSUSE) != 0)
#define	SS_ISCSVAL(attr)	(((attr)&SS_CSVAL) != 0)
#define	SS_ISDIRECTIO(attr)  	(((attr)&SS_DIRECTIO) != 0)
#define	SS_ISWORM(attr)		(((attr)&SS_WORM) != 0)
#define	SS_ISREADONLY(attr)  	(((attr)&SS_READONLY) != 0)
#define	SS_ISSETFA_G(attr)   	(((attr)&SS_SETFA_G) != 0)
#define	SS_ISSETFA_S(attr)   	(((attr)&SS_SETFA_S) != 0)
#define	SS_ISDFACL(attr)	(((attr)&SS_DFACL) != 0)
#define	SS_ISACL(attr)		(((attr)&SS_ACL) != 0)
#define	SS_ISDATAV(attr)	(((attr)&SS_DATA_V) != 0)
#define	SS_ISAIO(attr)		(((attr)&SS_AIO) != 0)
#define	SS_ISOBJECT_FS(attr)	(((attr)&SS_OBJECT_FS) != 0)
#define	SS_ISSETFA_O(attr)	(((attr)&SS_SETFA_O) != 0)
#define	SS_ISSETFA_H(attr)	(((attr)&SS_SETFA_H) != 0)

/*
 * SAMFS flags.
 */

#define	SS_STAGING		0x01	/* Stage is pending on the file */
#define	SS_STAGEFAIL		0x02	/* Error occurred on - */
					/* last stage attempt */

#define	SS_ISSTAGING(flags)	(((flags)&SS_STAGING) != 0)
#define	SS_ISSTAGEFAIL(flags)	(((flags)&SS_STAGEFAIL) != 0)

/*
 * Copy flag masks.
 */
#define	CF_STALE		0x0001	/* This archive copy is stale */
#define	CF_REARCH		0x0002	/* Copy is to be rearchived */
#define	CF_ARCH_I		0x0004	/* Copy is to be archived immediately */
#define	CF_VERIFIED		0x0008	/* Copy has been verified */
#define	CF_DAMAGED		0x0010	/* This archive copy is damaged */
#define	CF_UNARCHIVED		0x0020	/* This archive copy was unarchived */
#define	CF_INCONSISTENT 	0x0040	/* This archive copy is inconsistent */
#define	CF_ARCHIVED		0x0080	/* This archive copy made */
#define	CF_AR_FLAGS_MASK	0x00FF  /* the flags in the stat struct from */
					/* the AR_FLAGS in the inode */
#define	CF_PAX_ARCH_FMT		0x8000	/* from SAR_hdr_off0 in the inode */

int sam_stat(const char *path, struct sam_stat *buf, size_t bufsize);
int sam_lstat(const char *path, struct sam_stat *buf, size_t bufsize);
int sam_vsn_stat(const char *path, int copy, struct sam_section *buf,
	size_t bufsize);
int sam_segment_vsn_stat(const char *path, int copy, int segment_index,
	struct sam_section *buf, size_t bufsize);
int sam_segment_stat(const char *path, struct sam_stat *buf,
	size_t bufsize);
int sam_segment_lstat(const char *path, struct sam_stat *buf,
	size_t bufsize);
int sam_restore_file(const char *path, struct sam_stat *buf,
	size_t bufsize);
int sam_restore_copy(const char *path, int copy, struct sam_stat *buf,
	size_t bufsize, struct sam_section *vbuf, size_t vbufsize);

/*
 * macro NUM_SEGS, takes in, fsbuff,  a ptr to a sam_stat struct, returns the
 * number of segments of the file associated with fsbuff.
 */

#define	NUM_SEGS(fsbuff) (int)(((fsbuff) == NULL || (fsbuff)->st_size <= 0 || \
				(fsbuff)->segment_size <= 0 || \
				!SS_ISSEGMENT_F((fsbuff)->attr)) ? 0 : \
				((fsbuff)->st_size + \
				(offset_t)(fsbuff)->segment_size * \
				(SAM_MIN_SEGMENT_SIZE) - 1LL) / \
				((offset_t)(fsbuff)->segment_size * \
				(SAM_MIN_SEGMENT_SIZE)))

#ifdef  __cplusplus
}
#endif

#endif /* SAM_STAT_H */
