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
HUMAN_VERSION =			1.14
COMPONENT_SUMMARY =		python-rapidjson - Python wrapper around rapidjson
COMPONENT_PROJECT_URL =		https://github.com/python-rapidjson/python-rapidjson
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/ee/2b/fe5d7f5547e06e9e6020739115419c905ac91099089176363dfc0efd567a/python-rapidjson-1.14.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:26806f0a658c34b48d2951d8d3f846ca9deb93a34e664ef436db632a188b6779
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
