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
#   $WS_TOOLS/python-integrate-project -d python/python-rapidjson-39 python_rapidjson
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		python_rapidjson
HUMAN_VERSION =			1.23
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Python wrapper around rapidjson
COMPONENT_PROJECT_URL =		https://github.com/python-rapidjson/python-rapidjson
COMPONENT_ARCHIVE_HASH =	\
	sha256:0f845daeb26be147f5720a8c410308235092bb4fbb81ea408aa77203e26296fb
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# python-rapidjson >= 1.25 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytz
