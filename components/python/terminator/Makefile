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
# This file was automatically generated using the following command:
#   $WS_TOOLS/python-integrate-project terminator
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		terminator
HUMAN_VERSION =			2.1.3
COMPONENT_SUMMARY =		Multiple GNOME terminals in one window
COMPONENT_PROJECT_URL =		https://gnome-terminator.org/
COMPONENT_ARCHIVE_URL =		\
	https://github.com/gnome-terminator/terminator/releases/download/v$(HUMAN_VERSION)/terminator-$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:0ae9943f3d6b72230c14bcb355de84dd81274c033e76ca4698e80d7c93cd6ae5
COMPONENT_LICENSE =		GPL-2.0-only
COMPONENT_LICENSE_FILE =	COPYING

TEST_STYLE = setup.py

COMPONENT_FMRI =	terminal/terminator

# This is a standalone application.  Since no other Python project depends on
# it we just provide single unversioned package.
SINGLE_PYTHON_VERSION = yes

include $(WS_MAKE_RULES)/common.mk

# Make sure compiled binaries are installed at proper location
PYTHON_DATA = $(USRDIR)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/configobj
PYTHON_REQUIRED_PACKAGES += library/python/dbus-python
PYTHON_REQUIRED_PACKAGES += library/python/psutil
PYTHON_REQUIRED_PACKAGES += library/python/pycairo
PYTHON_REQUIRED_PACKAGES += library/python/pygobject
PYTHON_REQUIRED_PACKAGES += runtime/python
