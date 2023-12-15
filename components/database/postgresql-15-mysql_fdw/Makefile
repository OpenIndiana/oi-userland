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
# Copyright 2023 Andreas Wacknitz
#

BUILD_BITS= 64
BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	mysql_fdw
COMPONENT_VERSION=	2.9.1
ARCHIVE_VERSION=	REL-2_9_1
COMPONENT_SUMMARY=	MySQL Foreign Data Wrapper for PostgreSQL $(PG_VERSION)
COMPONENT_SRC=	$(COMPONENT_NAME)-$(ARCHIVE_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(HUMAN_VERSION).tar.gz
COMPONENT_PROJECT_URL=	https://github.com/EnterpriseDB/$(COMPONENT_NAME)
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/refs/tags/$(ARCHIVE_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:26e8dc2012de6151450fbf2a5cd591a3d5b8a52b1e3ec0600b14a4a6b4a06b54
COMPONENT_FMRI=	database/postgres-$(PG_VERNUM)/mysql_fdw
COMPONENT_CLASSIFICATION=	System/Databases
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE

PG_VERSION=	15

# Don't depend on host default pg_config
PATH= $(PG_HOME)/bin:$(MYSQL_BINDIR.$(BITS)):/usr/sbin:/usr/bin

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ENV   += USE_PGXS=1
COMPONENT_BUILD_ARGS  += MYSQL_LIBNAME=$(MYSQL_LIBDIR)/libmysqlclient.so
COMPONENT_INSTALL_ENV += USE_PGXS=1

# Manually added build dependencies
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
