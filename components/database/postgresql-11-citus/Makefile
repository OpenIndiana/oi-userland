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
BUILD_BITS= 64
USE_OPENSSL11= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		citus
COMPONENT_VERSION=	8.1.1
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=	Citus Open Source PostgreSQL extension
COMPONENT_SRC=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:859de72a95acff17d86d5a6e910126543798bff6cdd8f5f134268c03eabeaab3
COMPONENT_ARCHIVE_URL=	https://github.com/citusdata/citus/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL=	https://www.citusdata.com/
COMPONENT_FMRI=			database/postgres-11/citus
COMPONENT_CLASSIFICATION=	System/Databases
COMPONENT_LICENSE=		AGPLv3.0
COMPONENT_LICENSE_FILE=	LICENSE

PG_VERSION=	11
# Don't depend on host default pg_config
# Note, for PostgreSQL >= 9.6 $(PG_HOME)/bin contains 64-bit files
PATH=		$(PG_HOME)/bin:/usr/sbin:/usr/bin

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/curl
