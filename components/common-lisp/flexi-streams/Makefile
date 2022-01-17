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
# Copyright 2015 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		flexi-streams
COMPONENT_VERSION=	1.0.19
COMPONENT_SUMMARY=	FLEXI-STREAMS implements "virtual" bivalent streams
COMPONENT_PROJECT_URL=	http://weitz.de/flexi-streams/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:5e0d4cfa66496ec0ddd501de1d4c19c1d99232ee601d82dce9ef4585f2b47b29
COMPONENT_ARCHIVE_URL=	https://github.com/edicl/flexi-streams/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_FMRI=		library/common-lisp/flexi-streams
COMPONENT_LICENSE=	BSD-style

include ../../../make-rules/prep.mk
include ../../../make-rules/common-lisp.mk
include ../../../make-rules/ips.mk

build:		$(BUILD_32)

install:	$(INSTALL_32)
