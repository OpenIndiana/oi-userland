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
# Copyright 2015 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           xdriinfo
COMPONENT_VERSION=        1.0.6
COMPONENT_FMRI=           x11/diagnostic/xdriinfo
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  xdriinfo - DRI drivers configuration information query utility
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:d9ccd2c3e87899417acc9ea1f3e319a4198112babe1dc711273584f607449d51
COMPONENT_ARCHIVE_URL= \
  https://www.x.org/releases/individual/app/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.x.org/
COMPONENT_LICENSE=      MIT License

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

LDFLAGS+= -L$(USRLIBDIR)/mesa/$(LIBSUBDIR) -R$(USRLIBDIR)/mesa/$(LIBSUBDIR)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += x11/header/glproto

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/mesa
