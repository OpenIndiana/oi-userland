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

BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libpqxx
COMPONENT_VERSION= 6.2.5
COMPONENT_SUMMARY= C++ binding library for PostgreSQL
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:36fcf8439ac7f7cc68b21e95b20e921ece4487cda1cc1d09b798a84e7cb3a4b7
COMPONENT_ARCHIVE_URL= \
  https://github.com/jtv/libpqxx/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL= http://pqxx.org/development/libpqxx/
COMPONENT_FMRI= database/postgres/library/c++/libpqxx
COMPONENT_CLASSIFICATION= Development/Databases
COMPONENT_LICENSE= BSD
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Don't depend on host default pg_config
PATH=$(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT=	$(@D)/configure

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared

COMPONENT_POST_INSTALL_ACTION.64= ( mkdir -p $(PROTO_DIR)/usr/share/doc/libpqxx-$(COMPONENT_VERSION) && \
	$(CP) -a $(BUILD_DIR)/$(MACH64)/doc/html/* $(PROTO_DIR)/usr/share/doc/libpqxx-$(COMPONENT_VERSION) )

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += developer/documentation-tool/doxygen
REQUIRED_PACKAGES += text/xmlto
