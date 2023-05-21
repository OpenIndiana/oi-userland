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
HUMAN_VERSION =			3.0.0
COMPONENT_SUMMARY =		rapidfuzz - rapid fuzzy string matching
COMPONENT_PROJECT_URL =		https://github.com/maxbachmann/RapidFuzz
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/70/05/4030a8a7aa42d3e40ba7abf902de8e7e94ddcb61abda23f6a3ec5daf36df/rapidfuzz-3.0.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:4c1d895d16f62e9ac88d303eb918d90a390bd712055c849e01c558b7ae0fa908
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
