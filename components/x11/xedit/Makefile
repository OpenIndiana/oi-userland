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

COMPONENT_NAME=           xedit
COMPONENT_VERSION=        1.2.2
COMPONENT_REVISION=       1
COMPONENT_FMRI=           editor/xedit
COMPONENT_CLASSIFICATION= Development/Editors
COMPONENT_SUMMARY=  xedit - simple Xaw toolkit text editor for X
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:69aa42885dfc06332ca22eb01cc7187e49206e6d65b74113a8ee4cc345fc2927
COMPONENT_ARCHIVE_URL= \
  https://www.x.org/releases/individual/app/xedit-1.2.2.tar.bz2
COMPONENT_PROJECT_URL = https://www.x.org/
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= xedit.license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)


REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
