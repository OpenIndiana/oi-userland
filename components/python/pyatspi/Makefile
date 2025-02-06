#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017 Alexander Pyhalov
# Copyright 2021 Andreas Wacknitz
#

SINGLE_PYTHON_VERSION = no
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pyatspi
HUMAN_VERSION=		2.46.1
COMPONENT_SUMMARY=	Python wrapper around libatspi
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Accessibility
COMPONENT_ARCHIVE_HASH=	sha256:f91f6a57434e9c07d13d5c4bf819dd78e8ee605aac2ae45d8c64c28114fb041b
COMPONENT_FMRI=	library/python/pyatspi2
COMPONENT_CLASSIFICATION=	Applications/Universal Access
COMPONENT_LICENSE=	LGPL-2.0-only
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --with-python=$(PYTHON)
CONFIGURE_OPTIONS += --enable-tests

# Ensure Python modules are installed into vendor package directories:
CONFIGURE_ENV+=		am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV+=		am_cv_python_pyexecdir="$(PYTHON_VENDOR_PACKAGES)"

# Testing needs an X server
TEST_REQUIRED_PACKAGES += x11/server/xvfb
COMPONENT_PRE_TEST_ACTION += /usr/bin/Xvfb :0 >/dev/null 2>&1 &
COMPONENT_TEST_ENV += DISPLAY=:0
COMPONENT_POST_TEST_ACTION += /usr/bin/pkill -x Xvfb ;

# Manually added build dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python

# Auto-generated dependencies
