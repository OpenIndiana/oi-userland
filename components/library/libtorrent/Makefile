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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright 2020, Aurelien Larcher 
#

BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libtorrent
COMPONENT_VERSION=	0.13.8
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://rakshasa.github.io/rtorrent/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ed115a28f4ae8cfcd33b94a597c076ca74fd549867a26e4fac9505c27288e983
COMPONENT_ARCHIVE_URL=	http://rtorrent.net/downloads/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = \
        (cd $(@D) && \
	    autoreconf -f -I./scripts -I. )

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

# this is needed or we can't compile the rak headers
CC=$(CXX)

CXXFLAGS += -std=c++11
CXXFLAGS += $(gcc_OPT)

# Find issues with undefined symbols in build time
LD_OPTIONS += $(LD_Z_DEFS)

LDFLAGS += -lnsl -lsocket
LDFLAGS += -lz

unexport SHELLOPTS

CONFIGURE_OPTIONS  +=	--enable-shared
CONFIGURE_OPTIONS  +=	--disable-debug
CONFIGURE_OPTIONS  +=	--disable-static
#CONFIGURE_OPTIONS  +=	--with-ports
CONFIGURE_OPTIONS  +=	--disable-libtool-lock
CONFIGURE_OPTIONS.64 +=	--srcdir=$(BUILD_DIR_64)

COMPONENT_TEST_ENV +=	"LDFLAGS=-lnsl -lcppunit -lsocket -lz"
COMPONENT_TEST_TRANSFORMS = $(CONFIGURE_TEST_TRANSFORMS)
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
