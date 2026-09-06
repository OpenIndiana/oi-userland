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
#   $WS_TOOLS/python-integrate-project -d python/jaraco.compat-39 jaraco_compat
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		jaraco_compat
HUMAN_VERSION =			4.3.1
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Modules providing forward compatibility across Python versions
COMPONENT_ARCHIVE_HASH =	\
	sha256:8be915cbf8f696edf75377796e552e0c4e765226dde48ae15d9fb648161c39c8
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# jaraco.compat >= 4.4.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
