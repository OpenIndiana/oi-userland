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

COMPONENT_NAME= pgtcl
COMPONENT_VERSION= 	2.3.2
COMPONENT_SUMMARY= 	A Tcl client library for PostgreSQL
COMPONENT_SRC= 		Pgtcl-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:514b4fcaa8c6bbd9625943d4c01aafe73cbc26ddda482b510ced17192271a253
COMPONENT_ARCHIVE_URL= \
  https://github.com/flightaware/Pgtcl/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL = http://flightaware.github.io/Pgtcl/
COMPONENT_FMRI=	database/postgres/pgtcl
COMPONENT_CLASSIFICATION= Development/Databases
COMPONENT_LICENSE= BSD
COMPONENT_LICENSE_FILE= LICENSE

# Don't depend on host default pg_config
PATH=$(PG_BINDIR.$(BITS)):$(PATH.illumos)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS +=	--enable-threads
CONFIGURE_OPTIONS.64 +=	--enable-64bit

CONFIGURE_OPTIONS.32 += --libdir=/usr/lib/tcl8.6/pgtcl2.3
CONFIGURE_OPTIONS.64 += --libdir=/usr/lib/tcl8.6/pgtcl2.3/$(MACH64)

CONFIGURE_OPTIONS.32    += --with-tcl="/usr/lib"
CONFIGURE_OPTIONS.64    += --with-tcl="/usr/lib/$(MACH64)"

COMPONENT_POST_INSTALL_ACTION= ( mkdir -p $(PROTOUSRSHAREDOCDIR)/pgtcl-$(COMPONENT_VERSION) && \
	 cp -a $(SOURCE_DIR)/doc/html/* $(PROTOUSRSHAREDOCDIR)/pgtcl-$(COMPONENT_VERSION) )  

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += database/postgres-94/library
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += system/library
