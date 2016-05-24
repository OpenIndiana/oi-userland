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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= lz4
COMPONENT_VERSION= r131
IPS_COMPONENT_VERSION= 0.131
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_SUMMARY= Extremely Fast Compression algorithm
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
 sha256:9d4d00614d6b9dec3114b33d1224b6262b99ace24434c53487a0c8fd0b18cfed
COMPONENT_ARCHIVE_URL= \
  https://github.com/Cyan4973/lz4/archive/r131.tar.gz
COMPONENT_PROJECT_URL=  http://www.lz4.org
COMPONENT_FMRI=	library/lz4
COMPONENT_LICENSE=      BSD,GPLv2
COMPONENT_LICENSE_FILE= lz4.license
COMPONENT_CLASSIFICATION= System/Libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

BINDIR.32=/usr/bin
BINDIR.64=/usr/bin/$(MACH64)
LIBDIR.32=/usr/lib
LIBDIR.64=/usr/lib/$(MACH64)

COMMON_ENV = CC=$(CC)
COMMON_ENV += CFLAGS="$(CFLAGS)"
COMMON_ENV += PREFIX=/usr
COMMON_ENV += BINDIR=$(BINDIR.$(BITS))
COMMON_ENV += LIBDIR=$(LIBDIR.$(BITS))

COMPONENT_BUILD_ENV = $(COMMON_ENV)
COMPONENT_INSTALL_ENV = $(COMMON_ENV)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)
