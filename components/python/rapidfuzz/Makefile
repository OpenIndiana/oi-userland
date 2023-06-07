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
#   $WS_TOOLS/python-integrate-project rapidfuzz
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		rapidfuzz
HUMAN_VERSION =			3.1.1
COMPONENT_SUMMARY =		rapidfuzz - rapid fuzzy string matching
COMPONENT_PROJECT_URL =		https://github.com/maxbachmann/RapidFuzz
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/85/b8/30109278e342bd1ce335aacafa8b295dbd34adc1a2b862a191f377cbba05/rapidfuzz-3.1.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:a06a08be3cb7d7df7993dd16e84aaf59bd5a7ff98a9f1b3e893d18b273a71c64
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# We need GNU tools to build this project
PATH = $(PATH.gnu)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/scikit-build
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
