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
# Copyright 2025 Bill Sommerfeld
#

DROP_STATIC_LIBRARIES= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libdbi-drivers
COMPONENT_VERSION= 0.9.0
COMPONENT_SUMMARY= Database access drivers for libdbi
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL= http://libdbi-drivers.sourceforge.net/
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:43d2eacd573a4faff296fa925dd97fbf2aedbf1ae35c6263478210c61004c854

COMPONENT_ARCHIVE_URL= https://sourceforge.net/projects/$(COMPONENT_NAME)/files/$(COMPONENT_NAME)/$(COMPONENT_NAME)-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

COMPONENT_CLASSIFICATION=System/Libraries

COMPONENT_FMRI.sqlite3= library/libdbi/sqlite3
COMPONENT_FMRI.mysql= library/libdbi/mysql
COMPONENT_FMRI.pgsql= library/libdbi/pgsql

COMPONENT_LICENSE= LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

# tests exist but don't compile with modern compiler
# and require running database instances
COMPONENT_TEST_TARGETS=

CONFIGURE_OPTIONS += --enable-docs=no
CONFIGURE_OPTIONS += --with-dbi-libdir=/usr/lib/$(MACH64)

CONFIGURE_OPTIONS += --with-sqlite3

CONFIGURE_OPTIONS += --with-mysql --with-mysql-libdir=$(MYSQL_LIBDIR)
CONFIGURE_OPTIONS += --with-pgsql --with-pgsql-libdir=$(PG_LIBDIR)

# Borrowed from library/opendbx:
# RPATH needed to make 'make REQUIRED_PACKAGES' happy
COMPONENT_POST_CONFIGURE_ACTION= \
        (cd $(@D) ; \
	$(GSED) -i -e 's:^LDFLAGS = .*:LDFLAGS = -m64 -Wl,-rpath=$(MYSQL_LIBDIR):' drivers/mysql/Makefile; \
	$(GSED) -i -e 's:^LDFLAGS = .*:LDFLAGS = -m64 -Wl,-rpath=$(PG_LIBDIR):' drivers/pgsql/Makefile )

include $(WS_MAKE_RULES)/common.mk

CFLAGS += -std=c99 $(CPP_XPG6MODE)
# tests need this (and need more work)
CFLAGS += -Wno-error=int-conversion

# Manually added
REQUIRED_PACKAGES += $(MYSQL_CLIENT_PKG)
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/libdbi
REQUIRED_PACKAGES += system/library
