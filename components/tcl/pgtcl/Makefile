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

BUILD_BITS=32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= pgtcl
COMPONENT_VERSION= 	2.6.3
COMPONENT_REVISION=	1
COMPONENT_SUMMARY= 	A Tcl client library for PostgreSQL
COMPONENT_SRC= 		Pgtcl-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:7950d2640dd206dd07ad36ea96363f3d436d3d2be3fec8993c11f363c55f0d22
COMPONENT_ARCHIVE_URL= \
  https://github.com/flightaware/Pgtcl/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL = http://flightaware.github.io/Pgtcl/
COMPONENT_FMRI=	database/postgres/pgtcl
COMPONENT_CLASSIFICATION= Development/Databases
COMPONENT_LICENSE= BSD
COMPONENT_LICENSE_FILE= LICENSE

# Don't depend on host default pg_config
PATH=$(PG_BINDIR.$(BITS)):$(PATH.illumos)

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION += (cd $(@D) && autoreconf -fi)

CONFIGURE_OPTIONS +=	--enable-threads
CONFIGURE_OPTIONS.64 +=	--enable-64bit

CONFIGURE_OPTIONS.32 += --libdir=/usr/lib/tcl8.6/pgtcl
CONFIGURE_OPTIONS.64 += --libdir=/usr/lib/tcl8.6/pgtcl/$(MACH64)

CONFIGURE_OPTIONS.32    += --with-tcl="/usr/lib"
CONFIGURE_OPTIONS.64    += --with-tcl="/usr/lib/$(MACH64)"

COMPONENT_POST_INSTALL_ACTION= ( mkdir -p $(PROTOUSRSHAREDOCDIR)/pgtcl-$(COMPONENT_VERSION) && \
	 cp -a $(SOURCE_DIR)/doc/html/* $(PROTOUSRSHAREDOCDIR)/pgtcl-$(COMPONENT_VERSION) )  

# Build dependencies
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += system/library
