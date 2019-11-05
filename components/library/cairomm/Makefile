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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2018 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cairomm
COMPONENT_VERSION=	1.12.2
COMPONENT_SUMMARY=	cairomm - C++ Wrapper for the cairo Library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_FMRI=		library/desktop/c++/cairomm
COMPONENT_ARCHIVE_HASH= \
  sha256:45c47fd4d0aa77464a75cdca011143fea3ef795c4753f6e860057da5fb8bd599
COMPONENT_ARCHIVE_URL= \
  http://cairographics.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://cairographics.org/cairomm/

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CXXFLAGS += -std=c++11

CONFIGURE_OPTIONS += --sysconfdir=/etc

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/sigcpp
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += system/library
