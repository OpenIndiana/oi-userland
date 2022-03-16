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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
#
BUILD_BITS= 64
BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	xmltoman
COMPONENT_VERSION= 	0.4
COMPONENT_REVISION=	1
COMPONENT_SUMMARY= 	simple XML to man converter
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:948794a316aaecd13add60e17e476beae86644d066cb60171fc6b779f2df14b0
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/xmltoman/files/xmltoman/$(COMPONENT_ARCHIVE)/$(COMPONENT_ARCHIVE)/download
COMPONENT_PROJECT_URL=	https://sourceforge.net/projects/xmltoman

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ARGS += PREFIX=/usr
COMPONENT_INSTALL_ARGS += PREFIX=/usr

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
