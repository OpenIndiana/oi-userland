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
#   $WS_TOOLS/python-integrate-project PyQt5
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		PyQt5
HUMAN_VERSION =			5.15.11
COMPONENT_SUMMARY =		Python bindings for the Qt cross platform application toolkit
COMPONENT_ARCHIVE_HASH =	\
	sha256:fda45743ebb4a27b4b1a51c6d8ef455c4c1b5d610c90d2934c7802b5c1557c52
COMPONENT_LICENSE =		GPL-3.0-only
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# We need to accept license
COMPONENT_BUILD_ARGS += --config-setting=--confirm-license
# Use parallel build
COMPONENT_BUILD_ARGS += --config-setting=--jobs=$(PARALLEL_JOBS)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pyqt-builder
PYTHON_REQUIRED_PACKAGES += library/python/pyqt5-sip
PYTHON_REQUIRED_PACKAGES += library/python/sip
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
