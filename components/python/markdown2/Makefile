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
#   $WS_TOOLS/python-integrate-project markdown2
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		markdown2
HUMAN_VERSION =			2.4.10
COMPONENT_SUMMARY =		markdown2 - A fast and complete Python implementation of Markdown
COMPONENT_PROJECT_URL =		https://github.com/trentm/python-markdown2
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/8e/b3/64c459af88ea8c2eeb020d0edf3e36c62176e988c47e412133c37c5da5e7/markdown2-2.4.10.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:cdba126d90dc3aef6f4070ac342f974d63f415678959329cc7909f96cc235d72
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
