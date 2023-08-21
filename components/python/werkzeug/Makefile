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
#   $WS_TOOLS/python-integrate-project werkzeug
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		werkzeug
HUMAN_VERSION =			2.3.7
COMPONENT_SUMMARY =		werkzeug - The comprehensive WSGI web application library.
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/ef/56/0acc9f560053478a4987fa35c95d904f04b6915f6b5c4d1c14dc8862ba0a/werkzeug-2.3.7.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:2b8c0e447b4b9dbcc85dd97b6eeb4dcbaf6c8b6c3be0bd654e25553e0a2157d8
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE.rst

include $(WS_MAKE_RULES)/common.mk

# dev server does not work
PYTEST_ADDOPTS += -m 'not dev_server'

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += library/python/markupsafe
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/cffi
TEST_REQUIRED_PACKAGES.python += library/python/cryptography
TEST_REQUIRED_PACKAGES.python += library/python/ephemeral-port-reserve
TEST_REQUIRED_PACKAGES.python += library/python/iniconfig
TEST_REQUIRED_PACKAGES.python += library/python/packaging
TEST_REQUIRED_PACKAGES.python += library/python/pluggy
TEST_REQUIRED_PACKAGES.python += library/python/psutil
TEST_REQUIRED_PACKAGES.python += library/python/py
TEST_REQUIRED_PACKAGES.python += library/python/pycparser
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xprocess
TEST_REQUIRED_PACKAGES.python += library/python/watchdog
