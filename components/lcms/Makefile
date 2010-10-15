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

COMPONENT_NAME=		lcms
COMPONENT_VERSION=	1.19
IPS_PKG_NAME=		library/lcms
COMPONENT_DESCRIPTION=	"Little Color Management System"
COMPONENT_CLASSIFICATION="System/Multimedia Libraries"
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.littlecms.com/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:d5b075ccffc0068015f74f78e4bc39138bcfe2d4
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/project/lcms/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)?use_mirror=voxel

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--includedir=/usr/include/lcms

PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/archive-libraries-drop
PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/libtool-drop

# additional preparation after unpacking and patching
COMPONENT_PREP_ACTION=	$(RM) $(@D)/include/icc34.h

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)


REQUIRED_TOOL +=	/sbin/uname
REQUIRED_TOOL +=	/usr/bin/arch
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
REQUIRED_TOOL +=	/usr/bin/ggrep
REQUIRED_TOOL +=	/usr/bin/gmake
REQUIRED_TOOL +=	/usr/bin/grep
REQUIRED_TOOL +=	/usr/bin/gsed
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
REQUIRED_TOOL +=	/usr/bin/rm
REQUIRED_TOOL +=	/usr/bin/rmdir
REQUIRED_TOOL +=	/usr/bin/sed
REQUIRED_TOOL +=	/usr/bin/sort
REQUIRED_TOOL +=	/usr/bin/strip
REQUIRED_TOOL +=	/usr/bin/touch
REQUIRED_TOOL +=	/usr/bin/tr
REQUIRED_TOOL +=	/usr/gnu/bin/as
REQUIRED_TOOL +=	/usr/gnu/bin/echo
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
REQUIRED_FILE +=	/usr/include/dlfcn.h
REQUIRED_FILE +=	/usr/include/errno.h
REQUIRED_FILE +=	/usr/include/float.h
REQUIRED_FILE +=	/usr/include/jconfig.h
REQUIRED_FILE +=	/usr/include/jerror.h
REQUIRED_FILE +=	/usr/include/jmorecfg.h
REQUIRED_FILE +=	/usr/include/jpeglib.h
REQUIRED_FILE +=	/usr/include/limits.h
REQUIRED_FILE +=	/usr/include/math.h
REQUIRED_FILE +=	/usr/include/stdarg.h
REQUIRED_FILE +=	/usr/include/stdbool.h
REQUIRED_FILE +=	/usr/include/stdint.h
REQUIRED_FILE +=	/usr/include/stdio.h
REQUIRED_FILE +=	/usr/include/stdlib.h
REQUIRED_FILE +=	/usr/include/string.h
REQUIRED_FILE +=	/usr/include/sys/param.h
REQUIRED_FILE +=	/usr/include/sys/stat.h
REQUIRED_FILE +=	/usr/include/sys/types.h
REQUIRED_FILE +=	/usr/include/tiff.h
REQUIRED_FILE +=	/usr/include/tiffio.h
REQUIRED_FILE +=	/usr/include/time.h
REQUIRED_FILE +=	/usr/include/unistd.h
REQUIRED_FILE +=	/usr/include/wchar.h
REQUIRED_FILE +=	/usr/include/zconf.h
REQUIRED_FILE +=	/usr/include/zlib.h
REQUIRED_FILE +=	/usr/lib/$(MACH64)/libjpeg.so
REQUIRED_FILE +=	/usr/lib/$(MACH64)/libtiff.so
REQUIRED_FILE +=	/usr/lib/libjpeg.so
REQUIRED_FILE +=	/usr/lib/libtiff.so

include ../../make-rules/depend.mk
