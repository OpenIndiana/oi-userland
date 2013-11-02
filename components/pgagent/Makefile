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

include ../../make-rules/shared-macros.mk

CMAKE=	cmake

COMPONENT_NAME= 	pgAgent
COMPONENT_VERSION= 	3.3.0
COMPONENT_SUMMARY= 	pgAgent job scheduler for PostgreSQL
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-Source
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:110f2fd811a05ea8a420a79fcbb25b971e60f10f8abb8ab2bede8419c58b7321
COMPONENT_ARCHIVE_URL= \
  http://ftp.postgresql.org/pub/pgadmin3/release/pgagent/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.pgadmin.org/

# Don't depend on host default pg_config
PATH=		$(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION =        (cp -a $(SOURCE_DIR)/* $(@D))

CMAKE_OPTIONS = -D STATIC_BUILD=NO
# Don't depend on host default pg_config
CMAKE_OPTIONS += -D CMAKE_PROGRAM_PATH=$(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin
CMAKE_OPTIONS += -D CMAKE_BUILD_WITH_INSTALL_RPATH="TRUE"
CMAKE_OPTIONS += -D CMAKE_INSTALL_RPATH_USE_LINK_PATH="TRUE"

CMAKE_OPTIONS += -D CMAKE_INSTALL_PREFIX=/usr

$(BUILD_DIR)/%/.configured:     $(SOURCE_DIR)/.prep
	($(RM) -rf $(@D) ; $(MKDIR) $(@D))
	$(COMPONENT_PRE_CONFIGURE_ACTION)
	(cd $(@D) ; $(ENV) $(CONFIGURE_ENV) $(CMAKE) $(CMAKE_OPTIONS) $(SOURCE_DIR))
	$(COMPONENT_POST_CONFIGURE_ACTION)
	$(TOUCH) $@

build: $(BUILD_32)

install: $(INSTALL_32)
