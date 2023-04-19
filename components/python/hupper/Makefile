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
#   $WS_TOOLS/python-integrate-project hupper
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		hupper
HUMAN_VERSION =			1.12
COMPONENT_SUMMARY =		hupper - Integrated process monitor for developing and reloading daemons.
COMPONENT_PROJECT_URL =		https://github.com/Pylons/hupper
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/42/3d/70bef845298bb4746b94418efde81bcfe0fad479169c2e9649f95630bfa7/hupper-1.12.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:18b1653d9832c9f8e7d3401986c7e7af2ae6783616be0bc406bfe0b14134a5c6
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/mock
TEST_REQUIRED_PACKAGES.python += library/python/pip
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/watchdog
