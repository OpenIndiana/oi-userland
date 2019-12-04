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
# Copyright 2019 Alexander Pyhalov
#

BUILD_BITS=64
BUILD_STYLE=justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =	mysql_fdw
COMPONENT_VERSION =	REL-2_5_3
IPS_COMPONENT_VERSION =	2.5.3
COMPONENT_SUMMARY =	MySQL Foreign Data Wrapper for PostgreSQL $(PG_VERSION)
COMPONENT_SRC =	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH = \
  sha256:820e5bf1a55d64db91e4a5247f2859c2d485cc5eece28b6ad520e179e543e518
COMPONENT_ARCHIVE_URL = \
  https://github.com/EnterpriseDB/$(COMPONENT_NAME)/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL =	https://github.com/EnterpriseDB/mysql_fdw/
COMPONENT_FMRI =	database/postgres-$(PG_VERNUM)/mysql_fdw
COMPONENT_CLASSIFICATION =	System/Databases
COMPONENT_LICENSE =	MIT
COMPONENT_LICENSE_FILE =	LICENSE

PG_VERSION=	10
# Don't depend on host default pg_config
# Note, for PostgreSQL >= 9.6 $(PG_HOME)/bin contains 64-bit files
PATH=		$(PG_HOME)/bin:$(MYSQL_BINDIR.$(BITS)):/usr/sbin:/usr/bin

TEST_TARGET=	$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ENV	+=	USE_PGXS=0
COMPONENT_BUILD_ARGS	+=	MYSQL_LIBNAME=$(MYSQL_LIBDIR)/libmysqlclient.so
COMPONENT_INSTALL_ENV	+=	USE_PGXS=0

REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)
REQUIRED_PACKAGES += database/mariadb-101/library
