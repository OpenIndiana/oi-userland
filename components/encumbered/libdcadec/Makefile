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
# Copyright 2016 phorcys@126.com.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libdcadec
COMPONENT_VERSION= 0.2.0
COMPONENT_FMRI = library/audio/libdcadec
COMPONENT_PROJECT_URL = https://github.com/foo86/dcadec
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_SUMMARY= dcadec is a free DTS Coherent Acoustics decoder with support for HD extensions.
COMPONENT_SRC= dcadec-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:ed9d207fde3e8d576f3af8b0d1235b3371e315175757173689104efcaebf0d44
COMPONENT_ARCHIVE_URL= \
  https://github.com/foo86/dcadec/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE = LGPLv2.1

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ENV += CC=$(CC)
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += LDFLAGS="$(LDFLAGS)"
COMPONENT_BUILD_ARGS+= CONFIG_SHARED=1

COMPONENT_INSTALL_ENV += LDFLAGS="$(LDFLAGS)"
COMPONENT_INSTALL_ENV += PREFIX=$(USRDIR)
COMPONENT_INSTALL_ENV += BINDIR=$(USRBINDIR.$(BITS))
COMPONENT_INSTALL_ENV += LIBDIR=$(USRLIBDIR.$(BITS))
COMPONENT_INSTALL_ARGS+= CONFIG_SHARED=1

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
