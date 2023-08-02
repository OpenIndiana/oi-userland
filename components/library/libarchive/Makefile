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
# Copyright (c) 2012, 2015, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
#

BUILD_BITS= 64_and_32
USE_OPENSSL11= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libarchive
COMPONENT_VERSION=	3.7.1
COMPONENT_SUMMARY=	multi-format archive and compression library
COMPONENT_DESCRIPTION=	The libarchive(3LIB) library provides a flexible\
 interface for reading and writing archives in various formats such as\
 tar(1) and cpio(1). libarchive also supports reading and writing\
 archives compressed using various compression filters such as gzip(1)\
 and bzip2(1). The library is inherently stream-oriented;\
 readers serially iterate through the archive, writers serially\
 add things to the archive.
COMPONENT_SRC=			libarchive-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://www.libarchive.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:5d24e40819768f74daf846b99837fc53a3a9dcdf3ce1c2003fe0596db850f0f0
COMPONENT_ARCHIVE_URL=	https://www.libarchive.org/downloads/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			library/libarchive
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=		BSD-like

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-largefile
# We don't have an iconv library and using this will make depending packages fail when trying to find it:
CONFIGURE_OPTIONS += --without-iconv
# Linking libarchive with lzo violates LZO GPL licence
CONFIGURE_OPTIONS += --without-lzo
# We prefer openssl over nettle.
CONFIGURE_OPTIONS += --without-nettle
CONFIGURE_OPTIONS += --with-openssl
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-xml2
CONFIGURE_OPTIONS += --with-zlib

# libarchive's Makefile hard-codes some gcc-only flags in COMMON_CFLAGS, then
# appends CFLAGS to that.  Reset the former here so we can build with Studio.
COMPONENT_BUILD_ARGS +=	COMMON_CFLAGS=''
COMPONENT_BUILD_ARGS +=	CFLAGS="$(CFLAGS)"
COMPONENT_TEST_ARGS +=	COMMON_CFLAGS=''
COMPONENT_TEST_ARGS +=	CFLAGS="$(CFLAGS)"

CONFIGURE_OPTIONS.64 += LDFLAGS=-L$(OPENSSL_PREFIX)/lib/$(MACH64)
CONFIGURE_OPTIONS.32 += LDFLAGS=-L$(OPENSSL_PREFIX)/lib
CONFIGURE_OPTIONS += CPPFLAGS=-I$(OPENSSL_PREFIX)/include

# We need GNU awk for the following to work; hence the PATH tweak.
# We then convert BSD-style section numbers in the libarchive man pages to
# Solaris-style section numbers.
COMPONENT_PREP_ACTION = \
	cd $(@D)/doc ; rm -f man/*.[135] ; env PATH=/usr/gnu/bin:$$PATH $(CONFIG_SHELL) update.sh ; \
	cd $(@D)/libarchive ; \
	find . -name "*\.[35]" | xargs /usr/bin/gsed -i 's/\(Xr.*\|Dt.*\)3/\13ARCHIVE/' ; \
	find . -name "*\.[35]" | xargs /usr/bin/gsed -i \
	-e 's/Xr \(malloc\|getpwuid\|getgrgud\|strerror\|printf\|getpwnam\|getgrnam\) 3ARCHIVE/Xr \13C/' \
	-e 's/\(Dt.*LIBARCHIVE.*\)3ARCHIVE/\13LIB/' \
	-e 's/Xr \(libarchive\|archive\) 3ARCHIVE/Xr libarchive 3LIB/';

PKG_PROTO_DIRS += $(COMPONENT_SRC)/doc/man

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset and xtrace being
# set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS

# Tests may fail for other locales.
COMPONENT_TEST_ENV += LC_ALL=C.UTF-8

# Build requirements
REQUIRED_PACKAGES += print/filter/ghostscript
REQUIRED_PACKAGES += text/groff

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/lz4
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
