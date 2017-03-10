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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           orc
COMPONENT_VERSION=        0.4.26
IPS_COMPONENT_VERSION=    0.5.11
HUMAN_VERSION=            $(COMPONENT_VERSION)
COMPONENT_FMRI=           system/library/orc
COMPONENT_PROJECT_URL=    http://code.entropywave.com/projects/orc/
COMPONENT_SUMMARY=        The Oil Runtime Compiler for SIMD array operations
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
  sha256:7d52fa80ef84988359c3434e1eea302d077a08987abdde6905678ebcad4fa649
COMPONENT_ARCHIVE_URL= \
  http://gstreamer.freedesktop.org/src/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=        BSD

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Heals libgstvideoscale core dump
gcc_OPT = -O2

CONFIGURE_OPTIONS  +=	--with-pic
CONFIGURE_OPTIONS  +=	--enable-shared
CONFIGURE_OPTIONS  +=	--disable-static

ENV = /usr/bin/env -i

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
