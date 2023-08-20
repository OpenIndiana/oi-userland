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

BUILD_BITS = 64
BUILD_STYLE = cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	pgAgent
COMPONENT_VERSION= 	4.2.1
COMPONENT_REVISION=	2
COMPONENT_SUMMARY= 	pgAgent job scheduler for PostgreSQL
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-Source
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:caa8fa0587433839d733d0ad1d45f5cd6e2e47c9cd9ce5ab62ab2d0e6b317fb8
COMPONENT_ARCHIVE_URL=	https://ftp.postgresql.org/pub/pgadmin/pgagent/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.pgadmin.org/
COMPONENT_FMRI=	database/postgres/pgagent
COMPONENT_CLASSIFICATION=	System/Databases
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE

# Don't depend on host default pg_config
PATH=	$(PG_BINDIR.$(BITS)):/usr/bin/$(MACH64):/usr/bin

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CMAKE_ACTION = (cp -a $(SOURCE_DIR)/* $(@D))

# Workaround for cmake to look for files in build directory
$(BUILD_DIR)/%/.configured:     $(SOURCE_DIR)/.prep
	($(RM) -rf $(@D) ; $(MKDIR) $(@D))
	$(COMPONENT_PRE_CMAKE_ACTION)
	(cd $(@D) ; $(ENV) $(CMAKE_ENV) \
	        $(CMAKE) $(CMAKE_OPTIONS) $(@D))
	$(COMPONENT_POST_CMAKE_ACTION)
	$(TOUCH) $@

CXXFLAGS += -pthreads

CMAKE_OPTIONS = -D STATIC_BUILD=NO
# Don't depend on host default pg_config
CMAKE_OPTIONS += -D CMAKE_PROGRAM_PATH=$(PATH)
CMAKE_OPTIONS += -D CMAKE_BUILD_WITH_INSTALL_RPATH="TRUE"
CMAKE_OPTIONS += -D CMAKE_INSTALL_RPATH_USE_LINK_PATH="TRUE"
CMAKE_OPTIONS += -D CMAKE_INSTALL_PREFIX=/usr

# How can I tell cmake to use /usr/lib/amd64/cmake instead of /usr/lib/cmake?
CMAKE_OPTIONS += -D CMAKE_PREFIX_PATH="/usr/lib/$(MACH64)/cmake"

# Manually added build dependencies
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/boost
