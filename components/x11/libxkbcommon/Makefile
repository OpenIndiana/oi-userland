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
# Copyright 2016 Gary Mills
# Copyright 2016 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           libxkbcommon
COMPONENT_VERSION=        0.5.0
COMPONENT_FMRI=           x11/library/libxkbcommon
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  xkbcommon - library to handle keyboard descriptions
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:90bd7824742b9a6f52a6cf80e2cadd6f5349cf600a358d08260772615b89d19c
#
# If this download fails, try a manual download from a web browser,
# using the same URL.  Verify that the hash is correct.  Then, copy
# the file to the archives directory.
COMPONENT_ARCHIVE_URL= \
  http://xkbcommon.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://xkbcommon.org/
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION = (cd $(@D) && \
                         libtoolize --automake --copy --force && \
                         aclocal -Im4 && \
                         autoheader && \
                         automake -a -f -c &&\
                         autoconf )

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared
CONFIGURE_OPTIONS+= --with-default-rules=/usr/share/X11/xkb/rules
CONFIGURE_OPTIONS+= --enable-docs


build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libxcb
