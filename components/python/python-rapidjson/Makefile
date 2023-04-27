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
HUMAN_VERSION =			1.10
COMPONENT_SUMMARY =		python-rapidjson - Python wrapper around rapidjson
COMPONENT_PROJECT_URL =		https://github.com/python-rapidjson/python-rapidjson
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/28/86/f941b03934b9dfb4d1b780706f7676fd7926a8316cd694d82fc4e73222f0/python-rapidjson-1.10.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:acfecbf5edb91ec72a20a125de7f56b8c2f6161eff4c65382c8ee6a2484d3540
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# We need to compile some C++ sources
COMPONENT_BUILD_ENV += CXX="$(CXX)"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytz
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
