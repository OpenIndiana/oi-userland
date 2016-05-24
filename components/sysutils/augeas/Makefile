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
# Copyright 2016 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	augeas
COMPONENT_VERSION=	1.4.0
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Augeas-Tools is a configuration-file editing C library and shell toolkit
COMPONENT_SRC=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:659fae7ac229029e60a869a3b88c616cfd51cf2fba286cdfe3af3a052cb35b30
COMPONENT_ARCHIVE_URL=	\
  http://download.augeas.net/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://augeas.net/index.html
COMPONENT_FMRI=	library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CXXFLAGS.32=-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE
CFLAGS.32=	-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE

CXXFLAGS+=	$(CXXFLAGS.$(BITS))
CFLAGS+=	$(CFLAGS.$(BITS))

COMPONENT_POST_INSTALL_ACTION+= ( \
        $(CLONEY) $(SOURCE_DIR)/lenses $(PROTOUSRSHAREDIR)/$(COMPONENT_NAME)/lenses \
)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
