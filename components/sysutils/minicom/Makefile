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
# Copyright 2020 Oxide Computer Company
#

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		minicom
COMPONENT_VERSION=	2.7.1
COMPONENT_SUMMARY=	Serial communication program
COMPONENT_PROJECT_URL=	https://salsa.debian.org/minicom-team/minicom
COMPONENT_FMRI=		terminal/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Applications/System Utilities

COMPONENT_SRC=		$(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://salsa.debian.org/minicom-team/minicom/-/archive/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
    sha256:b9747d619d4ed473e50b4a74af6288848aa16bc41456791ed81704636477f5ee

COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

#
# This release archive is generated directly from a git tag, and thus does not
# have a prepared configure script.
#
COMPONENT_PREP_ACTION += (cd $(@D) && autoreconf -fi)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
