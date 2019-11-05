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

COMPONENT_NAME=           libxkbcommon
COMPONENT_VERSION=        0.8.0
COMPONENT_FMRI=           x11/library/libxkbcommon
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  xkbcommon - library to handle keyboard descriptions
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:e829265db04e0aebfb0591b6dc3377b64599558167846c3f5ee5c5e53641fe6d
COMPONENT_ARCHIVE_URL= \
  http://xkbcommon.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://xkbcommon.org/
COMPONENT_LICENSE=      MIT License

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION = (cd $(@D) && \
                         libtoolize --automake --copy --force && \
                         aclocal -Im4 && \
                         autoheader && \
                         automake -a -f -c && \
                         autoconf )

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared
CONFIGURE_OPTIONS+= --with-default-rules=/usr/share/X11/xkb/rules
CONFIGURE_OPTIONS+= --enable-docs

COMPONENT_TEST_TRANSFORMS= \
  '-n ' \
  '-e "/TOTAL/p" ' \
  '-e "/PASS/p" '  \
  '-e "/SKIP/p" '  \
  '-e "/XFAIL/p" ' \
  '-e "/FAIL/p" '  \
  '-e "/XPASS/p" ' \
  '-e "/ERROR/p" ' 


build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libxcb
