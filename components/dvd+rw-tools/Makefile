#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2013 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=           dvd+rw-tools
COMPONENT_VERSION=        7.1
COMPONENT_PROJECT_URL=    http://fy.chalmers.se/~appro/linux/DVD+RW/
COMPONENT_SUMMARY=        DVD creation utilities
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=        \
    sha256:f8d60f822e914128bcbc5f64fbe3ed131cbff9045dca7e12c5b77b26edde72ca
COMPONENT_ARCHIVE_URL=        http://fy.chalmers.se/~appro/linux/DVD+RW/tools/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_FMRI=		media/dvd+rw-tools
COMPONENT_CLASSIFICATION=	System/Media

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

CFLAGS += -D_FILE_OFFSET_BITS=64
CFLAGS += -DI_KNOW_ALL_ABOUT_SUDO

COMPONENT_BUILD_ARGS += CC=$(CC)
COMPONENT_BUILD_ARGS += CXX=$(CXX)
COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS)"

# common targets
build:                $(BUILD_32)

install:        $(INSTALL_32)

test:                $(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
