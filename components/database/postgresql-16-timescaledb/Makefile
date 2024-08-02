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
# Copyright 2024, Carsten Grzemba
#
BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	timescaledb
COMPONENT_VERSION=	2.16.0
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Timescaledb extension for PostgreSQL
COMPONENT_SRC = $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:c68c12c3d62f2e3c46d277d2558c20e31d3826b84e15a8594d1084874a1ea9a4
COMPONENT_ARCHIVE_URL=	https://github.com/timescale/timescaledb/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	www.timescale.com
COMPONENT_FMRI=	database/postgres-$(PG_VERNUM)/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Databases
COMPONENT_LICENSE=	Apache-2.0 TSL
COMPONENT_LICENSE_FILE=	LICENSE

PG_VERSION= 16

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ACTION= cd $(@D); \
	$(ENV) $(COMPONENT_BUILD_ENV) ./bootstrap -DCMAKE_C_FLAGS=-I$(PG_INCDIR) && \
	cd build && gmake

COMPONENT_INSTALL_ACTION= cd $(@D)/build && $(ENV) $(COMPONENT_INSTALL_ENV) gmake install DESTDIR=$(PROTO_DIR)


# Auto-generated dependencies
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += system/library
