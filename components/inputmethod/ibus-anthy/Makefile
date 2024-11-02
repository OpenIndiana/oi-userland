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

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         ibus-anthy
COMPONENT_VERSION=      1.5.16
COMPONENT_CLASSIFICATION=System/Internationalization
COMPONENT_SUMMARY=      iBus Japanese IME - anthy
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:15522214b58ad884acc9d9b1da13f15db7dcd76c3b18a88509046e5ec613d1ae
COMPONENT_ARCHIVE_URL=  https://github.com/ibus/ibus-anthy/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://github.com/fujiwarat/ibus-anthy/wiki
COMPONENT_FMRI=         system/input-method/ibus/anthy
COMPONENT_LICENSE=      GPL-2.0-only
COMPONENT_LICENSE_FILE= COPYING

# We are lacking pycotap
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# GNU make is expected
PATH= $(PATH.gnu)

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_ENV += PYTHON="$(PYTHON)"

# Testing needs UTF-8 locale
COMPONENT_TEST_ENV += LC_CTYPE=C.UTF-8

# Manually added build dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pip

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/input-method/library/libanthy
REQUIRED_PACKAGES += system/library
