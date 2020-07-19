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

BUILD_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ibus-anthy
COMPONENT_VERSION= 1.5.11
COMPONENT_CLASSIFICATION= System/Internationalization
COMPONENT_SUMMARY= iBus Japanese IME - anthy
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:809596b0d4630c5861a96fc28800ebaa1ab007787b22f5d7d3c7c0152fd78fff
COMPONENT_ARCHIVE_URL= \
  https://github.com/ibus/ibus-anthy/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://github.com/fujiwarat/ibus-anthy/wiki
COMPONENT_FMRI = system/input-method/ibus/anthy
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)
PYTHON_VERSION = 3.5

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS.64 += --libexecdir=/usr/lib/ibus/$(MACH64)

CONFIGURE_ENV += PYTHON="$(PYTHON)"
CONFIGURE_ENV += am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV += am_cv_python_pyexecdir="$(PYTHON_VENDOR_PACKAGES)"

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/input-method/library/libanthy
REQUIRED_PACKAGES += system/library
