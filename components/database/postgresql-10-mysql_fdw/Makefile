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
COMPONENT_VERSION =	REL-2_7_0
IPS_COMPONENT_VERSION =	2.7.0
COMPONENT_SUMMARY =	MySQL Foreign Data Wrapper for PostgreSQL $(PG_VERSION)
COMPONENT_SRC =	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH = sha256:99ca12c545292670fdbd63fe8e17e3b1376b0f88d9cdede24139a7992ca8b4d6
COMPONENT_ARCHIVE_URL = https://github.com/EnterpriseDB/$(COMPONENT_NAME)/archive/$(COMPONENT_VERSION).tar.gz
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

COMPONENT_BUILD_ENV	+=	USE_PGXS=1
COMPONENT_BUILD_ARGS	+=	MYSQL_LIBNAME=$(MYSQL_LIBDIR)/libmysqlclient.so
COMPONENT_INSTALL_ENV	+=	USE_PGXS=1

REQUIRED_PACKAGES += database/postgres-10/developer
REQUIRED_PACKAGES += database/mariadb-101/library
