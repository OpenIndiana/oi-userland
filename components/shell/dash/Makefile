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
# Copyright 2020 Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		dash
COMPONENT_VERSION=	0.5.11.5
COMPONENT_SUMMARY=	DASH is a POSIX-compliant implementation of /bin/sh that aims to be as small as possible.
COMPONENT_PROJECT_URL=  http://gondor.apana.org.au/~herbert/dash
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/files/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:db778110891f7937985f29bf23410fe1c5d669502760f584e54e0e7b29e123bd
COMPONENT_FMRI=		shell/dash
COMPONENT_CLASSIFICATION=System/Shells
COMPONENT_LICENSE=	BSD

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION= \
	(cd $(SOURCE_DIR) && autoreconf -fi)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
