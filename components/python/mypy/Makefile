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
#   $WS_TOOLS/python-integrate-project mypy
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		mypy
HUMAN_VERSION =			1.5.0
COMPONENT_SUMMARY =		mypy - Optional static typing for Python
COMPONENT_PROJECT_URL =		https://www.mypy-lang.org/
COMPONENT_ARCHIVE_URL =		\
	https://github.com/python/mypy/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:7e1ee15f4f3e5da884d3e7fc7979a2f73ad4a271843a24b4c6b45ade9ec166a0
COMPONENT_LICENSE =		MIT AND PSF-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:cov
# https://github.com/python/mypy/issues/15617
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/mypy-extensions
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += library/python/types-psutil
PYTHON_REQUIRED_PACKAGES += library/python/types-setuptools
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/attrs
TEST_REQUIRED_PACKAGES.python += library/python/black
TEST_REQUIRED_PACKAGES.python += library/python/filelock
TEST_REQUIRED_PACKAGES.python += library/python/lxml
TEST_REQUIRED_PACKAGES.python += library/python/mypy-extensions
TEST_REQUIRED_PACKAGES.python += library/python/pre-commit
TEST_REQUIRED_PACKAGES.python += library/python/psutil
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/tomli
TEST_REQUIRED_PACKAGES.python += library/python/types-psutil
TEST_REQUIRED_PACKAGES.python += library/python/types-setuptools
TEST_REQUIRED_PACKAGES.python += library/python/typing-extensions
