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
HUMAN_VERSION =			3.1.0
COMPONENT_SUMMARY =		rapidfuzz - rapid fuzzy string matching
COMPONENT_PROJECT_URL =		https://github.com/maxbachmann/RapidFuzz
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/4c/a4/2d161abdb4a50240078568fdab68e45031f07928cfef364e08f535334c77/rapidfuzz-3.1.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:5571e38ef9452cc89203c9f30fabf23b1fc59dcc2063762d0b037ebeb7c40a58
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
