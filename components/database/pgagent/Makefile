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

COMPONENT_NAME= 	pgAgent
COMPONENT_VERSION= 	3.4.0
COMPONENT_SUMMARY= 	pgAgent job scheduler for PostgreSQL
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-Source
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:0da0ac8f453cf34ab6f708eee036bed0fd0e5fa311de283b92d2ff06600bbb3d
COMPONENT_ARCHIVE_URL= \
  https://ftp.postgresql.org/pub/pgadmin/pgagent/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.pgadmin.org/
COMPONENT_FMRI=	database/postgres/pgagent
COMPONENT_CLASSIFICATION=	System/Databases
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE

# Don't depend on host default pg_config
PATH=		$(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CMAKE_ACTION =        (cp -a $(SOURCE_DIR)/* $(@D))

# Workaround for cmake to look for files in build directory
$(BUILD_DIR)/%/.configured:     $(SOURCE_DIR)/.prep
	($(RM) -rf $(@D) ; $(MKDIR) $(@D))
	$(COMPONENT_PRE_CMAKE_ACTION)
	(cd $(@D) ; $(ENV) $(CMAKE_ENV) \
	        $(CMAKE) $(CMAKE_OPTIONS) $(@D))
	$(COMPONENT_POST_CMAKE_ACTION)
	$(TOUCH) $@

CMAKE_OPTIONS = -D STATIC_BUILD=NO
# Don't depend on host default pg_config
CMAKE_OPTIONS += -D CMAKE_PROGRAM_PATH=$(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin
CMAKE_OPTIONS += -D CMAKE_BUILD_WITH_INSTALL_RPATH="TRUE"
CMAKE_OPTIONS += -D CMAKE_INSTALL_RPATH_USE_LINK_PATH="TRUE"

CMAKE_OPTIONS += -D CMAKE_INSTALL_PREFIX=/usr

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

REQUIRED_PACKAGES += database/postgres-94/library
REQUIRED_PACKAGES += library/graphics/wxwidgets
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += system/library/gcc-6-runtime
