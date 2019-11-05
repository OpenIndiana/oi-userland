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
# Copyright 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libtheora
COMPONENT_VERSION= 1.1.1
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= Theora video compression codec
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:40952956c47811928d1e7922cda3bc1f427eb75680c3c37249c91e949054916b
COMPONENT_ARCHIVE_URL= \
  http://downloads.xiph.org/releases/theora/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.theora.org
COMPONENT_FMRI=	codec/libtheora
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE = Xiph.org BSD-style
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

# Code in decode.c looks crappy and GCC warns about it.
# This seeems to disable some loop optimizations and fixes crash in oc_init()
gcc_OPT = -O2 

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --enable-shared
CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --disable-examples

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

# Build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/doxygen

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += system/library
