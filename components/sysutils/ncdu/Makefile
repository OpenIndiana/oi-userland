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
#

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ncdu
COMPONENT_VERSION=	1.13
COMPONENT_FMRI=		file/ncdu
COMPONENT_PROJECT_URL=	https://dev.yorhel.nl/$(COMPONENT_NAME)
COMPONENT_SUMMARY=	NCurses Disk Usage
COMPONENT_DESCRIPTION=	Disk usage analyzer with an ncurses interface
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:f4d9285c38292c2de05e444d0ba271cbfe1a705eee37c2b23ea7c448ab37255a
COMPONENT_ARCHIVE_URL=	https://dev.yorhel.nl/download/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	MIT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS +=	-I/usr/include/ncurses

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
