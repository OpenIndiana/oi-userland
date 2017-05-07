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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ibus-anthy
COMPONENT_VERSION= 1.2.7
# version was bumped in g11n/inputmethod
HUMAN_VERSION= 1.2.7
IPS_COMPONENT_VERSION= 1.3.9
COMPONENT_CLASSIFICATION= System/Internationalization
COMPONENT_SUMMARY= iBus Japanese IME - anthy
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:33c42c1612423f84fddd8c38f8b2439b8af5f0b5fc7725ae195a01b8999d85e9
COMPONENT_ARCHIVE_URL= \
  https://github.com/ibus/ibus-anthy/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://github.com/fujiwarat/ibus-anthy/wiki
COMPONENT_FMRI = system/input-method/ibus/anthy
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH = /usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --libexecdir=/usr/lib/ibus

CONFIGURE_ENV += PYTHON="$(PYTHON)"
CONFIGURE_ENV += am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV += am_cv_python_pyexecdir="$(PYTHON_VENDOR_PACKAGES)"

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(TEST_32)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/input-method/library/libanthy
REQUIRED_PACKAGES += system/library
