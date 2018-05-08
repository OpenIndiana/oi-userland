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
# Copyright 2016 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=			  appres
COMPONENT_VERSION=        1.0.5
COMPONENT_REVISION=       1
COMPONENT_FMRI=           x11/appres
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=        appres - Xt application resource list utility
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:ffad893712c81943b919e3cbfe46fc65259cc0d9eb96d5e658670e3fbb265928
COMPONENT_ARCHIVE_URL=    $(XORG_APP_BASE_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL =   $(XORG_PROJECT_URL)
COMPONENT_LICENSE=        MIT License

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

build: $(BUILD_64)

install: $(INSTALL_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/toolkit/libxt
