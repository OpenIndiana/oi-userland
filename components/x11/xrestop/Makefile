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
# Copyright 2017 Gary Mills
# Copyright 2016 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           xrestop
COMPONENT_VERSION=        0.4
COMPONENT_FMRI=           x11/xrestop
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  the xrestop X-Resource top utility
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:67c2fc94a7ecedbaae0d1837e82e93d1d98f4a6d759828860e552119af3ce257
COMPONENT_ARCHIVE_URL= \
  http://downloads.yoctoproject.org/releases/xrestop/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.x.org/
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= xrestop.license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH = $(PATH.gnu)

COMPONENT_PREP_ACTION = \
	( cd $(@D) && \
                 $(MKDIR) m4 && \
                 libtoolize --copy --force &&\
                 aclocal -I m4 &&\
                 automake -c -f -a &&\
                 autoconf )



build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxres
