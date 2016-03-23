#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Jim Klimov
#

# BuildRequires: cxxtools, sqlite-3, pg_config (postgres-9*/developer),
# mysql_config (mariadb-55/client, percona, mysql)

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	tntdb
COMPONENT_VERSION=	1.3
COMPONENT_SUMMARY=	C++ library to access SQL databases, easy and robust
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:093ab2694bc66bc05ae0a5c8a505d75ae84d4c35c2ddc0ff0283c5b9574b474b
COMPONENT_ARCHIVE_URL= \
  http://www.tntnet.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.tntnet.org/tntdb.html
COMPONENT_FMRI= library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE = LGPLv2.1
COMPONENT_LICENSE_FILE = COPYING

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CXXFLAGS.32=-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE
CFLAGS.32=-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE
CXXFLAGS+=$(CXXFLAGS.$(BITS))
CFLAGS+=$(CFLAGS.$(BITS))

# Using the /usr/bin/{$MACH64} directory here is important, to find the
# variant of pg_config and mysql_config (mediated links) with proper $BITS.
BINSUBDIR.32=bin
BINSUBDIR.64=bin/$(MACH64)

COMPONENT_COMMON_ENV +=	PATH=$(USRDIR)/$(BINSUBDIR.$(BITS)):/usr/bin:/usr/sfw/bin:/usr/ccs/bin:/usr/sbin:/usr/gnu/bin
COMPONENT_COMMON_ENV += CC="$(CC)"
COMPONENT_COMMON_ENV += CXX="$(CXX)"
COMPONENT_COMMON_ENV += CXXFLAGS="$(CXXFLAGS)"
COMPONENT_COMMON_ENV += LDFLAGS="$(LDFLAGS)"

CONFIGURE_ENV += $(COMPONENT_COMMON_ENV)
COMPONENT_BUILD_ENV += $(COMPONENT_COMMON_ENV)
COMPONENT_INSTALL_ENV += $(COMPONENT_COMMON_ENV)

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --with-mysql=yes
CONFIGURE_OPTIONS += --with-postgresql=yes
CONFIGURE_OPTIONS += --with-replicate=yes
CONFIGURE_OPTIONS += --with-oracle=no

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)
