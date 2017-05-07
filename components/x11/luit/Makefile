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

COMPONENT_NAME=           luit
COMPONENT_VERSION=        1.1.1
COMPONENT_FMRI=           terminal/luit
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SUMMARY=  luit - Locale and ISO 2022 support for Unicode terminals
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:30b0e787cb07a0f504b70f1d6123930522111ce9d4276f6683a69b322b49c636
COMPONENT_ARCHIVE_URL= \
  http://www.x.org/releases/individual/app/luit-1.1.1.tar.bz2
COMPONENT_PROJECT_URL = http://www.x.org/
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= luit.license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

PKG_CONFIG_PATH+=:$(USRSHAREDIR)/pkgconfig
LD_OPTIONS+= -L$(USRLIBDIR)/xorg/$(ARCHLIBSUBDIR) -R$(USRLIBDIR)/xorg/$(ARCHLIBSUBDIR)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)


REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libfontenc
