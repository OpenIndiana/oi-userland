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
HUMAN_VERSION =			3.14.1
COMPONENT_SUMMARY =		rapid fuzzy string matching
COMPONENT_PROJECT_URL =		https://github.com/rapidfuzz/RapidFuzz
COMPONENT_ARCHIVE_HASH =	\
	sha256:b02850e7f7152bd1edff27e9d584505b84968cacedee7a734ec4050c655a803c
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# We need GNU tools to build this project
PATH = $(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES.python += library/python/scikit-build-core
REQUIRED_PACKAGES.python += runtime/python
