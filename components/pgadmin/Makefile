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
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= 	pgadmin3
COMPONENT_VERSION= 	1.18.1
COMPONENT_SUMMARY= 	pgAdminIII administration and development GUI for PostgreSQL
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:27ac3e296a6ca3da9da8ee22ed98eabfe1377be507877ffc26048fc2a9c6cbc0
COMPONENT_ARCHIVE_URL= \
  http://ftp.postgresql.org/pub/pgadmin3/release/v$(COMPONENT_VERSION)/src/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.pgadmin.org

# Don't depend on host default pg_config
PATH=$(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

LDFLAGS+=   -L$(PG_LIBDIR.$(BITS))   -R$(PG_LIBDIR.$(BITS))
LDFLAGS+=   -lsocket -lnsl

CONFIGURE_OPTIONS += --with-pgsql=$(PG_HOME)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION =        (cp -a $(SOURCE_DIR)/* $(@D))

COMPONENT_BUILD_ENV     +=      LDFLAGS="$(LDFLAGS)"

build: $(BUILD_32)

install: $(INSTALL_32)
