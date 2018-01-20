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

COMPONENT_NAME= libpqxx
COMPONENT_VERSION= 4.0.1
COMPONENT_REVISION= 3
COMPONENT_SUMMARY= C++ binding library for PostgreSQL
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:097ceda2797761ce517faa5bee186c883df1c407cb2aada613a16773afeedc38
COMPONENT_ARCHIVE_URL= \
  http://pqxx.org/download/software/libpqxx/$(COMPONENT_ARCHIVE)
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

COMPONENT_POST_INSTALL_ACTION.64= ( mkdir -p $(PROTO_DIR)/usr/share/doc/libpqxx-4.0 && \
	cp -a $(SOURCE_DIR)/doc/html/* $(PROTO_DIR)/usr/share/doc/libpqxx-4.0 )  

COMPONENT_POST_INSTALL_ACTION += $(COMPONENT_POST_INSTALL_ACTION.$(BITS))

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/postgres-94/developer
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += system/library/gcc-6-runtime
REQUIRED_PACKAGES += system/library/math
