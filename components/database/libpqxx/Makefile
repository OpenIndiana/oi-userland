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
COMPONENT_VERSION= 6.2.4
COMPONENT_SUMMARY= C++ binding library for PostgreSQL
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:91a295d9e06fc36db5d993970aa1928e053a57ec03bf6284a1c534844ed35ed3
COMPONENT_ARCHIVE_URL= \
  https://github.com/jtv/libpqxx/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL= http://pqxx.org/development/libpqxx/
COMPONENT_FMRI= database/postgres/library/c++/libpqxx
COMPONENT_CLASSIFICATION= Development/Databases
COMPONENT_LICENSE= BSD
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Don't depend on host default pg_config
PATH=$(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT=	$(@D)/configure

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared

COMPONENT_POST_INSTALL_ACTION.64= ( mkdir -p $(PROTO_DIR)/usr/share/doc/libpqxx-$(COMPONENT_VERSION) && \
	cp -a $(BUILD_DIR)/amd64/doc/html/* $(PROTO_DIR)/usr/share/doc/libpqxx-$(COMPONENT_VERSION) )

COMPONENT_POST_INSTALL_ACTION += $(COMPONENT_POST_INSTALL_ACTION.$(BITS))

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/postgres-94/developer
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += developer/documentation-tool/doxygen
REQUIRED_PACKAGES += text/xmlto
