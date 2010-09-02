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

COMPONENT_NAME=		libmng
COMPONENT_VERSION=	1.0.10
IPS_PKG_NAME=		library/libmng
COMPONENT_DESCRIPTION=	"Multiple-image Network Graphics (MNG) format image files."
COMPONENT_CLASSIFICATION="System/Multimedia Libraries"
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.libmng.com/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:78ad516a1de79d00de720bf2a7c9afea2c896b09
COMPONENT_ARCHIVE_URL=	http://prdownloads.sourceforge.net/libmng/$(COMPONENT_ARCHIVE)

# The tarball doesn't come with a configure script.  We have to use the
# GNU auto* tools to generate one when we prep the code.
COMPONENT_PREP_ACTION =	(cd $(COMPONENT_SRC) ; \
			 $(CP) makefiles/configure.in makefiles/Makefile.am . ;\
			 aclocal-1.10 ; \
			 libtoolize ; \
			 automake-1.10 --add-missing ; \
			 autoconf )

CONFIGURE_OPTIONS +=	--includedir=/usr/include/libmng
CONFIGURE_OPTIONS +=	--localstatedir=/var
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--disable-libtool-lock
CONFIGURE_OPTIONS +=	--enable-largefile
CONFIGURE_OPTIONS +=	--enable-buildso
CONFIGURE_OPTIONS +=	--enable-read
CONFIGURE_OPTIONS +=	--enable-write
CONFIGURE_OPTIONS +=	--enable-display
CONFIGURE_OPTIONS +=	--enable-dynamic
CONFIGURE_OPTIONS +=	--enable-chunks
CONFIGURE_OPTIONS +=	--enable-storechunks
CONFIGURE_OPTIONS +=	--with-lcms
CONFIGURE_OPTIONS +=	--with-pic

# because Solaris puts the headers in a non-standard place
CONFIGURE_ENV +=	CPPFLAGS=-I/usr/include/lcms


include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/archive-libraries-drop
PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/libtool-drop

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)


REQUIRED_TOOL +=	/opt/sunstudio12.1/prod/bin/CC
REQUIRED_TOOL +=	/opt/sunstudio12.1/prod/bin/cc
REQUIRED_TOOL +=	/sbin/uname
REQUIRED_TOOL +=	/usr/bin/aclocal-1.10
REQUIRED_TOOL +=	/usr/bin/amd64/ld
REQUIRED_TOOL +=	/usr/bin/amd64/nm
REQUIRED_TOOL +=	/usr/bin/amd64/sort
REQUIRED_TOOL +=	/usr/bin/amd64/strip
REQUIRED_TOOL +=	/usr/bin/arch
REQUIRED_TOOL +=	/usr/bin/autoconf
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
REQUIRED_TOOL +=	/usr/bin/gawk
REQUIRED_TOOL +=	/usr/bin/gfind
REQUIRED_TOOL +=	/usr/bin/ggrep
REQUIRED_TOOL +=	/usr/bin/ginstall
REQUIRED_TOOL +=	/usr/bin/gmake
REQUIRED_TOOL +=	/usr/bin/grep
REQUIRED_TOOL +=	/usr/bin/gsed
REQUIRED_TOOL +=	/usr/bin/gtar
REQUIRED_TOOL +=	/usr/bin/gzip
REQUIRED_TOOL +=	/usr/bin/hostname
REQUIRED_TOOL +=	/usr/bin/i86/ksh93
REQUIRED_TOOL +=	/usr/bin/ld
REQUIRED_TOOL +=	/usr/bin/libtoolize
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
REQUIRED_TOOL +=	/usr/gnu/bin/m4
REQUIRED_TOOL +=	/usr/gnu/bin/mkdir
REQUIRED_TOOL +=	/usr/gnu/bin/sort
REQUIRED_TOOL +=	/usr/gnu/bin/uname

REQUIRED_FILE +=	/usr/include/jpeglib.h
REQUIRED_FILE +=	/usr/include/lcms/lcms.h
REQUIRED_FILE +=	/usr/include/limits.h
REQUIRED_FILE +=	/usr/include/math.h
REQUIRED_FILE +=	/usr/include/memory.h
REQUIRED_FILE +=	/usr/include/setjmp.h
REQUIRED_FILE +=	/usr/include/stddef.h
REQUIRED_FILE +=	/usr/include/stdio.h
REQUIRED_FILE +=	/usr/include/stdlib.h
REQUIRED_FILE +=	/usr/include/string.h
REQUIRED_FILE +=	/usr/include/strings.h
REQUIRED_FILE +=	/usr/include/zlib.h

include ../../make-rules/depend.mk
