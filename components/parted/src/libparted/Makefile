#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
#
# Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#
# Copyright 2014 Alexander Pyhalov
#

LIBRARY_LINK=	libparted.so
LIBRARY=	$(LIBRARY_LINK).8	

SRCDIR=		common

PLIBDIR=	$(SRCDIR)/lib
LIBPDIR=	$(SRCDIR)/libparted
LIBPADIR=	$(SRCDIR)/libparted/arch
LIBPCSDIR=	$(SRCDIR)/libparted/cs
LIBAMIGAFS=	$(SRCDIR)/libparted/fs/amiga
LIBEXT2FS=	$(SRCDIR)/libparted/fs/ext2
LIBFATFS=	$(SRCDIR)/libparted/fs/fat
LIBHFS=		$(SRCDIR)/libparted/fs/hfs
LIBJFS=		$(SRCDIR)/libparted/fs/jfs
LIBLINUXSWAP=	$(SRCDIR)/libparted/fs/linux_swap
LIBNTFS=	$(SRCDIR)/libparted/fs/ntfs
LIBREISERFS=	$(SRCDIR)/libparted/fs/reiserfs
LIBSOLARISX86=	$(SRCDIR)/libparted/fs/solaris_x86
LIBUFS=		$(SRCDIR)/libparted/fs/ufs
LIBXFS=		$(SRCDIR)/libparted/fs/xfs
LIBLABELS=	$(SRCDIR)/libparted/labels

OBJECTS=	$(PLIBDIR)/basename.o		$(PLIBDIR)/quotearg.o \
		$(PLIBDIR)/close-stream.o	$(PLIBDIR)/regex.o \
		$(PLIBDIR)/closeout.o		$(PLIBDIR)/rpmatch.o \
		$(PLIBDIR)/dirname.o		$(PLIBDIR)/safe-read.o \
		$(PLIBDIR)/error.o		$(PLIBDIR)/safe-write.o \
		$(PLIBDIR)/exitfail.o		$(PLIBDIR)/strcspn.o \
		$(PLIBDIR)/full-write.o		$(PLIBDIR)/stripslash.o \
		$(PLIBDIR)/getopt.o		$(PLIBDIR)/strndup.o \
		$(PLIBDIR)/version-etc-fsf.o \
		$(PLIBDIR)/localcharset.o	$(PLIBDIR)/version-etc.o \
		$(PLIBDIR)/long-options.o	$(PLIBDIR)/xalloc-die.o \
		$(PLIBDIR)/memcpy.o		$(PLIBDIR)/xmalloc.o \
		$(PLIBDIR)/memmove.o		$(PLIBDIR)/xstrndup.o \
		$(PLIBDIR)/memset.o \
		$(LIBPDIR)/debug.o		$(LIBPDIR)/exception.o \
		$(LIBPDIR)/device.o		$(LIBPDIR)/filesys.o \
		$(LIBPDIR)/timer.o		$(LIBPDIR)/unit.o \
		$(LIBPDIR)/disk.o		$(LIBPDIR)/libparted.o \
		$(LIBPADIR)/solaris.o \
		$(LIBPCSDIR)/constraint.o	$(LIBPCSDIR)/geom.o \
		$(LIBPCSDIR)/natmath.o \
		$(LIBAMIGAFS)/affs.o		$(LIBAMIGAFS)/amiga.o  \
		$(LIBAMIGAFS)/apfs.o		$(LIBAMIGAFS)/asfs.o  \
		$(LIBAMIGAFS)/interface.o \
		$(LIBEXT2FS)/interface.o	$(LIBEXT2FS)/ext2.o \
		$(LIBEXT2FS)/ext2_inode_relocator.o \
		$(LIBEXT2FS)/parted_io.o	$(LIBEXT2FS)/ext2_meta.o \
		$(LIBEXT2FS)/ext2_block_relocator.o \
		$(LIBEXT2FS)/ext2_mkfs.o	$(LIBEXT2FS)/tune.o \
		$(LIBEXT2FS)/ext2_buffer.o	$(LIBEXT2FS)/ext2_resize.o \
		$(LIBFATFS)/table.o		$(LIBFATFS)/bootsector.o \
		$(LIBFATFS)/clstdup.o		$(LIBFATFS)/count.o \
		$(LIBFATFS)/fatio.o		$(LIBFATFS)/traverse.o \
		$(LIBFATFS)/calc.o		$(LIBFATFS)/context.o \
		$(LIBFATFS)/fat.o		$(LIBFATFS)/resize.o \
		$(LIBHFS)/cache.o		$(LIBHFS)/probe.o \
		$(LIBHFS)/advfs.o		$(LIBHFS)/hfs.o \
		$(LIBHFS)/file.o		$(LIBHFS)/reloc.o \
		$(LIBHFS)/advfs_plus.o		$(LIBHFS)/journal.o \
		$(LIBHFS)/file_plus.o		$(LIBHFS)/reloc_plus.o \
		$(LIBJFS)/jfs.o \
		$(LIBLINUXSWAP)/linux_swap.o \
		$(LIBNTFS)/ntfs.o \
		$(LIBREISERFS)/geom_dal.o	$(LIBREISERFS)/reiserfs.o \
		$(LIBSOLARISX86)/solaris_x86.o \
		$(LIBUFS)/ufs.o \
		$(LIBXFS)/xfs.o \
		$(LIBLABELS)/dos.o		$(LIBLABELS)/efi_crc32.o \
		$(LIBLABELS)/mac.o		$(LIBLABELS)/sun.o \
		$(LIBLABELS)/aix.o		$(LIBLABELS)/dvh.o \
		$(LIBLABELS)/gpt.o		$(LIBLABELS)/pc98.o \
		$(LIBLABELS)/bsd.o		$(LIBLABELS)/loop.o \
		$(LIBLABELS)/rdb.o \

SRCS=		$(OBJECTS:%.o=%.c)


%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -fPIC -DPIC -c -o $@ $<

$(LIBRARY): $(OBJECTS)
	$(CC) -Wl,-M$(SRCDIR)/mapfile-vers -Wl,-zinterpose $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o  $(LIBRARY)

CFLAGS +=	$(CCVERBOSE)
CPPFLAGS +=	-I$(SRCDIR)/lib -I$(SRCDIR)/include
LDLIBS +=	-ldiskmgt -luuid -lc -lnvpair
LDFLAGS +=	-shared

$(LIBRARY_LINK): $(LIBRARY)
	ln -s $(LIBRARY) $(LIBRARY_LINK)

all: 	$(LIBRARY_LINK) 

clean: 
	rm -f $(LIBRARY) $(LIBRARY_LINK) $(OBJECTS)

HEADERS=	constraint.h crc32.h debug.h device.h \
		disk.h endian.h exception.h filesys.h \
		geom.h natmath.h parted.h solaris.h \
		timer.h unit.h

install: $(LIBRARY_LINK) 
	for i in $(HEADERS); do \
		install -D $(SRCDIR)/include/parted/$$i $(DESTDIR)/usr/include/parted/$$i; \
	done
	install -D $(LIBRARY) $(DESTDIR)/usr/lib/$(LIBRARY)
	ln -s $(LIBRARY) $(DESTDIR)/usr/lib/$(LIBRARY_LINK)

$(LIBRARY):	$(OBJECTS)
