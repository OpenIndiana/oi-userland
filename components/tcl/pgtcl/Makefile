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
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= pgtcl

COMPONENT_VERSION= 	1.9
COMPONENT_SUMMARY= 	A Tcl client library for PostgreSQL
COMPONENT_SRC= 		Pgtcl-$(PGTCL_COMMIT)
PGTCL_COMMIT=		3b2b2f8e35ec3ae65d2fc295e6a6ce7afbd5e26d
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH= \
  sha256:5c1c81a2b3874a63c7a5b25c07f2d2e562575366e803b6338262c4730696840d
COMPONENT_ARCHIVE_URL= \
  https://github.com/flightaware/Pgtcl/archive/$(PGTCL_COMMIT).zip
COMPONENT_PROJECT_URL = http://flightaware.github.io/Pgtcl/

# Don't depend on host default pg_config
PATH=$(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_OPTIONS +=	--enable-threads

CONFIGURE_OPTIONS.32 += --libdir=/usr/lib/tcl8.5/pgtcl1.9
CONFIGURE_OPTIONS.64 += --libdir=/usr/lib/tcl8.5/pgtcl1.9/$(MACH64)
#CONFIGURE_OPTIONS.32    += --with-tcl="/usr/lib"
#CONFIGURE_OPTIONS.64    += --with-tcl="/usr/lib/$(MACH64)"


COMPONENT_POST_INSTALL_ACTION= ( mkdir -p $(PROTOUSRSHAREDOCDIR)/pgtcl-$(COMPONENT_VERSION) && \
	 cp -a $(SOURCE_DIR)/doc/html/* $(PROTOUSRSHAREDOCDIR)/pgtcl-$(COMPONENT_VERSION) )  

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
