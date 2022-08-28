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
# Copyright 2016 Alexander Pyhalov
# Copyright 2019 Michal Nowak
#

BUILD_BITS= 64_and_32
BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		lz4
COMPONENT_VERSION=	1.9.4
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_SUMMARY=	Extremely Fast Compression algorithm
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:0b0e3aa07c8c063ddf40b082bdf7e37a1562bda40a0ff5272957f3e987e0e54b
COMPONENT_ARCHIVE_URL=	https://github.com/lz4/lz4/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL=	https://lz4.github.io/lz4/
COMPONENT_FMRI=		library/lz4
COMPONENT_LICENSE=	BSD,GPLv2
COMPONENT_LICENSE_FILE=	lz4.license
COMPONENT_CLASSIFICATION= System/Libraries

include $(WS_MAKE_RULES)/common.mk

BINDIR.32=/usr/bin/$(MACH32)
BINDIR.64=/usr/bin
LIBDIR.32=/usr/lib
LIBDIR.64=/usr/lib/$(MACH64)

COMMON_ENV = CC=$(CC)
COMMON_ENV += CFLAGS="$(CFLAGS)"
COMMON_ENV += PREFIX=/usr
COMMON_ENV += BINDIR=$(BINDIR.$(BITS))
COMMON_ENV += LIBDIR=$(LIBDIR.$(BITS))

COMPONENT_BUILD_ENV = $(COMMON_ENV)
COMPONENT_INSTALL_ENV = $(COMMON_ENV)
COMPONENT_TEST_ENV = $(COMMON_ENV)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
