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
# Copyright 2012 EveryCity Ltd. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		orc
COMPONENT_VERSION=	0.4.23
IPS_COMPONENT_VERSION=	0.5.11
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:767eaebce2941737b43368225ec54598b3055ca78b4dc50c4092f5fcdc0bdfe7
COMPONENT_ARCHIVE_URL=	http://gstreamer.freedesktop.org/src/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# Heals libgstvideoscale core dump
gcc_OPT = -O2

CONFIGURE_OPTIONS  +=	--with-pic
CONFIGURE_OPTIONS  +=	--enable-shared
CONFIGURE_OPTIONS  +=	--disable-static

ENV = /usr/bin/env -i

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
