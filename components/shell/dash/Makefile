#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Adam Stevko
# Copyright 2018 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		dash
COMPONENT_VERSION=	0.5.10.2
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	DASH is a POSIX-compliant implementation of /bin/sh that aims to be as small as possible.
COMPONENT_PROJECT_URL=  http://gondor.apana.org.au/~herbert/dash
COMPONENT_FMRI=		shell/dash
COMPONENT_CLASSIFICATION=System/Shells
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=\
	http://gondor.apana.org.au/~herbert/dash/files/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	\
  sha256:3c663919dc5c66ec991da14c7cf7e0be8ad00f3db73986a987c118862b5f6071
COMPONENT_LICENSE=	BSD

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION= \
	(cd $(SOURCE_DIR) && autoreconf -i)

CONFIGURE_BINDIR.64= $(CONFIGURE_BINDIR.32)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
