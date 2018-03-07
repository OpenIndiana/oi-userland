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

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           oclock
COMPONENT_VERSION=        1.0.4
COMPONENT_FMRI=           x11/oclock
COMPONENT_CLASSIFICATION= Applications/Accessories
COMPONENT_SUMMARY=  oclock - round X clock 
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:cc20cfc1c0d5128d89e1eecd9ba52e58f111075be163e0aeda5690dbaafbaefe
COMPONENT_ARCHIVE_URL= \
  https://www.x.org/releases/individual/app/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.x.org/
COMPONENT_LICENSE=      MIT License

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

build: $(BUILD_64)

install: $(INSTALL_64)

test: $(NO_TESTS)


REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxkbfile
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxt
