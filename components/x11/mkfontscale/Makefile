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

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= mkfontscale
COMPONENT_VERSION= 1.1.3
COMPONENT_SUMMARY= mkfontscale legacy X11 scalable font metadata creation tool
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:1e98df69ee5f4542d711e140e1d93e2c3f2775407ccbb7849110d52b91782a6a
COMPONENT_ARCHIVE_URL= \
  http://ftp.x.org/pub/individual/app/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.x.org/wiki/
COMPONENT_FMRI= x11/mkfontscale
COMPONENT_LICENSE= MIT
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_CLASSIFICATION= System/X11

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS += --with-bzip2

build: $(BUILD_64)

install: $(INSTALL_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += x11/library/libfontenc
