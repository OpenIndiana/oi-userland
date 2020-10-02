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
# Copyright 2016-2018 Aurelien Larcher.  All rights reserved.
# Copyright 2019 Michal Nowak
#

BUILD_BITS= 32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gstreamer1
COMPONENT_VERSION= 1.16.2
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= GNOME streaming media framework
COMPONENT_PROJECT_URL = http://gstreamer.freedesktop.org/
COMPONENT_FMRI= library/audio/gstreamer1
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_SRC_NAME= gstreamer
COMPONENT_SRC= $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:e3f044246783fd685439647373fa13ba14f7ab0b346eadd06437092f8419e94e
COMPONENT_ARCHIVE_URL= \
  http://gstreamer.freedesktop.org/src/$(COMPONENT_SRC_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= LGPLv2

include $(WS_MAKE_RULES)/common.mk

gcc_OPT = -O2

PATH = $(PATH.gnu)

CFLAGS += -I/usr/X11/include

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --libexecdir=$(USRLIBDIR.$(BITS))
CONFIGURE_OPTIONS += --disable-examples
CONFIGURE_OPTIONS.32 += --disable-introspection
CONFIGURE_OPTIONS.64 += --enable-introspection
CONFIGURE_OPTIONS += --program-suffix=""
CONFIGURE_OPTIONS += --with-package-origin="https://github.com/OpenIndiana/oi-userland"

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_INSTALL_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ENV += CC="$(CC)"

unexport SHELLOPTS
COMPONENT_TEST_TRANSFORMS= \
	'-n ' \
	'-e "/TOTAL/p" ' \
	'-e "/PASS/p" '  \
	'-e "/SKIP/p" '  \
	'-e "/XFAIL/p" ' \
	'-e "/FAIL/p" '  \
	'-e "/XPASS/p" ' \
	'-e "/ERROR/p" '

REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
