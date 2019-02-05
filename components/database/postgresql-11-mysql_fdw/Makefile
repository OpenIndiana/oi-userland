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
# Copyright 2017 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =	mysql_fdw
COMPONENT_VERSION =	REL-2_5_1
IPS_COMPONENT_VERSION =	2.5.1
COMPONENT_SUMMARY =	MySQL Foreign Data Wrapper for PostgreSQL 10
COMPONENT_SRC =	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH = \
  sha256:8367ed71e76000d4ec9661cab7e12c3c8d0ecc887d6f677f7d448a5a35bbd96e
COMPONENT_ARCHIVE_URL = \
  https://github.com/EnterpriseDB/$(COMPONENT_NAME)/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL =	https://github.com/EnterpriseDB/mysql_fdw/
COMPONENT_FMRI =	database/postgres-11/mysql_fdw
COMPONENT_CLASSIFICATION =	System/Databases
COMPONENT_LICENSE =	MIT
COMPONENT_LICENSE_FILE =	LICENSE

PG_VERSION=	11
# Don't depend on host default pg_config
# Note, for PostgreSQL >= 9.6 $(PG_HOME)/bin contains 64-bit files
PATH=		$(PG_HOME)/bin:$(MYSQL_BINDIR.$(BITS)):/usr/sbin:/usr/bin

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ENV	+=	USE_PGXS=0
COMPONENT_BUILD_ARGS	+=	MYSQL_LIBNAME=$(MYSQL_LIBDIR)/libmysqlclient.so
COMPONENT_INSTALL_ENV	+=	USE_PGXS=0

build: $(BUILD_64)

install: $(INSTALL_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += database/postgres-11/developer
REQUIRED_PACKAGES += database/mariadb-101/library
