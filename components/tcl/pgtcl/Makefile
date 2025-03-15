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
COMPONENT_VERSION= 	3.1.0
COMPONENT_REVISION= 	1
COMPONENT_SUMMARY= 	A Tcl client library for PostgreSQL
COMPONENT_SRC= 		Pgtcl-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:fded4aba99b84f4bc41abbaef8d7d0ba1ba6812e56a80689f98d22bd3ab98a23
COMPONENT_ARCHIVE_URL=	https://github.com/flightaware/Pgtcl/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL=	https://flightaware.github.io/Pgtcl/
COMPONENT_FMRI=	database/postgres/pgtcl
COMPONENT_CLASSIFICATION= Development/Databases
COMPONENT_LICENSE= BSD
COMPONENT_LICENSE_FILE= LICENSE

# Don't depend on host default pg_config
PATH=$(PG_BINDIR.$(BITS)):$(PATH.illumos)

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION += ( cd $(@D) && autoreconf -fi )

CONFIGURE_OPTIONS += --enable-threads
CONFIGURE_OPTIONS += --enable-64bit
CONFIGURE_OPTIONS += --libdir=/usr/lib/tcl8.6/pgtcl/$(MACH64)
CONFIGURE_OPTIONS += --with-tcl="/usr/lib/$(MACH64)"
ifeq ($(strip $(MACH)),sparc)
CONFIGURE_OPTIONS += --enable-64bit-vis
endif

COMPONENT_POST_INSTALL_ACTION= ( mkdir -p $(PROTOUSRSHAREDOCDIR)/pgtcl-$(COMPONENT_VERSION) && \
	 cp -a $(SOURCE_DIR)/doc/html/* $(PROTOUSRSHAREDOCDIR)/pgtcl-$(COMPONENT_VERSION) )  

# Build dependencies
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += system/library
