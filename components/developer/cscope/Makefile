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
# Copyright 2016 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
#
PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cscope
COMPONENT_VERSION=	15.9
COMPONENT_PROJECT_URL=	https://cscope.sourceforge.net/
COMPONENT_SUMMARY=	Cscope is a developer's tool for browsing source code.
COMPONENT_DESCRIPTION=	\
Cscope is a developer's tool for browsing source code. It has an impeccable \
Unix pedigree, having been originally developed at Bell Labs back in the \
days of the PDP-11. Cscope was part of the official AT&T Unix distribution \
for many years, and has been used to manage projects involving 20 million \
lines of code! 
COMPONENT_FMRI=         developer/cscope
COMPONENT_CLASSIFICATION=	Development/Editors
COMPONENT_SRC=		cscope-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:c5505ae075a871a9cd8d9801859b0ff1c09782075df281c72c23e72115d9f159
COMPONENT_ARCHIVE_URL= \
  https://downloads.sourceforge.net/cscope/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS +=	-D_FILE_OFFSET_BITS=64

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += library/ncurses
