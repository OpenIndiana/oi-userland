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
# Copyright 2016 Alexander Pyhalov
# Copyright 2019 Michal Nowak
#

BUILD_BITS = 32_and_64
BUILD_STYLE = meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         glib
COMPONENT_MJR_VERSION=	2.62
COMPONENT_MNR_VERSION=	6
COMPONENT_REVISION=     3
# Note: When updating this component make sure that it still works with our HAL.
# Version 2.66.x is known for its problems eg. when plugging/unplugging USB devices under X11.
# 2.62.6 is the last known working version (2.63.x, 2.64.x untested).
COMPONENT_VERSION=      $(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
# We need to have a fake version because we had delivered non-working versions before:
IPS_COMPONENT_VERSION=	2.70.0
COMPONENT_SUMMARY=      GNOME core libraries
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Libraries
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:104fa26fbefae8024ff898330c671ec23ad075c1c0bce45c325c6d5657d58b9c
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://www.gtk.org/
COMPONENT_FMRI=         library/glib2

include $(WS_MAKE_RULES)/common.mk

PYTHON_VERSION = 3.5

# dbus-daemon is in /usr/lib
PATH = $(PATH.gnu):/usr/lib

# socketpair(3socket) requires -lsocket -lnsl
LDFLAGS += -lsocket -lnsl

# Support for hexadecimal strings in strtod() is available in C99 mode only,
# but we cannot use -std=c99 because float/double support is broken there
# (https://www.illumos.org/issues/14935)
CFLAGS += -std=gnu99

# We need standard conforming getpwnam_r()/getpwuid_r()
CPPFLAGS += $(CPP_XPG6MODE)

# Some warnings are treated as errors by default but we do not want that
CFLAGS += -Wno-error=format-nonliteral
CFLAGS += -Wno-error=format-security

# We do not have getxattr() so disable xattr
CONFIGURE_OPTIONS += -Dxattr=false
CONFIGURE_OPTIONS += -Dfam=true
CONFIGURE_OPTIONS += -Dman=true

COMPONENT_POST_CONFIGURE_ACTION= \
  ( cd $(@D); $(GSED) -i "s/_FILE_OFFSET_BITS=64/_FILE_OFFSET_BITS=$(BITS)/g" ./build.ninja )

# We need to install libraries and set correct LD_LIBRARY_PATH before test
$(TEST_TARGET): $(INSTALL_TARGET)

COMPONENT_TEST_TRANSFORMER = $(NAWK)
COMPONENT_TEST_TRANSFORMS = "'/^(Fail|Ok|Expected Fail|Unexpected Pass|Skipped|Timeout)/'"

# dbus-daemon is needed for testing
REQUIRED_PACKAGES += system/library/dbus

# update-desktop-database is needed for testing
REQUIRED_PACKAGES += library/desktop/desktop-file-utils

# Auto-generated dependencies
REQUIRED_PACKAGES += library/file-monitor/gamin
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
