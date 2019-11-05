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
# Copyright 2018 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =	citus
COMPONENT_VERSION =	8.0.1
COMPONENT_SUMMARY =	Citus Open Source PostgreSQL extension
COMPONENT_SRC =	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH = \
  sha256:2636b88b7ec17b36a3298cf020a3af9f09ac3ab36ba958e57ad35f32b42e556c
COMPONENT_ARCHIVE_URL = \
  https://github.com/citusdata/citus/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL =	https://www.citusdata.com/
COMPONENT_FMRI =	database/postgres-10/citus
COMPONENT_CLASSIFICATION =	System/Databases
COMPONENT_LICENSE =	AGPLv3.0
COMPONENT_LICENSE_FILE =	LICENSE

PG_VERSION=	10
# Don't depend on host default pg_config
# Note, for PostgreSQL >= 9.6 $(PG_HOME)/bin contains 64-bit files
PATH=		$(PG_HOME)/bin:/usr/sbin:/usr/bin

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

build: $(BUILD_64)

install: $(INSTALL_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += database/postgres-10/library
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/curl
