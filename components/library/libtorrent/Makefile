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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libtorrent
COMPONENT_VERSION=	0.13.4
COMPONENT_REVISION=	1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://rakshasa.github.io/rtorrent/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:704e097119dc89e2ee4630396b25de1cd64b0549841347ea75b9ef9217084955
COMPONENT_ARCHIVE_URL=	http://rtorrent.net/downloads/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = \
        (cd $(@D) && \
	    autoreconf -f -I./scripts -I. )

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

# this is needed or we can't compile the rak headers
CC=$(CXX)

CXXFLAGS += -std=c++98
CXXFLAGS += $(gcc_OPT)

# Find issues with undefined symbols in build time
LD_OPTIONS += $(LD_Z_DEFS)

LDFLAGS += -lnsl -lsocket
LDFLAGS += -lz

CONFIGURE_OPTIONS  +=	--enable-shared
CONFIGURE_OPTIONS  +=	--disable-debug
CONFIGURE_OPTIONS  +=	--disable-static
#CONFIGURE_OPTIONS  +=	--with-ports
CONFIGURE_OPTIONS  +=	--disable-libtool-lock
CONFIGURE_OPTIONS.32 +=	--srcdir=$(BUILD_DIR_32)
CONFIGURE_OPTIONS.64 +=	--srcdir=$(BUILD_DIR_64)


# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

COMPONENT_TEST_ENV +=	"LDFLAGS=-lnsl -lcppunit -lsocket -lz"
test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
