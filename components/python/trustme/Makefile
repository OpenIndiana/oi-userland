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
#   $WS_TOOLS/python-integrate-project trustme
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		trustme
HUMAN_VERSION =			1.1.0
COMPONENT_SUMMARY =		trustme - #1 quality TLS certs while you wait, for the discerning tester
COMPONENT_PROJECT_URL =		https://github.com/python-trio/trustme
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/60/65/1e0fa6e1d336e4e50e41999699903ee216ac500c40ebb2578742d8f1c656/trustme-1.1.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:5375ad7fb427074bec956592e0d4ee2a4cf4da68934e1ba4bcf4217126bc45e6
COMPONENT_LICENSE =		Apache-2.0 OR MIT

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:cov
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cryptography
PYTHON_REQUIRED_PACKAGES += library/python/idna
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
