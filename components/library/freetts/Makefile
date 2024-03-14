#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017 Alexander Pyhalov
#

BUILD_STYLE= ant
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		freetts
COMPONENT_VERSION=	1.2.2
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=      FreeTTS Speech Synthesis System
COMPONENT_PROJECT_URL=	https://freetts.sourceforge.net/docs/index.php
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)-src.zip
COMPONENT_ARCHIVE_HASH=	sha256:270bbf8c3ab1571585f0a78818ba73b601ef515eb1e6087293c41177219ed156
COMPONENT_ARCHIVE_URL=	https://downloads.sourceforge.net/project/freetts/FreeTTS/FreeTTS%20$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/java/freetts
COMPONENT_CLASSIFICATION=	Applications/Universal Access
COMPONENT_LICENSE=	Other

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# userland-unpack can't overwrite META-INF directory
UNPACK= /usr/bin/unzip -o

CLEAN_PATHS += META-INF

COMPONENT_BUILD_ARGS= -Dsrc_dir=.

install: $(BUILD_64)
	$(MKDIR) $(PROTO_DIR)/usr/share/lib/freetts
	$(CP) $(BUILD_DIR_64)/lib/*.jar $(BUILD_DIR_64)/bin/*.jar $(PROTO_DIR)/usr/share/lib/freetts
	$(TOUCH) $(INSTALL_64)

# Manually added build dependencies
REQUIRED_PACKAGES += developer/build/ant

# Auto-generated dependencies
