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
#   $WS_TOOLS/python-integrate-project dnspython
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		dnspython
HUMAN_VERSION =			2.4.1
COMPONENT_SUMMARY =		dnspython - DNS toolkit
COMPONENT_PROJECT_URL =		https://www.dnspython.org
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/78/ad/db7b362200e11378d1d286a4452c7050dab47b0e6d99afa51364ad95a9f9/dnspython-2.4.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:c33971c79af5be968bb897e95c2448e11a645ee84d93b265ce0b7aabe5dfdca8
COMPONENT_LICENSE =		ISC
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/poetry-core
PYTHON_REQUIRED_PACKAGES += runtime/python
