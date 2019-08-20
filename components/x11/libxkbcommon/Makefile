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

X11_CATEGORY=LIB
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=     libxkbcommon
COMPONENT_VERSION=  0.8.0
COMPONENT_REVISION= 1
COMPONENT_FMRI=     x11/library/libxkbcommon
COMPONENT_SUMMARY=  xkbcommon - library to handle keyboard descriptions
COMPONENT_PROJECT_URL = http://xkbcommon.org/
COMPONENT_SRC=      $(COMPONENT_NAME)-xkbcommon-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  xkbcommon-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:0683c42c7e39b8f68786eab9140461031c8f2dd9616442cf77770d2aea956e7d
COMPONENT_ARCHIVE_URL= \
  https://github.com/xkbcommon/libxkbcommon/archive/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/common.mk

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

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libxcb
