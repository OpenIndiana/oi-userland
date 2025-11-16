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
#   $WS_TOOLS/python-integrate-project cached-property
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		cached-property
HUMAN_VERSION =			2.0.1
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		A decorator for caching properties in classes.
COMPONENT_PROJECT_URL =		https://github.com/pydanny/cached-property
COMPONENT_ARCHIVE_URL =		\
	https://github.com/pydanny/cached-property/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:2680524870b43cdcd729edf49b3042612b8a4d2fa089d9f2e9ce32d8d0d5d3ba
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Random thread number
COMPONENT_TEST_TRANSFORMS += "-e 's/\(Exception in thread \)Thread-[0-9]\{1,\}$$/\1\$$(THREAD)/'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/freezegun
TEST_REQUIRED_PACKAGES.python += library/python/pytest
