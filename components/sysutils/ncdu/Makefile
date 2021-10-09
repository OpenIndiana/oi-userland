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
# Copyright 2018 Harry Liebel
# Copyright 2021 Andreas Wacknitz
#

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ncdu
COMPONENT_VERSION=	1.16
COMPONENT_PROJECT_URL=	https://dev.yorhel.nl/$(COMPONENT_NAME)
COMPONENT_SUMMARY=	NCurses Disk Usage
COMPONENT_DESCRIPTION=	Disk usage analyzer with an ncurses interface
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:2b915752a183fae014b5e5b1f0a135b4b408de7488c716e325217c2513980fd4
COMPONENT_ARCHIVE_URL=	https://dev.yorhel.nl/download/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		file/ncdu
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_LICENSE=	MIT

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CFLAGS +=	-I/usr/include/ncurses

# Auto-generated dependencies
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
