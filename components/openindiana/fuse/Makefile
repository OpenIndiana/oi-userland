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
# Copyright 2016, Adam Stevko
#

BUILD_STYLE = justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		illumos-fusefs
COMPONENT_VERSION=	5955f660e3eece3e9144ea1d990186cc9a88bc13
IPS_COMPONENT_VERSION=	1.6
COMPONENT_REVISION=	1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH=	sha256:d411a6077e234e770c9d418839230a29709f5e6d821a2b212a87b9b3cb03a74b
COMPONENT_ARCHIVE_URL=	https://github.com/jurikm/illumos-fusefs/archive/$(COMPONENT_VERSION).zip

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# Force gcc 10.
# This should match the compiler used to build illumos-gate.
GCC_VERSION = 10

PATH.prepend += /opt/onbld/bin/i386

# Build
COMPONENT_BUILD_ACTION = \
	cd $(@D)/kernel && $(ENV) CC=$(CC) PATH=$(PATH) dmake -e

# Install
COMPONENT_PRE_INSTALL_ACTION +=	\
	$(MKDIR) $(PROTO_DIR) ;
COMPONENT_INSTALL_ACTION = \
	cd $(@D)/kernel && dmake install
COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTOUSRKERNELDRVDIR) $(PROTOUSRKERNELDRVDIR64) ; \
	$(INSTALL) $(@D)/kernel/proto/$(USRKERNELDRVDIR64)/fuse $(PROTOUSRKERNELDRVDIR64) ; \
	$(INSTALL) $(@D)/kernel/proto/$(USRKERNELDRVDIR)/fuse.conf $(PROTOUSRKERNELDRVDIR) ;

# Auto-generated dependencies
