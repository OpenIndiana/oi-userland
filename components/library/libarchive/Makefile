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
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libarchive
COMPONENT_VERSION=	3.1.2
COMPONENT_REVISION=	2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.libarchive.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:eb87eacd8fe49e8d90c8fdc189813023ccc319c5e752b01fb6ad0cc7b2c53d5e
COMPONENT_ARCHIVE_URL=	\
    $(COMPONENT_PROJECT_URL)downloads/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libarchive

TPNO=			24584

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-largefile
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

# We need GNU awk for the following to work; hence the PATH tweak.
# We then convert BSD-style section numbers in the libarchive man pages to
# Solaris-style section numbers.
COMPONENT_PREP_ACTION = \
	cd $(@D)/doc/man ; rm *.[135] ; env PATH=/usr/gnu/bin:$$PATH gmake all ; \
	cd $(@D)/libarchive ; \
	find . -name "*\.[35]" | xargs /usr/bin/gsed -i 's/\(Xr.*\|Dt.*\)3/\13ARCHIVE/' ; \
	find . -name "*\.[35]" | xargs /usr/bin/gsed -i \
	-e 's/Xr \(malloc\|getpwuid\|getgrgud\|strerror\|printf\|getpwnam\|getgrnam\) 3ARCHIVE/Xr \13C/' \
	-e 's/\(Dt.*LIBARCHIVE.*\)3ARCHIVE/\13LIB/' \
	-e 's/Xr \(libarchive\|archive\) 3ARCHIVE/Xr libarchive 3LIB/';

PKG_PROTO_DIRS += $(COMPONENT_SRC)/doc/man

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
	'-e "s|/tmp/.*_test.*|\\$$(TESTDIR)|g"' \
	'-e "s|^.*$(CC).*$$|XXX_CC_XXX|"' \
	'-e "s/ld: warning: symbol .* has differing sizes:$$/XXX_CC_XXX/"' \
	'-e "s/.*value=0x[0-9a-f]\+.*$$/XXX_CC_XXX/"' \
	'-e "s/.* definition taken$$/XXX_CC_XXX/"' \
	'-e "/^XXX_CC_XXX$$/d"'

build:		$(BUILD_32_and_64)
install:	$(INSTALL_32_and_64)
test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/lzo
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
