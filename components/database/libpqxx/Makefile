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
# Copyright 2018 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libpqxx
COMPONENT_VERSION= 7.7.5
COMPONENT_SUMMARY= C++ binding library for PostgreSQL
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:c7dc3e8fa2eee656f2b6a8179d72f15db10e97a80dc4f173f806e615ea990973
COMPONENT_ARCHIVE_URL= https://github.com/jtv/libpqxx/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL= https://pqxx.org/development/libpqxx/
COMPONENT_FMRI= database/postgres/library/c++/libpqxx
COMPONENT_CLASSIFICATION= Development/Databases
COMPONENT_LICENSE= BSD
COMPONENT_LICENSE_FILE= COPYING

# Running the tests needs a working Postgrsql server.
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Don't depend on host default pg_config
PATH= $(PG_BINDIR.$(BITS)):$(PATH.illumos)

CXXFLAGS += -std=c++17

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION = ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-documentation

# Manually added build dependencies
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)
REQUIRED_PACKAGES += developer/documentation-tool/doxygen

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
