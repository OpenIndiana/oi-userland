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
# Copyright (c) 2010, Oracle and/or it's affiliates.  All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		file
COMPONENT_VERSION=	5.0.4
IPS_PKG_NAME=		file/file
COMPONENT_DESCRIPTION=	"command and library to determine file type"
COMPONENT_CLASSIFICATION="Applications/System Utilities"
COMPONENT_SRC=		$(COMPONENT_NAME)-5.04
COMPONENT_PROJECT_URL =	ftp://ftp.astron.com/pub/file/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:56ddf7135471aa656334ed8fefe1112bcccc2cc3
COMPONENT_ARCHIVE_URL=	ftp://ftp.fu-berlin.de/unix/tools/file/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/archive-libraries-drop
PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/libtool-drop

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

REQUIRED_TOOL +=	/sbin/uname
REQUIRED_TOOL +=	/usr/bin/aclocal-1.10
REQUIRED_TOOL +=	/usr/bin/ar
REQUIRED_TOOL +=	/usr/bin/arch
REQUIRED_TOOL +=	/usr/bin/autoconf
REQUIRED_TOOL +=	/usr/bin/autoheader
REQUIRED_TOOL +=	/usr/bin/autom4te
REQUIRED_TOOL +=	/usr/bin/automake-1.10
REQUIRED_TOOL +=	/usr/bin/basename
REQUIRED_TOOL +=	/usr/bin/bash
REQUIRED_TOOL +=	/usr/bin/chmod
REQUIRED_TOOL +=	/usr/bin/cp
REQUIRED_TOOL +=	/usr/bin/diff
REQUIRED_TOOL +=	/usr/bin/dirname
REQUIRED_TOOL +=	/usr/bin/echo
REQUIRED_TOOL +=	/usr/bin/env
REQUIRED_TOOL +=	/usr/bin/expr
REQUIRED_TOOL +=	/usr/bin/find
REQUIRED_TOOL +=	/usr/bin/gawk
REQUIRED_TOOL +=	/usr/bin/getconf
REQUIRED_TOOL +=	/usr/bin/ggrep
REQUIRED_TOOL +=	/usr/bin/ginstall
REQUIRED_TOOL +=	/usr/bin/gmake
REQUIRED_TOOL +=	/usr/bin/grep
REQUIRED_TOOL +=	/usr/bin/gsed
REQUIRED_TOOL +=	/usr/bin/gpatch
REQUIRED_TOOL +=	/usr/bin/gtar
REQUIRED_TOOL +=	/usr/bin/gzip 
REQUIRED_TOOL +=	/usr/bin/hostname
REQUIRED_TOOL +=	/usr/bin/ksh93
REQUIRED_TOOL +=	/usr/bin/ld
REQUIRED_TOOL +=	/usr/bin/ln
REQUIRED_TOOL +=	/usr/bin/ls
REQUIRED_TOOL +=	/usr/bin/make
REQUIRED_TOOL +=	/usr/bin/mkdir
REQUIRED_TOOL +=	/usr/bin/mv
REQUIRED_TOOL +=	/usr/bin/nm
REQUIRED_TOOL +=	/usr/bin/ranlib
REQUIRED_TOOL +=	/usr/bin/rm
REQUIRED_TOOL +=	/usr/bin/rmdir
REQUIRED_TOOL +=	/usr/bin/sed
REQUIRED_TOOL +=	/usr/bin/sort
REQUIRED_TOOL +=	/usr/bin/strip
REQUIRED_TOOL +=	/usr/bin/touch
REQUIRED_TOOL +=	/usr/bin/tr
REQUIRED_TOOL +=	/usr/gnu/bin/as
REQUIRED_TOOL +=	/usr/gnu/bin/echo
REQUIRED_TOOL +=	/usr/gnu/bin/m4
REQUIRED_TOOL +=	/usr/gnu/bin/mkdir
REQUIRED_TOOL +=	$(SPRO_ROOT)/bin/cc
REQUIRED_TOOL +=	$(SPRO_ROOT)/bin/CC

REQUIRED_FILE +=	/lib/$(MACH64)/libc.so
REQUIRED_FILE +=	/lib/$(MACH64)/libm.so
REQUIRED_FILE +=	/lib/$(MACH64)/libz.so
REQUIRED_FILE +=	/lib/libc.so
REQUIRED_FILE +=	/lib/libm.so
REQUIRED_FILE +=	/lib/libz.so
REQUIRED_FILE +=	/usr/include/assert.h
REQUIRED_FILE +=	/usr/include/ctype.h
REQUIRED_FILE +=	/usr/include/dirent.h
REQUIRED_FILE +=	/usr/include/err.h
REQUIRED_FILE +=	/usr/include/errno.h
REQUIRED_FILE +=	/usr/include/fcntl.h
REQUIRED_FILE +=	/usr/include/getopt.h
REQUIRED_FILE +=	/usr/include/limits.h
REQUIRED_FILE +=	/usr/include/locale.h
REQUIRED_FILE +=	/usr/include/memory.h
REQUIRED_FILE +=	/usr/include/regex.h
REQUIRED_FILE +=	/usr/include/stdarg.h
REQUIRED_FILE +=	/usr/include/stddef.h
REQUIRED_FILE +=	/usr/include/stdint.h
REQUIRED_FILE +=	/usr/include/stdio.h
REQUIRED_FILE +=	/usr/include/stdlib.h
REQUIRED_FILE +=	/usr/include/string.h
REQUIRED_FILE +=	/usr/include/sys/dirent.h
REQUIRED_FILE +=	/usr/include/sys/ioctl.h
REQUIRED_FILE +=	/usr/include/sys/mkdev.h
REQUIRED_FILE +=	/usr/include/sys/mman.h
REQUIRED_FILE +=	/usr/include/sys/param.h
REQUIRED_FILE +=	/usr/include/sys/stat.h
REQUIRED_FILE +=	/usr/include/sys/time.h
REQUIRED_FILE +=	/usr/include/sys/types.h
REQUIRED_FILE +=	/usr/include/sys/utime.h
REQUIRED_FILE +=	/usr/include/sys/wait.h
REQUIRED_FILE +=	/usr/include/time.h
REQUIRED_FILE +=	/usr/include/unistd.h
REQUIRED_FILE +=	/usr/include/utime.h
REQUIRED_FILE +=	/usr/include/wchar.h
REQUIRED_FILE +=	/usr/include/wctype.h
REQUIRED_FILE +=	/usr/include/zlib.h

include ../../make-rules/depend.mk
