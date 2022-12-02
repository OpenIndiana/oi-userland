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
#   $WS_TOOLS/python-integrate-project tzdata
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		tzdata
COMPONENT_VERSION =		2022.7
COMPONENT_SUMMARY =		tzdata - Provider of IANA time zone data
COMPONENT_PROJECT_URL =		https://github.com/python/tzdata
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/5b/30/b7abfb11be6642d26de1c1840d25e8d90333513350ad0ebc03101d55e13b/tzdata-2022.7.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:fe5f866eddd8b96e9fcba978f8e503c909b19ea7efda11e52e39494bad3a7bfa
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-subtests
