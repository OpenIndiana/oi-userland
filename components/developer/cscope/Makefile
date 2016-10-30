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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cscope
COMPONENT_VERSION=	15.8b
IPS_COMPONENT_VERSION=	15.8.2
COMPONENT_PROJECT_URL=	http://cscope.sourceforge.net/
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
COMPONENT_ARCHIVE_HASH=	sha256:4889d091f05aa0845384b1e4965aa31d2b20911fb2c001b2cdcffbcb7212d3af
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/cscope/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS +=	-D_FILE_OFFSET_BITS=64

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += library/ncurses
