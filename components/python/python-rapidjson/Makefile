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
#   $WS_TOOLS/python-integrate-project python-rapidjson
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		python-rapidjson
HUMAN_VERSION =			1.13
COMPONENT_SUMMARY =		python-rapidjson - Python wrapper around rapidjson
COMPONENT_PROJECT_URL =		https://github.com/python-rapidjson/python-rapidjson
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/e6/ad/471996e8c15243be240b81af77c29bdc049b916387088bc3ef8cc6560164/python-rapidjson-1.13.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:ffe9d382be84ddcf197c188d2f49baa8b47270cec95a1dcb62496e2af3eb71d4
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytz
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
