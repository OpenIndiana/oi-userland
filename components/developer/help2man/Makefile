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
# Copyright 2013, Adam Stevko. All rights reserved.
# Copyright 2019, Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		help2man
COMPONENT_VERSION=	1.49.3
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	help2man is a tool for automatically generating simple manual pages from program output
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:4d7e4fdef2eca6afe07a2682151cea78781e0a4e8f9622142d9f70c083a2fd4f
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/help2man/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/help2man/
COMPONENT_FMRI=		developer/build/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Development/GNU
COMPONENT_LICENSE=	GPL-3.0-only
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET = $(NO_TESTS)

include $(WS_TOP)/make-rules/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl
