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
# Copyright 2017 Alexander Pyhalov
#

BUILD_BITS = 32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gstreamer
COMPONENT_VERSION= 0.10.36
COMPONENT_REVISION= 5
COMPONENT_SUMMARY= GNOME streaming media framework
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:e556a529e0a8cf1cd0afd0cab2af5488c9524e7c3f409de29b5d82bb41ae7a30
COMPONENT_ARCHIVE_URL= \
  http://gstreamer.freedesktop.org/src/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://gstreamer.freedesktop.org/
COMPONENT_FMRI = library/audio/gstreamer
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_LICENSE = LGPLv2.0
COMPONENT_LICENSE_FILE = COPYING

USE_DEFAULT_TEST_TRANSFORMS = yes

include $(WS_MAKE_RULES)/common.mk

gcc_OPT = -O2

PATH = $(PATH.gnu)

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS.32 += --libexecdir=/usr/lib
CONFIGURE_OPTIONS.64 += --libexecdir=/usr/lib/$(MACH64)
CONFIGURE_OPTIONS += --disable-examples
CONFIGURE_OPTIONS.32 += --enable-introspection=no
CONFIGURE_OPTIONS += --program-suffix=""

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_INSTALL_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ENV += CC="$(CC)"

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
